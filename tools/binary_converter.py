import os
import array
import struct
import numpy as np


def ndarray_to_binary(data, out, n=-1):
    with open(out, 'wb') as outfile:
        for i, row in enumerate(data):
            if i == n: break
            _write_floats(row.astype(np.float32), outfile)


def csv_to_binary(fname, out, delim=',', n=-1, skip_cols=0):
    import csv

    with open(fname, 'rb') as csvfile:
        datareader = csv.reader(csvfile, delimiter=delim)
        with open(out, 'wb') as outfile:
            for i, row in enumerate(datareader):
                if i == n: break
                floats = [float(x) for x in row[skip_cols:]]
                _write_floats(floats, outfile)


def mat_to_binary(fname, out, dataset, n=-1):
    from tables import open_file # PyTables

    fileh = open_file(fname, "r")
    data = getattr(fileh.root, dataset)

    with open(out, 'wb') as outfile:
        for i, row in enumerate(data.iterrows()):
            if i == n: break
            _write_floats(row, outfile)

    fileh.close()


def rdata_to_binary(fname, out, matrix, n=-1):
    import rpy2.robjects as robjects # RPy2
    import rpy2.robjects.numpy2ri

    robjects.r['load'](fname)
    data = robjects.numpy2ri.ri2py(robjects.r[matrix][0])

    with open(out, 'wb') as outfile:
        for i, row in enumerate(data):
            if i == n: break
            _write_floats(row.astype(np.float32), outfile)


def fvecs_to_binary(fname, out, n=-1):
    sz = os.path.getsize(fname)

    with open(fname, 'rb') as inp:
        dim = struct.unpack('i', inp.read(4))[0]

    with open(fname, 'rb') as inp:
        rows = sz / (dim + 1) / 4
        with open(out, 'wb') as outfile:
            for i in xrange(rows):
                if i == n: break
                tmp = struct.unpack('<i', inp.read(4))[0]
                vec = array.array('f')
                vec.read(inp, dim)
                _write_floats(vec, outfile)


def bvecs_to_binary(fname, out, n=-1):
    sz = os.path.getsize(fname)

    with open(fname, 'rb') as inp:
        dim = struct.unpack('i', inp.read(4))[0]

    with open(fname, 'rb') as inp:
        rows = sz / (dim + 4)
        with open(out, 'wb') as outfile:
            for i in xrange(rows):
                if i == n: break
                tmp = struct.unpack('<B', inp.read(1))[0]
                vec = array.array('B')
                vec.read(inp, dim)
                _write_floats([float(x) for x in vec], outfile)


def stdin_to_binary(out, delimiter=',', n=-1):
    import sys

    with open(out, 'wb') as outfile:
        for i, row in enumerate(sys.stdin):
            if i == n: break
            sample = [float(x) for x in row.strip().split(delimiter)]
            _write_floats(sample, outfile)


def stl_to_binary(fname, out, n=-1):
    data = np.memmap(fname, dtype=np.uint8, shape=(100000, 3 * 96 * 96))
    with open(out, 'wb') as outfile:
        for i, row in enumerate(data):
            if i == n: break
            _write_floats(row[:96 * 96].astype(np.float32), outfile)


def mnist_to_binary(fname, out, n=-1):
    import struct

    with open(fname, 'rb') as train_image:
        _, _, img_row, img_col = struct.unpack('>IIII', train_image.read(16))
        images = np.fromfile(train_image, dtype=np.uint8).reshape(60000, img_row * img_col)
        data = images.astype(np.float32)

    ndarray_to_binary(data, out, n)


def trevi_to_binary(fname, out):
    from scipy.misc import imread

    with open(out, 'wb') as outfile:
        for f in os.listdir(fname):
            if not f.endswith('.bmp'): continue
            img = imread(fname + '/' + f)
            for r in range(16):
                for c in range(16):
                    patch = img[r * 64 : r * 64 + 64, c * 64 : c * 64 + 64]
                    _write_floats(patch.flatten().astype(np.float32), outfile)


def random_to_binary(N, out):
    with open(out, 'wb') as outfile:
        for i in range(N):
            x = np.random.randn(4096)
            _write_floats((x / np.linalg.norm(x)).astype(np.float32), outfile)


def sample_test_set(fname, out1, out2, n, dim):
    import random

    sz = os.path.getsize(fname)
    N = sz / (4 * dim)
    pos = set(random.sample(range(N), n))
    with open(fname, 'rb') as f:
        with open(out1, 'wb') as outfile1:
            with open(out2, 'wb') as outfile2:
                for i in range(N):
                    f.seek(i * 4 * dim)
                    floats = struct.unpack('f' * dim, f.read(dim * 4))
                    if i in pos:
                        _write_floats(floats, outfile2)
                    else:
                        _write_floats(floats, outfile1)


def _write_floats(floats, outfile):
    float_arr = array.array('d', floats)
    s = struct.pack('f' * len(float_arr), *float_arr)
    outfile.write(s)


if __name__ == '__main__':
    import sys

    if sys.argv[1] == '--sample':
        sample_test_set(sys.argv[2], sys.argv[3], sys.argv[4], int(sys.argv[5]), int(sys.argv[6]))
        sys.exit(0)

    inf, outf = sys.argv[1], sys.argv[2]

    if inf.endswith('.fvecs'):
        fvecs_to_binary(inf, outf, -1 if len(sys.argv) == 3 else int(sys.argv[3]))
    elif inf.endswith('.bvecs'):
        bvecs_to_binary(inf, outf, -1 if len(sys.argv) == 3 else int(sys.argv[3]))
    elif inf.endswith('.csv'):
        csv_to_binary(inf, outf)
    elif inf.endswith('.txt'):
        csv_to_binary(inf, outf, ' ')
    elif inf.endswith('.bin'):
        stl_to_binary(inf, outf)
    elif inf.endswith('.mat'):
        mat_to_binary(inf, outf, sys.argv[3])
    elif inf.endswith('.RData'):
        rdata_to_binary(inf, outf, sys.argv[3])
    elif inf.endswith('idx3-ubyte'):
        mnist_to_binary(inf, outf)
    elif inf.endswith('/'):
        trevi_to_binary(inf, outf)
    else:
        random_to_binary(int(inf), outf)

if [ ! -f "parameters/$1.sh" ]; then
    echo Invalid data set 1>&2
    exit
fi

. "parameters/$1.sh"

mkdir -p "results/$DATASET_NAME"
for K in 1 10 100; do
    ./exact/tester "data/$DATASET_NAME/train.bin" "data/$DATASET_NAME/test.bin" $DIM $K > "data/$DATASET_NAME/truth_$K"
done

echo -n > "results/$DATASET_NAME/mrpt.txt"
for n_trees in $MRPT_N_TREES; do
    for depth in $MRPT_DEPTH; do
        ./mrpt/tester "data/$DATASET_NAME" $DIM $n_trees $depth 1 1 >> "results/$DATASET_NAME/mrpt.txt"
    done
done

echo -n > "results/$DATASET_NAME/mrpt-sparse.txt"
for n_trees in $MRPT_N_TREES; do
    for depth in $MRPT_DEPTH; do
        ./mrpt/tester "data/$DATASET_NAME" $DIM $n_trees $depth $MRPT_SPARSITY 1 >> "results/$DATASET_NAME/mrpt-sparse.txt"
    done
done

echo -n > "results/$DATASET_NAME/mrpt-voting.txt"
for n_trees in $MRPT_VOTING_N_TREES; do
    for depth in $MRPT_DEPTH; do
        ./mrpt/tester "data/$DATASET_NAME" $DIM $n_trees $depth $MRPT_SPARSITY $MRPT_VOTES >> "results/$DATASET_NAME/mrpt-voting.txt"
    done
done

echo -n > "results/$DATASET_NAME/flann.txt"
for n_trees in $FLANN_N_TREES; do
    env LD_LIBRARY_PATH=./flann/lib/lib ./flann/tester "data/$DATASET_NAME" $DIM $n_trees $FLANN_CHECKS >> "results/$DATASET_NAME/flann.txt"
done

echo -n > "results/$DATASET_NAME/flann-kmeans.txt"
for branching in $FLANN_BRANCHING; do
    env LD_LIBRARY_PATH=./flann/lib/lib ./flann-kmeans/tester "data/$DATASET_NAME" $DIM $branching $FLANN_ITERATIONS $FLANN_CHECKS >> "results/$DATASET_NAME/flann-kmeans.txt"
done

echo -n > "results/$DATASET_NAME/kgraph.txt"
for lll in $KGRAPH_K; do
    env LD_LIBRARY_PATH=./kgraph/lib ./kgraph/tester "data/$DATASET_NAME" $DIM $lll $KGRAPH_COST >> "results/$DATASET_NAME/kgraph.txt"
done

echo -n > "results/$DATASET_NAME/falconn.txt"
for tables in $FALCONN_TABLES; do
    for hash_bits in $FALCONN_HASH_BITS; do
        ./falconn/tester "data/$DATASET_NAME" $DIM $tables $hash_bits >> "results/$DATASET_NAME/falconn.txt"
    done
done

echo -n > "results/$DATASET_NAME/ann.txt"
./ann/tester "data/$DATASET_NAME" $DIM $ANN_EPS >> "results/$DATASET_NAME/ann.txt"

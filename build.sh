if [ "$1" != "test" ]
then
    echo "Building cache binary"
    gcc -Wall -g3 src/dll.c src/hashmap.c src/lru.c src/main.c -DLOG -o cache
    echo "Finished build cache"
else
    echo "Building test binary"
    gcc -Wall -g3 src/dll.c src/hashmap.c src/lru.c src/test.c -DLOG -o test
    echo "Finished build test"
    ./test
    if [ $? == 0 ]
    then
        echo "Passed all tests"
    else
        echo "Failed some test"
    fi
fi

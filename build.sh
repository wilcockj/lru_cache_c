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
    echo "Calling valgrind to check for memory leaks in tests"
    valgrindoutput=$(valgrind --leak-check=full ./test 2>&1)
    if echo "$valgrindoutput" | grep -q "no leaks are possible"; then
        echo "No memory leaks detected."
        clipped_output=$(echo "$valgrindoutput" | tail -n 8)
        echo "$clipped_output"
    else
        echo "Memory leaks detected!"
        echo "$valgrindoutput"
    fi

fi

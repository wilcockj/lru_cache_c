if [[ $1 != 'test' ]]
then
    echo "Building cache binary"
    gcc -Wall -g3 src/hashmap.c src/lru.c src/main.c -o cache
else
    echo "Building test binary"
    gcc -Wall -g3 src/hashmap.c src/lru.c src/test.c -o test
    ./test
    if [ $? == 0 ]
    then
        echo "Passed all tests"
    else
        echo "Failed some test"
    fi
    rm ./test
fi

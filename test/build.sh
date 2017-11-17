if [ ! -n "$CXX" ]; then
    CXX=g++
fi

$CXX test/test.cpp -Iinclude -Llib -labstractalgorithm
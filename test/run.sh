export LD_LIBRARY_PATH=`pwd`/lib:$LD_LIBRARY_PATH

valgrind --leak-check=full --undef-value-errors=no ./a.out $1
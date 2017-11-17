BASE_DIR=`pwd`

rm build -rf
mkdir build

pushd build

cmake ..

make -j8

INSTALL_DIR=$BASE_DIR/abstractalgorithm_distribute
rm -rf $INSTALL_DIR
make install/strip DESTDIR=$INSTALL_DIR

popd

rm libabstractalgorithm -rf
mkdir libabstractalgorithm

pushd libabstractalgorithm

cp -r ../abstractalgorithm_distribute/include ./
cp -r ../abstractalgorithm_distribute/lib ./

popd
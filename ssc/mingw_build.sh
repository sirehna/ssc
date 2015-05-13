#!/bin/sh
if [ $# -eq 0 ]
then
    buildType=Debug
else
    buildType=$1
fi

mkdir build
./foreach.sh externalDependencies.txt fetch_rebase.sh
cd build
cmake .. -G "MSYS Makefiles" -DCMAKE_COLOR_MAKEFILE=OFF -DCMAKE_BUILD_TYPE=${buildType}
cd ..

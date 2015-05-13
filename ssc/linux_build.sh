#!/bin/sh

if [ $# -eq 0 ]
then
    buildType=Debug
else
    buildType=$1
fi

mkdir build
./foreach.sh externalDependencies.txt svn_export.sh $1 $2
cd build
cmake .. -DCMAKE_BUILD_TYPE=${buildType}
cd ..

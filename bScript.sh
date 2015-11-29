#!/bin/bash

wget "https://github.com/bulletphysics/bullet3/archive/2.83.6.zip"
unzip 2.83.6.zip
cd bullet3-2.83.6/build3
./premake4_linux64 gmake
cd gmake
make
cd ../../..

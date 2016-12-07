#!/bin/bash
# Libs Installation Script

########## libWann - https://github.com/firmino/libwann ##########

# Cloning from github and generating build
git clone https://github.com/firmino/libwann.git
cd libwann
make all
cd ../

########## PreProcessing - https://github.com/HeavenVolkoff/PreProcessing.git ########## 

# Cloning from github and generating build
git clone --recursive https://github.com/FogoDev/PreProcessing.git
cd PreProcessing
cmake ./
make
cd ../

# Moving to respectives directories
rm -Rf include
rm -Rf libs
mkdir include
mkdir libs
mv libwann/include/*.hpp ./include/
mv libwann/build/libwann.so ./libs/
mv PreProcessing/libPreProcessing.so ./libs
mv PreProcessing/include/PreProcessing.h ./include

# Build application
make all

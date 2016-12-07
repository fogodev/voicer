#!/bin/bash


# PreProcessing Rebuild Script
cp ./include/PreProcessing.h ./PreProcessing/include/
cd PreProcessing
cmake ./
make
cd ..

# Moving dynamic library
mv PreProcessing/libPreProcessing.so ./libs


# Rebuilding voicer
make all

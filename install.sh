#!/bin/bash
# Libs Installation Script

########## libWann - https://github.com/firmino/libwann ##########

# Cloning from github and generating build
git clone https://github.com/firmino/libwann
cd libwann
make all
cd ../

# Moving to respectives directories
rm -Rf include
rm -Rf libs
mkdir include
mkdir libs
mv libwann/include/*.hpp ./include/
mv libwann/build/libwann.so ./libs/

# Cleaning libwann from directory
rm -Rf libwann 

# Build application
make all

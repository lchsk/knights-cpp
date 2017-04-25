#!/bin/sh

rm -f Makefile
rm -f CMakeCache.txt
rm -f cmake_install.cmake
rm -f cmake_uninstall.cmake
rm -f install_manifest.txt
rm -f nohup.out
rm -rf CMakeFiles
rm -rf ./bin
rm -rf _CPack_Packages
rm -f CPackSourceConfig.cmake CPackConfig.cmake

cd tests; \
rm -f Makefile; \
rm -f CMakeCache.txt; \
rm -rf CMakeFiles; \
rm -rf cmake_install.cmake; \

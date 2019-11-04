if [ -f "Makefile" ]; then
    make clean
    rm Makefile
fi

if [ -f "cmake_install.cmake" ]; then
    rm cmake_install.cmake
fi

if [ -f "CMakeCache.txt" ]; then
    rm CMakeCache.txt
fi

rm -rf CMakeFiles
rm -rf build

mkdir build

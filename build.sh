cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_CXX_COMPILER=g++-10 -D param=linux-release -B build -S .
cd build
make -j8
cd ..

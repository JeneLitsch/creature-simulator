cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_CXX_COMPILER=clang++ -D param=linux-release -B build -S .
cd build
make -j8
cd ..

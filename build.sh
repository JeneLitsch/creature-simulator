cmake . -D CMAKE_CXX_COMPILER=clang++-14 -D param=linux-release -B build -S .
cd build
make 
cd ..

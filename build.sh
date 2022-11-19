cmake .\
	-B build -S .\
	-DCMAKE_CXX_COMPILER=clang++\
	-Dparam=linux-release\
	-DCMAKE_EXPORT_COMPILE_COMMANDS=1
cd build
make 
cd ..

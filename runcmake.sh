rm ./bin/NCraftExe
cmake . -B build
cmake --build build
cd bin
./NCraftExe

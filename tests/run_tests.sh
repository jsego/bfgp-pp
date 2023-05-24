cmake -S . -B build
cmake --build build -j8
cd build && ctest -V

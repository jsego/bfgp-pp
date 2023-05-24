cmake -DCMAKE_INSTALL_PREFIX=/usr/local -S . -B build
cmake --build build -j8
sudo cmake --install build


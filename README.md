# Practice 11: Package manager vcpkg

cmake -B build -S . -G Ninja -DCMAKE_TOOLCHAIN_FILE="~/vcpkg/scripts/buildsystems/vcpkg.cmake" -Wno-dev

cmake --build build

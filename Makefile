install:
	cmake -S . -B build -DCMAKE_INSTALL_PREFIX=${HOME}/.local -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build -j$(nproc)
	cmake --install build

clean:
	rm -rf build
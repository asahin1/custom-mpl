.PHONY: install examples tests clean

install:
	cmake -S . -B build -DCMAKE_INSTALL_PREFIX=${HOME}/.local -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build -j$(nproc)
	cmake --install build

examples:
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCUSTOM_MPL_BUILD_EXAMPLES=ON 
	cmake --build build -j$(nproc)

tests:
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCUSTOM_MPL_BUILD_TESTS=ON 
	cmake --build build -j$(nproc)
	ctest --test-dir build

clean:
	rm -rf build
install:
	cmake -S . -B build -DCMAKE_PREFIX_PATH="$HOME/.local/search"
	cmake --build build
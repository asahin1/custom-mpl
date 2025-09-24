# custom-mpl

Header-first C++ implementations of motion planning algorithms, with pluggable datastructures and problem definitions.

- `include/search`: public headers (templates & .tpp)
- `src/search`: non-templated .cpp (timers), explicit instantiations (optional)
- `src/apps`: demos
- `tests`: unit tests (Catch2)

Build:

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build
```

# custom-mpl

Header-first C++ implementations of motion planning algorithms, with pluggable datastructures and problem definitions.

- `include/custom-mpl`: public headers (templates & .tpp)
- `examples`: examples
- `tests`: unit tests (Catch2)

**To install:**

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=${HOME}/.local -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j$(nproc)
cmake --install build
```

---

**To test:**

```bash
ctest --test-dir build
```

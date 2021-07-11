# Matrix

This is an abstract library implementing an effective class of matrices of arbitrary objects with basic linear algebra operations and random generator.

## Building
```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

## TODO
1. Linear system solving (? LDU decomposition/Gauss with partial pivoting)
  1. ? Matrix rank
  2. ? Matrix norm(s)
2. Add second tier linear algebra operations support
3. Add paralleling to algebra logic (Gaussian alg etc.)
4. ? use BLAS/LAPACK/uBLAS for standard types
5. ? use autotools in addition to CMake

## Done
1. Matrix on arbitrary objects
2. Basic linear algebra logic
3. Determinant calculation (Gaussian algorithm and Minors method)
4. Move/Copy constructor/operator=
5. Random matrix generator with custom algorithm support
6. Autotests (97% line coverage)
7. Multithreading to basic operators

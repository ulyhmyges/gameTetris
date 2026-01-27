# Work in progress

Configure and Build

debug mode:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

release mode:

```sh
cmake -S . -B build
cmake --build build
```

Run

The executable should be in the `build` directory:

```sh
cd build
./bin/hello
```
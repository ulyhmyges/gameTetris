# Configure and Build

```sh
cmake -S . -B build
cmake --build build
```

# Run

The executable should be in the `build` directory:

```sh
cd build
./hello
```

If there wasn't an executable there despite the above Build section running successfully, it's likely because you're following this guide using the Visual Studio toolchain, it should instead be in the `build/Debug` directory:

```sh
cd build/Debug
./hello
```
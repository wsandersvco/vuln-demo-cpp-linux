# ARM64 C++ Sample Project

A simple Linux ARM64 sample project demonstrating various computations and ARM NEON intrinsics, built with GCC 13.

## Features

- Factorial computation
- ARM NEON SIMD dot product operations
- Matrix multiplication
- Mathematical functions (sin, cos, sqrt, log)
- Utility functions (distance, average, Fibonacci, prime checking)

## Requirements

- GCC 13 (gcc-13)
- Linux ARM64 target architecture
- Make build system

## Building

To build the project:

```bash
make
```

### Building on macOS for Veracode Scanning

On macOS, the native GCC 13 may not produce correct ARM64 Linux output for Veracode Static Analysis. Use Docker to build in a proper ARM64 Linux environment:

```bash
make docker-build
```

This will:
- Run the build inside an `arm64v8/gcc:13.2.0` Docker container
- Generate correct ARM64 Linux preprocessed files (.ii)
- Produce output suitable for Veracode Static Scan

### Build Output

The build process will:
- Compile all C++ source files using `gcc-13`
- Generate preprocessed files (.ii) in the build directory
- Generate assembly files (.s)
- Create the executable `arm64_sample`

## Running

After building, run the executable:

```bash
./build/arm64_sample
```

## Cleaning

To clean all build artifacts:

```bash
make clean
```

## Project Structure

- `main.cpp` - Main program with various computational demonstrations
- `utils.cpp/utils.h` - Utility functions for common operations
- `Makefile` - Build configuration

## Build Details

The project uses the following compiler flags:
- `-march=armv8-a` - Target ARM64 architecture
- `-save-temps=obj` - Generate preprocessed (.ii) and assembly (.s) files
- `-std=c++17` - Use C++17 standard
- `-O2` - Optimization level 2

## Libraries Used

- Standard C++ Library (iostream, vector, cmath, numeric)
- ARM NEON intrinsics (arm_neon.h)
- Math library (libm)

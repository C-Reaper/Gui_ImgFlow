## Overview

The project appears to be a C/C++ application for image processing and rendering. The main functionality involves creating a simple flow-based image transformation tool, which can be built and executed on various platforms (Linux, Windows, Wine, and WebAssembly). The application uses direct rendering methods, likely leveraging hardware acceleration features such as AVX2.

## Features

- **Image Processing**: Basic image processing capabilities are implemented, allowing for the creation of a flow-based image transformation tool.
- **Platform Support**:
  - Linux
  - Windows (native and through Wine)
  - WebAssembly

## Project Structure

The project is structured into several directories and files:

- `build/`: Contains build artifacts like executable files.
- `src/`: Source code directory containing `Main.c` as the entry point and other `.h` header files used by `Main.c`.
- `Makefile.linux`, `Makefile.windows`, `Makefile.wine`, `Makefile.web`: Build configurations for different platforms.

### Prerequisites

- **C/C++ Compiler and Debugger**: GCC, Clang
- **Make utility**
- **Standard Development Tools**
- **Libraries**:
  - For Linux: X11, PNG, JPEG
  - For Windows: WINAPI (via Wine)
  - WebAssembly: Emscripten

## Build & Run

### Build Process

To build the project for a specific platform, use the appropriate Makefile:

```sh
cd <Project>
make -f Makefile.(os) all
```

For example, to build for Linux:

```sh
make -f Makefile.linux all
```

For clean rebuild:

```sh
make -f Makefile.linux clean
make -f Makefile.linux all
```

### Execution

To execute the built application:

```sh
make -f Makefile.(os) exe
```

For example, to run the Linux build:

```sh
make -f Makefile.linux exe
```

The `Makefile.web` can be used to compile and serve the WebAssembly version of the application.
[![main CI](https://github.com/rturrado/rtc/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/rtc/actions/workflows/main_ci.yml)
[![unixlike-builds CI](https://github.com/rturrado/rtc/actions/workflows/unixlike-builds_ci.yml/badge.svg)](https://github.com/rturrado/rtc/actions/workflows/unixlike-builds_ci.yml)

# rtc

Some utilities I use in different C++ projects (for example, in [the_modern_cpp_challenge](https://github.com/rturrado/the_modern_cpp_challenge)).

rtc is implemented as a header-only library.

## Use from a CMake project

The easiest way to use the rtc library from a CMake project is via `FetchContent`.

The example below tells CMake to download a given GitHub tag, but you could fetch the head of the repository instead.

```CMake
include(FetchContent)
FetchContent_Declare(rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "ef1952b961eb0a28940c319b76df5e65e9ae790b"
)
FetchContent_MakeAvailable(rtc)

target_link_libraries(${PROJECT_NAME} rtc)
```

## Installation

### Requirements
- cmake 3.14.
- git.

### Clone
```bash
git clone https://github.com/rturrado/rtc.git
```

### Install
The following code snippet assumes that you are within the cloned directory.

Notice the library will be installed under `${CMAKE_INSTALL_PREFIX}`.<br/>
You can change the installation `<folder>` using the option `-DCMAKE_INSTALL_PREFIX=<folder>`.

```bash
cmake --preset windows-msvc-release
cmake --build --preset windows-msvc-release --install
```

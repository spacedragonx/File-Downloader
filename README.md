# Multi-threaded File Downloader
<img width="957" alt="image" src="">


## 📌 Overview
Multi-threaded File Downloader is a modern C++ project built with **C++17** and **CMake**.  
It demonstrates usage of popular libraries like **libcurl**, **CLI11**, and **indicators**, while following clean coding practices and modular design.  

---

## ⚡ Features
- Command-line interface using **CLI11**
- Progress indicators with **indicators**
- HTTP requests powered by **cpr (libcurl wrapper)**
- CMake-based build system for easy cross-platform compilation

---

## 🛠️ Requirements
Make sure the following are installed before building:

- C++17 compatible compiler (MSVC, GCC, or Clang)
- [CMake 3.14+](https://cmake.org/download/)
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)

---

## 🚀 Build Instructions

```bash
# Clone the repository
git clone https://github.com/spacedragonx/File-Downloader
cd File-Downloader

# Install dependencies via vcpkg (example)
vcpkg install cpr cli11 indicators

# Configure build
cmake -B build -S .

# Build project
cmake --build build

## Acknowledgments

- [CPR](https://github.com/libcpr/cpr) for HTTP requests
- [CLI11](https://github.com/CLIUtils/CLI11) for command-line parsing
- [indicators](https://github.com/p-ranav/indicators) for progress bars

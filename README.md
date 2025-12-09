<div align="center">

# FILE-DOWNLOADER

_Accelerate Your Downloads, Unleash Seamless Efficiency_

<br>

[![Last Commit](https://img.shields.io/badge/last%20commit-september-blue?style=for-the-badge&labelColor=555555)](https://github.com/spacedragonx/File-Downloader/commits)
[![C++](https://img.shields.io/badge/c++-85.2%25-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white&labelColor=555555)](https://github.com/spacedragonx/File-Downloader)
[![Languages](https://img.shields.io/badge/languages-2-blue?style=for-the-badge&labelColor=555555)](https://github.com/spacedragonx/File-Downloader)

<br>

<p>Built with the tools and technologies:</p>

[![JSON](https://img.shields.io/badge/JSON-black?style=for-the-badge&logo=json&logoColor=white)](https://www.json.org/)
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)

</div>

<img width="957" alt="terminal image" src="https://github.com/spacedragonx/File-Downloader/blob/master/Images/TerminalOutput.png?raw=true">

---
## Table of Contents

* [Overview](#overview)
* [Installation](#installation)
* [Features](#Features)
* [Requirements](#Requirements)

---

##  Overview
File-Downloader is a high-performance, multi-threaded utility designed to accelerate large file downloads over HTTP. It seamlessly manages concurrent requests, supports HTTP range requests, and provides real-time progress updates, ensuring fast and reliable data acquisition.
  

---

##  Features
- Command-line interface using **CLI11**
- Progress indicators with **indicators**
- HTTP requests powered by **cpr (libcurl wrapper)**
- CMake-based build system for easy cross-platform compilation

---

### Why File-Downloader?

This project aims to simplify and speed up large file downloads for developers. The core features include:

* 🛠️ **Multi-threaded Download:** Parallelizes file retrieval for maximum speed.
* 🌐 **HTTP Range Support:** Efficiently downloads large files in chunks.
* 📊 **Progress Indicators:** Visual feedback during lengthy downloads.
* 🔧 **Command-line Interface:** User-friendly control over download parameters.
* 🚀 **Cross-platform Build:** Easy setup with CMake for diverse environments.

---

##  Requirements
Make sure the following are installed before building:

- C++17 compatible compiler (MSVC, GCC, or Clang)
- [CMake 3.14+](https://cmake.org/download/)
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)

---

##  installation

## Clone the repository
```bash
git clone https://github.com/spacedragonx/File-Downloader
cd File-Downloader
```
## Install dependencies via vcpkg (example)
```bash
vcpkg install cpr cli11 indicators
```
## Configure build
```bash
cmake -B build -S .
```
## Build project
```bash
cmake --build build
```
## Acknowledgments

- [CPR](https://github.com/libcpr/cpr) for HTTP requests
- [CLI11](https://github.com/CLIUtils/CLI11) for command-line parsing
- [indicators](https://github.com/p-ranav/indicators) for progress bars

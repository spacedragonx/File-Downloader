<div align="center">

<img width="300" height='300' alt="logo" src="https://github.com/spacedragonx/File-Downloader/blob/master/Images/MTFDlogo.png?raw=true">

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
* [Features](#Features)
* [Requirements](#Requirements)
* [Installation](#Installation)
* [Usage](#Usage)

---

##  Overview
File-Downloader is a high-performance, multi-threaded utility designed to accelerate large file downloads over HTTP. It seamlessly manages concurrent requests, supports HTTP range requests, and provides real-time progress updates, ensuring fast and reliable data acquisition.
  

---

##  Features

| Feature | Description |
| :--- | :--- |
| **Multi-Threaded Acceleration** | Splits files into segments and downloads them simultaneously using `std::thread`. |
| **Real-Time Progress** | Visual progress bar with speed metrics and ETA. |
| **Memory Efficient** | Optimized buffer management to handle large files with low RAM footprint. |
| **Cross-Platform** | Built using standard C++ libraries and CMake for easy portability. |

---

## How It Works (Technical Architecture)

This tool is built to showcase **Systems Programming** capabilities by implementing a multi-threaded download engine. The process follows this architectural flow:

1.  **Head Request**
    : The client first sends an HTTP `HEAD` request to the server to fetch the `Content-Length` header. This allows the program to determine the file size without downloading the actual content.

2.  **Segmentation**
    : The total file size is logically divided by the user-defined number of threads.
    * *Example:* 100MB file ÷ 4 threads = **25MB per chunk**.

3.  **Range Requests**
    : Each thread initiates a separate socket connection and sends an HTTP `GET` request with a specific `Range: bytes=start-end` header. This instructs the server to send only that specific segment of data.

4.  **Concurrency**
    : The application utilizes C++17 `std::thread` to run downloads in parallel. Shared resources are managed using `std::mutex` (if necessary for logging) or atomic operations to prevent race conditions during execution.

5.  **File Assembly**
    : Instead of merging files at the end, data is written directly to the correct position on the disk in real-time. The tool uses `fseek` (or file pointers) to seek the specific offset for every chunk, ensuring the final file is reconstructed continuously and correctly.
---

##  Requirements
Make sure the following are installed before building:

- C++17 compatible compiler (MSVC, GCC, or Clang)
- [CMake 3.14+](https://cmake.org/download/)
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)

---

##  Installation

### Clone the repository
```bash
git clone https://github.com/spacedragonx/File-Downloader
cd File-Downloader
```
### Install dependencies via vcpkg (example)
```bash
vcpkg install cpr cli11 indicators
```
### Configure build
```bash
cmake -B build -S .
```
### Build project
```bash
cmake --build build
```
---

## Usage

### Basic Usage:
```bash
./File-Downloader <URL>
```

### Advanced Usage (Specify Threads):
```bash
./File-Downloader <URL> <OUTPUT_FILENAME> <THREAD_COUNT>
```

### Example:
```bash
./File-Downloader [https://proof.ovh.net/files/100Mb.dat](https://proof.ovh.net/files/100Mb.dat) my_file.dat 8
```
---

## Acknowledgments

- [CPR](https://github.com/libcpr/cpr) for HTTP requests
- [CLI11](https://github.com/CLIUtils/CLI11) for command-line parsing
- [indicators](https://github.com/p-ranav/indicators) for progress bars

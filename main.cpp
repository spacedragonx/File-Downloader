#include "MTFD.h"
#include <iostream>
#include <string>
#include <optional>

int main() {
    Downloader dl;
    std::string url;
    std::string filename;
    int threads = 4;

    std::cout << "Enter URL to download: ";
    std::getline(std::cin, url);

    if (!dl.test_connection(url)) {
        std::cerr << "Cannot connect to the URL." << std::endl;
        return 1;
    }

    std::cout << "Enter output filename (press Enter to use default): ";
    std::getline(std::cin, filename);

    std::cout << "Enter number of threads (default 4): ";
    std::string thread_input;
    std::getline(std::cin, thread_input);
    if (!thread_input.empty()) {
        threads = std::stoi(thread_input);
    }

    std::optional<std::string> out_file;
    if (!filename.empty()) out_file = filename;

    dl.download_file(url, out_file, threads);

    std::cout << "Download finished!" << std::endl;
    return 0;
}

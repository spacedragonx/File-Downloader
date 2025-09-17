// MTFD.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <string>
#include <optional>

class Downloader {
public:
    // Download a file with optional output filename and number of threads
    void download_file(const std::string& url, const std::optional<std::string>& output_file = std::nullopt, int num_threads = 4);

    // Test connection to a URL
    bool test_connection(const std::string& url);

private:
    void download_chunk(const std::string& url, size_t start, size_t end, const std::string& chunk_file, int chunk_id);
    void merge_chunks(const std::string& output_file, int num_chunks);
    std::string get_filename_from_url(const std::string& url);
    std::string format_size(size_t size);
};

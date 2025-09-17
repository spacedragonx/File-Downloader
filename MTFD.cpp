#include "MTFD.h"
#include <cpr/cpr.h>
#include <indicators/progress_bar.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <cmath>
#include <sstream>

std::mutex console_mutex;
std::atomic<size_t> total_progress(0);

std::string Downloader::get_filename_from_url(const std::string& url) {
    size_t pos = url.find_last_of("/");
    if (pos != std::string::npos) return url.substr(pos + 1);
    return "downloaded_file";
}

std::string Downloader::format_size(size_t size) {
    double size_mb = static_cast<double>(size) / (1024 * 1024);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << size_mb;
    return ss.str();
}

bool Downloader::test_connection(const std::string& url) {
    try {
        cpr::Response r = cpr::Head(cpr::Url{ url });

        if (r.error) {
            std::cerr << "❌ Connection error: " << r.error.message << std::endl;
            if (r.error.code == cpr::ErrorCode::SSL_CONNECT_ERROR) {
                std::cerr << "   → SSL not enabled in CPR build. Reinstall CPR with: "
                    << "vcpkg install cpr[ssl]:x64-windows" << std::endl;
            }
            return false;
        }

        if (r.status_code >= 200 && r.status_code < 300) {
            std::cout << "✅ Connected successfully. Status code: " << r.status_code << std::endl;
            return true;
        }
        else {
            std::cerr << "❌ Server returned HTTP " << r.status_code << std::endl;
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return false;
    }
}
void Downloader::download_file(const std::string& url, const std::optional<std::string>& output_file, int num_threads) {
    cpr::Response r = cpr::Head(cpr::Url{ url });
    if (r.status_code != 200) {
        std::cerr << "Failed to get file information. Status code: " << r.status_code << std::endl;
        return;
    }

    size_t file_size = std::stoull(r.header["Content-Length"]);
    size_t chunk_size = std::ceil(static_cast<double>(file_size) / num_threads);
    std::string filename = output_file.value_or(get_filename_from_url(url));

    indicators::ProgressBar progress_bar{
        indicators::option::BarWidth{50},
        indicators::option::Start{"["},
        indicators::option::Fill{"="},
        indicators::option::Lead{">"},
        indicators::option::Remainder{" "},
        indicators::option::End{"]"},
        indicators::option::ForegroundColor{indicators::Color::green},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true},
        indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
    };

    std::vector<std::thread> threads;
    total_progress = 0;

    for (int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? file_size - 1 : (i + 1) * chunk_size - 1;
        std::string chunk_file = filename + ".part" + std::to_string(i);
        threads.emplace_back(&Downloader::download_chunk, this, url, start, end, chunk_file, i);
    }

    // Update progress bar
    while (total_progress < file_size) {
        size_t current = total_progress.load();
        progress_bar.set_progress(100.0 * current / file_size);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto& t : threads) t.join();

    progress_bar.set_progress(100);
    std::cout << "\nDownload complete. Merging chunks..." << std::endl;

    merge_chunks(filename, num_threads);

    std::cout << "File saved as: " << filename << std::endl;
}

void Downloader::download_chunk(const std::string& url, size_t start, size_t end, const std::string& chunk_file, int chunk_id) {
    cpr::Response r = cpr::Get(
        cpr::Url{ url },
        cpr::Header{ {"Range", "bytes=" + std::to_string(start) + "-" + std::to_string(end)} }
    );

    if (r.status_code == 206 || r.status_code == 200) {
        std::ofstream out(chunk_file, std::ios::binary);
        out.write(r.text.c_str(), r.text.size()); // For text
        // For binary files, use: out.write(reinterpret_cast<const char*>(r.binary.data()), r.binary.size());
        out.close();
        total_progress += (end - start + 1);
    }
    else {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cerr << "Failed to download chunk " << chunk_id << ". Status code: " << r.status_code << std::endl;
    }
}

void Downloader::merge_chunks(const std::string& output_file, int num_chunks) {
    std::ofstream out(output_file, std::ios::binary);
    for (int i = 0; i < num_chunks; ++i) {
        std::string chunk_file = output_file + ".part" + std::to_string(i);
        std::ifstream in(chunk_file, std::ios::binary);
        out << in.rdbuf();
        in.close();
        std::remove(chunk_file.c_str());
    }
    out.close();
}


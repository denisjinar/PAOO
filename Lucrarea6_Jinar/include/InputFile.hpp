#pragma once

#include <cstdio>
#include <memory>
#include <string>

class InputFile {
public:
    explicit InputFile(const char* path);

    // Item 14: fișierul are un singur proprietar.
    InputFile(const InputFile&) = delete;
    InputFile& operator=(const InputFile&) = delete;
    InputFile(InputFile&&) noexcept = default;
    InputFile& operator=(InputFile&&) noexcept = default;

    bool is_open() const noexcept;
    std::string read_all();

private:
    struct CloseFile {
        void operator()(std::FILE* file) const noexcept;
    };

    std::unique_ptr<std::FILE, CloseFile> file_;
};
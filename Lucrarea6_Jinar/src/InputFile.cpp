#include "InputFile.hpp"

#include <cstddef>
#include <stdexcept>

void InputFile::CloseFile::operator()(std::FILE* file) const noexcept {
    std::fclose(file);
}

InputFile::InputFile(const char* path)
    : file_(std::fopen(path, "rb")) {
    if (!file_) {
        throw std::runtime_error(
            std::string("Nu s-a putut deschide fisierul: ") + path);
    }
}

bool InputFile::is_open() const noexcept {
    return static_cast<bool>(file_);
}

std::string InputFile::read_all() {
    if (!file_) {
        throw std::logic_error("Obiectul nu detine un fisier.");
    }

    auto* file = file_.get();
    if (std::fseek(file, 0, SEEK_SET) != 0) {
        throw std::runtime_error("Pozitionarea la inceputul fisierului a esuat.");
    }

    std::string result;
    char chunk[256];
    std::size_t count;

    while ((count = std::fread(chunk, 1, sizeof chunk, file)) != 0) {
        result.append(chunk, count);
    }

    if (std::ferror(file)) {
        throw std::runtime_error("Citirea fisierului a esuat.");
    }

    return result;
}
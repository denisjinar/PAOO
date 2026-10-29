#include "Playlist.h"
#include <iostream>
#include <stdexcept>

namespace {
char* copiaza(const char* s) {
    std::size_t n = 0;
    while (s[n] != '\0') ++n;
    char* r = new char[n + 1];
    for (std::size_t i = 0; i <= n; ++i) r[i] = s[i];
    return r;
}
}
Playlist::Playlist(const char* nume, std::size_t capacitate)
    : nume_(copiaza(nume)), melodii_(new std::string[capacitate]),
      nr_(0), cap_(capacitate) {
    std::cout << "[Playlist] constructor: \"" << nume_ << "\"\n";
}
Playlist::Playlist(const Playlist& other)
    : nume_(copiaza(other.nume_)), melodii_(new std::string[other.cap_]),
      nr_(other.nr_), cap_(other.cap_) {
    for (std::size_t i = 0; i < nr_; ++i) melodii_[i] = other.melodii_[i];
    std::cout << "[Playlist] copy constructor: \"" << nume_ << "\" (copie profunda)\n";
}
Playlist::Playlist(Playlist&& other) noexcept
    : nume_(other.nume_), melodii_(other.melodii_), nr_(other.nr_), cap_(other.cap_) {
    other.nume_ = nullptr;
    other.melodii_ = nullptr;
    other.nr_ = 0;
    other.cap_ = 0;
    std::cout << "[Playlist] move constructor: \"" << nume_ << "\" (resurse preluate)\n";
}
Playlist::~Playlist() {
    std::cout << "[Playlist] destructor: \"" << (nume_ ? nume_ : "(goala)")
              << "\" -> delete[] nume si melodii\n";
    delete[] nume_;
    delete[] melodii_;
}

void Playlist::adauga(const std::string& melodie) {
    if (nr_ == cap_) {
        std::size_t nouCap = cap_ == 0 ? 4 : cap_ * 2;
        std::string* nou = new std::string[nouCap];
        for (std::size_t i = 0; i < nr_; ++i) nou[i] = melodii_[i];
        delete[] melodii_;
        melodii_ = nou;
        cap_ = nouCap;
    }
    melodii_[nr_++] = melodie;
}

void Playlist::redenumeste(const char* nume) {
    char* nou = copiaza(nume);
    delete[] nume_;
    nume_ = nou;
}

const char* Playlist::nume() const { return nume_ ? nume_ : "(goala)"; }

const std::string& Playlist::melodie(std::size_t i) const {
    if (i >= nr_) throw std::out_of_range("index invalid");
    return melodii_[i];
}
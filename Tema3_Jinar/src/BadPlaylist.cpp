#include "BadPlaylist.h"
#include <iostream>

BadPlaylist::BadPlaylist(const char* nume) : nume_(new char[32]()), capacitate_(32) {
    redenumeste(nume);
    std::cout << "[BadPlaylist] constructor: \"" << nume_ << "\" la "
              << static_cast<const void*>(nume_) << "\n";
}

BadPlaylist::~BadPlaylist() {
    std::cout << "[BadPlaylist] destructor: delete[] "
              << static_cast<const void*>(nume_) << "\n";
    delete[] nume_;
}

void BadPlaylist::redenumeste(const char* nume) {
    std::size_t i = 0;
    for (; nume[i] != '\0' && i + 1 < capacitate_; ++i) nume_[i] = nume[i];
    nume_[i] = '\0';
}
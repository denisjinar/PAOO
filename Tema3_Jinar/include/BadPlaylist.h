#pragma once
#include <cstddef>

class BadPlaylist {
private:
    char*       nume_;
    std::size_t capacitate_;

public:
    explicit BadPlaylist(const char* nume);
    ~BadPlaylist();

    void        redenumeste(const char* nume);
    const char* nume() const { return nume_; }
};
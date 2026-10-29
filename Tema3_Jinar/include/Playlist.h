#pragma once
#include <cstddef>
#include <string>

class Playlist {
private:
    char*        nume_;
    std::string* melodii_;
    std::size_t  nr_;
    std::size_t  cap_;

public:
    explicit Playlist(const char* nume, std::size_t capacitate = 4);
    Playlist(const Playlist& other);
    Playlist(Playlist&& other) noexcept;
    ~Playlist();

    Playlist& operator=(const Playlist&) = delete;
    Playlist& operator=(Playlist&&) = delete;

    void adauga(const std::string& melodie);
    void redenumeste(const char* nume);

    const char*        nume() const;
    std::size_t        numarMelodii() const { return nr_; }
    const std::string& melodie(std::size_t i) const;
    const void*        adresaMelodii() const { return melodii_; }
};
#include "Document.hpp"

#include <utility>

Document::Document(std::string title)
    : title_(std::move(title)) {}

const std::string& Document::title() const {
    return title_;
}

void Document::swap(Document& other) noexcept {
    title_.swap(other.title_);
}
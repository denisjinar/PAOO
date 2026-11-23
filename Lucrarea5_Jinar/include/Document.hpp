#pragma once

#include <string>

class Document {
public:
    explicit Document(std::string title);
    const std::string& title() const;

protected:
    void swap(Document& other) noexcept;

private:
    std::string title_;
};
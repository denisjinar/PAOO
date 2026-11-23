#pragma once

#include "Document.hpp"

#include <cstddef>
#include <string>
#include <vector>

class Report final : public Document {
public:
    Report(std::string title, int revision, std::vector<int> scores);
    Report(const Report& other);
    Report& operator=(const Report& other);

    int revision() const;
    const std::vector<int>& scores() const;
    void set_score(std::size_t index, int score);

private:
    void swap(Report& other) noexcept;

    int revision_;
    std::vector<int> scores_;
};
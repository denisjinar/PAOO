#include "Report.hpp"

#include <utility>

Report::Report(std::string title, int revision, std::vector<int> scores)
    : Document(std::move(title)),
      revision_(revision),
      scores_(std::move(scores)) {}

Report::Report(const Report& other)
    : Document(other),
      revision_(other.revision_),
      scores_(other.scores_) {}

Report& Report::operator=(const Report& other) {
    if (this != &other) {
        Report copy(other);
        swap(copy);
    }

    return *this;
}

int Report::revision() const {
    return revision_;
}

const std::vector<int>& Report::scores() const {
    return scores_;
}

void Report::set_score(std::size_t index, int score) {
    scores_.at(index) = score;
}

void Report::swap(Report& other) noexcept {
    Document::swap(other);
    std::swap(revision_, other.revision_);
    scores_.swap(other.scores_);
}
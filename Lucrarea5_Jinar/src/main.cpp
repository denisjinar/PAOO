#include "Report.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

static_assert(std::is_same_v<
    decltype(std::declval<Report&>() = std::declval<const Report&>()),
    Report&>);

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool same_state(const Report& first, const Report& second) {
    return first.title() == second.title()
        && first.revision() == second.revision()
        && first.scores() == second.scores();
}

void test_assignment_chain() {
    Report a("A", 1, {1});
    Report b("B", 2, {2});
    const Report c("C", 3, {8, 9});

    Report& result = (a = b = c);
    require(&result == &a, "Item 10: rezultatul trebuie sa fie o referinta la a");
    require(same_state(a, c) && same_state(b, c),
            "Item 10: atribuirea in lant a esuat");

    result.set_score(0, 42);
    require(a.scores().at(0) == 42,
            "Item 10: referinta trebuie sa permita modificarea lui a");
}

void test_self_assignment() {
    Report report("Raport", 4, {10, 20});
    const Report expected("Raport", 4, {10, 20});

    require(&(report = report) == &report,
            "Item 11: autoatribuirea directa trebuie sa intoarca destinatia");
    require(same_state(report, expected),
            "Item 11: autoatribuirea directa a schimbat starea");

    const Report& alias = report;
    require(&(report = alias) == &report,
            "Item 11: autoatribuirea prin alias trebuie sa intoarca destinatia");
    require(same_state(report, expected),
            "Item 11: autoatribuirea prin alias a schimbat starea");
}

void test_complete_copy() {
    const Report source("Rezultate", 7, {11, 22});
    Report constructed(source);
    Report assigned("Anterior", 1, {99});

    assigned = source;

    require(same_state(constructed, source),
            "Item 12: constructorul nu a copiat intreaga stare");
    require(same_state(assigned, source),
            "Item 12: operatorul de atribuire nu a copiat intreaga stare");

    constructed.set_score(0, 55);
    assigned.set_score(1, 66);

    require(source.scores() == std::vector<int>{11, 22},
            "Item 12: modificarea copiilor a afectat sursa");
    require(constructed.scores() == std::vector<int>{55, 22},
            "Item 12: copiile nu sunt independente");
    require(assigned.scores() == std::vector<int>{11, 66},
            "Item 12: copiile nu sunt independente");
}

}

int main() {
    try {
        test_assignment_chain();
        std::cout << "Item 10 - Atribuire in lant: OK\n";

        test_self_assignment();
        std::cout << "Item 11 - Autoatribuire directa si prin alias: OK\n";

        test_complete_copy();
        std::cout << "Item 12 - Copiere completa si independenta: OK\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
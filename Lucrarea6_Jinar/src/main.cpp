#include "InputFile.hpp"
#include "ShoppingCart.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

static_assert(!std::is_copy_constructible_v<InputFile>);
static_assert(!std::is_copy_assignable_v<InputFile>);
static_assert(std::is_nothrow_move_constructible_v<InputFile>);
static_assert(std::is_nothrow_move_assignable_v<InputFile>);

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void test_file() {
    InputFile file("CMakeLists.txt");
    require(file.read_all().find("project(EffectiveCpp13To14") != std::string::npos,
            "Continutul fisierului este incorect.");
}

struct Interrupted {};

void test_cleanup_on_exception() {
    std::weak_ptr<ShoppingCart> observer;

    try {
        auto cart = std::make_shared<ShoppingCart>();
        observer = cart;
        require(!observer.expired(), "Cosul trebuie sa existe in blocul try.");

        throw Interrupted{};
    } catch (const Interrupted&) {
        require(observer.expired(), "Cosul trebuie distrus la iesirea prin exceptie.");
    }
}

void test_unique_ownership() {
    InputFile original("CMakeLists.txt");
    const std::string expected = original.read_all();

    InputFile moved(std::move(original));
    require(!original.is_open(), "Sursa trebuie sa fie goala dupa mutare.");

    InputFile destination("src/main.cpp");
    destination = std::move(moved);
    require(!moved.is_open(), "Sursa trebuie sa fie goala dupa atribuirea prin mutare.");
    require(destination.read_all() == expected, "Fisierul nu a fost transferat corect.");
}

void test_cart_copy() {
    ShoppingCart cart;
    cart.add("Cafea");
    cart.add("Ceai");

    ShoppingCart preview(cart);
    ShoppingCart saved;
    saved.add("Lapte");
    saved = cart;

    require(preview.quantity("Cafea") == 1 && preview.quantity("Ceai") == 1,
            "Simularea trebuie sa inceapa cu toate produsele din cos.");
    require(saved.quantity("Cafea") == 1 && saved.quantity("Ceai") == 1
                && saved.quantity("Lapte") == 0,
            "Atribuirea trebuie sa preia intregul cos.");

    preview.add("Cafea");
    saved.add("Ceai");

    require(cart.quantity("Cafea") == 1 && cart.quantity("Ceai") == 1,
            "Modificarea unei copii a afectat cosul original.");
    require(preview.quantity("Cafea") == 2 && preview.quantity("Ceai") == 1
                && saved.quantity("Cafea") == 1 && saved.quantity("Ceai") == 2,
            "Copiile cosului trebuie sa fie independente.");
}

void test_shared_cart() {
    auto product_page = std::make_shared<ShoppingCart>();
    std::weak_ptr<ShoppingCart> observer = product_page;
    auto checkout_page = product_page;

    product_page->add("Cafea");
    require(checkout_page->quantity("Cafea") == 1,
            "Pagina de finalizare trebuie sa vada produsul adaugat.");

    product_page.reset();
    require(!observer.expired() && checkout_page->quantity("Cafea") == 1,
            "Cosul trebuie sa ramana disponibil pe pagina de finalizare.");

    checkout_page.reset();
    require(observer.expired(), "Ultimul proprietar trebuie sa elibereze cosul.");
}

}

int main() {
    try {
        test_file();
        test_cleanup_on_exception();
        std::cout << "Item 13 - RAII si eliberare la exceptie: OK\n";

        test_unique_ownership();
        std::cout << "Item 14 - Proprietate exclusiva si mutare: OK\n";

        test_cart_copy();
        std::cout << "Item 14 - Copie independenta a cosului: OK\n";

        test_shared_cart();
        std::cout << "Item 14 - Acelasi cos pe doua pagini: OK\n";
    } catch (const std::exception& error) {
        std::cerr << "Verificare esuata: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
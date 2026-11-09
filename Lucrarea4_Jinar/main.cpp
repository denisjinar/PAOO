
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Carte {
private:
    const int id;
    string titlu;
    string autor;
    int anPublicare;

public:

    Carte(int idCarte, string titluCarte,
          string autorCarte, int an)
        : id(idCarte),
          titlu(std::move(titluCarte)),
          autor(std::move(autorCarte)),
          anPublicare(an) {
    }

    void afiseaza() const {
        cout << "[" << id << "] " << titlu
             << "-" << autor
             << " (" << anPublicare << ")\n";
    }
};

class FisaImprumut {
private:
    int numar = 0;
    string cititor = "Necunoscut";

public:
    FisaImprumut() = default;

    FisaImprumut(int n, string nume)
        : numar(n), cititor(std::move(nume)) {
    }



    void afiseaza() const {
        cout << "Fisa " << numar
             << ": " << cititor << '\n';
    }
};

class Biblioteca {
private:
    vector<Carte> carti;

public:
    void adauga(const Carte& carte) {
        carti.push_back(carte);
    }

    void afiseaza() const {
        for (const auto& carte : carti) {
            carte.afiseaza();
        }
    }
};

class BibliotecaUnica {
private:
    string nume;

    explicit BibliotecaUnica(string n)
        : nume(std::move(n)) {
    }

public:
    BibliotecaUnica(const BibliotecaUnica&) = delete;

    BibliotecaUnica& operator=(
        const BibliotecaUnica&) = delete;

    BibliotecaUnica(BibliotecaUnica&&) = delete;

    BibliotecaUnica& operator=(
        BibliotecaUnica&&) = delete;

    static BibliotecaUnica& instanta() {
        static BibliotecaUnica b("Biblioteca centrala");
        return b;
    }

    void afiseaza() const {
        cout << "Manager: " << nume << '\n';
    }
};

int main() {

    cout << "ITEM 4: Initializare obiecte\n";

    int numarCarti = 0;

    cout << "Numar initial de carti: "
         << numarCarti << '\n';

    Carte carte1(1, "Ion", "Liviu Rebreanu", 1920);
    carte1.afiseaza();

    cout << "\nITEM 5: Functii generate implicit\n";

    FisaImprumut fisa1;
    FisaImprumut fisa2(10, "Maria");

    FisaImprumut fisa3 = fisa2;

    fisa1 = fisa3;

    fisa1.afiseaza();
    fisa2.afiseaza();
    fisa3.afiseaza();

    Biblioteca b1;
    b1.adauga(carte1);

    Biblioteca b2 = b1;

    b2.adauga(Carte(2, "Morometii",
                   "Marin Preda", 1955));

    cout << "Biblioteca initiala:\n";
    b1.afiseaza();

    cout << "Biblioteca copiata si modificata:\n";
    b2.afiseaza();

    cout << "\nITEM 6:Interzicere copiere\n";

    BibliotecaUnica& manager =
        BibliotecaUnica::instanta();

    manager.afiseaza();

    return 0;
}

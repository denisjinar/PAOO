#include <iostream>
#include <utility>
#include <vector>
#include "Playlist.h"
#include "BadPlaylist.h"

static Playlist creeazaPlaylist() {
    Playlist p("Pentru drum");
    p.adauga("Melodia 1");
    p.adauga("Melodia 2");
    return p;
}

int main() {
    {
        Playlist p("Rock");
        p.adauga("Song A");
        p.adauga("Song B");
        std::cout << p.nume() << " are " << p.numarMelodii() << " melodii\n";
    }

    std::cout << "\nFara copy constructor:\n";
    {
        BadPlaylist* a = new BadPlaylist("Favorite");
        BadPlaylist* copie = new BadPlaylist(*a);
        std::cout << "a.nume()      = " << static_cast<const void*>(a->nume()) << "\n"
                  << "copie.nume()  = " << static_cast<const void*>(copie->nume())
                  << "  <- acelasi pointer\n";
        copie->redenumeste("Redenumit");
        std::cout << "Dupa copie->redenumeste(\"Redenumit\"): a->nume() = \""
                  << a->nume() << "\"  <- originalul s-a schimbat\n";
        delete a;
#ifdef DEMO_DOUBLE_FREE
        delete copie;
#else
        std::cout << "copie nu e distrusa ca sa nu apara double free "
                     "(ruleaza cu -DDEMO_DOUBLE_FREE=ON pentru crash)\n";
#endif
    }

    std::cout << "\nCu copy constructor:\n";
    {
        Playlist a("Favorite");
        a.adauga("Song 1");
        Playlist copie(a);
        copie.redenumeste("Redenumit");
        copie.adauga("Song 2");
        std::cout << "a: \"" << a.nume() << "\" cu " << a.numarMelodii() << " melodie\n"
                  << "copie: \"" << copie.nume() << "\" cu " << copie.numarMelodii()
                  << " melodii\n";
    }

    std::cout << "\nMove constructor:\n";
    {
        Playlist sursa("Chill");
        sursa.adauga("Song X");
        Playlist mutat(std::move(sursa));
        std::cout << "mutat: \"" << mutat.nume() << "\" cu " << mutat.numarMelodii()
                  << " melodie; sursa: \"" << sursa.nume() << "\" cu "
                  << sursa.numarMelodii() << " melodii\n";

        std::cout << "\nReturn dintr-o functie:\n";
        Playlist r = creeazaPlaylist();
        std::cout << "r: \"" << r.nume() << "\" cu " << r.numarMelodii() << " melodii\n";

        std::cout << "\nRealocarea unui vector:\n";
        std::vector<Playlist> v;
        v.push_back(Playlist("P1"));
        v.push_back(Playlist("P2"));
    }

    std::cout << "\nSfarsit program.\n";
    return 0;
}
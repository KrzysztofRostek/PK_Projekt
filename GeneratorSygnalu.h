#pragma once
#include "qmath.h"
#include <cmath>
#include <cstdint>

class GeneratorSygnalu
{
public:
    enum Tryb { SINUS, PROSTOKAT };

private:
    Tryb tryb;
    double A;   // amplituda
    double S;   // składowa stała
    double p;   // wypełnienie (0.0 - 1.0)
    double TRZ; // okres rzeczywisty [s]
    int TT;     // taktowanie symulacji [ms]
    double czasAkumulowany; // Akumulowany czas w sekundach
    int ostatniKrok;       // Ostatni krok dla śledzenia zmiany interwału

public:
    GeneratorSygnalu()
        : tryb(SINUS)
        , A(1.0)
        , S(0.0)
        , p(0.5)
        , TRZ(1.0)
        , TT(100)
        , czasAkumulowany(0.0)
        , ostatniKrok(-1)
    {}

    void ustawTryb(Tryb t) { tryb = t; }
    void ustawA(double a) { A = a; }
    void ustawS(double s) { S = s; }
    void ustawP(double pp) {
        // Ogranicz wypełnienie do zakresu 0.0 - 1.0
        p = qBound(0.0, pp, 1.0);
    }
    void ustawTRZ(double trz) { TRZ = trz; }
    void ustawTT(int tt) { TT = tt; }

    Tryb getTryb() const { return tryb; }
    int getTT() const { return TT; }

    // Generuj wartość na podstawie czasu (nie indeksu próbki)
    double generuj(int i)
    {
        // Oblicz czas dla tego kroku
        double deltaCzas = TT / 1000.0; // Konwersja ms na s

        if (ostatniKrok == -1 || i <= ostatniKrok) {
            // Reset lub pierwsze wywołanie
            czasAkumulowany = 0;
        } else {
            // Normalny postęp - dodaj interwał czasu
            czasAkumulowany += deltaCzas;
        }

        ostatniKrok = i;

        switch (tryb) {
        case SINUS: {
            if (TRZ <= 0) return S;
            double czestotliwosc = 1.0 / TRZ;
            return A * sin(2.0 * M_PI * czestotliwosc * czasAkumulowany) + S;
        }
        case PROSTOKAT: {
            if (TRZ <= 0) return S;
            double okres = TRZ;
            double pozycjaWOkresie = fmod(czasAkumulowany, okres);
            double czasWlaczenia = okres * p;

            // Dla prostokąta: 0 do A (lub S do A+S)
            if (pozycjaWOkresie < czasWlaczenia) {
                return A + S; // stan wysoki: A + S
            } else {
                return S; // stan niski: tylko S (0 + S)
            }
        }
        default: {
            return S;
        }
        }
    }

    // Reset generatora
    void reset() {
        czasAkumulowany = 0.0;
        ostatniKrok = -1;
    }
};

#pragma once

#include "GeneratorSygnalu.h"
#include "ModelARX.h"
#include "RegulatorPID.h"

class ProstyUAR
{
private:
    ModelARX &obiekt;  //referemcka dp ARX
    RegulatorPID &pid; //referencja do PID

    double wartwyjsc_poprzedni; //poprzednie wyjście y(k-1)

public:
    ProstyUAR(ModelARX &arx, RegulatorPID &pid) // Konstruktor
        : obiekt(arx)
        , pid(pid)
        , wartwyjsc_poprzedni(0.0)
    {}

    void reset() //reset
    {
        wartwyjsc_poprzedni = 0.0;
        pid.reset();
        obiekt.reset();
    }

    void krok(double &generator,
              double &uchyb,
              double &PID,
              double &WartWyjsc,
              GeneratorSygnalu &gen,
              int k)
    {
        // wartość zadana
        generator = gen.generuj(k);

        // uchyb
        uchyb = generator - wartwyjsc_poprzedni;

        // regulator
        PID = pid.symuluj(uchyb);

        // obiekt ARX
        WartWyjsc = obiekt.symuluj(PID);

        // aktualizacja pamięci
        wartwyjsc_poprzedni = WartWyjsc;
    }
    double symuluj(double wartosczadana)
    {
        double uchyb
            = wartosczadana
              - wartwyjsc_poprzedni; //obliczamy różnice między zawrtością zadaną a poprzednim wyjściem obiektu

        double PID = pid.symuluj(uchyb); //podajemy uchyb na regulatora PID

        double WartWyjsc = obiekt.symuluj(PID); //podajemy sygnał sterujący do ModeluARX

        wartwyjsc_poprzedni = WartWyjsc; //zapisujemy wyjście do obliczeń uchybu

        return WartWyjsc; //zwracamy wartość
    }
};


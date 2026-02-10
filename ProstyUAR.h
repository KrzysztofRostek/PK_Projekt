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
        // 1. wartość zadana
        generator = gen.generuj(k);

        // 2. uchyb
        uchyb = generator - wartwyjsc_poprzedni;

        // 3. regulator
        PID = pid.symuluj(uchyb);
     /*   const double MAX_STEROWANIE = 100.0;
        if (PID > MAX_STEROWANIE) {
            PID = MAX_STEROWANIE;
        }
        if (PID < -MAX_STEROWANIE) {
            PID = -MAX_STEROWANIE;
        }
*/
        // 4. obiekt ARX
        WartWyjsc = obiekt.symuluj(PID);

        // 5. aktualizacja pamięci
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

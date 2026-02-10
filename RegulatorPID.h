#pragma once
#include <cmath>

class RegulatorPID
{
public:
    enum LiczCalk { PROSTOKATNY, TRAPEZOWY, Wew, Zew, ZERO }; //Sposób obliczania całki

private:
    double Kp; //wzmocnienie
    double Ti; //stała całkowania
    double Td; //stała różniczkowania
    double T;  //okres próbkowania

    double uchyb_poprzedni; //poprzedni uchyb u(k-1)
    double akum_wew;        //akumulator całki prostokątny trapezowy wew
    double akum_zew;        //akumulator całki zew

    LiczCalk typCalki;
    static constexpr double EPS = 1e-12; //stała do porównań z zerem

public:
    double P; // Składnik proporcjonalny
    double I; // Składnik całkujący
    double D; // Składnik różniczkujący

    RegulatorPID(double Kp_ = 1.0, double Ti_ = 0.0, double Td_ = 0.0, double T_ = 1.0)
        : Kp(Kp_)
        , Ti(Ti_)
        , Td(Td_)
        , T(T_)
        , uchyb_poprzedni(0.0)
        , akum_wew(0.0)
        , akum_zew(0.0)
        , typCalki(PROSTOKATNY)
        , P(0.0)
        , I(0.0)
        , D(0.0)
    {}

    void reset() //resetowanie uchybu,? i ?
    {
        uchyb_poprzedni = 0.0;
        akum_wew = 0.0;
        akum_zew = 0.0;
    }

    void setKp(double kp)
    { //seter wzmocnienia
        Kp = kp;
    }
    void setTd(double td)
    { //seter stałej różniczkowania
        Td = td;
    }
    void setT(double t)
    { //seter okresu próbkowania
        T = t;
    }
    void setStalaCalk(double ti)
    { //seter stałej całkowania
        Ti = ti;
    }

    void setLiczCalk(LiczCalk metoda) //zmiana sposobu liczenia całki
    {
        if (typCalki
            != metoda) { //sprawdzamy czy sposób liczenia na jaki chcemy zmienić jest inny od akutalnego
            if (typCalki == Zew && metoda != Zew) { //tylko dla całki zew
                double ZapiszTi;
                if (Ti
                    > EPS) { //jeśli Ti jest bardzo małe pobieramy wartość 1 aby uniknąć dzielenia przez 0
                    ZapiszTi = Ti;
                } else {
                    ZapiszTi = 1.0;
                };
                akum_wew = akum_zew / ZapiszTi;
            } else if (typCalki != Zew && metoda == Zew) { //zmiana z wew na zew
                double ZapiszTi;
                if (Ti
                    > EPS) { //jeśli Ti jest bardzo małe pobieramy wartość 1 aby uniknąć mnożenia przez 0
                    ZapiszTi = Ti;
                } else {
                    ZapiszTi = 1.0;
                };
                akum_zew = akum_wew * ZapiszTi;
            }
        }
        typCalki = metoda; //ustawiamy nowy aktualny typ liczenia całki
    }

    LiczCalk getLiczCalk() const { return typCalki; }

    double symuluj(double uchyb)
    {
        // --- P ---
        P = Kp * uchyb; // ZAPISZ do P!

        // --- I ---
        I = 0.0;
        bool czy_calka = (typCalki != ZERO) && (Ti > EPS);

        if (czy_calka) {
            switch (typCalki) {
            case PROSTOKATNY:
            case Wew:
                akum_wew += (T / Ti) * uchyb;
                I = akum_wew;
                break;

            case TRAPEZOWY:
                akum_wew += (T / (2.0 * Ti)) * (uchyb + uchyb_poprzedni);
                I = akum_wew;
                break;

            case Zew:
                akum_zew += T * uchyb;
                I = akum_zew / Ti;
                break;

            default:
                I = 0.0;
                break;
            }
        }

        // --- D ---
        D = 0.0; // Resetuj D
        if (Td > EPS) {
            D = Td * (uchyb - uchyb_poprzedni) / T;
        }

        double PID = P + I + D;
        uchyb_poprzedni = uchyb;

        return PID;
    }
};

#pragma once
#include <cmath>

class RegulatorPID
{
public:
    enum LiczCalk { PROSTOKATNY, TRAPEZOWY, Wew, Zew, ZERO };

private:
    double Kp;
    double Ti;
    double Td;
    double T;
    double uchyb_poprzedni;
    double akum_wew;
    double akum_zew;
    LiczCalk typCalki;
    static constexpr double EPS = 1e-12;

public:
    double P;
    double I;
    double D;

    RegulatorPID(double Kp_ = 1.0, double Ti_ = 0.0, double Td_ = 0.0, double T_ = 1.0)
        : Kp(Kp_), Ti(Ti_), Td(Td_), T(T_),
        uchyb_poprzedni(0.0), akum_wew(0.0), akum_zew(0.0),
        typCalki(PROSTOKATNY), P(0.0), I(0.0), D(0.0)
    {}

    void reset() {
        uchyb_poprzedni = 0.0;
        akum_wew = 0.0;
        akum_zew = 0.0;
        I = 0.0;
        P = 0.0;
        D = 0.0;
    }

    void setKp(double kp) { Kp = kp; }
    void setTd(double td) { Td = td; }
    void setT(double t) { T = t; }

    void setStalaCalk(double ti)
    {
        // Zeruj całkę przy zmianie Ti na 0
        if (ti <= EPS && Ti > EPS) {
            akum_wew = 0.0;
            akum_zew = 0.0;
            I = 0.0;
        }
        Ti = ti;
    }

    void setLiczCalk(LiczCalk metoda) {
        if (typCalki != metoda) {
            if (Ti > EPS) {  // TYLKO jeśli Ti > 0
                if (typCalki == Zew && metoda != Zew) {
                    akum_wew = akum_zew / Ti;
                } else if (typCalki != Zew && metoda == Zew) {
                    akum_zew = akum_wew * Ti;
                }
            } else {
                // Gdy Ti = 0, po prostu zeruj akumulatory
                akum_wew = 0.0;
                akum_zew = 0.0;
            }
        }
        typCalki = metoda;
    }

    LiczCalk getLiczCalk() const { return typCalki; }

    double symuluj(double uchyb)
    {
        // --- P ---
        P = Kp * uchyb;

        // --- I ---
        bool czy_calka = (Ti > EPS);

        if (czy_calka) {
            switch (typCalki) {
            case Wew:
                akum_wew += uchyb / Ti;
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
        } else {
            // Gdy Ti = 0, całka jest ZAWSZE 0
            I = 0.0;
        }

        // --- D ---
        D = Td * (uchyb - uchyb_poprzedni) / T;

        double PID = P + I + D;
        uchyb_poprzedni = uchyb;

        return PID;
    }
};

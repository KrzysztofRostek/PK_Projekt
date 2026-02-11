#pragma once
using namespace std;
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
class ModelARX
{
private:
    double A[10];         //zależność od poprzednich wartości wyjścia
    double B[10];         //zależność od wcześniejszych wartości sterowania
    int IleA;             //liczba wartości wyjścia
    int IleB;             //liczba wartości sterujących
    int opoznienie;       //jakie opóźnienie między sygnałem u a reakcją y
    double odchylenie;    //amplituda możliwego szumu
    double HistWyjsc[20]; //tablica histori wyjść y[k-1]
    double HistSter[30];    //tablica histori watości sterujących u[k-1]
    double umin;
    double umax;
    double ymin;
    double ymax;
    bool ograniczenia;
    double saturacja(double wartosc, double min_val, double max_val)
    {
        if (wartosc > max_val) return max_val;
        if (wartosc < min_val) return min_val;
        return wartosc;
    }
public:
    ModelARX(const vector<double> &a, //wektor współczynników A
             const vector<double> &b, //weksto współczynników B
             int opoznienie = 1,
             double odchylenie = 0.0)
        : opoznienie(opoznienie)
        , odchylenie(odchylenie) //inicializacja pól
    {
        IleA = a.size(); //zapisanie długości wektora a i b
        IleB = b.size();
        for (int i = 0; i < IleA; ++i) {
            A[i] = a[i]; //kopiowanie wspczynników wekoru a do tablicy A
        }
        for (int i = 0; i < IleB; ++i) {
            B[i] = b[i]; //kopiowanie wspczynników wekoru b do tablicy B
        }
        srand(time(0));
        reset();
    }
    void ustawParametry(const vector<double> &a_wektor,
                        const vector<double> &b_wektor,
                        int nowe_opoznienie,
                        double nowe_odchylenie)
    {
        opoznienie = nowe_opoznienie;
        odchylenie = nowe_odchylenie;

        if (a_wektor.size() < 10) {
            IleA = a_wektor.size();
        } else {
            IleA = 10;
        }

        if (b_wektor.size() < 10) {
            IleB = b_wektor.size();
        } else {
            IleB = 10;
        }

        for (int i = 0; i < IleA; ++i) {
            A[i] = a_wektor[i];
        }

        for (int i = 0; i < IleB; ++i) {
            B[i] = b_wektor[i];
        }
    }
    void setOgraniczenia(bool Ograniczenia){ograniczenia = Ograniczenia;}
    void setUmin(double Umin) { umin = Umin; }
    void setUmax(double Umax) { umax = Umax; }
    void setYmin(double Ymin) { ymin = Ymin; }
    void setYmax(double Ymax) { ymax = Ymax; }
    void reset() //resetowanie histori wyjść i histori wartości sterujących
    {
        for (int i = 0; i < IleA; ++i) {
            HistWyjsc[i] = 0.0;
        }
        for (int i = 0; i < IleB + opoznienie + 1; ++i) {
            HistSter[i] = 0.0;
        }
    }
    double losowySzum() //generowanie losowego szumu w zakresie [-odchylenie, odchylenie]
    {
        if (odchylenie == 0.0)
            return 0.0;
        double r = (double) rand() / RAND_MAX; // [0,1]
        r = 2.0 * r - 1.0;                     // [-1,1]
        return r * odchylenie;
    }
    double symuluj(double WartSter)
    {
        if(ograniczenia){
        WartSter = saturacja(WartSter, ymin, ymax);
        }
        // przesunięcie historii sterowania
        for (int i = 29; i > 0; --i) {
            HistSter[i] = HistSter[i-1];
        }
        HistSter[0] = WartSter;

        // obliczenie wyjścia
        double WartWyjsc = 0.0;

        for (int i = 0; i < IleB; ++i) {
            int OpozSter= i + opoznienie;
            if (OpozSter < 30)
                WartWyjsc += B[i] * HistSter[OpozSter];
        }

        for (int i = 0; i < IleA; ++i) {
            WartWyjsc -= A[i] * HistWyjsc[i];
        }

        WartWyjsc += losowySzum();
        if(ograniczenia){
        WartWyjsc = saturacja(WartWyjsc, ymin, ymax);
        }
        // przesunięcie historii wyjść
        for (int i = IleA-1; i > 0; --i) {
            HistWyjsc[i] = HistWyjsc[i-1];
        }
        HistWyjsc[0] = WartWyjsc;

        return WartWyjsc;
    }
};

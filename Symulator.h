#pragma once

#include <QObject>
#include <QTimer>
#include "GeneratorSygnalu.h"
#include "ModelARX.h"
#include "ProstyUAR.h"
#include "RegulatorPID.h"
#include <vector>

class SymulatorUAR : public QObject
{
    Q_OBJECT

private:
    // WARSTWA DANYCH
    GeneratorSygnalu generator;
    RegulatorPID pid;
    ModelARX arx;
    ProstyUAR uar;

    // STAN SYMULACJI
    int k;
    double w, e, u, y;

    // ZEGAR
    bool symuluj;
    int interwalMs;
    QTimer timer;

public:
    // KONSTRUKTOR - INLINE
    SymulatorUAR(const GeneratorSygnalu &gen,
                 const RegulatorPID &pid_,
                 const ModelARX &arx_,
                 QObject *parent = nullptr)
        : QObject(parent)
        , generator(gen)
        , pid(pid_)
        , arx(arx_)
        , uar(arx, pid)
        , k(0)
        , w(0.0)
        , e(0.0)
        , u(0.0)
        , y(0.0)
        , symuluj(false)
        , interwalMs(200)
    {
        timer.setInterval(interwalMs);
        connect(&timer, &QTimer::timeout, this, &SymulatorUAR::Tick);
    }

    // STEROWANIE SYMULACJĄ
    void start()
    {
        symuluj = true;
        if (!timer.isActive())
            timer.start();
    }

    void stop()
    {
        symuluj = false;
        timer.stop();
    }

    void reset()
    {
        stop();
        k = 0;
        w = e = u = y = 0.0;
        uar.reset();
    }


    // Generator
    void setGeneratorTryb(GeneratorSygnalu::Tryb t) { generator.ustawTryb(t); }
    void setGeneratorA(double a) { generator.ustawA(a); }
    void setGeneratorS(double s) { generator.ustawS(s); }
    void setGeneratorP(double p) { generator.ustawP(p); }
    void setGeneratorTRZ(double trz) { generator.ustawTRZ(trz); }
    void setGeneratorTT(int tt) { generator.ustawTT(tt); }

    void setGeneratorCzestotliwosc(double f)
    {
        if (f > 0)
            setGeneratorTRZ(1.0 / f);
    }

    // Regulator PID
    void setPID_Kp(double kp) { pid.setKp(kp); }
    void setPID_Ti(double ti) { pid.setStalaCalk(ti); }
    void setPID_Td(double td) { pid.setTd(td); }
    void setPID_T(double t) { pid.setT(t); }
    void setPID_TypCalki(RegulatorPID::LiczCalk typ) { pid.setLiczCalk(typ); }

    // ARX
    void setARX(const std::vector<double> &a,
                const std::vector<double> &b,
                int opoznienie,
                double szum)
    {
        arx.ustawParametry(a, b, opoznienie, szum);

    }
    void setARX_Umin(double umin) { arx.setUmin(umin); }
    void setARX_Umax(double umax) { arx.setUmax(umax); }
    void setARX_Ymin(double ymin) { arx.setYmin(ymin); }
    void setARX_Ymax(double ymax) { arx.setYmax(ymax); }
    void setARX_Ograniczenia(bool aktywne) {arx.setOgraniczenia(aktywne);}


    // Ręczny krok symulacji
    void krokSymulacji()
    {
        if (symuluj) {
            uar.krok(w, e, u, y, generator, k);
            k++;
        }
    }

    // GETTERY
    int getKrok() const { return k; }
    double getWartoscZadana() const { return w; }
    double getUchyb() const { return e; }
    double getSterowanie() const { return u; }
    double getWyjscie() const { return y; }

    int getInterwalMs() const { return interwalMs; }
    void setInterwalMs(int ms)
    {
        if (ms < 1)
            ms = 1;
        interwalMs = ms;
        timer.setInterval(ms);
    }

    bool czysymuluj() const { return symuluj; }
    double getP() const { return pid.P; }
    double getI() const { return pid.I; }
    double getD() const { return pid.D; }

signals:
    void krokWykonany(double w, double y, double e, double u, int k, double P, double I, double D);

private slots:
    void Tick()
    {
        if (!symuluj)
            return;
        uar.krok(w, e, u, y, generator, k);

        double wartP = getP();
        double wartI = getI();
        double wartD = getD();

        emit krokWykonany(w, y, e, u, k, wartP, wartI, wartD); //emitujemy dane

        k++;
    }
};

#include "Symulator.h"

// KONSTRUKTOR
SymulatorUAR::SymulatorUAR(const GeneratorSygnalu &gen,
                           const RegulatorPID &pid_,
                           const ModelARX &arx_,
                           QObject *parent)
    : QObject(parent)
    , generator(gen)
    , pid(pid_)
    , arx(arx_)
    , uar(arx, pid)
    , symuluj(false)
    , k(0)
    , w(0.0)
    , e(0.0)
    , u(0.0)
    , y(0.0)
    , interwalMs(200)
{
    timer.setInterval(interwalMs);
    connect(&timer, &QTimer::timeout, this, &SymulatorUAR::Tick);
}

// ZEGAR
void SymulatorUAR::Tick()
{
    if (!symuluj)
        return;

    uar.krok(w, e, u, y, generator, k);
    k++;
}

// START
void SymulatorUAR::start()
{
    symuluj = true;
    if (!timer.isActive())
        timer.start();
}

// STOP
void SymulatorUAR::stop()
{
    symuluj = false;
    timer.stop();
}

// RESET
void SymulatorUAR::reset()
{
    stop();
    k = 0;
    w = e = u = y = 0.0;
    uar.reset();
}

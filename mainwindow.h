#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Symulator.h"
#include "arxwindow.h"
#include "qvalueaxis.h"
#include "MenedzerKonfiguracji.h"
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ustawARXDane(const std::vector<double> &a,
                      const std::vector<double> &b,
                      int opoznienie,
                      double szum,
                      double uMin, double uMax,
                      double yMin, double yMax,
                      bool aktywne);
private slots:
    void on_Sin_Button_clicked();

    void on_Square_Button_clicked();

    void on_spinBOX_WzmocK_editingFinished();

    void on_spinBOX_Amplituda_editingFinished();

    void on_spinBOX_Czstotliwosc_editingFinished();

    void on_spinBOX_Td_editingFinished();

    void on_spinBOX_Ti_editingFinished();

    void on_spinBOX_Interwal_editingFinished();

    void on_radio_przed_toggled(bool checked);

    void on_radio_pod_toggled(bool checked);

    void on_Reset_d_clicked();

    void on_Reset_i_clicked();

    void on_START_Button_clicked();

    void on_Konf_ARX_Button_clicked();

    void on_STOP_Bttun_clicked();

    void on_RESET_Button_clicked();

    void on_Zapisz_Button_clicked();

    void on_Wczytaj_Button_clicked();

    void on_spinBox_Wypelnienie_editingFinished();

    void on_SpinBox_Stala_editingFinished();

    void onKrokWykonany(double w, double y, double e, double u, int k, double P, double I, double D);

    void przeliczWykresy();

    void on_spinBoxOknoczasowe_editingFinished();

private:
    Ui::MainWindow *ui;
    MenedzerKonfiguracji menedzerKonfig;
    ARXwindow *arxwindow = nullptr;

    SymulatorUAR symulator;

    QLineSeries *seriaP;
    QLineSeries *seriaI;
    QLineSeries *seriaD;
    QLineSeries *seriaUchyb;
    QLineSeries *seriaRegulator;
    QLineSeries *seriaRegulowana;
    QLineSeries *seriaZad;

    QValueAxis *mainX;
    QValueAxis *mainY;

    QValueAxis *uchybX;
    QValueAxis *uchybY;

    QValueAxis *regX;
    QValueAxis *regY;

    QValueAxis *pidX;
    QValueAxis *pidY;

    // Popraw kolejność inicjalizacji (ZMIEŃ KOLEJNOŚĆ!)
    QTimer *timerPrzeliczania;
    bool przeliczanieWykresu;
    double doceloweOknoCzasowe;
    double T; // okres próbkowania [s]

    void wyczyscWykresy();
    // Funkcja pomocnicza do automatycznego skalowania pionowego
    void dopasujSkalePionowa(QValueAxis *osY, QLineSeries *pierwszaSeria, QLineSeries *drugaSeria = nullptr, QLineSeries *trzeciaSeria = nullptr);

    std::vector<double> aktualnyWektorA;
    std::vector<double> aktualnyWektorB;
    int aktualneOpoznienie;
    double aktualnySzum;

    double arx_uMin = -10.0;
    double arx_uMax = 10.0;
    double arx_yMin = -10.0;
    double arx_yMax = 10.0;
    bool arx_ograniczenia = true;
    void usunStarePunkty(double nowyCzasStartu);
    void usunStarePunktyZSERII(QLineSeries *seria, double nowyCzasStartu);
    void usunNiewidocznePunkty(double minCzas);
    void usunNiewidoczneZSERII(QLineSeries *seria, double minCzas);
    int ostatnieK;
    double skumulowanyCzas;
    double ostatniCzas;

};

#endif // MAINWINDOW_H

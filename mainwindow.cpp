#include "mainwindow.h"
#include "Symulator.h"
#include "arxwindow.h"
#include "qvalueaxis.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDebug>

// Poprawiona kolejność inicjalizacji w konstruktorze
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , symulator(GeneratorSygnalu(), RegulatorPID(), ModelARX({0}, {0}))
    , przeliczanieWykresu(false)
    , doceloweOknoCzasowe(10.0)
    , ostatnieK(-1)
    , skumulowanyCzas(0.0)
    , aktualnyWektorA({0})
    , aktualnyWektorB({0})
    , aktualneOpoznienie(1)
    , aktualnySzum(0.0)
{
    ui->setupUi(this);
    this->showMaximized();

    timerPrzeliczania = new QTimer(this);
    timerPrzeliczania->setSingleShot(true);
    timerPrzeliczania->setInterval(150);
    connect(timerPrzeliczania, &QTimer::timeout, this, &MainWindow::przeliczWykresy);

    //----Serie----//
    seriaP = new QLineSeries();
    seriaI = new QLineSeries();
    seriaD = new QLineSeries();
    seriaUchyb = new QLineSeries();
    seriaRegulator = new QLineSeries();
    seriaZad = new QLineSeries();
    seriaRegulowana = new QLineSeries();

    //----Tytuły----//
    seriaZad->setName("Wartość zadana");
    seriaRegulowana->setName("Wartość regulowana");
    seriaP->setName("P");
    seriaI->setName("I");
    seriaD->setName("D");
    seriaUchyb->setName("Uchyb");
    seriaRegulator->setName("Sterowanie u");

    //----Połączenie z symulatorem----//
    connect(&symulator, &SymulatorUAR::krokWykonany, this, &MainWindow::onKrokWykonany);

    //----Konfiguracja Wykresu Głównego (MAIN)----//
    QChart *Mainchart = new QChart();
    QChartView *MainchartView = new QChartView(Mainchart);
    Mainchart->setAnimationOptions(QChart::NoAnimation);
    MainchartView->setMinimumSize(600, 400);
    Mainchart->addSeries(seriaZad);
    Mainchart->addSeries(seriaRegulowana);
    Mainchart->setTitle("Zadana i Regulowana");

    mainX = new QValueAxis();
    mainY = new QValueAxis();
    mainX->setTitleText("Czas [s]");
    mainY->setTitleText("Wartość");
    mainX->setTickCount(11);
    Mainchart->addAxis(mainX, Qt::AlignBottom);
    Mainchart->addAxis(mainY, Qt::AlignLeft);
    seriaZad->attachAxis(mainX); seriaZad->attachAxis(mainY);
    seriaRegulowana->attachAxis(mainX); seriaRegulowana->attachAxis(mainY);

    MainchartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_5->addWidget(MainchartView);

    //----Konfiguracja Wykresu PID----//
    QChart *PIDchart = new QChart();
    QChartView *PIDchartView = new QChartView(PIDchart);
    PIDchart->setAnimationOptions(QChart::NoAnimation);
    PIDchart->addSeries(seriaP);
    PIDchart->addSeries(seriaI);
    PIDchart->addSeries(seriaD);
    PIDchart->setTitle("Składowe sterowania PID");

    pidX = new QValueAxis();
    pidY = new QValueAxis();
    pidX->setTitleText("Czas [s]");
    pidY->setTitleText("Wartość");
    PIDchart->addAxis(pidX, Qt::AlignBottom);
    PIDchart->addAxis(pidY, Qt::AlignLeft);
    seriaP->attachAxis(pidX); seriaP->attachAxis(pidY);
    seriaI->attachAxis(pidX); seriaI->attachAxis(pidY);
    seriaD->attachAxis(pidX); seriaD->attachAxis(pidY);

    PIDchartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_4->addWidget(PIDchartView, 1);

    //----Konfiguracja Wykresu Uchybu----//
    QChart *Uchybchart = new QChart();
    QChartView *UchybchartView = new QChartView(Uchybchart);
    Uchybchart->setAnimationOptions(QChart::NoAnimation);
    Uchybchart->addSeries(seriaUchyb);
    Uchybchart->setTitle("Uchyb");

    uchybX = new QValueAxis();
    uchybY = new QValueAxis();
    uchybX->setTitleText("Czas [s]");
    uchybY->setTitleText("Wartość");
    Uchybchart->addAxis(uchybX, Qt::AlignBottom);
    Uchybchart->addAxis(uchybY, Qt::AlignLeft);
    seriaUchyb->attachAxis(uchybX); seriaUchyb->attachAxis(uchybY);

    UchybchartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_4->addWidget(UchybchartView, 1);

    //----Konfiguracja Wykresu Regulatora----//
    QChart *Regulatorchart = new QChart();
    QChartView *RegulatorchartView = new QChartView(Regulatorchart);
    Regulatorchart->setAnimationOptions(QChart::NoAnimation);
    Regulatorchart->addSeries(seriaRegulator);
    Regulatorchart->setTitle("Regulator");

    regX = new QValueAxis();
    regY = new QValueAxis();
    regX->setTitleText("Czas [s]");
    regY->setTitleText("Wartość");
    Regulatorchart->addAxis(regX, Qt::AlignBottom);
    Regulatorchart->addAxis(regY, Qt::AlignLeft);
    seriaRegulator->attachAxis(regX); seriaRegulator->attachAxis(regY);

    RegulatorchartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_4->addWidget(RegulatorchartView, 1);
    RegulatorchartView->setMinimumSize(0, 300);
}

void MainWindow::onKrokWykonany(double w, double y, double e, double u, int k, double P, double I, double D)
{
    // 1. UZYSKAJ INTERWAŁ
    static double aktualnyInterwalMs = symulator.getInterwalMs();
    double nowyInterwalMs = symulator.getInterwalMs();

    if (qAbs(nowyInterwalMs - aktualnyInterwalMs) > 0.1) {
        qDebug() << "Zmiana interwału:" << aktualnyInterwalMs << "->" << nowyInterwalMs << "ms";
        aktualnyInterwalMs = nowyInterwalMs;
    }

    double interwalS = aktualnyInterwalMs / 1000.0;

    // 2. OBLICZ CZAS - PROSTE PODEJŚCIE
    double t;

    if (k == 0 || k < ostatnieK) {
        // Reset
        t = 0;
        skumulowanyCzas = 0;
        ostatnieK = k;
    }
    else {
        // Normalny postęp
        t = skumulowanyCzas + interwalS;
        skumulowanyCzas = t;
        ostatnieK = k;
    }

    // 3. DEBUG
    static int debugCount = 0;
    if (debugCount++ % 100 == 0) {
        qDebug() << QString("Krok: %1  Czas: %2s  Interwał: %3ms  w: %4")
                        .arg(k)
                        .arg(t, 0, 'f', 3)
                        .arg(aktualnyInterwalMs)
                        .arg(w, 0, 'f', 6);
    }

    // 4. DODAJ PUNKTY
    seriaZad->append(t, w);
    seriaRegulowana->append(t, y);
    seriaP->append(t, P);
    seriaI->append(t, I);
    seriaD->append(t, D);
    seriaUchyb->append(t, e);
    seriaRegulator->append(t, u);

    // 5. PRZESUŃ OKNO
    if (seriaZad->count() > 1) {
        double najstarszyCzas = seriaZad->at(0).x();

        if ((t - najstarszyCzas) > doceloweOknoCzasowe) {
            double nowyStart = t - doceloweOknoCzasowe;
            usunNiewidocznePunkty(nowyStart);
        }
    }

    // 6. USTAW ZAKRESY
    if (seriaZad->count() > 0) {
        double startTime = qMax(0.0, t - doceloweOknoCzasowe);
        double endTime = t;

        mainX->setRange(startTime, endTime);
        pidX->setRange(startTime, endTime);
        uchybX->setRange(startTime, endTime);
        regX->setRange(startTime, endTime);

        dopasujSkalePionowa(mainY, seriaZad, seriaRegulowana);
        dopasujSkalePionowa(pidY, seriaP, seriaI, seriaD);
        dopasujSkalePionowa(uchybY, seriaUchyb);
        dopasujSkalePionowa(regY, seriaRegulator);
    }
}
void MainWindow::dopasujSkalePionowa(QValueAxis *osY, QLineSeries *pierwszaSeria, QLineSeries *drugaSeria, QLineSeries *trzeciaSeria)
{
    double minWartosc = 999999.0;
    double maxWartosc = -999999.0;
    bool czyZnalezionoJakikolwiekPunkt = false;

    // Pobieramy aktualny czas rozpoczecia wykresu z osi X
    double czasStartu = mainX->min();

    // Tworzymy liste pomocnicza
    QList<QLineSeries*> listaSerii;

    if (pierwszaSeria != nullptr) listaSerii.append(pierwszaSeria);
    if (drugaSeria != nullptr) listaSerii.append(drugaSeria);
    if (trzeciaSeria != nullptr) listaSerii.append(trzeciaSeria);

    // Szukamy od początku do końca (prostsze)
    for (QLineSeries *seria : listaSerii) {
        QList<QPointF> punkty = seria->points();

        for (int i = 0; i < punkty.size(); i++) {
            // Sprawdzamy, czy punkt miesci sie w widocznym oknie czasowym
            if (punkty[i].x() >= czasStartu) {
                czyZnalezionoJakikolwiekPunkt = true;

                if (punkty[i].y() < minWartosc) minWartosc = punkty[i].y();
                if (punkty[i].y() > maxWartosc) maxWartosc = punkty[i].y();
            }
        }
    }

    if (czyZnalezionoJakikolwiekPunkt) {
        double rozpietosc = maxWartosc - minWartosc;

        if (rozpietosc < 0.001) {
            // Dla plaskiego sygnalu dajemy staly margines
            osY->setRange(minWartosc - 0.5, maxWartosc + 0.5);
        } else {
            // ZWIĘKSZONY margines (15% zamiast 10%) dla lepszej czytelności
            double margines = rozpietosc * 0.15;
            // Minimalny margines
            if (margines < 0.1) margines = 0.1;
            osY->setRange(minWartosc - margines, maxWartosc + margines);
        }
    }
}



void MainWindow::on_spinBoxOknoczasowe_editingFinished()
{
    int noweOkno = ui->spinBoxOknoczasowe->value();

    // Jeśli nie ma zmian, wyjdź
    if (qFuzzyCompare(noweOkno, doceloweOknoCzasowe)) {
        return;
    }

    qDebug() << "Zmiana okna czasowego:" << doceloweOknoCzasowe << "->" << noweOkno;

    // 1. ZAPAMIĘTAJ AKTUALNY STAN
    double staryOkno = doceloweOknoCzasowe;
    bool bylyPunkty = (seriaZad->count() > 0);
    double aktualnyCzas = 0;

    if (bylyPunkty) {
        aktualnyCzas = seriaZad->points().last().x();
    }

    // 2. Ustaw nowe okno
    doceloweOknoCzasowe = noweOkno;

    // 3. Jeśli nie ma punktów, po prostu ustaw zakres
    if (!bylyPunkty) {
        mainX->setRange(0, doceloweOknoCzasowe);
        pidX->setRange(0, doceloweOknoCzasowe);
        uchybX->setRange(0, doceloweOknoCzasowe);
        regX->setRange(0, doceloweOknoCzasowe);
        return;
    }

    // 4. OBLICZ NOWY ZAKRES OSI X (NAJWAŻNIEJSZE!)
    double nowyStart = aktualnyCzas - doceloweOknoCzasowe;
    if (nowyStart < 0) nowyStart = 0;
    double nowyKoniec = aktualnyCzas;

    // 5. USTAWIENIE ZAKRESU OSI X (natychmiast!)
    mainX->setRange(nowyStart, nowyKoniec);
    pidX->setRange(nowyStart, nowyKoniec);
    uchybX->setRange(nowyStart, nowyKoniec);
    regX->setRange(nowyStart, nowyKoniec);

    // 6. USUŃ PUNKTY KTÓRE SĄ TERAZ POZA WIDOKIEM
    // (tylko jeśli zmniejszamy okno - przy zwiększaniu nic nie usuwamy)
    if (noweOkno < staryOkno) {
        usunNiewidocznePunkty(nowyStart);
    }

    // 7. NATYCHMIASTOWE ODŚWIEŻENIE
    QApplication::processEvents();

}

void MainWindow::usunNiewidocznePunkty(double minCzas)
{
    // Usuwa punkty starsze niż minCzas ze WSZYSTKICH serii

    // Dla każdej serii indywidualnie
    usunNiewidoczneZSERII(seriaZad, minCzas);
    usunNiewidoczneZSERII(seriaRegulowana, minCzas);
    usunNiewidoczneZSERII(seriaP, minCzas);
    usunNiewidoczneZSERII(seriaI, minCzas);
    usunNiewidoczneZSERII(seriaD, minCzas);
    usunNiewidoczneZSERII(seriaUchyb, minCzas);
    usunNiewidoczneZSERII(seriaRegulator, minCzas);
}

void MainWindow::usunNiewidoczneZSERII(QLineSeries *seria, double minCzas)
{
    if (!seria || seria->count() == 0) return;

    // Zbierz tylko punkty które mają być zachowane
    QVector<QPointF> punktyDoZachowania;
    QList<QPointF> wszystkiePunkty = seria->points();

    for (const QPointF &punkt : wszystkiePunkty) {
        if (punkt.x() >= minCzas) {
            punktyDoZachowania.append(punkt);
        }
    }

    // Jeśli liczba się zmieniła, zastąp serie
    if (punktyDoZachowania.size() != seria->count()) {
        seria->clear();
        for (const QPointF &punkt : punktyDoZachowania) {
            seria->append(punkt);
        }
    }
}
void MainWindow::usunStarePunkty(double nowyCzasStartu)
{
    // Usuń punkty z każdej serii, które są starsze niż nowy czas startu
    usunStarePunktyZSERII(seriaZad, nowyCzasStartu);
    usunStarePunktyZSERII(seriaRegulowana, nowyCzasStartu);
    usunStarePunktyZSERII(seriaP, nowyCzasStartu);
    usunStarePunktyZSERII(seriaI, nowyCzasStartu);
    usunStarePunktyZSERII(seriaD, nowyCzasStartu);
    usunStarePunktyZSERII(seriaUchyb, nowyCzasStartu);
    usunStarePunktyZSERII(seriaRegulator, nowyCzasStartu);
}
void MainWindow::usunStarePunktyZSERII(QLineSeries *seria, double nowyCzasStartu)
{
    if (!seria || seria->count() == 0) return;

    // 1. Zbierz punkty które mają być ZACHOWANE (>= nowyCzasStartu)
    QVector<QPointF> punktyDoZachowania;
    QList<QPointF> wszystkiePunkty = seria->points();

    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        if (wszystkiePunkty[i].x() >= nowyCzasStartu) {
            punktyDoZachowania.append(wszystkiePunkty[i]);
        }
    }

    // 2. Jeśli liczba punktów się zmieniła, ZASTĄP serie
    if (punktyDoZachowania.size() != seria->count()) {
        seria->clear();

        // 3. Dodaj zachowane punkty z powrotem
        for (const QPointF &punkt : punktyDoZachowania) {
            seria->append(punkt);
        }
    }
}

void MainWindow::wyczyscWykresy()
{
    seriaZad->clear();
    seriaRegulowana->clear();
    seriaP->clear();
    seriaI->clear();
    seriaD->clear();
    seriaUchyb->clear();
    seriaRegulator->clear();

    mainX->setRange(0, doceloweOknoCzasowe);
    pidX->setRange(0, doceloweOknoCzasowe);
    uchybX->setRange(0, doceloweOknoCzasowe);
    regX->setRange(0, doceloweOknoCzasowe);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Sin_Button_clicked()
{
    symulator.setGeneratorTryb(GeneratorSygnalu::SINUS);
}

void MainWindow::on_Square_Button_clicked()
{
    symulator.setGeneratorTryb(GeneratorSygnalu::PROSTOKAT);
}

void MainWindow::on_spinBOX_WzmocK_editingFinished()
{
    symulator.setPID_Kp(ui->spinBOX_WzmocK->value());
    ui->spinBOX_WzmocK->setMinimum(0.0);
    ui->spinBOX_WzmocK->setMaximum(1000.0);
    ui->spinBOX_WzmocK->setSingleStep(0.1);
    ui->spinBOX_WzmocK->setDecimals(1);
}

void MainWindow::on_spinBOX_Amplituda_editingFinished()
{
    symulator.setGeneratorA(ui->spinBOX_Amplituda->value());
    ui->spinBOX_Amplituda->setMinimum(0.0);
    ui->spinBOX_Amplituda->setMaximum(1000.0);
    ui->spinBOX_Amplituda->setSingleStep(0.1);
    ui->spinBOX_Amplituda->setDecimals(1);
}

void MainWindow::on_spinBOX_Czstotliwosc_editingFinished()
{
    symulator.setGeneratorTRZ(ui->spinBOX_Czstotliwosc->value());
    ui->spinBOX_Czstotliwosc->setMinimum(0.01);
    ui->spinBOX_Czstotliwosc->setMaximum(1000.0);
    ui->spinBOX_Czstotliwosc->setSingleStep(0.01);
    ui->spinBOX_Czstotliwosc->setDecimals(2);
}

void MainWindow::on_spinBox_Wypelnienie_editingFinished()
{
    symulator.setGeneratorP(ui->spinBox_Wypelnienie->value());
}

void MainWindow::on_SpinBox_Stala_editingFinished()
{
    symulator.setGeneratorS(ui->SpinBox_Stala->value());
}

void MainWindow::on_spinBOX_Td_editingFinished()
{
    symulator.setPID_Td(ui->spinBOX_Td->value());
    ui->spinBOX_Td->setMinimum(0.0);
    ui->spinBOX_Td->setMaximum(1000.0);
    ui->spinBOX_Td->setSingleStep(0.1);
    ui->spinBOX_Td->setDecimals(2);
}

void MainWindow::on_spinBOX_Ti_editingFinished()
{
    symulator.setPID_Ti(ui->spinBOX_Ti->value());
    ui->spinBOX_Ti->setMinimum(0.0);
    ui->spinBOX_Ti->setMaximum(1000.0);
    ui->spinBOX_Ti->setSingleStep(0.1);
    ui->spinBOX_Ti->setDecimals(1);
}

void MainWindow::on_spinBOX_Interwal_editingFinished()
{
    int nowyInterwal = ui->spinBOX_Interwal->value();
    int staryInterwal = symulator.getInterwalMs();

    qDebug() << "Zmiana interwału z" << staryInterwal << "na" << nowyInterwal << "ms";



    // Ustaw nowy interwał
    symulator.setGeneratorTT(nowyInterwal);
    symulator.setInterwalMs(nowyInterwal);
    symulator.setPID_T(nowyInterwal / 1000.0);

    // Aktualizuj UI
    ui->spinBOX_Interwal->setMaximum(1000);
    ui->spinBOX_Interwal->setMinimum(10);
    ui->spinBOX_Interwal->setSingleStep(1);
    ui->spinBOX_Interwal->setDecimals(0);
}

void MainWindow::on_radio_przed_toggled(bool checked)
{
    if (checked)
        symulator.setPID_TypCalki(RegulatorPID::Zew);
}

void MainWindow::on_radio_pod_toggled(bool checked)
{
    if (checked)
        symulator.setPID_TypCalki(RegulatorPID::Wew);
}

void MainWindow::on_Reset_d_clicked()
{
    symulator.setPID_Td(0);
}

void MainWindow::on_Reset_i_clicked()
{
    symulator.setPID_Ti(0);
}

void MainWindow::on_START_Button_clicked()
{
    symulator.start();
}

void MainWindow::on_STOP_Bttun_clicked()
{
    symulator.stop();
}

void MainWindow::on_RESET_Button_clicked()
{
    symulator.reset();

    symulator.setPID_Kp(0);
    ui->spinBOX_WzmocK->setValue(0);

    symulator.setPID_Ti(0);
    ui->spinBOX_Ti->setValue(0);

    symulator.setPID_Td(0);
    ui->spinBOX_Td->setValue(0);

    symulator.setGeneratorA(0);
    ui->spinBOX_Amplituda->setValue(0);

    symulator.setGeneratorTRZ(1.0);
    ui->spinBOX_Czstotliwosc->setValue(1.0);

    symulator.setGeneratorTT(200);
    symulator.setInterwalMs(200);
    symulator.setPID_T(0.2);
    ui->spinBOX_Interwal->setValue(200);

    symulator.setGeneratorS(0);
    ui->SpinBox_Stala->setValue(0);

    symulator.setGeneratorP(0.5);
    ui->spinBox_Wypelnienie->setValue(0.5);

    symulator.setPID_TypCalki(RegulatorPID::Zew);
    ui->radio_przed->setChecked(true);
    ui->radio_pod->setChecked(false);

    aktualnyWektorA = {0};
    aktualnyWektorB = {0};
    aktualneOpoznienie = 1;
    aktualnySzum = 0.0;
    symulator.setARX(aktualnyWektorA, aktualnyWektorB, aktualneOpoznienie, aktualnySzum);

    ostatnieK = -1;
    skumulowanyCzas = 0.0;
    wyczyscWykresy();
}

void MainWindow::przeliczWykresy()
{
    przeliczanieWykresu = false;

}
void MainWindow::ustawARXDane(const std::vector<double> &a,
                              const std::vector<double> &b,
                              int opoznienie,
                              double szum,
                              double uMin, double uMax,
                              double yMin, double yMax,
                              bool aktywne)
{
    aktualnyWektorA = a;
    aktualnyWektorB = b;
    aktualneOpoznienie = opoznienie;
    aktualnySzum = szum;
    arx_uMin = uMin;
    arx_uMax = uMax;
    arx_yMin = yMin;
    arx_yMax = yMax;
    arx_ograniczenia = aktywne;

    symulator.setARX(a, b, opoznienie, szum);

    symulator.setARX_Umin(uMin);
    symulator.setARX_Umax(uMax);
    symulator.setARX_Ymin(yMin);
    symulator.setARX_Ymax(yMax);
    symulator.setARX_Ograniczenia(aktywne);
}

void MainWindow::on_Konf_ARX_Button_clicked()
{
    if (!arxwindow) {
        arxwindow = new ARXwindow(this);

        connect(arxwindow, &ARXwindow::zatwierdzonoARX, this, &MainWindow::ustawARXDane);
    }

    arxwindow->ustawDane(aktualnyWektorA, aktualnyWektorB, aktualneOpoznienie, aktualnySzum,
                         arx_uMin, arx_uMax, arx_yMin, arx_yMax, arx_ograniczenia);

    arxwindow->show();
    arxwindow->raise();
    arxwindow->activateWindow();
}

void MainWindow::on_Zapisz_Button_clicked()
{
    QString sciezka = QFileDialog::getSaveFileName(this, "Zapisz konfigurację",
                                                   "", "JSON (*.json)");
    if (sciezka.isEmpty()) return;
    bool sukces = menedzerKonfig.zapiszKonfiguracje(
        sciezka,
        aktualnyWektorA, aktualnyWektorB, aktualneOpoznienie, aktualnySzum,
        ui->spinBOX_WzmocK->value(), ui->spinBOX_Ti->value(),
        ui->spinBOX_Td->value(), ui->radio_przed->isChecked() ? 0 : 1,
        ui->Sin_Button->isChecked() ? 0 : 1,
        ui->spinBOX_Amplituda->value(),
        ui->spinBOX_Czstotliwosc->value(),
        ui->SpinBox_Stala->value(),
        ui->spinBox_Wypelnienie->value(),
        ui->spinBOX_Interwal->value()
        );

    if (sukces) {
        QMessageBox::information(this ,"sukces", "konfiguracja zapisana");
    } else {
        QMessageBox::warning(this, "blad", "nie udało sie zapisac");
    }
}

void MainWindow::on_Wczytaj_Button_clicked()
{
    QString sciezka = QFileDialog::getOpenFileName(this, "Wczytaj konfigurację",
                                                   "", "JSON (*.json)");
    if (sciezka.isEmpty()) return;

    std::vector<double> a, b;
    int opoznienie;
    double odchylenie, Kp, Ti, Td;
    int typCalki, trybGeneratora;
    double amplituda, StalaSkladniowa, Wypelnienie, czestotliwosc;
    int interwalMs;

    bool sukces = menedzerKonfig.wczytajKonfiguracje(
        sciezka,
        a, b, opoznienie, odchylenie,
        Kp, Ti, Td, typCalki,
        trybGeneratora, amplituda, czestotliwosc, StalaSkladniowa, Wypelnienie,
        interwalMs
        );

    if (sukces) {
        aktualnyWektorA = a;
        aktualnyWektorB = b;
        aktualneOpoznienie = opoznienie;
        aktualnySzum = odchylenie;

        symulator.setARX(a, b, opoznienie, odchylenie);

        ui->spinBOX_WzmocK->setValue(Kp);
        ui->spinBOX_Ti->setValue(Ti);
        ui->spinBOX_Td->setValue(Td);

        if (typCalki == 0) {
            ui->radio_przed->setChecked(true);
            ui->radio_pod->setChecked(false);
        } else {
            ui->radio_przed->setChecked(false);
            ui->radio_pod->setChecked(true);
        }

        if (trybGeneratora == 0) {
            ui->Sin_Button->setChecked(true);
            ui->Square_Button->setChecked(false);
        } else {
            ui->Sin_Button->setChecked(false);
            ui->Square_Button->setChecked(true);
        }

        ui->spinBOX_Amplituda->setValue(amplituda);
        ui->spinBOX_Czstotliwosc->setValue(czestotliwosc);
        ui->SpinBox_Stala->setValue(StalaSkladniowa);
        ui->spinBox_Wypelnienie->setValue(Wypelnienie);
        ui->spinBOX_Interwal->setValue(interwalMs);

        QMessageBox::information(this, "sukces", "konfiguracja wczytana");
    } else {
        QMessageBox::warning(this, "blad", "nie udało sie wczytac");
    }
}

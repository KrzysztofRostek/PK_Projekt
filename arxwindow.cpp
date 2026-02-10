#include "arxwindow.h"
#include "ui_arxwindow.h"

ARXwindow::ARXwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ARXwindow)
{
    ui->setupUi(this);

    // Ustawienia minimalnych i maksymalnych wartosci Spin Boxow
    ui->SpinBox_WektorA->setMinimum(-1000.0);
    ui->SpinBox_WektorA->setMaximum(1000.0);
    ui->SpinBox_WektorA->setSingleStep(0.01);
    ui->SpinBox_WektorA->setDecimals(4);

    ui->SpinBox_WektorB->setMinimum(-1000.0);
    ui->SpinBox_WektorB->setMaximum(1000.0);
    ui->SpinBox_WektorB->setSingleStep(0.01);
    ui->SpinBox_WektorB->setDecimals(4);

    ui->spinBoxOpoznienie->setMinimum(1);
    ui->spinBoxOpoznienie->setMaximum(100);
    ui->spinBoxOpoznienie->setSingleStep(1);



    ui->doubleSpinBox_sigma->setMinimum(0.0);
    ui->doubleSpinBox_sigma->setMaximum(100.0);
    ui->doubleSpinBox_sigma->setSingleStep(0.01);
    ui->doubleSpinBox_sigma->setDecimals(2);

    QList<QDoubleSpinBox*> limitBoxes = {
        ui->doubleSpinBoxSterowaniaMIN,
        ui->doubleSpinBoxSterowaniaMAX,
        ui->doubleSpinBoxRegulowanaMIN,
        ui->doubleSpinBoxRegulowanaMAX
    };

    for(auto box : limitBoxes) {
        box->setMinimum(-10000.0);
        box->setMaximum(10000.0);
        box->setSingleStep(1.0);
        box->setDecimals(2);
    }

    // Wartości domyślne startowe
    ui->doubleSpinBoxSterowaniaMIN->setValue(-10.0);
    ui->doubleSpinBoxSterowaniaMAX->setValue(10.0);
    ui->doubleSpinBoxRegulowanaMIN->setValue(-10.0);
    ui->doubleSpinBoxRegulowanaMAX->setValue(10.0);

    // Checkbox domyślnie włączony
    ui->checkBoxOgraniczenie->setChecked(true);
}

ARXwindow::~ARXwindow()
{
    delete ui;
}

void ARXwindow::ustawDane(const std::vector<double>& wektorA,
                          const std::vector<double>& wektorB,
                          int opoznienie,
                          double sigma,
                          double uMin, double uMax,
                          double yMin, double yMax,
                          bool czyAktywne)
{
    // Wypełnienie listy A
    ui->listWidget_wektorA->clear();
    for (double val : wektorA) {
        ui->listWidget_wektorA->addItem(new QListWidgetItem(QString::number(val, 'f', 4)));
    }

    // Wypełnienie listy B
    ui->listWidget_wektorB->clear();
    for (double val : wektorB) {
        ui->listWidget_wektorB->addItem(new QListWidgetItem(QString::number(val, 'f', 4)));
    }

    ui->spinBoxOpoznienie->setValue(opoznienie);
    ui->doubleSpinBox_sigma->setValue(sigma);

    // Ustawienie wartości w DoubleSpinBoxach
    ui->doubleSpinBoxSterowaniaMIN->setValue(uMin);
    ui->doubleSpinBoxSterowaniaMAX->setValue(uMax);
    ui->doubleSpinBoxRegulowanaMIN->setValue(yMin);
    ui->doubleSpinBoxRegulowanaMAX->setValue(yMax);

    // Checkbox
    ui->checkBoxOgraniczenie->setChecked(czyAktywne);
}

void ARXwindow::on_Add_Button_wektorA_clicked()
{
    double val = ui->SpinBox_WektorA->value();
    QListWidgetItem *item = new QListWidgetItem(QString::number(val), ui->listWidget_wektorA);
    ui->listWidget_wektorA->addItem(item);
    ui->SpinBox_WektorA->clear();
}

void ARXwindow::on_Remove_Button_wektorA_clicked()
{
    delete ui->listWidget_wektorA->takeItem(ui->listWidget_wektorA->currentRow());
}

void ARXwindow::on_Add_Button_wektorB_clicked()
{
    double val = ui->SpinBox_WektorB->value();
    QListWidgetItem *item = new QListWidgetItem(QString::number(val), ui->listWidget_wektorB);
    ui->listWidget_wektorB->addItem(item);
    ui->SpinBox_WektorB->clear();
}

void ARXwindow::on_Remove_Button_wektorB_clicked()
{
    delete ui->listWidget_wektorB->takeItem(ui->listWidget_wektorB->currentRow());
}

void ARXwindow::on_Zatwierdz_Button_clicked()
{
    std::vector<double> wektorA, wektorB;
    for (int i = 0; i < ui->listWidget_wektorA->count(); ++i)
        wektorA.push_back(ui->listWidget_wektorA->item(i)->text().toDouble());
    for (int i = 0; i < ui->listWidget_wektorB->count(); ++i)
        wektorB.push_back(ui->listWidget_wektorB->item(i)->text().toDouble());

    int opoznienie = ui->spinBoxOpoznienie->value();
    double sigma = ui->doubleSpinBox_sigma->value();

    // --- Pobranie wartości z DoubleSpinBoxów ---
    double uMin = ui->doubleSpinBoxSterowaniaMIN->value();
    double uMax = ui->doubleSpinBoxSterowaniaMAX->value();
    double yMin = ui->doubleSpinBoxRegulowanaMIN->value();
    double yMax = ui->doubleSpinBoxRegulowanaMAX->value();
    bool aktywne = ui->checkBoxOgraniczenie->isChecked();

    // Emitowanie sygnału z kompletem danych
    emit zatwierdzonoARX(wektorA, wektorB, opoznienie, sigma, uMin, uMax, yMin, yMax, aktywne);

    this->close();
}

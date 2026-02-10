/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *START_Button;
    QPushButton *STOP_Bttun;
    QPushButton *RESET_Button;
    QLabel *label_9;
    QSpinBox *spinBoxOknoczasowe;
    QVBoxLayout *verticalLayout_5;
    QPushButton *Konf_ARX_Button;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *Wczytaj_Button;
    QPushButton *Zapisz_Button;
    QLabel *label;
    QDoubleSpinBox *spinBOX_Interwal;
    QHBoxLayout *horizontalLayout_17;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Sin_Button;
    QPushButton *Square_Button;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *spinBOX_Amplituda;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QDoubleSpinBox *spinBOX_Czstotliwosc;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_2;
    QDoubleSpinBox *spinBox_Wypelnienie;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_6;
    QDoubleSpinBox *SpinBox_Stala;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *Reset_d;
    QDoubleSpinBox *spinBOX_Td;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *Reset_i;
    QDoubleSpinBox *spinBOX_Ti;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_5;
    QDoubleSpinBox *spinBOX_WzmocK;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radio_przed;
    QRadioButton *radio_pod;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QMenuBar *menubar;
    QMenu *menuUAR;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1671, 999);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_11 = new QVBoxLayout(centralwidget);
        verticalLayout_11->setObjectName("verticalLayout_11");
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");

        horizontalLayout_13->addLayout(horizontalLayout_5);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMinimumSize(QSize(0, 0));
        groupBox_4->setMaximumSize(QSize(498, 230));
        verticalLayout_10 = new QVBoxLayout(groupBox_4);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(13);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(10);
        verticalLayout_12->setObjectName("verticalLayout_12");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        START_Button = new QPushButton(groupBox_4);
        START_Button->setObjectName("START_Button");
        START_Button->setMinimumSize(QSize(0, 50));

        horizontalLayout_11->addWidget(START_Button);

        STOP_Bttun = new QPushButton(groupBox_4);
        STOP_Bttun->setObjectName("STOP_Bttun");
        STOP_Bttun->setMinimumSize(QSize(0, 50));

        horizontalLayout_11->addWidget(STOP_Bttun);


        verticalLayout_12->addLayout(horizontalLayout_11);

        RESET_Button = new QPushButton(groupBox_4);
        RESET_Button->setObjectName("RESET_Button");
        RESET_Button->setMinimumSize(QSize(0, 50));

        verticalLayout_12->addWidget(RESET_Button);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName("label_9");

        verticalLayout_12->addWidget(label_9);

        spinBoxOknoczasowe = new QSpinBox(groupBox_4);
        spinBoxOknoczasowe->setObjectName("spinBoxOknoczasowe");
        spinBoxOknoczasowe->setMinimumSize(QSize(0, 30));
        spinBoxOknoczasowe->setMinimum(5);
        spinBoxOknoczasowe->setMaximum(50);
        spinBoxOknoczasowe->setValue(10);

        verticalLayout_12->addWidget(spinBoxOknoczasowe);


        horizontalLayout_10->addLayout(verticalLayout_12);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(14);
        verticalLayout_5->setObjectName("verticalLayout_5");
        Konf_ARX_Button = new QPushButton(groupBox_4);
        Konf_ARX_Button->setObjectName("Konf_ARX_Button");
        Konf_ARX_Button->setMinimumSize(QSize(0, 50));

        verticalLayout_5->addWidget(Konf_ARX_Button);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        Wczytaj_Button = new QPushButton(groupBox_4);
        Wczytaj_Button->setObjectName("Wczytaj_Button");
        Wczytaj_Button->setMinimumSize(QSize(0, 50));

        horizontalLayout_12->addWidget(Wczytaj_Button);

        Zapisz_Button = new QPushButton(groupBox_4);
        Zapisz_Button->setObjectName("Zapisz_Button");
        Zapisz_Button->setMinimumSize(QSize(0, 50));

        horizontalLayout_12->addWidget(Zapisz_Button);


        verticalLayout_5->addLayout(horizontalLayout_12);

        label = new QLabel(groupBox_4);
        label->setObjectName("label");

        verticalLayout_5->addWidget(label);

        spinBOX_Interwal = new QDoubleSpinBox(groupBox_4);
        spinBOX_Interwal->setObjectName("spinBOX_Interwal");
        spinBOX_Interwal->setMinimumSize(QSize(0, 30));
        spinBOX_Interwal->setDecimals(0);
        spinBOX_Interwal->setMinimum(10.000000000000000);
        spinBOX_Interwal->setMaximum(1000.000000000000000);
        spinBOX_Interwal->setValue(50.000000000000000);

        verticalLayout_5->addWidget(spinBOX_Interwal);


        horizontalLayout_10->addLayout(verticalLayout_5);


        verticalLayout_10->addLayout(horizontalLayout_10);


        verticalLayout_9->addWidget(groupBox_4);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setContentsMargins(-1, 10, -1, -1);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(199, 16777215));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Sin_Button = new QPushButton(groupBox);
        Sin_Button->setObjectName("Sin_Button");
        Sin_Button->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(Sin_Button);

        Square_Button = new QPushButton(groupBox);
        Square_Button->setObjectName("Square_Button");
        Square_Button->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(Square_Button);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setSizeIncrement(QSize(0, 0));
        label_3->setBaseSize(QSize(0, 0));
        label_3->setLineWidth(1);

        horizontalLayout_3->addWidget(label_3);

        spinBOX_Amplituda = new QDoubleSpinBox(groupBox);
        spinBOX_Amplituda->setObjectName("spinBOX_Amplituda");
        spinBOX_Amplituda->setMinimumSize(QSize(0, 30));
        spinBOX_Amplituda->setDecimals(1);
        spinBOX_Amplituda->setMaximum(1000.000000000000000);
        spinBOX_Amplituda->setSingleStep(0.100000000000000);
        spinBOX_Amplituda->setValue(1.000000000000000);

        horizontalLayout_3->addWidget(spinBOX_Amplituda);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        spinBOX_Czstotliwosc = new QDoubleSpinBox(groupBox);
        spinBOX_Czstotliwosc->setObjectName("spinBOX_Czstotliwosc");
        spinBOX_Czstotliwosc->setMinimumSize(QSize(0, 30));
        spinBOX_Czstotliwosc->setMaximum(1000.000000000000000);
        spinBOX_Czstotliwosc->setSingleStep(0.010000000000000);
        spinBOX_Czstotliwosc->setValue(3.000000000000000);

        horizontalLayout_6->addWidget(spinBOX_Czstotliwosc);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(-1, 0, -1, -1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_15->addWidget(label_2);

        spinBox_Wypelnienie = new QDoubleSpinBox(groupBox);
        spinBox_Wypelnienie->setObjectName("spinBox_Wypelnienie");
        spinBox_Wypelnienie->setMinimumSize(QSize(0, 30));
        spinBox_Wypelnienie->setMaximum(1.000000000000000);
        spinBox_Wypelnienie->setValue(0.500000000000000);

        horizontalLayout_15->addWidget(spinBox_Wypelnienie);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(-1, 0, -1, -1);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_16->addWidget(label_6);

        SpinBox_Stala = new QDoubleSpinBox(groupBox);
        SpinBox_Stala->setObjectName("SpinBox_Stala");
        SpinBox_Stala->setMinimumSize(QSize(0, 30));
        SpinBox_Stala->setMinimum(-1000.000000000000000);
        SpinBox_Stala->setMaximum(1000.000000000000000);

        horizontalLayout_16->addWidget(SpinBox_Stala);


        verticalLayout->addLayout(horizontalLayout_16);


        verticalLayout_6->addLayout(verticalLayout);


        horizontalLayout_17->addWidget(groupBox);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(199, 16777215));
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(12);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        Reset_d = new QPushButton(groupBox_3);
        Reset_d->setObjectName("Reset_d");
        Reset_d->setMinimumSize(QSize(0, 30));

        horizontalLayout_8->addWidget(Reset_d);

        spinBOX_Td = new QDoubleSpinBox(groupBox_3);
        spinBOX_Td->setObjectName("spinBOX_Td");
        spinBOX_Td->setMinimumSize(QSize(0, 30));
        spinBOX_Td->setMaximum(1000.000000000000000);
        spinBOX_Td->setSingleStep(0.100000000000000);
        spinBOX_Td->setValue(0.200000000000000);

        horizontalLayout_8->addWidget(spinBOX_Td);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");

        verticalLayout_2->addWidget(label_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        Reset_i = new QPushButton(groupBox_3);
        Reset_i->setObjectName("Reset_i");
        Reset_i->setMinimumSize(QSize(0, 30));

        horizontalLayout_9->addWidget(Reset_i);

        spinBOX_Ti = new QDoubleSpinBox(groupBox_3);
        spinBOX_Ti->setObjectName("spinBOX_Ti");
        spinBOX_Ti->setMinimumSize(QSize(0, 30));
        spinBOX_Ti->setMaximum(1000.000000000000000);
        spinBOX_Ti->setSingleStep(0.100000000000000);
        spinBOX_Ti->setValue(5.000000000000000);

        horizontalLayout_9->addWidget(spinBOX_Ti);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");

        horizontalLayout_20->addWidget(label_5);

        spinBOX_WzmocK = new QDoubleSpinBox(groupBox_3);
        spinBOX_WzmocK->setObjectName("spinBOX_WzmocK");
        spinBOX_WzmocK->setMinimumSize(QSize(82, 30));
        spinBOX_WzmocK->setDecimals(1);
        spinBOX_WzmocK->setMaximum(1000.000000000000000);
        spinBOX_WzmocK->setSingleStep(0.100000000000000);
        spinBOX_WzmocK->setValue(0.500000000000000);

        horizontalLayout_20->addWidget(spinBOX_WzmocK);


        verticalLayout_2->addLayout(horizontalLayout_20);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radio_przed = new QRadioButton(groupBox_3);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(radio_przed);
        radio_przed->setObjectName("radio_przed");

        horizontalLayout->addWidget(radio_przed);

        radio_pod = new QRadioButton(groupBox_3);
        buttonGroup->addButton(radio_pod);
        radio_pod->setObjectName("radio_pod");

        horizontalLayout->addWidget(radio_pod);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(verticalLayout_4);


        horizontalLayout_17->addWidget(groupBox_3);


        verticalLayout_9->addLayout(horizontalLayout_17);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_9->addItem(verticalSpacer);


        horizontalLayout_13->addLayout(verticalLayout_9);


        verticalLayout_11->addLayout(horizontalLayout_13);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");

        verticalLayout_11->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1671, 21));
        menuUAR = new QMenu(menubar);
        menuUAR->setObjectName("menuUAR");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuUAR->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "G\305\202\303\263wne opcje", nullptr));
        START_Button->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        STOP_Bttun->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        RESET_Button->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Okno czasowe", nullptr));
        Konf_ARX_Button->setText(QCoreApplication::translate("MainWindow", "Konfiguracja ARX", nullptr));
        Wczytaj_Button->setText(QCoreApplication::translate("MainWindow", "Wczytaj", nullptr));
        Zapisz_Button->setText(QCoreApplication::translate("MainWindow", "Zapisz", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Interwa\305\202", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "sygna\305\202", nullptr));
        Sin_Button->setText(QCoreApplication::translate("MainWindow", "sinus", nullptr));
        Square_Button->setText(QCoreApplication::translate("MainWindow", "square", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "amplituda", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Okres", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Wype\305\202nienie P", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a S", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "PID", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "r\303\263zniczkowania Td", nullptr));
        Reset_d->setText(QCoreApplication::translate("MainWindow", "RESET d", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "ca\305\202kowania Ti", nullptr));
        Reset_i->setText(QCoreApplication::translate("MainWindow", " RESET I", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "wzmocnienie K", nullptr));
        radio_przed->setText(QCoreApplication::translate("MainWindow", "przed suma", nullptr));
        radio_pod->setText(QCoreApplication::translate("MainWindow", "pod suma", nullptr));
        menuUAR->setTitle(QCoreApplication::translate("MainWindow", "UAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

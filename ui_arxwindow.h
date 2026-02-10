/********************************************************************************
** Form generated from reading UI file 'arxwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARXWINDOW_H
#define UI_ARXWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ARXwindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *spinBoxOpoznienie;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *SpinBox_WektorA;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Remove_Button_wektorA;
    QPushButton *Add_Button_wektorA;
    QListWidget *listWidget_wektorA;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QDoubleSpinBox *doubleSpinBox_sigma;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *SpinBox_WektorB;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *Remove_Button_wektorB;
    QPushButton *Add_Button_wektorB;
    QListWidget *listWidget_wektorB;
    QCheckBox *checkBoxOgraniczenie;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxRegulowanaMAX;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxRegulowanaMIN;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxSterowaniaMAX;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxSterowaniaMIN;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *Anuluj_Button;
    QPushButton *Zatwierdz_Button;
    QMenuBar *menubar;
    QMenu *menuKonfiguracja_ARX;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ARXwindow)
    {
        if (ARXwindow->objectName().isEmpty())
            ARXwindow->setObjectName("ARXwindow");
        ARXwindow->resize(830, 738);
        centralwidget = new QWidget(ARXwindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        spinBoxOpoznienie = new QSpinBox(groupBox_2);
        spinBoxOpoznienie->setObjectName("spinBoxOpoznienie");

        verticalLayout_4->addWidget(spinBoxOpoznienie);


        verticalLayout_6->addWidget(groupBox_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        SpinBox_WektorA = new QDoubleSpinBox(centralwidget);
        SpinBox_WektorA->setObjectName("SpinBox_WektorA");

        horizontalLayout->addWidget(SpinBox_WektorA);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Remove_Button_wektorA = new QPushButton(centralwidget);
        Remove_Button_wektorA->setObjectName("Remove_Button_wektorA");

        horizontalLayout_2->addWidget(Remove_Button_wektorA);

        Add_Button_wektorA = new QPushButton(centralwidget);
        Add_Button_wektorA->setObjectName("Add_Button_wektorA");

        horizontalLayout_2->addWidget(Add_Button_wektorA);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget_wektorA = new QListWidget(centralwidget);
        listWidget_wektorA->setObjectName("listWidget_wektorA");

        verticalLayout->addWidget(listWidget_wektorA);


        verticalLayout_6->addLayout(verticalLayout);


        horizontalLayout_6->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        doubleSpinBox_sigma = new QDoubleSpinBox(groupBox);
        doubleSpinBox_sigma->setObjectName("doubleSpinBox_sigma");

        verticalLayout_3->addWidget(doubleSpinBox_sigma);


        verticalLayout_5->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        SpinBox_WektorB = new QDoubleSpinBox(centralwidget);
        SpinBox_WektorB->setObjectName("SpinBox_WektorB");

        horizontalLayout_3->addWidget(SpinBox_WektorB);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Remove_Button_wektorB = new QPushButton(centralwidget);
        Remove_Button_wektorB->setObjectName("Remove_Button_wektorB");

        horizontalLayout_4->addWidget(Remove_Button_wektorB);

        Add_Button_wektorB = new QPushButton(centralwidget);
        Add_Button_wektorB->setObjectName("Add_Button_wektorB");

        horizontalLayout_4->addWidget(Add_Button_wektorB);


        verticalLayout_2->addLayout(horizontalLayout_4);

        listWidget_wektorB = new QListWidget(centralwidget);
        listWidget_wektorB->setObjectName("listWidget_wektorB");

        verticalLayout_2->addWidget(listWidget_wektorB);


        verticalLayout_5->addLayout(verticalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_6);

        checkBoxOgraniczenie = new QCheckBox(centralwidget);
        checkBoxOgraniczenie->setObjectName("checkBoxOgraniczenie");

        verticalLayout_7->addWidget(checkBoxOgraniczenie);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");

        horizontalLayout_7->addWidget(label_3);

        doubleSpinBoxRegulowanaMAX = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxRegulowanaMAX->setObjectName("doubleSpinBoxRegulowanaMAX");

        horizontalLayout_7->addWidget(doubleSpinBoxRegulowanaMAX);


        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        horizontalLayout_8->addWidget(label_4);

        doubleSpinBoxRegulowanaMIN = new QDoubleSpinBox(groupBox_3);
        doubleSpinBoxRegulowanaMIN->setObjectName("doubleSpinBoxRegulowanaMIN");

        horizontalLayout_8->addWidget(doubleSpinBoxRegulowanaMIN);


        verticalLayout_8->addLayout(horizontalLayout_8);


        horizontalLayout_11->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_9 = new QVBoxLayout(groupBox_4);
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName("label_6");

        horizontalLayout_9->addWidget(label_6);

        doubleSpinBoxSterowaniaMAX = new QDoubleSpinBox(groupBox_4);
        doubleSpinBoxSterowaniaMAX->setObjectName("doubleSpinBoxSterowaniaMAX");

        horizontalLayout_9->addWidget(doubleSpinBoxSterowaniaMAX);


        verticalLayout_9->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName("label_5");

        horizontalLayout_10->addWidget(label_5);

        doubleSpinBoxSterowaniaMIN = new QDoubleSpinBox(groupBox_4);
        doubleSpinBoxSterowaniaMIN->setObjectName("doubleSpinBoxSterowaniaMIN");

        horizontalLayout_10->addWidget(doubleSpinBoxSterowaniaMIN);


        verticalLayout_9->addLayout(horizontalLayout_10);


        horizontalLayout_11->addWidget(groupBox_4);


        verticalLayout_7->addLayout(horizontalLayout_11);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        Anuluj_Button = new QPushButton(centralwidget);
        Anuluj_Button->setObjectName("Anuluj_Button");

        horizontalLayout_5->addWidget(Anuluj_Button);

        Zatwierdz_Button = new QPushButton(centralwidget);
        Zatwierdz_Button->setObjectName("Zatwierdz_Button");

        horizontalLayout_5->addWidget(Zatwierdz_Button);


        verticalLayout_7->addLayout(horizontalLayout_5);

        ARXwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ARXwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 830, 21));
        menuKonfiguracja_ARX = new QMenu(menubar);
        menuKonfiguracja_ARX->setObjectName("menuKonfiguracja_ARX");
        ARXwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ARXwindow);
        statusbar->setObjectName("statusbar");
        ARXwindow->setStatusBar(statusbar);

        menubar->addAction(menuKonfiguracja_ARX->menuAction());

        retranslateUi(ARXwindow);

        QMetaObject::connectSlotsByName(ARXwindow);
    } // setupUi

    void retranslateUi(QMainWindow *ARXwindow)
    {
        ARXwindow->setWindowTitle(QCoreApplication::translate("ARXwindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ARXwindow", "Op\303\263\305\272nienie transportowe k", nullptr));
        label->setText(QCoreApplication::translate("ARXwindow", "Wektor A", nullptr));
        Remove_Button_wektorA->setText(QCoreApplication::translate("ARXwindow", "Usu\305\204", nullptr));
        Add_Button_wektorA->setText(QCoreApplication::translate("ARXwindow", "Dodaj ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ARXwindow", "sigma ", nullptr));
        label_2->setText(QCoreApplication::translate("ARXwindow", "Wektor B", nullptr));
        Remove_Button_wektorB->setText(QCoreApplication::translate("ARXwindow", "Usu\305\204", nullptr));
        Add_Button_wektorB->setText(QCoreApplication::translate("ARXwindow", "Dodaj ", nullptr));
        checkBoxOgraniczenie->setText(QCoreApplication::translate("ARXwindow", "Ograniczenie", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ARXwindow", "Ogranicznie warto\305\233ci regulowanej", nullptr));
        label_3->setText(QCoreApplication::translate("ARXwindow", "MAX", nullptr));
        label_4->setText(QCoreApplication::translate("ARXwindow", "MIN", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ARXwindow", "Ogranicznie warto\305\233ci sterowania", nullptr));
        label_6->setText(QCoreApplication::translate("ARXwindow", "MAX", nullptr));
        label_5->setText(QCoreApplication::translate("ARXwindow", "MIN", nullptr));
        Anuluj_Button->setText(QCoreApplication::translate("ARXwindow", "Anuluj", nullptr));
        Zatwierdz_Button->setText(QCoreApplication::translate("ARXwindow", "Zatwierd\305\272", nullptr));
        menuKonfiguracja_ARX->setTitle(QCoreApplication::translate("ARXwindow", "Konfiguracja ARX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ARXwindow: public Ui_ARXwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARXWINDOW_H

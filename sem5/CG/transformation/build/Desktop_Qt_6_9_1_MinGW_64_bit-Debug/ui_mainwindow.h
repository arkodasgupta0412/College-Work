/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *translate;
    QPushButton *rotate;
    QPushButton *scale;
    QPushButton *reflectY;
    QPushButton *reflectX;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *drawPolygon;
    QPushButton *restoreOriginal;
    QPushButton *shear;
    QGraphicsView *grid;
    QPushButton *clear;
    QDoubleSpinBox *spinBoxX_translate;
    QDoubleSpinBox *spinBoxY_translate;
    QDoubleSpinBox *spinBox_rotate;
    QDoubleSpinBox *spinBoxY_scale;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxX_scale;
    QLabel *label_6;
    QDoubleSpinBox *spinBoxY_shear;
    QLabel *label_7;
    QDoubleSpinBox *spinBoxX_shear;
    QLabel *label_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(938, 745);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        translate = new QPushButton(centralwidget);
        translate->setObjectName("translate");
        translate->setGeometry(QRect(790, 80, 111, 41));
        rotate = new QPushButton(centralwidget);
        rotate->setObjectName("rotate");
        rotate->setGeometry(QRect(790, 220, 111, 41));
        scale = new QPushButton(centralwidget);
        scale->setObjectName("scale");
        scale->setGeometry(QRect(790, 360, 111, 41));
        reflectY = new QPushButton(centralwidget);
        reflectY->setObjectName("reflectY");
        reflectY->setGeometry(QRect(590, 590, 171, 41));
        reflectX = new QPushButton(centralwidget);
        reflectX->setObjectName("reflectX");
        reflectX->setGeometry(QRect(400, 590, 171, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(810, 130, 16, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(870, 130, 16, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(820, 270, 41, 20));
        drawPolygon = new QPushButton(centralwidget);
        drawPolygon->setObjectName("drawPolygon");
        drawPolygon->setGeometry(QRect(20, 590, 171, 41));
        restoreOriginal = new QPushButton(centralwidget);
        restoreOriginal->setObjectName("restoreOriginal");
        restoreOriginal->setGeometry(QRect(210, 590, 171, 41));
        shear = new QPushButton(centralwidget);
        shear->setObjectName("shear");
        shear->setGeometry(QRect(790, 500, 111, 41));
        grid = new QGraphicsView(centralwidget);
        grid->setObjectName("grid");
        grid->setGeometry(QRect(20, 20, 741, 541));
        clear = new QPushButton(centralwidget);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(350, 650, 91, 41));
        spinBoxX_translate = new QDoubleSpinBox(centralwidget);
        spinBoxX_translate->setObjectName("spinBoxX_translate");
        spinBoxX_translate->setGeometry(QRect(780, 150, 63, 29));
        spinBoxY_translate = new QDoubleSpinBox(centralwidget);
        spinBoxY_translate->setObjectName("spinBoxY_translate");
        spinBoxY_translate->setGeometry(QRect(850, 150, 63, 29));
        spinBox_rotate = new QDoubleSpinBox(centralwidget);
        spinBox_rotate->setObjectName("spinBox_rotate");
        spinBox_rotate->setGeometry(QRect(810, 290, 63, 29));
        spinBoxY_scale = new QDoubleSpinBox(centralwidget);
        spinBoxY_scale->setObjectName("spinBoxY_scale");
        spinBoxY_scale->setGeometry(QRect(850, 430, 63, 29));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(810, 410, 16, 20));
        spinBoxX_scale = new QDoubleSpinBox(centralwidget);
        spinBoxX_scale->setObjectName("spinBoxX_scale");
        spinBoxX_scale->setGeometry(QRect(780, 430, 63, 29));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(870, 410, 16, 20));
        spinBoxY_shear = new QDoubleSpinBox(centralwidget);
        spinBoxY_shear->setObjectName("spinBoxY_shear");
        spinBoxY_shear->setGeometry(QRect(850, 560, 63, 29));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(810, 540, 16, 20));
        spinBoxX_shear = new QDoubleSpinBox(centralwidget);
        spinBoxX_shear->setObjectName("spinBoxX_shear");
        spinBoxX_shear->setGeometry(QRect(780, 560, 63, 29));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(870, 540, 16, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 938, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        translate->setText(QCoreApplication::translate("MainWindow", "Translate", nullptr));
        rotate->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        scale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        reflectY->setText(QCoreApplication::translate("MainWindow", "Reflect along Y-axis", nullptr));
        reflectX->setText(QCoreApplication::translate("MainWindow", "Reflect along X-axis", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "angle", nullptr));
        drawPolygon->setText(QCoreApplication::translate("MainWindow", "Draw Polygon", nullptr));
        restoreOriginal->setText(QCoreApplication::translate("MainWindow", "Restore Original", nullptr));
        shear->setText(QCoreApplication::translate("MainWindow", "Shear", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

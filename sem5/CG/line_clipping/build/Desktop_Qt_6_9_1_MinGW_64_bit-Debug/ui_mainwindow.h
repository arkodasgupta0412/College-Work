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
#include <QtWidgets/QGraphicsView>
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
    QPushButton *drawLine;
    QPushButton *restoreLine;
    QGraphicsView *grid;
    QPushButton *clearAll;
    QPushButton *eraseLine;
    QPushButton *drawWindow;
    QPushButton *eraseWindow;
    QPushButton *clipLineCohenSuther;
    QPushButton *clipLineLiangBarsky;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1051, 622);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        drawLine = new QPushButton(centralwidget);
        drawLine->setObjectName("drawLine");
        drawLine->setGeometry(QRect(850, 20, 111, 41));
        restoreLine = new QPushButton(centralwidget);
        restoreLine->setObjectName("restoreLine");
        restoreLine->setGeometry(QRect(850, 70, 111, 41));
        grid = new QGraphicsView(centralwidget);
        grid->setObjectName("grid");
        grid->setGeometry(QRect(20, 20, 741, 541));
        clearAll = new QPushButton(centralwidget);
        clearAll->setObjectName("clearAll");
        clearAll->setGeometry(QRect(860, 510, 91, 41));
        eraseLine = new QPushButton(centralwidget);
        eraseLine->setObjectName("eraseLine");
        eraseLine->setGeometry(QRect(850, 120, 111, 41));
        drawWindow = new QPushButton(centralwidget);
        drawWindow->setObjectName("drawWindow");
        drawWindow->setGeometry(QRect(820, 210, 171, 41));
        eraseWindow = new QPushButton(centralwidget);
        eraseWindow->setObjectName("eraseWindow");
        eraseWindow->setGeometry(QRect(820, 260, 171, 41));
        clipLineCohenSuther = new QPushButton(centralwidget);
        clipLineCohenSuther->setObjectName("clipLineCohenSuther");
        clipLineCohenSuther->setGeometry(QRect(790, 360, 231, 41));
        clipLineLiangBarsky = new QPushButton(centralwidget);
        clipLineLiangBarsky->setObjectName("clipLineLiangBarsky");
        clipLineLiangBarsky->setGeometry(QRect(790, 410, 231, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1051, 25));
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
        drawLine->setText(QCoreApplication::translate("MainWindow", "Draw Line", nullptr));
        restoreLine->setText(QCoreApplication::translate("MainWindow", "Restore Line", nullptr));
        clearAll->setText(QCoreApplication::translate("MainWindow", "Clear All", nullptr));
        eraseLine->setText(QCoreApplication::translate("MainWindow", "Erase Line", nullptr));
        drawWindow->setText(QCoreApplication::translate("MainWindow", "Draw Clipping Window", nullptr));
        eraseWindow->setText(QCoreApplication::translate("MainWindow", "Erase Clipping Window", nullptr));
        clipLineCohenSuther->setText(QCoreApplication::translate("MainWindow", "Clip Line (Cohen-Sutherland)", nullptr));
        clipLineLiangBarsky->setText(QCoreApplication::translate("MainWindow", "Clip Line (Liang-Barsky)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

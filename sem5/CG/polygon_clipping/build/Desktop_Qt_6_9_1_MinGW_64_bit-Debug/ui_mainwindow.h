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
    QPushButton *drawPolygon;
    QPushButton *restorePolygon;
    QGraphicsView *grid;
    QPushButton *clearAll;
    QPushButton *erasePolygon;
    QPushButton *drawWindow;
    QPushButton *eraseWindow;
    QPushButton *clipPolygonSutherHodge;
    QPushButton *clipPolygonWeilerAther;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1068, 643);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        drawPolygon = new QPushButton(centralwidget);
        drawPolygon->setObjectName("drawPolygon");
        drawPolygon->setGeometry(QRect(850, 20, 131, 41));
        restorePolygon = new QPushButton(centralwidget);
        restorePolygon->setObjectName("restorePolygon");
        restorePolygon->setGeometry(QRect(850, 80, 131, 41));
        grid = new QGraphicsView(centralwidget);
        grid->setObjectName("grid");
        grid->setGeometry(QRect(20, 20, 741, 561));
        clearAll = new QPushButton(centralwidget);
        clearAll->setObjectName("clearAll");
        clearAll->setGeometry(QRect(870, 540, 91, 41));
        erasePolygon = new QPushButton(centralwidget);
        erasePolygon->setObjectName("erasePolygon");
        erasePolygon->setGeometry(QRect(850, 140, 131, 41));
        drawWindow = new QPushButton(centralwidget);
        drawWindow->setObjectName("drawWindow");
        drawWindow->setGeometry(QRect(830, 240, 171, 41));
        eraseWindow = new QPushButton(centralwidget);
        eraseWindow->setObjectName("eraseWindow");
        eraseWindow->setGeometry(QRect(830, 300, 171, 41));
        clipPolygonSutherHodge = new QPushButton(centralwidget);
        clipPolygonSutherHodge->setObjectName("clipPolygonSutherHodge");
        clipPolygonSutherHodge->setGeometry(QRect(810, 380, 221, 41));
        clipPolygonWeilerAther = new QPushButton(centralwidget);
        clipPolygonWeilerAther->setObjectName("clipPolygonWeilerAther");
        clipPolygonWeilerAther->setGeometry(QRect(810, 440, 221, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1068, 25));
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
        drawPolygon->setText(QCoreApplication::translate("MainWindow", "Draw Polygon", nullptr));
        restorePolygon->setText(QCoreApplication::translate("MainWindow", "Restore Polygon", nullptr));
        clearAll->setText(QCoreApplication::translate("MainWindow", "Clear All", nullptr));
        erasePolygon->setText(QCoreApplication::translate("MainWindow", "Erase Polygon", nullptr));
        drawWindow->setText(QCoreApplication::translate("MainWindow", "Draw Clipping Window", nullptr));
        eraseWindow->setText(QCoreApplication::translate("MainWindow", "Erase Clipping Window", nullptr));
        clipPolygonSutherHodge->setText(QCoreApplication::translate("MainWindow", "Clip (Sutherland Hodgeman)", nullptr));
        clipPolygonWeilerAther->setText(QCoreApplication::translate("MainWindow", "Clip Polygon (Weiler Atherton)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

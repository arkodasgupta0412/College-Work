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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <my_label.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    my_label *frame;
    QLabel *mouse_movement;
    QLabel *mouse_pressed;
    QPushButton *draw_line;
    QPushButton *clear;
    QMenuBar *menubar;
    QMenu *menuMainWindow;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new my_label(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 30, 431, 341));
        mouse_movement = new QLabel(centralwidget);
        mouse_movement->setObjectName("mouse_movement");
        mouse_movement->setGeometry(QRect(640, 70, 63, 20));
        mouse_pressed = new QLabel(centralwidget);
        mouse_pressed->setObjectName("mouse_pressed");
        mouse_pressed->setGeometry(QRect(630, 140, 63, 20));
        draw_line = new QPushButton(centralwidget);
        draw_line->setObjectName("draw_line");
        draw_line->setGeometry(QRect(640, 290, 90, 29));
        clear = new QPushButton(centralwidget);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(640, 370, 90, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuMainWindow = new QMenu(menubar);
        menuMainWindow->setObjectName("menuMainWindow");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMainWindow->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        frame->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        mouse_movement->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        mouse_pressed->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        draw_line->setText(QCoreApplication::translate("MainWindow", "Draw Line", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        menuMainWindow->setTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>

/*
 * Autor: Alec Damian Martinez
 * Date: June 6, 2016
 * @file: main.cpp
 * @brief: The main function class that sets the title of the window and contains the MainWindow class which is where
 * the entire game code exists
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Straight Outta Kuiper");
    //w.setFixedHeight(675);
    //w.setFixedWidth(750);
    w.show();

    return a.exec();
}

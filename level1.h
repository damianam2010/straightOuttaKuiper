#ifndef LEVEL1_H
#define LEVEL1_H

#include <QMainWindow>
#include "mainwindow.h"

/*
 * Autor: Alec Damian Martinez
 * Date: June 6, 2016
 * @file: level1.h
 * @class: Level1
 * @brief: the title of this file has nothing to do with level 1. It actually is the header file for the
 * cpp file that displays the instructions for the game
 *
*/


namespace Ui {
class Level1;
}

class Level1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = 0);
    ~Level1();
    void paintEvent(QPaintEvent* e);

private:
    Ui::Level1 *ui;

};

#endif // LEVEL1_H

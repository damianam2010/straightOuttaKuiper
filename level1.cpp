#include "level1.h"
#include "ui_level1.h"


/*
 * Autor: Alec Damian Martinez
 * Date: June 6, 2016
 * @file: level1.cpp
 * @class: Level1
 * @brief: This file has nothing to do with level1. Instead, this file contains a paintEvent that
 * paints the background for the game instruction and it also includes the ui that displays this
 * instruction text.
*/
Level1::Level1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Level1)
{
    ui->setupUi(this);
}

Level1::~Level1()
{
    delete ui;
}

void Level1::paintEvent(QPaintEvent *e){
    QPainter* painter = new QPainter();
    painter->begin(this);

    //painter->drawLine(10,10,100,100);
    painter->drawPixmap(0,0,this->width(),this->height(),QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/space2BG.jpg"));
    painter->drawPixmap(50,5,450-100,45,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/titleinstructions.png"));

}

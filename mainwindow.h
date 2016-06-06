#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QPoint>
#include <QKeyEvent>
#include <string>
#include "level1.h"
#include <vector>

/*
 * Autor: Alec Damian Martinez
 * Date: June 6, 2016
 * @file: mainwindow.h
 * @class: MainWindow
 * @brief: the header file containing all class function declrations and class variables
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit constructor
    explicit MainWindow(QWidget *parent = 0);
    //explicit desctructor inherited from the QMainWindow class
    ~MainWindow();
    //all paintEvents that will update what is displayed on the mainWindow
    void paintEvent(QPaintEvent *e);
    //the function that handles all keystrokes
    void keyPressEvent(QKeyEvent *e);
    //the window length. This value is fixed
    int winLength = 750;
    //the window height. This value is fixed
    int winHeight = 675;
    //a boolean that creates a flicker effect when the game starts (for aesthetics)
    bool flickOn = true;

public slots:
    //the member function that makes the Title flicker on and off
    void flickerTitle();

    //the function that is constantly running to move the ball
    void moveBall();

    //the function that displays the instructions at the beginning of the game
    void instructions();


private:
    Ui::MainWindow *ui;
    //main TitlePage background
    QPixmap* background;
    QTimer* flickerTimer;
    //This timer will produce movement of the ball
    QTimer* ballTimer;
    //ONLY ONE OF THESE BOOLEANS CAN BE TRUE AT A TIME
    bool title,level1,level2,level3,gameOver, finish;
    //The dimensions of the board
    int rows, columns;
    //The length and height of the blocks
    int blockLength, blockHeight;
    //The location and width of the paddle
    int paddleX, paddleY, paddleWidth;
    //number of lives
    int lives;
    //ball location and Horizontal/Vertical Velocity and Diameter
    int ballX, ballY, ballH, ballV, ballD = 30;    //ideally, the ball velocity is always fixed
    //is the ball moving? this is controlled by pressing the spaceBar
     bool gameOn, victory;
    std::vector<int> blockStatus;
};

#endif // MAINWINDOW_H

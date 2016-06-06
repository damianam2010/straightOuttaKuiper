#include "mainwindow.h"
//#include "level1.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

/*
 * Autor: Alec Damian Martinez
 * Date: June 6, 2016
 * @file: mainwindow.cpp
 * @class: MainWindow
 * @brief: this contains all the class definitions of the MainWindow class which contains all of the
 * code for the main starting window. the game starts with a display of the title with a flickering sign
 * indicating how to start
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set the background of the title screen
    background = new QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/spaceBG.jpg");
    flickerTimer = new QTimer();
    ballTimer = new QTimer();

    connect(flickerTimer,SIGNAL(timeout()),this,SLOT(flickerTitle()));
    flickerTimer->start(1000);

    //very short timer for the ballTimer. This is to ensure as "fluid" and continuous motion as possible
    connect(ballTimer,SIGNAL(timeout()),this,SLOT(moveBall()));
    ballTimer->start(50);

    //when a mainwindow is created. all the booleans except the title are set to false
    title = true; level1 = false; level2 = false; gameOver = false; finish = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){
    //create a painter to handle all the paintEvents
    QPainter* painter = new QPainter();
    painter->begin(this);

    //if we are at the title or the finish screen we will display the main title background
    if(title || finish){
        painter->drawPixmap(0,0,this->width(),this->height(),*background);
        //if we are at the title we will have the flickering screen
        if(title){
            //TITLE OF THE GAME
            painter->drawPixmap(65,225,winLength-130,85,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/TitleText1.png"));
            //INSTRUCTION FOR HOW TO START

            if(flickOn){
                painter->drawPixmap(winLength/2 - 130, 350, 260, 45,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/instructText.png"));
                painter->drawPixmap(winLength/2 - 150, 400, 300, 45,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/instructions.png"));
            }
        }
        //if we are at the finish line, we will just display a congratulations message
        else if(finish){
            painter->drawPixmap(winLength/2-250,winHeight/2-100,500,120,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/congratstext.png"));
        }
    }
    //ALL THE PAINTED EVENTS FOR LEVEL 1
    else if(level1){
        painter->drawPixmap(0,0,this->width(),this->height(),QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/kuiperBG.jpg"));
        //PAINT THE BLOCKS except the bottom row
        for(int i=0; i<columns;i++){
            for(int j=0; j<rows-1;j++){
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::red);
            }
        }
        //just paint the last row
        for(int i=0; i<columns;i++){
            int j = rows-1;
            //if the status is still on, the block is red
            if(blockStatus[i]==1)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::red);
            //if the status is off, the block is yellow
            else if(blockStatus[i]==0)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::yellow);
        }
        //PAINT THE NUMBER OF LIVES YOU HAVE ON THE FAR RIGHT
        for(int i=0; i< lives; i++){
            painter->drawPixmap(winLength-32,winHeight/2-100+32*i,30,30,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/heart2.png"));
        }
        //PAINT THE PADDLE
        painter->fillRect(paddleX, paddleY, paddleWidth,5,Qt::white);

        //PAINT THE BALL
        painter->drawPixmap(ballX,ballY,ballD,ballD,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/ball.png"));

        //if we beat the level, we will display a victory message
        if(victory)
        {
            painter->drawPixmap(winLength/2-150,winHeight/2-60,300,100,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/victorytext.png"));
        }

        //if we lost all our lives, we will display a gameOver message
        if(gameOver)
        {
                painter->drawPixmap(winLength/2-225,winHeight/2-100,450,200,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/gameovertext.png"));
        }

    }

    //PAINT EVENTS FOR LEVEL 2
    else if(level2){
        painter->drawPixmap(0,0,this->width(),this->height(),QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/spaceBG2.jpg"));
        //PAINT THE BLOCKS
        for(int i=0; i<columns;i++){
            for(int j=0; j<rows-1;j++){
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::red);
            }
        }
        //JUST FOR THE LAST ROW
        for(int i=0; i<columns;i++){
            int j = rows-1;
            if(blockStatus[i]>=1)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::red);
            else if(blockStatus[i]==0)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::yellow);
        }
        //PAINT THE NUMBER OF LIVES YOU HAVE ON THE FAR RIGHT
        for(int i=0; i< lives; i++){
            painter->drawPixmap(winLength-32,winHeight/2-100+32*i,30,30,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/heart2.png"));
        }
        //PAINT THE PADDLE
        painter->fillRect(paddleX, paddleY, paddleWidth,5,Qt::white);

        //PAINT THE BALL
        painter->drawPixmap(ballX,ballY,ballD,ballD,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/ball.png"));

        if(victory)
        {
            painter->drawPixmap(winLength/2-225,winHeight/2-60,450,120,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/victorytext.png"));
        }
        if(gameOver)
        {
                painter->drawPixmap(winLength/2-150,winHeight/2-100,375,200,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/gameovertext.png"));
        }

    }

    //PAINT EVENTS FOR LEVEL 3
    else if(level3){
        painter->drawPixmap(0,0,this->width(),this->height(),QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/spaceBG3.png"));
        //PAINT THE BLOCKS
        for(int i=0; i<columns;i++){
            for(int j=0; j<rows-1;j++){
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::blue);
            }
        }
        //JUST FOR THE LAST ROW
        for(int i=0; i<columns;i++){
            int j = rows-1;
            if(blockStatus[i]==2)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::blue);
            else if(blockStatus[i]==1)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::red);
            else if(blockStatus[i]==0)
                painter->fillRect(i*blockLength+10,j*blockHeight+15,blockLength-1,blockHeight-1,Qt::yellow);
        }
        //PAINT THE NUMBER OF LIVES YOU HAVE ON THE FAR RIGHT
        for(int i=0; i< lives; i++){
            painter->drawPixmap(winLength-32,winHeight/2-100+32*i,30,30,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/heart2.png"));
        }
        //PAINT THE PADDLE
        painter->fillRect(paddleX, paddleY, paddleWidth,5,Qt::white);

        //PAINT THE BALL
        painter->drawPixmap(ballX,ballY,ballD,ballD,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/ball.png"));

        if(victory)
        {
            painter->drawPixmap(winLength/2-150,winHeight/2-60,300,120,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/victorytext.png"));
        }
        if(gameOver)
        {
                painter->drawPixmap(winLength/2-225,winHeight/2-100,450,200,QPixmap("/Users/Damian/Desktop/PIC 10C/Game/game/gameovertext.png"));
        }

    }

    painter->end();

    this->update();
}
/*
 *  @function flickerTitle()
 *  @brief this is a function that just toggles the flicker boolean of the main title screen
 *  this function is purely for aesthetics
 *
*/
void MainWindow::flickerTitle(){
    //if flick is on, then turn it off. or vice versa
    flickOn = !flickOn;
    update();
}

/*
 *  @function moveBall()
 *  @brief this is a function that controls the movement of the ball. The movement of the ball depends on the variety
 *  of factors. If the ball hits a wall, the velocity in that direction is completely deflected. The ball is constantly
 *  updating it's x position and y position. This horizonal velocity is changed by the location that the ball hits the
 *  paddle. The vertical velocity is fixed for each level, but gets progressively faster
*/
void MainWindow::moveBall(){
    if(gameOn){
        //the ball is hit by the paddle
        if(ballY + ballD + 5*ballV > paddleY && ballX + ballD > paddleX && ballX < (paddleX + paddleWidth)){
        ballV *=-1; //reverse the direction of ballV
        ballH += (ballX - ((paddleX+paddleWidth*1.0/2.0)))/(paddleWidth*1.0/4.0);
        }
        //the paddle misses the ball
        else if(ballY - 2*ballD > paddleY)
        {
            lives -= 1;
            gameOn = false;
            if(lives == 0)
                gameOver = true;
            //RESET THE POSITION OF THE BALL
            ballY = winHeight - 80;
            ballX = winLength/2;
            ballH = 0;
        }
        //the paddle hits the rows
        else if(ballY + 5*ballV < rows*blockHeight)
        {
            ballV *= -1; //vertical velocity is reflected
            //depending on where the ball hit the blocks, we need to update the status of those blocks
            if(ballX < blockLength + 10){
                blockStatus[0] -= 1;
                if(blockStatus[0] < 0)
                    blockStatus[0] = 0;
            }
            else if(ballX < blockLength*2 + 10){
                blockStatus[1] -= 1;
                if(blockStatus[1] < 0)
                    blockStatus[1] = 0;
            }
            else if(ballX < blockLength*3 + 10){
                blockStatus[2] -= 1;
                if(blockStatus[2] < 0)
                    blockStatus[2] = 0;
            }
            else if(ballX < blockLength*4 + 10){
                blockStatus[3] -= 1;
                if(blockStatus[3] < 0)
                    blockStatus[3] = 0;
            }
            else{
                blockStatus[4] -= 1;
                if(blockStatus[4] < 0)
                    blockStatus[4] = 0;
            }
            //note that blockStatus only applies to the bottom row.
            //if the bottom row has all their statuses reduced to zero, we clear that row
            //and we repaint it
            int sum = 0;
            for(auto x:blockStatus)
                sum+=x;
            if(sum == 0){
                rows-=1;
                if(!level3){
                    blockStatus = std::vector<int>(columns,1);
                }
                else if(level3){
                    blockStatus = std::vector<int>(columns,2);
                }
            }

            if(rows == 0)
            {
                gameOn = false;
                victory = true;
            }
            update();
        }
        //the paddle hits the walls
        else if(ballX + ballH*5 < 0 || ballX + ballH*5 + ballD > winLength)
        {
            ballH *= -1; //reverse the horizontal velocity
        }
        //adjust the ball position depending on the horizontal velocity and vertical velocity
        ballX += ballH*5;
        ballY += 5*ballV;
    }
}

//THIS IS WHERE EVERYTHING IS INITIALIZED
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(gameOver)
    {
        gameOver = false;
        title = true;
    }
    else if(title)
    {
        if(e->key()==Qt::Key_Up){
            //we enter level 1, leave the title page
            level1 = true; title = false;
            //rows = 1; columns = 2;  //for demonstration purposes
            rows = 3; columns = 4;
            blockLength = (winLength-20)/(columns);
            blockHeight = 40;
            //THE STATUS IS INITIALIZED TO 1
            blockStatus = std::vector<int>(columns,1); //this will be constantly updated
            //The paddle location is set
            paddleWidth = 150;
            paddleX = winLength/2 - paddleWidth/2;
            paddleY = winHeight - 35;
            //set the number of lives
            //lives = 1; //for demonstration purposes
            lives = 5;
            //set the location of ball
            ballX = winLength/2; ballY = winHeight - 70; ballH = 0; ballV = 2;
            //the game is not on
            gameOn = false, victory = false;
        }
        //this generates the instructions page if the Space bar is pressed
        else if(e->key()==Qt::Key_Space){
            instructions();
        }
        else
            std::cout<<"Please enter a valid input" << std::endl;
    }
    //if P is pressed, pause the game
    else if(e->key()==Qt::Key_P)
    {
        gameOn = !gameOn;
    }
    //CONTROLS FOR LEVEL1
    else if(level1)
    {
        if(e->key()==Qt::Key_Space && !victory){
            gameOn = true;
            ballV = -2;
        }
        if(e->key()==Qt::Key_Left && !victory){
            if(paddleX >=20)
                paddleX-=20;
            else
                paddleX = 0;
        }
        if(e->key()==Qt::Key_Right && !victory){
            if(paddleX <= winLength - paddleWidth)
                paddleX+=20;
            else
                paddleX = winLength - paddleWidth;
        }
        //IF VICTORIOUS MOVE ON TO LEVEL 2 AFTER PRESSING A KEY
        if(victory)
        {
            level1 = false;
            level2 = true;
            //rows = 1; columns = 2;  //for demonstration purposes
            rows = 3; columns = 5;
            blockLength = (winLength-20)/(columns);
            blockHeight = 40;
            //THE STATUS IS INITIALIZED TO 1
            blockStatus = std::vector<int>(columns,1); //this will be constantly updated
            //The paddle location is set and it becomes a little longer
            paddleWidth = 170;
            paddleX = winLength/2 - paddleWidth/2;
            paddleY = winHeight - 35;
            //NUMBER OF LIVES IS UNCHANGED
            //set the location of ball
            ballX = winLength/2; ballY = winHeight - 70; ballH = 0; ballV = 2;
            //the game is not on
            gameOn = false, victory = false;
        }
        repaint();
    }
    //CONTROLS FOR LEVEL2
    else if(level2)
    {
        if(e->key()==Qt::Key_Space && !victory){
            gameOn = true;
            ballV = -3;
        }
        if(e->key()==Qt::Key_Left && !victory){
            if(paddleX >=30)
                paddleX-=30;
            else
                paddleX = 0;
        }
        if(e->key()==Qt::Key_Right && !victory){
            if(paddleX <= winLength - paddleWidth - 30)
                paddleX+=30;
            else
                paddleX = winLength - paddleWidth;
        }
        //IF VICTORIOUS MOVE ON TO LEVEL 3
        if(victory)
        {
            level2 = false;
            level3 = true;
            //rows = 2; columns = 2; //for demonstration purposes
            rows = 3; columns = 5;
            blockLength = (winLength-20)/(columns);
            blockHeight = 40;
            //THE STATUS IS INITIALIZED TO 1
            blockStatus = std::vector<int>(columns,2); //this will be constantly updated
            //The paddle location is set and it becomes a little longer
            paddleWidth = 150;
            paddleX = winLength/2 - paddleWidth/2;
            paddleY = winHeight - 35;
            //NUMBER OF LIVES IS UNCHANGED
            //lives = 5;
            //set the location of ball
            ballX = winLength/2; ballY = winHeight - 70; ballH = 0; ballV = 3;
            //the game is not on
            gameOn = false, victory = false;
        }
        repaint();
    }

    //CONTROLS FOR LEVEL3
    else if(level3)
    {
        if(e->key()==Qt::Key_Space && !victory){
            gameOn = true;
            ballV = -5;
        }
        if(e->key()==Qt::Key_Left && !victory){
            if(paddleX >=30)
                paddleX-=30;
            else
                paddleX = 0;
        }
        if(e->key()==Qt::Key_Right && !victory){
            if(paddleX <= winLength - paddleWidth)
                paddleX+=30;
            else
                paddleX = winLength - paddleWidth;
        }
        if(victory)
        {
            victory = false;
            finish = true;
        }
        repaint();
    }

    //CONTROLS FOR THE FINISH SCREEN
    else if(finish){
        finish = false;
        title = true; //return to the title
    }
}



void MainWindow::instructions(){
    QWidget* w = this->centralWidget();
    //delete the current central widget by setting it's parent to null
    w->setParent(nullptr);
    Level1* level = new Level1(this);
    this->setCentralWidget(level);

}



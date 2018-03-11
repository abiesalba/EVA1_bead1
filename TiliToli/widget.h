#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QLabel>
#include <QString>
#include <QFrame>
#include <QVector>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include "traveller.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void startNewGame();
    void plusButtonClicked();

private:
    QVBoxLayout *layout, *newGamePanelLayout;
    QHBoxLayout *upperPanelLayout;
    QRadioButton *newGameEasy, *newGameMedium, *newGameHard;
    QGridLayout *gameLayout, *pointsPanelLayout;
    QFrame *newGamePanel, *upperPanel, *pointsPanel, *gamePanel;
    QLabel *newGameLabel, *pointsLabel, *elapsedTimeLabel;

    QPushButton *newGame;

    //-----Játékfelület-----

    QHBoxLayout *newGameLayout, *speedLayout;
    QVBoxLayout *thisWatersideLayout, *bridgeLayout, *otherWatersideLayout;
    QGridLayout *selectGoPanel;
    QLabel *thisWatersideText, *actSpeedText, *headCountText, *bridgeText, *otherWatersideText;

    //To get the actual members of the group who will go:
    QLabel *actYoungHeadcountLCD, *actMiddleHeadcountLCD, *actOldHeadcountLCD, *actSpeedLCD;

    //The current members of this waterside:
    QLabel *currentYoungHeadcountLCD, *currentMiddleHeadcountLCD, *currentOldHeadcountLCD;

    //Images:
    QLabel *youngTravellerIMG, *middleTravellerIMG, *oldTravellerIMG, *bridgeIMG, *tentIMG;

    //Set the group ho will go:
    QPushButton *plusYoung, *plusMiddle, *plusOld, *goOtherSide;

    //Members of the other waterside:
    QLabel *finishText, *finishNum;

    //Get who have the lamp:
    QRadioButton * lampAtYoung, *lampAtMiddle, *lampAtOld;



    //-----Storaged values------

    int elapsedTime, currentYoungHeadcount, currentMiddleHeadcount, currentOldHeadcount;
    int currentHeadcount(){
        return currentYoungHeadcount+currentMiddleHeadcount+currentOldHeadcount;
    }
    int finishedHeadcount, startHeadCount;

    //Egy lépéshez
    int actYoungHeadcount, actMiddleHeadcount, actOldHeadcount;

    //void updateTable(int);
    bool isGameOver();

    //Compue the actual speed of the group:
    int actSpeed(){
        int speed =0;
        if(actYoungHeadcount > 0) speed = 3;
        if(actMiddleHeadcount > 0) speed = 6;
        if(actOldHeadcount > 0) speed = 9;
        return speed;
    }



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

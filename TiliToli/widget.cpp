#include "widget.h"
#include "ui_widget.h"
#include <cstdlib>
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(trUtf8("Átkelés a hídon"));

    // A fo frame letrehozasa
    layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize); // fix meretu ablak


    upperPanel = new QFrame(this);  // az informaciokat tartalmazo felso panel

    newGamePanel = new QFrame(upperPanel); // az uj jatek kezdeseert felelos resz

    newGameLabel = new QLabel(newGamePanel);    // tablameret felirat
    newGameLabel->setText("Kereskedők:");

    // tablameretek radiogombjai
    newGameEasy = new QRadioButton(newGamePanel);
    newGameEasy->setText("2 fiatal, 2 középkorú, 1 idős");
    newGameEasy->setChecked(true);
    newGameMedium = new QRadioButton(newGamePanel);
    newGameMedium->setText("4 fiatal, 3 középkorú, 3 idős");
    newGameHard = new QRadioButton(newGamePanel);
    newGameHard->setText("5 fiatal, 5 középkorú, 5 idős");
    newGame = new QPushButton("Új játék");
    newGame->setFixedSize(75, 30);

    newGamePanelLayout = new QVBoxLayout();
    newGamePanelLayout->addWidget(newGameLabel);
    newGamePanelLayout->addWidget(newGameEasy);
    newGamePanelLayout->addWidget(newGameMedium);
    newGamePanelLayout->addWidget(newGameHard);
    newGamePanelLayout->addWidget(newGame);

    newGamePanel->setLayout(newGamePanelLayout);

    // az időt kijelző panel
    pointsPanel = new QFrame(upperPanel);
    pointsLabel = new QLabel(pointsPanel);
    pointsLabel->setText("Eltelt idő:");

    elapsedTimeLabel = new QLabel(pointsPanel);
    elapsedTimeLabel->setStyleSheet("QLabel { color : rgb(0,0,70); }");
    elapsedTimeLabel->setText("0");
    elapsedTimeLabel->setFont(QFont("Tahoma", 32));



    pointsPanelLayout = new QGridLayout();
    pointsPanelLayout->addWidget(pointsLabel, 0, 0);
    pointsPanelLayout->addWidget(elapsedTimeLabel, 1, 0);
    pointsPanel->setLayout(pointsPanelLayout);


    // az uj jatek kezdeseert es a pontok kijelzeseert felelos panelek elhelyezese

    upperPanelLayout = new QHBoxLayout();
    upperPanelLayout->addWidget(newGamePanel);
    upperPanelLayout->addWidget(pointsPanel);
    upperPanel->setLayout(upperPanelLayout);


    // a jatekot vezerlo negyzetracs letrehozasa

    gamePanel = new QFrame(this);
    gameLayout = new QGridLayout();
    gamePanel->setLayout(gameLayout);

    // a felso panel es a jatek vezerlo paneljenek hozzaadasa az ablakhoz

    layout->addWidget(upperPanel);
    layout->addWidget(gamePanel);
    setLayout(layout);

    // kapcsolatok

    connect(newGame, SIGNAL(clicked()), this, SLOT(startNewGame()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::startNewGame()
{
    // kezdeti ertekek beallitasa
    elapsedTime = 0;
    elapsedTimeLabel->setText(QString::number(elapsedTime));
    actYoungHeadcount = 0;
    actMiddleHeadcount = 0;
    actOldHeadcount = 0;
    finishedHeadcount = 0;

    // létszámok meghatarozasa
    if (newGameEasy->isChecked()){
        currentYoungHeadcount = 2;
        currentMiddleHeadcount = 2;
        currentOldHeadcount = 1;
        startHeadCount = 5;
        finishedHeadcount = 0;
    }
    else if (newGameMedium->isChecked()){
        currentYoungHeadcount = 4;
        currentMiddleHeadcount = 3;
        currentOldHeadcount = 3;
        startHeadCount = 10;
        finishedHeadcount = 0;
    }
    else{
        currentYoungHeadcount = 5;
        currentMiddleHeadcount = 5;
        currentOldHeadcount = 5;
        startHeadCount = 15;
        finishedHeadcount = 0;
    }



    //felület felépítése

    newGameLayout = new QHBoxLayout; //egész játékfelület
    thisWatersideLayout = new QVBoxLayout; //ez a part
    bridgeLayout = new QVBoxLayout; //hid
    otherWatersideLayout = new QVBoxLayout; //túlpart
    layout->addLayout(newGameLayout);

    newGameLayout->addLayout(thisWatersideLayout);
    newGameLayout->addLayout(bridgeLayout);
    newGameLayout->addLayout(otherWatersideLayout);

    //Ez a part:
    thisWatersideText = new QLabel;
    thisWatersideText->setText("Vízpart");
    thisWatersideText->setFont(QFont("Tahoma", 20));
    thisWatersideLayout->addWidget(thisWatersideText);

    speedLayout = new QHBoxLayout;
    thisWatersideLayout->addLayout(speedLayout);

    actSpeedText = new QLabel;
    actSpeedText->setText("Sebesség:");
    //actSpeedText->setFont(QFont("Tahoma", 14));
    speedLayout->addWidget(actSpeedText);

    actSpeedLCD = new QLabel;
    actSpeedLCD->setText("0");
    speedLayout->addWidget(actSpeedLCD);

    headCountText = new QLabel;
    headCountText->setText("Átmenők kiválasztása:");
    thisWatersideLayout->addWidget(headCountText);

    //Túlpartra induló csapat kiválasztásához:
    selectGoPanel = new QGridLayout;
    thisWatersideLayout->addLayout(selectGoPanel);

    actYoungHeadcountLCD = new QLabel;
    actYoungHeadcountLCD->setText(QString::number(actYoungHeadcount));
    selectGoPanel->addWidget(actYoungHeadcountLCD,0,0);

    actMiddleHeadcountLCD = new QLabel;
    actMiddleHeadcountLCD->setText(QString::number(actMiddleHeadcount));
    selectGoPanel->addWidget(actMiddleHeadcountLCD,0,1);

    actOldHeadcountLCD = new QLabel;
    actOldHeadcountLCD->setText(QString::number(actOldHeadcount));
    selectGoPanel->addWidget(actOldHeadcountLCD,0,2);

    youngTravellerIMG = new QLabel;
    //add the image
    youngTravellerIMG->setText("Fiatal");
    selectGoPanel->addWidget(youngTravellerIMG,1,0);

    middleTravellerIMG = new QLabel;
    //add image
    middleTravellerIMG->setText("Középkorú");
    selectGoPanel->addWidget(middleTravellerIMG,1,1);

    oldTravellerIMG = new QLabel;
    //add image
    oldTravellerIMG->setText("Idős");
    selectGoPanel->addWidget(oldTravellerIMG, 1, 2);

    //Pushbuttons:
    plusYoung = new QPushButton;
    plusYoung->setText("+");
    plusYoung->setObjectName("Young");
    selectGoPanel->addWidget(plusYoung, 2, 0);

    plusMiddle = new QPushButton;
    plusMiddle->setText("+");
    plusMiddle->setObjectName("Middle");
    selectGoPanel->addWidget(plusMiddle,2,1);

    plusOld = new QPushButton;
    plusOld->setText("+");
    plusOld->setObjectName("Old");
    selectGoPanel->addWidget(plusOld,2,2);

    //Eseménykezelők bekötése:
    connect(plusYoung, SIGNAL(clicked()), this, SLOT(plusButtonClicked()));
    connect(plusMiddle, SIGNAL(clicked()), this, SLOT(plusButtonClicked()));
    connect(plusOld, SIGNAL(clicked()), this, SLOT(plusButtonClicked()));

    //Radio buttons:

    lampAtYoung = new QRadioButton;
    lampAtYoung->setChecked(true);
    selectGoPanel->addWidget(lampAtYoung,3, 0);

    lampAtMiddle = new QRadioButton;
    selectGoPanel->addWidget(lampAtMiddle, 3, 1);

    lampAtOld = new QRadioButton;
    selectGoPanel->addWidget(lampAtOld, 3, 2);

    //Headcounts:
    currentYoungHeadcountLCD = new QLabel;
    currentYoungHeadcountLCD->setText(QString::number(currentYoungHeadcount));
    selectGoPanel->addWidget(currentYoungHeadcountLCD, 4, 0);

    currentMiddleHeadcountLCD = new QLabel;
    currentMiddleHeadcountLCD->setText(QString::number(currentMiddleHeadcount));
    selectGoPanel->addWidget(currentMiddleHeadcountLCD, 4,1);

    currentOldHeadcountLCD = new QLabel;
    currentOldHeadcountLCD->setText(QString::number(currentOldHeadcount));
    selectGoPanel->addWidget(currentOldHeadcountLCD, 4, 2);

    //Híd:
    bridgeText = new QLabel;
    bridgeText->setText("Híd");
    bridgeText->setFont(QFont("Tahoma", 20));
    bridgeLayout->addWidget(bridgeText);

    bridgeIMG = new QLabel;
    bridgeIMG->setText("Ez egy híd");
    bridgeLayout->addWidget(bridgeIMG);

    goOtherSide = new QPushButton;
    goOtherSide->setText("Go!");
    bridgeLayout->addWidget(goOtherSide);

    //Túlpart:
    otherWatersideText = new QLabel;
    otherWatersideText->setText("Túlpart");
    otherWatersideText->setFont(QFont("Tahoma", 20));
    otherWatersideLayout->addWidget(otherWatersideText);

    tentIMG = new QLabel;
    //add img
    tentIMG->setText("Sátor");
    otherWatersideLayout->addWidget(tentIMG);

    finishText = new QLabel;
    finishText->setText("Átjutottak:");
    otherWatersideLayout->addWidget(finishText);

    finishNum = new QLabel;
    finishNum->setText("0");
    otherWatersideLayout->addWidget(finishNum);


    // elozo racs torlese
    /*foreach(Traveller* tile, buttonGrid)
    {
        gameLayout->removeWidget(tile);
        delete tile;
    }
    buttonGrid.clear();*/

}
void Widget::plusButtonClicked()
{
    //Which plus button was clicked?
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();

    bool plusAble = (actYoungHeadcount + actMiddleHeadcount + actOldHeadcount) < 3;

    if(senderObjName == "Young" && plusAble){
        actYoungHeadcount++;
        actYoungHeadcountLCD->setText(QString::number(actYoungHeadcount));
    }
    else if(senderObjName == "Middle" && plusAble){
        actMiddleHeadcount++;
        actMiddleHeadcountLCD->setText(QString::number(actMiddleHeadcount));
    }
    else if(senderObjName == "Old" && plusAble){
        actOldHeadcount++;
        actOldHeadcountLCD->setText(QString::number(actOldHeadcount));
    }

    actSpeedLCD->setText(QString::number(actSpeed()));
    //elapsedTime++; //nem itt kell majd állítani
    elapsedTimeLabel->setText(QString::number(elapsedTime));
    if(isGameOver()){
        QMessageBox::information(this, "Nyertél!", QString::number(elapsedTime)+" idő alatt oldottad meg a feladványt.");
        startNewGame();
    }
}

bool Widget::isGameOver()
{
    bool endGame = false;

     return endGame;
}



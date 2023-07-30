#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

//Starting connection level
int connectionValue = 1;

//Starting minutes and seconds values for the sessions
int secondsValue = 0;
int secondsValue45 = 0;
int secondsValueUser = 0;
int minutesValue20 = 20;
int minutesValue45 = 45;
int minutesValueUser = 0;

//Starting sessions at the off value
bool sessionRunning = false;
bool sessionRunning45 = false;
bool sessionRunningUser = false;
bool sessionLoaded = false;

bool connected = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QTimer that keeps track of the three sessions
    updateClock = new QTimer(this);
    connect(updateClock, SIGNAL(timeout()), this, SLOT(update()));
    connect(updateClock, SIGNAL(timeout()), this, SLOT(update45()));
    connect(updateClock, SIGNAL(timeout()), this, SLOT(updateUser()));
    updateClock->start(1000);

    //Makes the dials behind the session iconcs invisible
    ui->dial->setVisible(false);
    ui->secondsDial->setVisible(false);

    ui->dial45min->setVisible(false);
    ui->dial45sec->setVisible(false);

    ui->dialUser->setVisible(false);
    ui->secondsDialUser->setVisible(false);

    // Starting state of the application is off
    powerState = false;
    changePowerState();

    deviceControl.replaceBattery();

    //Connects the power UI button to the powerChange function
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerChange);

    //Connects the record UI button to the recButton function
    connect(ui->recordButton, &QPushButton::released,this,&MainWindow::recButton_clicked);
    //connects the load UI button to the loadButton function
    connect(ui->loadButton,&QPushButton::released,this,&MainWindow::loadButton_clicked);

    connect(ui->upIntensity_2,&QPushButton::released,this,&MainWindow::upIntensity_clicked);

    connect(ui->downIntensity_2,&QPushButton::released,this,&MainWindow::downIntensity_clicked);

    connect(ui->replaceBattery,&QPushButton::released,this,&MainWindow::replaceBattery);

    /*----------------------------------------------------------------------------------------
    The below are the images used for the application. Each are saved as resource files
    ---------------------------------------------------------------------------------------- */

    QPixmap pix(":/resources/img/audioInput.JPG");
    int w = ui->audioInput->width();
    int h = ui->audioInput->height();
    ui->audioInput->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix2(":/resources/img/cesOutput.JPG");
    int wcesOutput = ui->cesOutput->width();
    int hcesOutput = ui->cesOutput->height();
    ui->cesOutput->setPixmap(pix2.scaled(wcesOutput,hcesOutput,Qt::KeepAspectRatio));

    QPixmap pix3(":/resources/img/delta.JPG");
    int wdelta = ui->delta->width();
    int hdelta = ui->delta->height();
    ui->delta->setPixmap(pix3.scaled(wdelta,hdelta,Qt::KeepAspectRatio));


    QPixmap pix5(":/resources/img/100Hz.JPG");
    int w100Hz = ui->hundredHZ->width();
    int h100Hz = ui->hundredHZ->height();
    ui->hundredHZ->setPixmap(pix5.scaled(w100Hz,h100Hz,Qt::KeepAspectRatio));

    QPixmap pix6(":/resources/img/intensity.JPG");
    int wIntensity = ui->intensity->width();
    int hIntensity = ui->intensity->height();
    ui->intensity->setPixmap(pix6.scaled(wIntensity,hIntensity,Qt::KeepAspectRatio));

    QPixmap pix7(":/resources/img/20MinSession.JPG");
    int wmin20 = ui->min20->width();
    int hmin20 = ui->min20->height();
    ui->min20->setPixmap(pix7.scaled(wmin20,hmin20,Qt::KeepAspectRatio));



    QPixmap pix9(":/resources/img/45MinSession.JPG");
    int wmin45 = ui->min45->width();
    int hmin45 = ui->min45->height();
    ui->min45->setPixmap(pix9.scaled(wmin45,hmin45,Qt::KeepAspectRatio));

    QPixmap pix10(":/resources/img/UserDesignedSession.JPG");
    int wudSession = ui->udSession->width();
    int hudSession = ui->udSession->height();
    ui->udSession->setPixmap(pix10.scaled(wudSession,hudSession,Qt::KeepAspectRatio));

    QPixmap pix11(":/resources/img/startSession.JPG");
    int wsessionStart = ui->sessionStart->width();
    int hsessionStart = ui->sessionStart->height();
    ui->sessionStart->setPixmap(pix11.scaled(wsessionStart,hsessionStart,Qt::KeepAspectRatio));

    QPixmap pix12(":/resources/img/alpha.JPG");
    int walpha = ui->alpha->width();
    int halpha = ui->alpha->height();
    ui->alpha->setPixmap(pix12.scaled(walpha,halpha,Qt::KeepAspectRatio));

    QPixmap pix14(":/resources/img/MeT.JPG");
    int wMET = ui->MET->width();
    int hMET = ui->MET->height();
    ui->MET->setPixmap(pix14.scaled(wMET,hMET,Qt::KeepAspectRatio));

    ui->powerButton->setIcon(QIcon("://resources/img/powerOn.JPG"));


    QIcon upArrow("://resources/img/Up.JPG");
    QIcon downArrow("://resources/img/down.JPG");


    ui->upIntensity_2->setIcon(upArrow);
    ui->upIntensity_2->setIconSize(QSize(60,60));
    ui->downIntensity_2->setIcon(downArrow);
    ui->downIntensity_2->setIconSize(QSize(60,60));
}

/*----------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------- */

MainWindow::~MainWindow()
{
    delete ui;
}

//Switches between enabling and disabling buttons when the power state changes
void MainWindow::changePowerState() {
    ui->start->setEnabled(powerState);
    ui->start45->setEnabled(powerState);
    ui->startUser->setEnabled(powerState);
    ui->replaceBattery->setEnabled(powerState);
    ui->connctionDial->setEnabled(powerState);
    ui->sessionNumberSpinBox->setEnabled(powerState);
    ui->intensitySpinBox->setEnabled(powerState);
    ui->batterySpinBox->setEnabled(powerState);
    ui->reset->setEnabled(powerState);
    ui->upIntensity_2->setEnabled(powerState);
    ui->downIntensity_2->setEnabled(powerState);
    ui->recordButton->setEnabled(powerState);
    ui->loadButton->setEnabled(powerState);
    ui->recordDial->setEnabled(powerState);
    ui->textEdit->setEnabled(powerState);

}


void MainWindow::powerChange() {

    if (ui->batterySpinBox->value() > 0) {
        powerState  = !powerState;
        changePowerState();
    }

    if (powerState == false) {
        ui->powerButton->setText("OFF");
        ui->powerButton->setStyleSheet("* { color: red }");

        ui->textEdit->setText("");

        ui->dial->setValue(20);
        ui->secondsDial->setValue(0);
        ui->start->setText("START");
        ui->start->setStyleSheet("* { color: green }");

        ui->dial45min->setValue(45);
        ui->dial45sec->setValue(0);
        ui->start45->setText("START");
        ui->start45->setStyleSheet("* { color: green }");

        ui->dialUser->setValue(0);
        ui->secondsDialUser->setValue(0);
        ui->startUser->setText("START");
        ui->startUser->setStyleSheet("* { color: green }");

        sessionRunning = false;
        sessionRunning45 = false;
        sessionRunningUser = false;

    } else {
        ui->powerButton->setText("ON");
        ui->powerButton->setStyleSheet("* { color: green }");
    }
}



void MainWindow::replaceBattery() {
    deviceControl.replaceBattery();
    ui->batteryBar->setValue(10);
    ui->batterySpinBox->setValue(deviceControl.getPowerLevel()/18);
    on_reset_clicked();
    ui->start->setEnabled(true);
    ui->start45->setEnabled(true);
    ui->startUser->setEnabled(true);
    ui->reset->setEnabled(true);
}

void MainWindow::batteryDecay(){

    int simIntens = ui->intensitySpinBox->value();
    if(simIntens == 0){
        //account for the zero
        simIntens = 1;
    }
    int updateCharge = deviceControl.getPowerLevel();
    if(updateCharge <= 250){

        on_reset_clicked();
        ui->start->setEnabled(false);
        ui->start45->setEnabled(false);
        ui->startUser->setEnabled(false);
        ui->reset->setEnabled(false);

    }

    updateCharge = updateCharge - (simIntens * 0.05);
    QString test = QString::number(updateCharge) + "\n";
    qDebug(test.toLatin1());
    deviceControl.setPowerLevel(updateCharge);
    ui->batteryBar->setValue(deviceControl.getPowerLevel()/180);
    ui->batterySpinBox->setValue(deviceControl.getPowerLevel()/18);

}


/*----------------------------------------------------------------------------------------
The below are 3 update functions that initiate timers for the 20 minute, 45 minute
and User Designated sessions
---------------------------------------------------------------------------------------- */


//The standard 20 minute session
void MainWindow::update() {
    if (sessionRunning) {
        if (secondsValue > 0) {
            --secondsValue;
            ui->secondsDial->setValue(secondsValue);
            on_secondsDial_valueChanged(secondsValue);
        } else if (minutesValue20 > 0) {
            secondsValue = 59;
            ui->secondsDial->setValue(secondsValue);
            on_secondsDial_valueChanged(secondsValue);
            --minutesValue20;
            ui->dial->setValue(minutesValue20);
            on_dial_valueChanged(minutesValue20);
        } else {
            secondsValue = 59;
            ui->secondsDial->setValue(secondsValue);
            on_secondsDial_valueChanged(secondsValue);
            minutesValue20 = 59;
            ui->dial->setValue(minutesValue20);
            on_dial_valueChanged(minutesValue20);

        }

    }
}

//45 minute session
void MainWindow::update45() {
    if (sessionRunning45) {
        if (secondsValue45 > 0) {
            --secondsValue45;
            ui->dial45sec->setValue(secondsValue45);
            on_dial45sec_valueChanged(secondsValue45);
        } else if (minutesValue45 > 0) {
            secondsValue45 = 59;
            ui->dial45sec->setValue(secondsValue45);
            on_dial45sec_valueChanged(secondsValue45);
            --minutesValue45;
            ui->dial45min->setValue(minutesValue45);
            on_dial45min_valueChanged(minutesValue45);
        } else {
            secondsValue45 = 59;
            ui->dial45sec->setValue(secondsValue45);
            on_dial45sec_valueChanged(secondsValue45);
            minutesValue45 = 59;
            ui->dial45min->setValue(minutesValue45);
            on_dial45min_valueChanged(minutesValue45);

        }

    }
}

//User Designated session length
void MainWindow::updateUser() {
    if (sessionRunningUser) {
        if (secondsValueUser > 0) {
            --secondsValueUser;
            ui->secondsDialUser->setValue(secondsValueUser);
            on_secondsDialUser_valueChanged(secondsValueUser);
        } else if (minutesValueUser > 0) {
            secondsValueUser = 59;
            ui->secondsDialUser->setValue(secondsValueUser);
            on_secondsDialUser_valueChanged(secondsValueUser);
            --minutesValueUser;
            ui->dialUser->setValue(minutesValueUser);
            on_dialUser_valueChanged(minutesValueUser);
        } else {
            secondsValueUser = 59;
            ui->secondsDialUser->setValue(secondsValueUser);
            on_secondsDialUser_valueChanged(secondsValueUser);
            minutesValueUser = 59;
            ui->dialUser->setValue(minutesValueUser);
            on_dialUser_valueChanged(minutesValueUser);

        }

    }

}


/*----------------------------------------------------------------------------------------
The below are the private slots implemented
---------------------------------------------------------------------------------------- */

//minutes dial for the 20 minutes session
void MainWindow::on_dial_valueChanged(int dialVal)
{
    minutesValue20 = dialVal;
    if (minutesValue20 >= 10) {
        ui->minutes->setText(QString::number(minutesValue20));
    } else {
        ui->minutes->setText('0'+QString::number(minutesValue20));
    }
}

//minutes dial for the 45 minutes session
void MainWindow::on_dial45min_valueChanged(int dialVal)
{
    minutesValue45 = dialVal;
    if (minutesValue45 >= 10) {
        ui->minutes45->setText(QString::number(minutesValue45));
    } else {
        ui->minutes45->setText('0'+QString::number(minutesValue45));
    }
}

//minutes dial for the User Designated session
void MainWindow::on_dialUser_valueChanged(int dialVal)
{
    minutesValueUser = dialVal;
    if (minutesValueUser >= 0) {
        ui->minutesUser->setText(QString::number(minutesValueUser));
    } else {
        ui->minutesUser->setText('0'+QString::number(minutesValueUser));
    }
}

//seconds dial for the 20 minute session
void MainWindow::on_secondsDial_valueChanged(int dialVal)
{
    secondsValue = dialVal;
    if (secondsValue >= 10) {
        ui->seconds->setText(QString::number(secondsValue));
    } else {
        ui->seconds->setText('0'+QString::number(secondsValue));
    }

   batteryDecay();
}

//seconds dial for the 45 minute session
void MainWindow::on_dial45sec_valueChanged(int dialVal)
{
    secondsValue45 = dialVal;
    if (secondsValue45 >= 10) {
        ui->seconds45->setText(QString::number(secondsValue45));
    } else {
        ui->seconds45->setText('0'+QString::number(secondsValue45));
    }

    batteryDecay();
}

//seconds dial for the User Generated session
void MainWindow::on_secondsDialUser_valueChanged(int dialVal)
{
    secondsValueUser = dialVal;
    if (secondsValueUser >= 0) {
        ui->secondsUser->setText(QString::number(secondsValueUser));
    } else {
        ui->secondsUser->setText('0'+QString::number(secondsValueUser));
    }

   batteryDecay();
}

//Dial for managing connection.
void MainWindow::on_connctionDial_valueChanged(int dialVal)
{
    connectionValue = dialVal;
    if (connectionValue >= 6 && powerState == true && sessionRunning == true) {
        connected = false;
        powerState = !powerState;
        ui->connctionDial->setValue(0);
        ui->powerButton->setText("OFF");
        ui->powerButton->setStyleSheet("* { color: red }");
        changePowerState();
        on_start_clicked();
    }

    if (connectionValue >= 6 && powerState == true && sessionRunning45 == true) {
        connected = false;
        powerState = !powerState;
        ui->connctionDial->setValue(0);
        ui->powerButton->setText("OFF");
        ui->powerButton->setStyleSheet("* { color: red }");
        changePowerState();
        on_start45_clicked();
    }

    if (connectionValue >= 6 && powerState == true && sessionRunningUser == true) {
        connected = false;
        powerState = !powerState;
        ui->connctionDial->setValue(0);
        ui->powerButton->setText("OFF");
        ui->powerButton->setStyleSheet("* { color: red }");
        changePowerState();
        on_startUser_clicked();
    }

}

//Start button for 20 minute session
void MainWindow::on_start_clicked()
{
    if (sessionRunning == false) {
        sessionRunning = true;
        ui->start->setText("STOP");
        ui->start->setStyleSheet("* { color: red }");
        sessionRunning45 = false;
        sessionRunningUser = false;
        ui->start45->setEnabled(!powerState);
        ui->startUser->setEnabled(!powerState);

        int intensityLev = ui->intensitySpinBox->value();
        int sessionType = ui->sessionNumberSpinBox->value();

        QString sessionL = "Length: 20mins\n";

        QString sessionI = "Intensity:" + QString::number(intensityLev) + "\n";
        QString sessionT;

        if(sessionType == 1){
            sessionT = "Type: MET\n";
        } else if(sessionType == 2) {
            sessionT = "Type: Sub-Delta\n";
        } else if(sessionType == 3) {
            sessionT = "Type: Delta\n";
        }else if(sessionType == 4) {
            sessionT = "Type: Theta\n";
        }else if(sessionType == 5) {
            sessionT = "Type: Alpha\n";
        }else if(sessionType == 6) {
            sessionT = "Type: SMR\n";
        }else if(sessionType == 7) {
            sessionT = "Type: Beta\n";
        }else if(sessionType == 8) {
            sessionT = "Type: 100 Hz\n";
        }else{
            sessionT = "";
        }

        QString combine = sessionT+" " + sessionL+ " " + sessionI;
        ui->textEdit->setText(combine);

    }
    else {
        sessionRunning = false;
        ui->start->setText("START");
        ui->start->setStyleSheet("* { color: green }");
        ui->start45->setEnabled(powerState);
        ui->startUser->setEnabled(powerState);

    }
}

//Start button for 45 minute session
void MainWindow::on_start45_clicked()
{
    if (sessionRunning45 == false) {


        int intensityLev = ui->intensitySpinBox->value();
        int sessionType = ui->sessionNumberSpinBox->value();

        QString sessionL = "Length: 45mins\n";

        QString sessionI = "Intensity:" + QString::number(intensityLev) + "\n";
        QString sessionT;

        if(sessionType == 1){
            sessionT = "Type: MET\n";
        } else if(sessionType == 2) {
            sessionT = "Type: Sub-Delta\n";
        } else if(sessionType == 3) {
            sessionT = "Type: Delta\n";
        }else if(sessionType == 4) {
            sessionT = "Type: Theta\n";
        }else if(sessionType == 5) {
            sessionT = "Type: Alpha\n";
        }else if(sessionType == 6) {
            sessionT = "Type: SMR\n";
        }else if(sessionType == 7) {
            sessionT = "Type: Beta\n";
        }else if(sessionType == 8) {
            sessionT = "Type: 100 Hz\n";
        }else{
            sessionT = "";
        }

        QString combine = sessionT+" " + sessionL+ " " + sessionI;
        ui->textEdit->setText(combine);



        sessionRunning45 = true;
        ui->start45->setText("STOP");
        ui->start45->setStyleSheet("* { color: red }");
        sessionRunning = false;
        sessionRunningUser = false;
        ui->start->setEnabled(!powerState);
        ui->startUser->setEnabled(!powerState);
    }
    else {
        sessionRunning45 = false;
        ui->start45->setText("START");
        ui->start45->setStyleSheet("* { color: green }");
        ui->start->setEnabled(powerState);
        ui->startUser->setEnabled(powerState);
    }
}

//Start button for User Designated session
void MainWindow::on_startUser_clicked()
{

    if(sessionLoaded == true){

    if (sessionRunningUser == false) {


        sessionRunningUser = true;
        ui->startUser->setText("STOP");
        ui->startUser->setStyleSheet("* { color: red }");
        sessionRunning = false;
        sessionRunning45 = false;
        ui->start->setEnabled(!powerState);
        ui->start45->setEnabled(!powerState);
    }
    else {
        sessionRunningUser = false;
        ui->startUser->setText("START");
        ui->startUser->setStyleSheet("* { color: green }");
        ui->start->setEnabled(powerState);
        ui->start45->setEnabled(powerState);
    }
    } else{
        sessionRunningUser = false;
        ui->startUser->setText("NOTHING LOADED");
        ui->startUser->setStyleSheet("* { color: green }");
        ui->start->setEnabled(powerState);
        ui->start45->setEnabled(powerState);

    }

}

//Resets the sessions to their starting point
void MainWindow::on_reset_clicked()
{
    sessionRunning=false;
    sessionRunning45=false;
    sessionRunningUser=false;

    ui->dial->setValue(20);
    ui->secondsDial->setValue(0);
    ui->start->setText("START/STOP");
    ui->start->setStyleSheet("* { color: black }");
    ui->start->setEnabled(true);

    ui->dial45min->setValue(45);
    ui->dial45sec->setValue(0);
    ui->start45->setText("START/STOP");
    ui->start45->setStyleSheet("* { color: black }");
    ui->start45->setEnabled(true);

    ui->dialUser->setValue(0);
    ui->secondsDialUser->setValue(0);
    ui->startUser->setText("START/STOP");
    sessionLoaded=false; //reset loaded
    ui->startUser->setStyleSheet("* { color: black }");
    ui->startUser->setEnabled(true);

    ui->textEdit->setText("");
}


void MainWindow::recButton_clicked(){
    int dialValue = ui->recordDial->value();
    int intensityValue = ui->intensitySpinBox->value();
    int typeValue = ui->sessionNumberSpinBox->value();
    int sessionLength;
    if(sessionRunning == true){
        sessionLength = 20;
    }else if(sessionRunning45 == true){
        sessionLength = 45;
    }else{
        sessionLength = 20;
    }

    //stores the value of the session
    deviceControl.saveSession(sessionLength,typeValue,intensityValue,dialValue);



}

void MainWindow::loadButton_clicked(){
    sessionLoaded = true;
    int dialValue = ui->recordDial->value();
    int intensityValue = deviceControl.getSessionIntensity(dialValue);
    int typeValue = deviceControl.getSessionType(dialValue);
    int sessionLength = deviceControl.getSessionLength(dialValue);
    QString sessionInfo = deviceControl.getSessionInfo(dialValue);

    ui->intensitySpinBox->setValue(intensityValue);
    ui->sessionNumberSpinBox->setValue(typeValue);
    ui->textEdit->setText(sessionInfo);
    minutesValueUser = sessionLength;
    ui->startUser->setText("START");
    ui->startUser->setStyleSheet("* { color: green }");


}

void MainWindow::recDialValueChanged(int value){
    int dialValue = value;


}

void MainWindow::upIntensity_clicked(){
    int value = ui->intensitySpinBox->value();
    if(value <=9){
        value++;
        ui->intensitySpinBox->setValue(value);
    }


}

void MainWindow::downIntensity_clicked(){
    int val = ui->intensitySpinBox->value();
    if(val >0){
        val = val - 1;
        ui->intensitySpinBox->setValue(val);
    }


}

/*----------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------- */

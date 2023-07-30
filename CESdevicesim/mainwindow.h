#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QListWidget>
#include <QGraphicsView>
#include <QTime>
#include <QStatusBar>
#include <QVector>
#include <QtGlobal>

#include <QDial>
#include <QTimer>

#include <QMainWindow>
#include "control.h"
#include "session.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_secondsDial_valueChanged(int value);
    void on_dial_valueChanged(int);
    void on_start_clicked();
    void update();
    void update45();
    void updateUser();
    void powerChange();

    void on_dial45sec_valueChanged(int value);

    void on_dial45min_valueChanged(int value);

    void on_start45_clicked();

    void on_reset_clicked();

    void on_dialUser_valueChanged(int value);

    void on_secondsDialUser_valueChanged(int value);

    void on_startUser_clicked();

    void on_connctionDial_valueChanged(int value);

    void recDialValueChanged(int value);

    void recButton_clicked();

    void loadButton_clicked();

    void upIntensity_clicked();

    void downIntensity_clicked();

private:
    Ui::MainWindow *ui;
    control deviceControl;
    session* sessionTime;
    QTimer *updateClock;
    bool powerState;

    QString timeString;

    void updateTimer();
    int getPowerLevel();
    void changePowerState();
    void resetConnection();
    void replaceBattery();
    void batteryDecay();
};
#endif // MAINWINDOW_H

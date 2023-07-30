#ifndef CONTROL_H
#define CONTROL_H
#include "connection.h"
#include "power.h"
#include "recorder.h"
#include "sessiondata.h"
#include <iostream>

class control
{
public:
    control();
    void runSession();
    int getPowerLevel();
    int testConnection();
    //there are no setters for the battery and connection because all the user should be able to do is reset the connection and replace the battery
    //which involves clicking the relevant button, there is no need for the user to be able to modify the values directly
    int resetConnection();
    void replaceBattery();
    void drainPower();
    int getSessionLength(int);
    int getSessionIntensity(int);
    int getSessionType(int);
    void saveSession(int,int,int,int);
    QString getSessionInfo(int);
    void setPowerLevel(int);

private:
    connection* deviceConnection;
    power devicePower;
    recorder deviceRecorder;
};

#endif // CONTROL_H

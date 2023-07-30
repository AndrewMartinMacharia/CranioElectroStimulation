#include "control.h"

control::control()
{
   // connection* deviceConnection = new connection();
   // power* devicePower = new power();
    //initialized recorder object
    //we should add a display statement when the device is properly constructed
}

void control::runSession(){
    //this will probably only be really possible to do well when we have the UI stuff properly set up

   // devicePower->setBatteryCharge(devicePower->getBatteryCharge()-1);


}


//These are the ways the window can interact with the connection and power of the device
//There are no setters for the values, but the connection strength/battery level can be obtained and reset
int control::testConnection(){return deviceConnection->testConnection();}

int control::getPowerLevel(){return devicePower.getBatteryCharge();}

void control::setPowerLevel(int s){devicePower.setBatteryCharge(s);}

int control::resetConnection(){return deviceConnection->resetConnection();}

void control::replaceBattery(){devicePower.changeBattery();}

void control::drainPower(){
    int currPower = devicePower.getBatteryCharge() - 1;
    devicePower.setBatteryCharge(currPower);
}

//function gets the sessionlength found at iteration v
int control::getSessionLength(int v){
    return deviceRecorder.getSessionData(v).getSessionLength();
}
//gets the sessionIntensity found at it v
int control::getSessionIntensity(int v){
     return deviceRecorder.getSessionData(v).getSessionIntensity();
}
//gets the session type found at iter v
int control::getSessionType(int v){
    return deviceRecorder.getSessionData(v).getSessionType();
}
//saves the new session at the iter
void control::saveSession(int length, int type, int intensity, int i){

       deviceRecorder.addSession(intensity,length,type,i);

}

QString control::getSessionInfo(int v){
    return deviceRecorder.getSessionData(v).getSessionData();
}

#include "sessiondata.h"

SessionData::SessionData(int sessionLength, int sessionType, int sessionIntensity)
{
    this->sessionLength = sessionLength;
    this->sessionType = sessionType;
    this->sessionIntensity = sessionIntensity;


}

int SessionData::getSessionLength(){
    return sessionLength;
}
int SessionData::getSessionType(){
    return sessionType;
}
int SessionData::getSessionIntensity(){
    return sessionIntensity;
}
void SessionData::setSessionLength(int sessionLength){
    this->sessionLength = sessionLength;
}
void SessionData::setSessionType(int sessionType){
    this->sessionType = sessionType;
}
void SessionData::setSessionIntensity(int sessionIntensity){
    this->sessionIntensity = sessionIntensity;
}
/* for debug
void SessionData::printSessionData(){
    QString sessionL = QString::number(this->sessionLength);
    QString sessionI = QString::number(this->sessionIntensity);
    QString sessionT;

    if(this->sessionType == 1){
        sessionT = "MET";
    } else if(this->sessionType == 2) {
        sessionT = "Sub-Delta";
    } else if(this->sessionType == 3) {
        sessionT = "Delta";
    }else if(this->sessionType == 4) {
        sessionT = "Theta";
    }else if(this->sessionType == 5) {
        sessionT = "Alpha";
    }else if(this->sessionType == 6) {
        sessionT = "SMR";
    }else if(this->sessionType == 7) {
        sessionT = "Beta";
    }else if(this->sessionType == 8) {
        sessionT = "100 Hz";
    }else{
        sessionT = "";
    }



}
*/
QString SessionData::getSessionData(){
    QString sessionL = "Length:" + QString::number(getSessionLength()) + "\n";
    QString sessionI = "Intensity:" + QString::number(getSessionIntensity()) + "\n";
    QString sessionT;

    if(getSessionType() == 1){
        sessionT = "Type: MET\n";
    } else if(getSessionType() == 2) {
        sessionT = "Type: Sub-Delta\n";
    } else if(getSessionType() == 3) {
        sessionT = "Type: Delta\n";
    }else if(getSessionType() == 4) {
        sessionT = "Type: Theta\n";
    }else if(getSessionType() == 5) {
        sessionT = "Type: Alpha\n";
    }else if(getSessionType() == 6) {
        sessionT = "Type: SMR\n";
    }else if(getSessionType() == 7) {
        sessionT = "Type: Beta\n";
    }else if(getSessionType() == 8) {
        sessionT = "Type: 100 Hz\n";
    }else{
        sessionT = "";
    }

    QString combine = sessionT+" " + sessionL+ " " + sessionI;
    return combine;
}

#include "recorder.h"

recorder::recorder()
{

    initalizeVector();

}


void recorder::recordSession(){



}

void recorder::initalizeVector(){
    sessions.resize(10);
    for(int i = 0; i<10;i++){
        SessionData blankData;
        sessions[i] = blankData;
    }
}


SessionData recorder::getSessionData(int i){
    return sessions[i];
}


void recorder::addSession(int intensity, int length, int type, int i){
    SessionData data(length,type,intensity);
    sessions[i] = data;

}
void recorder::removeSession(int i){
    SessionData blankData;
    sessions[i] = blankData;

}

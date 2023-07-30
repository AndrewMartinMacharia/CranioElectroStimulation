#include "session.h"

session::session()
{

}

//getter for sessionTime

int session::getSession20() const {return sessionTime;}
int session::getSessionSeconds() const {return secondsTime;}

//setter for sesstionTime
void session::setSessionTime(int session) {sessionTime = session;}

void session::changeTime20(){setSessionTime(MINUTE20);}

void session::setSessionSeconds(int seconds) {secondsTime = seconds;}

void session::changeSeconds(){setSessionSeconds(SECONDS);}

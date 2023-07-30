#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QString>
class SessionData
{
public:
    SessionData(int=20,int=1,int=1);
    int getSessionLength();
    int getSessionType();
    int getSessionIntensity();
    void setSessionLength(int);
    void setSessionType(int);
    void setSessionIntensity(int);
  //  void printSessionData(); for debug reasons
    QString getSessionData();

private:
    int sessionLength; // 20, 45 , custom mins
    int sessionType; // 1-8 for the set session types
    int sessionIntensity; // 1-8 for the intensity

};

#endif // SESSIONDATA_H

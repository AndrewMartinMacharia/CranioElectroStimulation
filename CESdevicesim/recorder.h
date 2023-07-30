#ifndef RECORDER_H
#define RECORDER_H

#include <QString>
#include <QVector>
#include "sessiondata.h"

class recorder
{

public:
    recorder();
    void recordSession();


    //helpers
    void setSessionData(QString);
    void addSession(int,int,int,int);
    void removeSession(int);
    SessionData getSessionData(int);
    void initalizeVector();


private:

    QVector<SessionData> sessions;
    int numRecordings;

};

#endif // RECORDER_H

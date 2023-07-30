#ifndef CONNECTION_H
#define CONNECTION_H
#define CONNECTIONLEVELS 7
#include "power.h"
#include <stdlib.h>
#include <time.h>

class connection{

private:
    power devicePower;
    bool connectionStatus;
    int connectionInt;
    //moved the getters and setters to the private function, as testConnection is all that needs to be public
    void setConnectionLevel(int);
    int getConnectionLevel() const;

public:
    connection();
    int testConnection();
    int resetConnection();



};

#endif // CONNECTION_H

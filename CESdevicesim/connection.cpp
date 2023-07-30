#include "connection.h"
#include "power.h"

//constructor
connection::connection(){
    this->connectionStatus = false;
    this->connectionInt = 1;

}

//testConnection() -> return 0 if an error is detected (no 9V battery), otherwise return 1
int connection::testConnection(){
    if (devicePower.getBatteryCharge() <= 0){
        return 8;
    } else {
        return getConnectionLevel();
    }
}

//resetConnection -> return 0 if connection cannot be reset, otherwise return 1
int connection::resetConnection(){
    //My thought for this is the reset can be randomized, so a user may need to reset the connection multiple times
    //srand(time(0));
    //Initializes the random number generator then generates the new connection
    //The new connection will be of a value of 1-8, according to the possible levels listed in the manual
    //1-3 (inclusive) indicates the strongest connection, 4-6 moderate, and 7-8 is little/no connection
    //int newConnection = (rand()%CONNECTIONLEVELS) + 1;
    //setConnectionLevel(newConnection);
    connectionInt = 8;
    return connectionInt;
}

//getter for connectionLevel
int connection::getConnectionLevel() const {return connectionInt;}

//setter for connectionLevel
void connection::setConnectionLevel(int connect) {connectionInt = connect;}

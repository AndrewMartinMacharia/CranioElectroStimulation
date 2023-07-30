#ifndef POWER_H
#define POWER_H
#define MAXCHARGE 1800

class power
{
public:
    power();
    void changeBattery();
    int getBatteryCharge() const;
    void setBatteryCharge(int);
private:
    int batteryCharge;
};

#endif // POWER_H


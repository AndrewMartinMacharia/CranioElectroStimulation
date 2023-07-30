#ifndef SESSION_H
#define SESSION_H
#define MINUTE20 20
#define SECONDS 0
#define SECONDS59 59


class session
{
public:
    session();
    void changeTime20();
    void changeSeconds();
    int getSession20() const;
    int getSessionSeconds() const;
    void setSessionTime(int);
    void setSessionSeconds(int);

private:
    int sessionTime;
    int secondsTime;

};

#endif // SESSION_H

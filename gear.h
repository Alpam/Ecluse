#ifndef GEAR_H
#define GEAR_H

#define AMONT 0
#define AVAL 1
#define FERME 2
#define OUVRE 3
#define PANNE 4
#define EN_OUVERTURE 5
#define EN_FERMETURE 6
#define STOP 7
#define ON true
#define OFF false

class Gear // classe abstraite
{
public:
    Gear();
    virtual ~Gear();
    virtual void sendSignal(int signal, int zone) = 0;
    virtual bool open();
    virtual bool close();
    virtual int getState();
    virtual bool getAlarm();
    virtual bool getPanne();
    virtual void putAlarm();
    virtual void disableAlarm();
    virtual void declarePanne();
    virtual void resolvedPanne();

protected:
    int state;
    bool alarm;
    bool panne;
    virtual void switchState(int newState);
    virtual void setAlarm(bool a);
    virtual void setPanne(bool a);
};


#endif // GEAR_H

#ifndef GEAR_H
#define GEAR_H

#define AMONT 0
#define AVAL 1
#define FERME 2
#define OUVRE 3
#define EN_ARRET 4
#define EN_OUVERTURE 5
#define EN_FERMETURE 6
#define ON true
#define OFF false

class Gear // classe abstraite
{
public:
    Gear();
    virtual ~Gear();
    virtual bool open();
    virtual bool close();
    virtual int getState();
    virtual bool getAlarm();
    virtual bool getPanne();
    virtual void putAlarm();
    virtual void disableAlarm();
    virtual void declarePanne();
    virtual void resolvedPanne();
    virtual void arret();
    int state;

protected:
    bool alarm;
    bool panne;
    virtual void switchState(int newState);
    virtual void setAlarm(bool a);
    virtual void setPanne(bool a);
};


#endif // GEAR_H

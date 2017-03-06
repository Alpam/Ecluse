#ifndef GEAR_H
#define GEAR_H

#define FERME 0
#define OUVERT 1
#define PANNE 2
#define EN_OUVERTURE 3
#define EN_FERMETURE 4
#define ON true
#define OFF false

class Gear // classe abstraite
{
public:
    Gear();
    virtual ~Gear();
    virtual bool getAlarm();
    virtual int getState();
    virtual void switchState(int newState);
    virtual void setAlarm(bool a);
    virtual void sendSignal(int signal, int num) = 0;
private:
    int state;
    bool alarm;
};


#endif // GEAR_H

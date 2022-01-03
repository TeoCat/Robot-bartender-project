#ifndef POMP_H
#define POMP_H

#include <cstring>
#include <Arduino.h>

enum POMP_COMMAND {
    REVERSE,
    RUN,
    STOP,
};

enum STATE {
    START = 0,
    WAIT = 1,
    BREAK = 2,
};

enum STAGE {
    FIRST,
    SECOND,
};

class Pomp {
public:
    Pomp() = delete;

    Pomp(int pin1_pomp, int pin2_pomp, int pin1_relay, int pin2_relay)
            : pin1_pomp(pin1_pomp), pin2_pomp(pin2_pomp), pin1_relay(pin1_relay), pin2_relay(pin2_relay) {
        pinMode(pin1_pomp, OUTPUT);
        pinMode(pin2_pomp, OUTPUT);
        pinMode(pin1_relay, OUTPUT);
        pinMode(pin2_relay, OUTPUT);
    }

    bool operation(char *data);
    void SetPomp(POMP_COMMAND command);
    bool Timer(unsigned int time1, unsigned int time2);

private:
    int pin1_pomp, pin2_pomp, pin1_relay, pin2_relay;
    unsigned long timer1 = 0;
    STATE state = START;
    STAGE stage = FIRST;
};



#endif //POMP_H

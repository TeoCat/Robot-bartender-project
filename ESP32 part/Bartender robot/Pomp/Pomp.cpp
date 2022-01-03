#include "Pomp.h"

bool Pomp::operation(char *data) {
    if (state == START && stage==FIRST){
        char * cocktail = strtok (data," ,");
        if (strcmp(cocktail, "Otvertka") == 0) {
            digitalWrite(pin2_relay, HIGH);
            digitalWrite(pin1_relay, LOW);
            SetPomp(RUN);
            state=WAIT;
            return true;
        }
    }
    else if (state == START && stage==SECOND){
        digitalWrite(pin1_relay, HIGH);
        digitalWrite(pin2_relay, LOW);
        SetPomp(RUN);
        state=WAIT;
        return true;
    }
    else if (state == WAIT){
        return true;
    }
    else if (state == BREAK && stage==FIRST){
        SetPomp(STOP);
        digitalWrite(pin2_relay, LOW);
        digitalWrite(pin1_relay, LOW);
        state=START;
        stage=SECOND;
        return true;
    }
    else if (state == BREAK && stage==SECOND){
        SetPomp(STOP);
        digitalWrite(pin1_relay, LOW);
        digitalWrite(pin2_relay, LOW);
        state=START;
        stage=FIRST;
        Serial.println("Done");
        return false;
    }
    return false;
}

void Pomp::SetPomp(POMP_COMMAND command) {
    switch (command) {
        case REVERSE:
            digitalWrite(pin2_pomp, HIGH);
            digitalWrite(pin1_pomp, LOW);
            break;
        case RUN:
            digitalWrite(pin1_pomp, HIGH);
            digitalWrite(pin2_pomp, LOW);
            break;
        case STOP:
            digitalWrite(pin2_pomp, LOW);
            digitalWrite(pin1_pomp, LOW);
            break;
    }
}

bool Pomp::Timer(unsigned int time1, unsigned int time2) {
    if (stage == FIRST){
        if (timer1 == 0) timer1 = millis();
        if (millis() - timer1 >= time1) {
            timer1 = 0;
            state = BREAK;
            return true;
        }
        return false;
    }
    if (stage == SECOND){
        if (timer1 == 0) timer1 = millis();
        if (millis() - timer1 >= time2) {
            timer1 = 0;
            state = BREAK;
            return true;
        }
        return false;
    }
}

#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
public:
    Encoder(int CHA, int CHB);
    int getPosition();
    void reset();

private:
    int _CHA;
    int _CHB;
    volatile int _position;
    void handleInterrupt();
    static void handleInterrupt0();
    static void handleInterrupt1();
};

#endif
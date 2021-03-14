#include <Arduino.h>

class Motor{
    public:
        void stop();
        void setPos(int pos);
        Motor(PinName I1,PinName i2,PinName E);
    private:
        PinName I1;
        PinName I2;
        PinName E;

};
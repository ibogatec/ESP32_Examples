#include <Arduino.h>

char    static constexpr TAG[]{ "\tMAIN.CPP" };

uint8_t static constexpr PIN_LED{ 2 };

void setup()
{
    pinMode( PIN_LED, OUTPUT );

}

void loop()
{
    digitalWrite( PIN_LED, HIGH );

    delay( 2000 );

    
    digitalWrite( PIN_LED, LOW );

    delay( 2000 );
}

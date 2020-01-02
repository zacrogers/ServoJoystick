#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H


enum class Mode
{
    JOYSTICK = 0,
    DEFAULT
};

typedef struct
{
    uint16_t x;
    uint16_t y;
}Pos;

typedef struct
{
    uint8_t x_pin;
    uint8_t y_pin;
    uint8_t btn_pin;
}JoyStick;



#endif /* MY_STRUCTS_H */

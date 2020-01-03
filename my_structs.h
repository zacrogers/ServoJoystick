#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

enum Mode
{
    JOYSTICK = 0,
    RANDOM,
    FOLLOW,
    PLAY,
};

enum PlayState
{
    PLAYING = 0,
    STOPPED,
    PAUSED
};

enum BtnIndex
{
    BT_PLAY = 0,
    BT_STOP, 
    BT_SAVE,
    BT_EDIT,
    BT_INCR_STEP,
    BT_DECR_STEP
};

/* Coordinates should be stored as angle */
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

typedef struct
{
    uint8_t s0;
    uint8_t s1;
    uint8_t s2;
}Mux;

/* Used to index quick_pos array */
enum Position
{
    TL = 0, // top left
    TM,     // top middle
    TR,     // top right
    ML,     // mid left
    MC,     // mid centre
    MR,     // mid right
    BL,     // bottom left
    BM,     // bottom middle
    BR,     // bottom right
    NUM_POSITIONS
};

#define MAX_ANGLE 180
#define MID_ANGLE 90
#define MIN_ANGLE 0

extern const Pos quick_pos[NUM_POSITIONS] = {{MIN_ANGLE, MAX_ANGLE}, {MID_ANGLE, MAX_ANGLE}, {MAX_ANGLE, MAX_ANGLE},
                                             {MIN_ANGLE, MID_ANGLE}, {MID_ANGLE, MID_ANGLE}, {MAX_ANGLE, MID_ANGLE},
                                             {MIN_ANGLE, MIN_ANGLE}, {MID_ANGLE, MIN_ANGLE}, {MAX_ANGLE, MIN_ANGLE}};

#endif /* MY_STRUCTS_H */

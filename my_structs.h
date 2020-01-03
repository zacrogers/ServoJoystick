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

extern const Pos quick_pos[NUM_POSITIONS] = {{0, 180}, {90, 180}, {180, 180},
                                             {0, 90},  {90, 90},  {180, 90},
                                             {0, 0},   {90, 0},   {180, 0}};

#endif /* MY_STRUCTS_H */

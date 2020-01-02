#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

num Mode
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
    Pos start;
    Pos end;
}Move;

/* Used to index quick_pos array */
enum Position
{
    TL = 0, // top left
    TR,     // top right
    TM,     // top middle
    ML,     // mid left
    MR,     // mid right
    MC,     // mid centre
    BL,     // bottom left
    BR,     // bottom right
    BM,     // bottom middle
    NUM_POSITIONS
};

const Pos quick_pos[NUM_POSITIONS] = {{0, 0}, {0, 0}, {0, 0},
                                      {0, 0}, {90, 90}, {0, 0},
                                      {0, 0}, {0, 0}, {0, 0}};

const Move[] = {};

#endif /* MY_STRUCTS_H */

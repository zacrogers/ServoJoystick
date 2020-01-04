#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

/* Servo control method mode */
enum Mode
{
    JOYSTICK = 0,
    RANDOM,
    FOLLOW,
    PLAY,
};

/* Control playing of programmed sequence or random mode */
enum PlayState
{
    PLAYING = 0,
    STOPPED,
    PAUSED
};

/* Indexes of buttons for setting mux channel  */
enum BtnIndex
{
    BT_PLAY = 0,
    BT_STOP, 
    BT_SAVE,
    BT_INCR_STEP,
    BT_DECR_STEP,
    BT_DISP_WIDTH
};

/* Coordinates should be stored as angle */
typedef struct
{
    uint16_t x;
    uint16_t y;
}Pos;

/* Structs for storing pin defines */
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
    uint8_t out;
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

#define MAX_ANGLE 110
#define MID_ANGLE 90
#define MIN_ANGLE 70

/* For quickly moving laser without having to input angles manually each time */
extern const Pos quick_pos[NUM_POSITIONS] = {{MIN_ANGLE, MAX_ANGLE}, {MID_ANGLE, MAX_ANGLE}, {MAX_ANGLE, MAX_ANGLE},
                                             {MIN_ANGLE, MID_ANGLE}, {MID_ANGLE, MID_ANGLE}, {MAX_ANGLE, MID_ANGLE},
                                             {MIN_ANGLE, MIN_ANGLE}, {MID_ANGLE, MIN_ANGLE}, {MAX_ANGLE, MIN_ANGLE}};

#endif /* MY_STRUCTS_H */

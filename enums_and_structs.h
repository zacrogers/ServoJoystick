#ifndef ENUMS_AND_STRUCTS_H
#define ENUMS_AND_STRUCTS_H


#define NUM_LEDS 4
#define NUM_BTNS 3

/* Speed of position changes in random mode */
#define MAX_SPEED 1000
#define MIN_SPEED 200

/* Play state of servos */
enum class State
{
    PLAY,
    STOP,
};

/* Control mode */
enum class Mode
{
    RANDOM,
    JOYSTICK
};

/* Indexes of led pin defines */
enum class LedInd
{
    PLAY     = 0,
    STOP     = 1,
    RANDOM   = 2,
    JOYSTICK = 3
};

/* Indexes of button pin defines */
enum class BtnInd
{
    PLAY     = 0,
    MODE     = 1,
    WIDTH    = 2
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

#endif /* ENUMS_AND_STRUCTS_H */

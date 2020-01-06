#include <Servo.h>
#include "enums_and_structs.h"

#define NUM_LEDS 4
#define NUM_BTNS 3

#define MAX_SPEED 1000
#define MIN_SPEED 200

enum class State
{
    PLAY,
    STOP,
};

enum class Mode
{
    RANDOM,
    JOYSTICK
};

enum class LedInd
{
    PLAY     = 0,
    STOP     = 1,
    RANDOM   = 2,
    JOYSTICK = 3
};


enum class BtnInd
{
    PLAY     = 0,
    MODE     = 1,
    WIDTH    = 2
};

const uint8_t SPEED_POT = A5;
const uint8_t BTN_PINS[NUM_BTNS] = {2, 5, 8};
const uint8_t LED_PINS[NUM_LEDS] = {3, 4, 6, 7};

const JoyStick js = {.x_pin   = A4, 
                     .y_pin   = A3, 
                     .btn_pin = 99};

Servo servo_x;
Servo servo_y;

Pos curr_pos = {.x = 90, .y = 90};

Mode      current_mode = JOYSTICK;
PlayState play_state   = STOPPED;

uint8_t  width_padding = 0;
uint16_t speed         = 200;

void setup()
{
    servo_x.attach(8); 
    servo_y.attach(9);
    
    pinMode(js.x_pin, INPUT);
    pinMode(js.y_pin, INPUT);
    pinMode(SPEED_POT, INPUT);
    
    for(uint8_t btn = 0; btn < NUM_BTNS; ++btn)
    {
        pinMode(BTN_PINS[btn], INPUT);    
    }

    for(uint8_t led = 0; led < NUM_LEDS; ++btn)
    {
        pinMode(LED_PINS[led], OUTPUT);    
    }
    
    attachInterrupt(digitalPinToInterrupt(BTN_PINS[BtnInd::PLAY]), toggle_playstate, RISING);
    
    set_pos(curr_pos);
}

void loop()
{
    speed = analongRead(SPEED_POT);
    speed = map(speed, 0, 1023, MIN_SPEED, MAX_SPEED);

    poll_buttons();
    
    switch(current_mode)
    {
        case JOYSTICK:
            read_joystick();
            break;

        case RANDOM:
            play_random();
            break;    
    }
}

/* Read analog joystick values and set global current position */
Pos read_joystick(void)
{
    curr_pos.x = analogRead(js.x_pin);
    curr_pos.y = analogRead(js.y_pin);
    
    curr_pos.x = map(curr_pos.x, 0, 1023, MIN_ANGLE, MAX_ANGLE);
    curr_pos.y = map(curr_pos.y, 0, 1023, MIN_ANGLE, MAX_ANGLE);
    
    set_pos(curr_pos);
}

/* Cycle through random positions, each step separated by a delay */
 void play_random(void)
 {
    if(play_state == PLAYING)
    {
        Pos randpos = quick_pos[random(0, NUM_POSITIONS)];
        set_pos(randpos);
        delay(speed);
    }
 }

/* Set xy posistion of laser pointer */
void set_pos(Pos p)
{
    servo_x.write(p.x);
    servo_y.write(p.y);
}

/* Play button set as interrupt so not included in polling function */
void poll_buttons(void)
{
    if(digitalRead(BTN_PINS[BtnInd::MODE) == HIGH)
    {
        cycle_mode();
        delay(200);
    }
    
    if(digitalRead(BTN_PINS[BtnInd::WIDTH) == HIGH)
    {
        set_width();
        delay(200);
    }
}

/* Set the width of the throw of the laser */
void set_width(void)
{
    if(width_padding < 70)
        width_padding = width_padding + 10;
    
    if(width_padding == 70)
        width_padding = 0;
}

/* Toggles playstate and sets status leds */
void toggle_playstate(void)
{
    if(play_state == State::PLAYING)
    {
        play_state == State::STOPPED;
        digitalWrite(LED_PINS[LedInd::PLAY], LOW);
        digitalWrite(LED_PINS[LedInd::STOP], HIGH);        
    }
    
    else if(play_state == State::STOPPED)
    {
        play_state == State::PLAYING;    
        digitalWrite(LED_PINS[LedInd::STOP], LOW);
        digitalWrite(LED_PINS[LedInd::PLAY], HIGH);   
    }
    
    delay(200); /* Debounce */
}

/* Toggles mode and sets status leds */
void toggle_mode(void)
{
    if(current_mode == Mode::JOYSTICK)
    {
        current_mode == Mode::RANDOM;
        digitalWrite(LED_PINS[LedInd::JOYSTICK], LOW);
        digitalWrite(LED_PINS[LedInd::RANDOM], HIGH);        
    }
    
    else if(current_mode == Mode::RANDOM)
    {
        current_mode == Mode::JOYSTICK;    
        digitalWrite(LED_PINS[LedInd::RANDOM], LOW);
        digitalWrite(LED_PINS[LedInd::JOYSTICK], HIGH);   
    }
}

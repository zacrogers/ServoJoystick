#include <Servo.h>
#include "my_structs.h"

#define NUM_LEDS 5
#define NUM_BTNS 3

#define MAX_SPEED 1000
#define MIN_SPEED 200

enum State
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
    PLAY,
    STOP,
    RANDOM,
    JOYSTICK
};


enum BtnInd
{
    PLAY,
    MODE,
    WIDTH
};

constuint8_t SPEED_POT = ;
const uint8_t BTN_PINS[NUM_BTNS] = {};
const uint8_t LED_PINS[NUM_LEDS] = {};

const JoyStick js = {.x_pin   = A6, 
                     .y_pin   = A7, 
                     .btn_pin = 99};

Servo servo_x;
Servo servo_y;

Pos curr_pos = {.x = 90, .y = 90};

Mode      current_mode = JOYSTICK;
PlayState play_state   = STOPPED;

/**/
uint8_t width_padding = 0;
int speed = 200;

void setup()
{
    servo_x.attach(8); 
    servo_y.attach(9);
    
    pinMode(js.x_pin, INPUT);
    pinMode(js.y_pin, INPUT);
    
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
    speed = map(speed,0, 1023, MIN_SPEED, MAX_SPEED);

    poll_buttons();
    
    switch(curr_mode)
    {
        case JOYSTICK:
            read_joystick();
            break;

        case RANDOM:
            play_random();
            break;    
    }
}

Pos read_joystick(void)
{
    curr_pos.x = analogRead(js.x_pin);
    curr_pos.y = analogRead(js.y_pin);
    
    curr_pos.x = map(curr_pos.x, 0, 1023, MIN_ANGLE, MAX_ANGLE);
    curr_pos.y = map(curr_pos.y, 0, 1023, MIN_ANGLE, MAX_ANGLE);
    
    set_pos(curr_pos);
}

 void play_random(void)
 {
    if(play_state == PLAYING)
    {
        Pos randpos = quick_pos[random(0, NUM_POSITIONS)];
        set_pos(randpos);
        delay(speed);
    }
 }

void set_pos(Pos p)
{
    servo_x.write(p.x);
    servo_y.write(p.y);
}

void poll_buttons(void)
{
    /* Use joystick button to cycle through modes */
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


void handle_buttons(uint8_t btn)
{
    switch(btn)
    {
        case BT_PLAY:
            toggle_playstate();
            break;
            
        case BT_STOP:
            break;
            
        case BT_SAVE:
            set_step(current_step, Pos pos);
            break;
            
        case BT_INCR_STEP:
            incr_step();
            break;
            
        case BT_DECR_STEP:
            decr_step();
            break;
            
        case BT_DISP_WIDTH:
            set_width();
            break;
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

/* If mode is PLAY or RANDOM, stop or start movement */
void toggle_playstate(void)
{
    if(play_state == PLAYING)
    {
        play_state == STOPPED;
        digitalWrite(LED_PINS[LedInd::PLAY], LOW);
        digitalWrite(LED_PINS[LedInd::STOP], HIGH);        
    }
    
    else if(play_state == STOPPED)
    {
        play_state == PLAYING;    
        digitalWrite(LED_PINS[LedInd::STOP], LOW);
        digitalWrite(LED_PINS[LedInd::PLAY], HIGH);   
    }
    
    delay(200); /* Debounce */
}

void cycle_mode(void)
{
    if(current_mode == JOYSTICK)
    {
        current_mode == RANDOM;
        digitalWrite(LED_PINS[LedInd::JOYSTICK], LOW);
        digitalWrite(LED_PINS[LedInd::RANDOM], HIGH);        
    }
    
    else if(current_mode == RANDOM)
    {
        current_mode == JOYSTICK;    
        digitalWrite(LED_PINS[LedInd::RANDOM], LOW);
        digitalWrite(LED_PINS[LedInd::JOYSTICK], HIGH);   
    }
}

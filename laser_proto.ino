#include <Servo.h>
#include "my_structs.h"

uint8_t disp_offset = 15;

/* For quickly moving laser without having to input angles manually each time */
extern const Pos quick_pos[NUM_POSITIONS] = {{MIN_ANGLE - disp_offset, MAX_ANGLE  + disp_offset},  // top left
                                             {MID_ANGLE, MAX_ANGLE  + disp_offset},                // top middle
                                             {MAX_ANGLE  + disp_offset, MAX_ANGLE  + disp_offset}, // top right
                                             {MIN_ANGLE - disp_offset, MID_ANGLE},                 // mid left
                                             {MID_ANGLE, MID_ANGLE},                               // mid centre
                                             {MAX_ANGLE  + disp_offset, MID_ANGLE},                // mid right
                                             {MIN_ANGLE - disp_offset, MIN_ANGLE},                 // bottom left
                                             {MID_ANGLE, MIN_ANGLE - disp_offset},                 // bottom middle
                                             {MAX_ANGLE  + disp_offset, MIN_ANGLE - disp_offset}}; // bottom right


/* Pin Defines */
const JoyStick   JOY_STICK                 = {.x_pin = A5, .y_pin = A4, .btn_pin = 5};
const uint8_t    LED_PINS[NUM_LEDS]        = {3, 4, 6, 7};
const uint8_t    BTN_PINS[NUM_BUTTONS]     = {2, 5, 8};
const uint8_t    SPEED_POT                 = A3;
const uint8_t    SERVO_X_PIN               = 9;
const uint8_t    SERVO_Y_PIN               = 10;

Servo            servo_x;
Servo            servo_y;

/* Variables */
Pos              curr_pos                  = {.x = 90, .y = 90};
Mode             current_mode              = JOYSTICK;
PlayState        play_state                = PLAYING;
int              play_speed                = 100;


void setup()
{
    Serial.begin(9600);
    servo_x.attach(SERVO_X_PIN); 
    servo_y.attach(SERVO_Y_PIN);

    for(uint8_t btn = 0; btn < NUM_BUTTONS; ++btn)
    {
        pinMode(BTN_PINS[btn], INPUT);  
    }
    
    for(uint8_t led = 0; led < NUM_LEDS; ++led)
    {
        pinMode(LED_PINS[led], OUTPUT);  
    }
    
    pinMode(JOY_STICK.x_pin, INPUT);
    pinMode(JOY_STICK.y_pin, INPUT);
    pinMode(SPEED_POT,       INPUT);

    attachInterrupt(digitalPinToInterrupt(BTN_PINS[PLAY]), toggle_playstate, RISING);
    
    set_pos(curr_pos);

    /* Init leds*/
    digitalWrite(LED_PINS[JOYSTICK], HIGH);
    digitalWrite(LED_PINS[PLAYING],  HIGH);
}


void loop()
{
    play_speed = analogRead(SPEED_POT);
    play_speed = map(play_speed, 0, 1023, 200, 1000);
    
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


void read_joystick(void)
{
    curr_pos.x = analogRead(JOY_STICK.x_pin);
    curr_pos.y = analogRead(JOY_STICK.y_pin);

    uint8_t min_angle = MIN_ANGLE - disp_offset + 5;
    uint8_t max_angle = MAX_ANGLE + disp_offset - 5;
    
    curr_pos.x = map(curr_pos.x, 0, 1023, min_angle, max_angle);
    curr_pos.y = map(curr_pos.y, 0, 1023, min_angle, max_angle);
    
    set_pos(curr_pos);
}


void play_random(void)
{
    if(play_state == PLAYING)
    {
        Pos randpos = quick_pos[random(0, NUM_POSITIONS)];
        set_pos(randpos);
        delay(play_speed);
    }
}


void set_pos(Pos p)
{
    servo_x.write(p.x);
    servo_y.write(p.y);
}


void poll_buttons(void)
{
    if(digitalRead(BTN_PINS[MODE]) == HIGH)
    {
        cycle_mode();
        delay(250);
    }

    if(digitalRead(BTN_PINS[OFFSET]) == HIGH)
    {
        set_width();
        delay(250);
    }    
}


/* Set the width of the throw of the laser */
void set_width(void)
{
    if(disp_offset < 70)
        disp_offset = disp_offset + 10;
    
    if(disp_offset == 70)
        disp_offset = disp_offset - 10;
}


void toggle_playstate(void)
{
    if(play_state == PLAYING)
    {
        play_state = STOPPED;
        digitalWrite(LED_PINS[STOPPED], HIGH);
        digitalWrite(LED_PINS[PLAYING], LOW);
    }
    else if(play_state == STOPPED)
    {
        play_state = PLAYING;    
        digitalWrite(LED_PINS[PLAYING], HIGH);
        digitalWrite(LED_PINS[STOPPED], LOW);
    }
    delay(250);
}


void cycle_mode(void)
{
    switch(current_mode)
    {
        case JOYSTICK:
            current_mode = RANDOM;
            digitalWrite(LED_PINS[JOYSTICK], LOW);
            digitalWrite(LED_PINS[RANDOM], HIGH);
            break;

        case RANDOM:
            current_mode = JOYSTICK;
            digitalWrite(LED_PINS[RANDOM], LOW);
            digitalWrite(LED_PINS[JOYSTICK], HIGH);
            break;
    }
}

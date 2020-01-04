#include <Servo.h>
#include "my_structs.h"
#include "7_segment.hh"

const uint8_t play_btn_pin = 3;

const JoyStick js = {.x_pin   = A6, 
                     .y_pin   = A7, 
                     .btn_pin = 5};

const Mux btn_mux = {.s0  = 6,
                     .s1  = 7,
                     .s2  = 10
                     .out = A3};

7Segment disp = 7Segment(11, 12, 13);

Servo servo_x;
Servo servo_y;

Pos curr_pos = {.x = 90, .y = 90};
Pos sequence[8] = {};

uint8_t   current_step = 0;
Mode      current_mode = JOYSTICK;
PlayState play_state   = STOPPED;

/**/
uint8_t width_padding = 0;

void setup()
{
    servo_x.attach(8); 
    servo_y.attach(9);
    
    pinMode(btn_mux.s0, OUTPUT);
    pinMode(btn_mux.s1, OUTPUT);
    pinMode(btn_mux.s2, OUTPUT);
    
    pinMode(js.x_pin, INPUT);
    pinMode(js.y_pin, INPUT);
    pinMode(js.btn_pin, INPUT);
    
    pinMode(play_btn_pin, INPUT);
    
    set_pos(curr_pos);
}

void loop()
{
    poll_buttons();
    
    switch(curr_mode)
    {
        case JOYSTICK:
            read_joystick();
            break;
            
        case PLAY:
            play_routine();
            break;          
            
        case FOLLOW:
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
        delay(500);
    }
 }

void play_routine(void)
{
    if(play_state == PLAYING)
    {
        for(int step = 1; step < 8; ++step)
        {
            disp.set_num(step);
            set_pos(sequence[step]);
            delay(500);
        }
    }
    else
    {
        disp.set_num(current_step);
        set_pos(sequence[current_step]);    
    }
}

void set_step(uint8_t step, Pos pos)
{
    sequence[step] = pos;
}

void set_pos(Pos p)
{
    servo_x.write(p.x);
    servo_y.write(p.y);
}

void poll_buttons(void)
{
    /* Use joystick button to cycle through modes */
    if(digitalRead(js.btn_pin) == HIGH)
    {
        cycle_mode();
    }
    
    /* Poll mux inputs */
    for(uint8_t btn = 0; btn < 8; ++btn)
    {
        if(digitalRead(btn_mux.out) == HIGH)
        {
            handle_buttons(btn);
        }
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

void set_width(void)
{
    if(width_padding < 70)
        width_padding = width_padding + 10;
    
    if(width_padding == 70)
        width_padding = 0;
}

void incr_step(void)
{
    if(step < 8)
        step++;
}

void decr_step(void)
{
    if(step > 0)
        step--;
}

/* If mode is PLAY or RANDOM, stop or start movement */
void toggle_playstate(void)
{
    if(play_state == PLAYING)
        play_state == STOPPED;
    
    else if(play_state == STOPPED)
        (play_state == PLAYING);    
}

void cycle_mode(void)
{
    switch(current_mode)
    {
        case JOYSTICK:
            current_mode == FOLLOW;
            break;
        
        case FOLLOW:
            current_mode == PLAY;
            break;
            
        case PLAY:
            current_mode == RANDOM;
            break;
            
        case RANDOM:
            current_mode == JOYSTICK;
            break;
    }
}

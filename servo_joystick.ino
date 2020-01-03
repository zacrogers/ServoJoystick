#include <Servo.h>
#include "my_structs.h"

const uint8_t play_btn_pin = 3;

const JoyStick js = {.x_pin   = A0, 
                     .y_pin   = A1, 
                     .btn_pin = 5};

const Mux btn_mux = {.s0 = 6,
                     .s1 = 7,
                     .s2 = 10};

Servo servo_x;
Servo servo_y;

Pos curr_pos = {.x = 90, .y = 90};

Pos path[5] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

Mode      curr_mode  = JOYSTICK;
PlayState play_state = STOPPED;

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
    
    curr_pos.x = map(curr_pos.x, 0, 1023, 0, 180);
    curr_pos.y = map(curr_pos.y, 0, 1023, 0, 180);
    
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
        for(int i = 0; i < 5; ++i)
        {
            set_pos(path[i]);
            delay(500);
        }
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
    if(digitalRead(js.btn_pin) == HIGH)
    {
        cycle_mode();
    }
    
    if(digitalRead(play_btn_pin) == HIGH)
    {
        toggle_playstate();
    }
}

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

#include <Servo.h>

Servo servo_x;
Servo servo_y;

JoyStick js = {.x_pin   = A0, 
               .y_pin   = A1, 
               .btn_pin = 5};
Pos pos = {0};

void setup
{
    servo_x.attach(8); 
    servo_y.attach(9);
    
    pinMode(js.x_pin, INPUT);
    pinMode(js.y_pin, INPUT);
    pinMode(js.btn_pin, INPUT);
    
    init_pos();
}

void loop
{
    pos.x = analogRead(js.x_pin);
    pos.y = analogRead(js.y_pin);
    
    pos.x = map(pos.x, 0, 1023, 0, 180);
    pos.y = map(pos.y, 0, 1023, 0, 180);
    
    servo_x.write(pos.x);
    servo_y.write(pos.y);
}

void init_pos()
{
    servo_x.write(90);
    servo_y.write(90);
}

# RobotControl

<img width="700" height="540" alt="2WD-Ultrasonic-Smart-Tracking-Moteur-Robot-Car-Kit-For-Arduino-front-960x540" src="https://github.com/user-attachments/assets/70aeab89-f4e4-45cd-a978-5d10de4d4f8c" />


code.ino sketch implements a right-hand wall-following maze solver for a two-motor
differential-drive robot using an ultrasonic distance sensor mounted on a servo and a single IR
sensor used as a "kill / black-line" switch. The robot scans forward and to the right, then
chooses motion commands to keep the right side near a wall while avoiding frontal collisions.


Platform: Arduino Uno
● Sensors: HC-SR04 ultrasonic sensor (trigger + echo), analog IR sensor (for black-line /
kill switch), hobby servo for sweeping the ultrasonic sensor
● Actuators: Two DC motors driven by an H-bridge (4 direction control pins + 2 PWM
speed pins)
● Purpose: Navigate a maze by keeping a wall on the right side and avoiding obstacles in
front.



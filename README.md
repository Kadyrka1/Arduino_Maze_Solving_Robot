# RobotControl

This Arduino sketch implements a right-hand wall-following maze solver for a two-motor
differential-drive robot using an ultrasonic distance sensor mounted on a servo and a single IR
sensor used as a "kill / black-line" switch. The robot scans forward and to the right, then
chooses motion commands to keep the right side near a wall while avoiding frontal collisions.

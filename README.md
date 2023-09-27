# ELEC1100 Project: Line Tracking Car

This project aims to program a car that can track a white line on a dark mat using four sensors and two motors. The car should be able to start, stop, turn, and reverse according to the line and the bumper sensor.

![](https://i.imgur.com/k4M0rus.jpg)

## Path

The path that the car should follow is shown in the figure below. It consists of straight lines, 90-degree corners, gentle curves, and T-junctions.

![](https://i.imgur.com/et1GYIU.png)

The car should follow these steps:

1. After power on, the car should stop after board initialization.
2. Put the car at the start position with all front-bar sensors on the horizontal start white line. The car should still be at stop state.
3. The bumper sensor is triggered by a white paper to start running.
4. Follow the straight line until reaching a T-junction.
5. Turn left at the T-junction.
6. Navigate the 90-degree corners (finish all four of them).
7. Navigate the gentle curve until reaching another T-junction.
8. Turn right at the T-junction.
9. Follow the straight line until reaching a U-shaped connection.
10. Turn right at the U-shaped connection.
11. Navigate the 90-degree corners (finish all three of them).
12. Follow the straight line until reaching a white wall.
13. The bumper sensor is triggered by the white wall to let the car move backward.
14. The car can stop after moving back to the 30 cm mark from the white wall.

The goal is to achieve a perfect run in 25 seconds. The timer stops counting when the car stops behind the 30 cm mark.

## Hardware

![](https://i.imgur.com/olhzu2H.png)

The car has the following hardware components:

- A car battery that provides power to the circuit
- A LM7805 DC regulator that converts the battery voltage to 5V
- A L293 H-bridge that controls the direction of the motors
- A 74HC14 hex inverter that converts the DC voltage to AC voltage for the sensors
- Four Bright Sensing Sensors: three down-sensing (left, center, right) and one forward-sensing (bumper)
- Two motors: left and right of the bot
- A microcontroller board with an Arduino Nano
- Caster wheel for stability

The sensors are connected to the analog pins A0, A1, A2, and A3 of the board through the inverter. The motors are controlled by the digital pins D3, D4, D5, and D6 of the board through the H-bridge. The direction and speed of the motors are determined by the DIR and PWM signals respectively.

## Software

The code for the project is written in C++ and uploaded to the board using the Arduino IDE. The code consists of two main parts: the setup function and the loop function.

The setup function runs once when the board is powered on or reset. It defines the pins as input or output, and initializes the output pins to stop the car at the start position.

The loop function runs repeatedly until the power is turned off. It reads the sensor measurements and executes different actions based on the logic in the code. The actions include starting, stopping, turning, reversing, and straightening.

The code also defines some constants and variables that are used in the script. The constants include the pin numbers and the maximum speed of the motors. The variables include the sensor values and some counters and flags that keep track of the car’s state.

### Logic

![](https://i.imgur.com/O09U9gY.png)

### Truth Table

| bumperSensor | centralSensor | leftSensor | rightSensor | countBumper | countStep | flagStraight | Action | L_DIR | R_DIR | pinL_PWM | pinR_PWM |
|--------------|---------------|------------|-------------|-------------|-----------|--------------|--------|-------|-------|----------|----------|
| LOW          | x             | x          | x           | 0           | x         | x            | Start moving forward  | HIGH  | HIGH  | max_speed | max_speed |
| LOW          | x             | x          | x           | 1           | x         | x            | Stop and reverse      | LOW   | LOW   | max_speed * 0.6  | max_speed * 0.6  |
| HIGH         | LOW           | LOW        | LOW         | 1           | 0         | x            | Turn left             | LOW   | HIGH  | max_speed * 0.65  | max_speed * 0.65 |
| HIGH         | LOW           | LOW        | LOW         | 1           | >0        | x            | Turn right            | HIGH  | LOW   | max_speed * 0.75  | max_speed * 0.75 |
| HIGH         | LOW           | HIGH       | LOW         | 1           | x         | x            | Turn right            | HIGH  | LOW   | max_speed  | max_speed |
| HIGH         | LOW           | LOW        | HIGH        | 1           | x         | x            | Turn left             | LOW   | HIGH  | max_speed  | max_speed |
| HIGH         | HIGH          | x          | x           | 1           | x         | 1            | Straighten            | -     | -     | -          | -         |
| HIGH         | -             | -          | -           | >1          | -         | -            | -                     | -     | -     | -          | -         |



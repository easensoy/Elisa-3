# Elisa-3

The Elisa-3 robot is an autonomous robot designed for swarm robotics research and experimentation. It is specifically developed for educational and research purposes, allowing users to explore swarm robotic algorithms and behaviors.

The Elisa-3 robot is also a small, low-cost robot equipped with various sensors and actuators. It features a circular shape and has a diameter of approximately 5 centimeters. The robot is equipped with infrared proximity sensors, light sensors, and an array of RGB LEDs. It also has two independently controlled wheels that enable it to move and navigate its environment.

More importantly, the Elisa-3 robot is capable of autonomous behavior, meaning it can operate without direct human control. It can perceive its surroundings using its sensors and make decisions based on programmed algorithms. The robot can execute tasks such as obstacle avoidance, light-following, swarm coordination, and other behaviors that are commonly explored in swarm robotics. In my project, I performed four different tasks, such as: 

- [x] Black line following in a simple track

- [x] Black line following in a curved track

- [x] Keep inside the box and avoid obstacles

- [x] Line and corrider following

While the Elisa-3 robot is often used in swarm robotics research, it can also be used for individual robot experiments and projects. Its small size, affordability, and autonomy make it a suitable platform for learning and exploring robotics concepts.

## Actuation of the Robot

An H-bridge is an electronic circuit that allows the direction and speed control of a DC motor. It consists of four switches (usually transistors or MOSFETs) arranged in an "H" configuration. The motor is connected between the switches in the middle of the H-bridge, and the switches on the top and bottom control the motor's direction of rotation.

![image](https://github.com/easensoy/Elisa-3/assets/76905667/c736fa87-d292-4928-a817-caa6984bbb5c)

PWM (Pulse Width Modulation) is a technique used to control the average voltage applied to a device by rapidly switching it on and off at a high frequency. In the context of motor control, PWM is used to control the speed of the motor.

![image](https://github.com/easensoy/Elisa-3/assets/76905667/b00ff589-7ef1-4739-88d9-fba5153a751d)

These two pave the way for two gains for the system: 

Speed Control: By applying a PWM signal to the input of the H-bridge, the average voltage across the motor terminals can be controlled. The duty cycle of the PWM signal determines the average voltage applied to the motor, and thus, the speed of the motor. A higher duty cycle corresponds to a higher average voltage and faster motor speed, while a lower duty cycle corresponds to a lower average voltage and slower motor speed.

Direction Control: The H-bridge allows the motor to rotate in both forward and reverse directions. By controlling the state of the switches in the H-bridge, the polarity of the voltage applied to the motor terminals can be changed, thereby changing the motor's direction of rotation.


# The image of the robot
![20220516_133206](https://user-images.githubusercontent.com/76905667/180611538-d0e1da62-15ba-44e9-b2c8-17734cd83ac6.jpg)

The robot needed to achieve the four different tasks. All tasks are achieved by providing clockwise and counterclockwise motion.

Task 1


The first task is to track the black line by crossing the circle.
![1](https://user-images.githubusercontent.com/76905667/180611648-be38b909-58e7-4558-b54d-5772b4fe6caf.png)

Task 2


The second one is a more complex task that requires it to traverse steep turns.
![2](https://user-images.githubusercontent.com/76905667/180611657-a8244dd5-9d60-4fcf-a75c-26a4499b77c7.png)

Task 3


The third task is about keeping inside the black frame while avoiding obstacles.
![3](https://user-images.githubusercontent.com/76905667/180611665-cbc9489d-02e9-4922-af18-8f3901065c64.png)

Task 4


The aim of the last task is to cross the junctions and follow the white corridor to reach the final line.
![4](https://user-images.githubusercontent.com/76905667/180611671-7c8242c4-fb36-467a-a68f-eef019b80b0b.png)

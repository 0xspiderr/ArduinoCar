### Libraries used
* IRRemote.h
* NewPing.h // for ultrasonic sensor
* NewTone.h // IRremote uses the same timer as the default Tone.h library
          // so we use this to not get errors when using the buzzer and infrared remote.

### Needed materials
* Two 9V batteries
* 9V battery adapters for Arduino/wire connections
* Arduino UNO
* Wires Male-to-male/ female-to-female and normal 22-AWG wires
* HC-SR04 Ultrasonic Sensor(optional)
* Any infrared remote and a receiver sensor
* A buzzer for sound(optional)
* Four 3-12V gear motors
* L298N motor driver(Do yourself a favour and buy something else, this motor driver is very power hungry and inneficient.
You could get something like this at a very cheap price on aliexpress:https://www.sparkfun.com/sparkfun-motor-driver-dual-tb6612fng-1a.html)
* Soldering iron(optional) - I soldered the ultrasonic sensor pins, IR sensor pins and the gear motors pins with wires for better stability.
If you don't have a soldering iron that is fine and you can wrap the wires around the connector pins.

!!! 
For people that don't have a car chassis like me:
* Electrical tape
* Wire cutters
* Wire strippers
* Take a shoe box or icecream container(even better) and measure the distance
on the motor between the two screws then mark that on the box.
Make holes with a thin screwdriver.
Then you can assemble the car like in the photos below.
Just be careful to secure the motors with electrical tape/wires,
otherwise the car will not go straight.
!!!

## Beware
For the car to fully work you should connect the motor shield to 4 AA batteries using
a battery holder(which I didn't have), otherwise the car works fine without the ultrasonic sensor connected.

### Schematics

![Schematic](https://github.com/user-attachments/assets/2e82772b-8ebd-411c-8295-17016e4c1233)

![IMG-20250328-WA0001 1](https://github.com/user-attachments/assets/1845dbbe-92a2-4917-a9ee-a5a028be7bf7)

https://github.com/user-attachments/assets/9518d48b-33e9-4931-b15b-d2a90e6b1555

https://github.com/user-attachments/assets/cb45fef7-72d3-43ca-8cbf-7b301f450b34

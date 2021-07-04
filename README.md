# Clock Pulse Controller

This project is based on [Ben Eater's Clock module](https://www.youtube.com/watch?v=kRlSFm519Bo&t=0s). I decided to make an Arduino implementation of this as, while I have plenty of 555 chips lying around, The only logic gates I had in my inventory were NAND gates. 

The purpose of Ben Eater's series is to not use Microcontrollers and to build a computer from scratch. However, since this module is largely just a debug unit, I figured this would do for now. For production, it would probably need to be switched out for a Crystal Oscillator anyway. 

I wanted to make this module as small as possible so I aim to fit it all on a 170pin ElectroCookie PCB. Here is a wiring diagram of the circuit showing how to configure the components. 

## PINS

| PIN  | PIN Mode | Usage                          | Description                                                  |
| ---- | -------- | ------------------------------ | ------------------------------------------------------------ |
| 2    | INPUT    | Mode Select Button             | Switches between Automatic and Manual Clock Pulses           |
| 3    | INPUT    | Halt Interrupt Service Routine | Halts the program execution and prevents pulse change        |
| 10   | INPUT    | Manual Pulse Button            | Manually toggles between Rising and Falling edge of pulse on press |
| A0   | OUTPUT   | Potentiometer Read             | Reads the value of the potentiometer to raise or lower clock pulse width frequency |

## Features

This features all the same functionality of Ben's clock module. 

Clock pulse can be Automatic or Manual and the pulse can be halted with a HIGH signal interrupt on PIN 3.



## BOM

1 x Arduino Pro Micro

1 x Green LED

2 x 2 pin tactile push to make buttons

1 x 1kΩ potentiometer

1 x 220Ω resistor

1 x 170 ElectroCookie PCB

2 x 12 pin Headers

1 x 3 pin header 



## Circuit Diagram

![https://i.imgur.com/MKkBQW6.png](https://i.imgur.com/MKkBQW6.png)



## Photo of Completed Module

![https://i.imgur.com/CI5Ckob.jpeg](https://i.imgur.com/CI5Ckob.jpeg)


# Bloom

## Abstract
Interaction with data is unintuitive. There are no natural, physical affordances, including for security. It is also inaccessible to those who cannot effectively navigate the pixel empire (e.g. children, elderly), and for those who can, screen addition can be a real problem. In this project, we make data intuitive to human nature by drawing from the metaphor of a dandelion flower. Our device blooms to indicate when more data is added, and, when blown, data is cleared and sent away.

[![Alt text](https://img.youtube.com/vi/J2vZu5a8wUI/0.jpg)](https://www.youtube.com/watch?v=J2vZu5a8wUI)


## Implementation

The system interfaces an Arduino (on the flower) and python (on a computer) using serial. The Arduino and servo motor are powered over USB.

When the system is on, python begins watching a specified folder, representing the flower’s memory. Once images or data are added to that folder, python takes note of the folder size and sends a byte to arduino to rotate the servo motor to an angle indicating the folder’s capacity. As the folder reaches capacity, the flower similarly approaches full bloom. This provides the user with an intuitive indication of how much data has been added to the flower’s memory.

A microphone sensor on the flower is able to detect a blowing sound input, represented as sustained noise over a threshold volume, for at least 1 second. When the flower is blown, Arduino detects this signal and sends a message to Python in the form of a byte. Python now performs a task on the flower folder, such as using os to delete files or to send it to a pre-programmed recipient. Since the folder is now empty, the servo rotates in the opposite direction, which produces an effect representing that when a dandelion flower is blown. The system then continues to await new data being added to the flower’s memory.

More details are available in [this document](https://docs.google.com/document/d/1DxvCYafuAFx3aNjNNNF-St48AnnFLWvnj-jQwCuf0DA/).


### Electronic

  - SRC SM-S4303R Continuous Rotation Servo
  - SEN-14262 Sound Detector
  - ATmega328P Arduino Nano


### Software

Python (3) prerequisites - can be installed with pip:

 - watchdog
 - serial
 - glob

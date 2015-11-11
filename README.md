# ArdosAVR-GCC
ArdOS is a powerful but compact multitasking operating system for the Arduino series of microcontroller boards centered around the Atmel ATmega 168, 328, 1280 and 2560 microcontrollers. This repository allows user to use Ardos in Atmel studio (at the moment, it is compiled with AS version 7.0. with  AVR8/GNU C Compiler : 4.9.2.

ArdOS features:
Full compatibility with the Arduino libraries and IDE.
A small compact kernel.
A multitasking priority-based scheduler for hard real-time applications.
A true sleep function that frees the microcontroller to perform other tasks.
Binary and counting semaphores.
Mutex locks and conditional variables.
First-in-first-out (FIFO) message queues.
Priority message queues.
Configurable. You can exclude parts of ArdOS from compilation to minimize memory usage, and control the stack size of each task.
For more information, please visit Ardos' repository https://bitbucket.org/ctank/ardos-ide/wiki/Home

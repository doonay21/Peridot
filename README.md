Peridot
=======

The Peridot programing language is an esoteric programming language based on [Brainfuck](http://en.wikipedia.org/wiki/Brainfuck) and fully compatible with it.
It was designed to extend the functionality of Brainfuck.

Uploaded interpreter (0.1a version) is covering 100% of Peridot commands, and just a few built-in system functions.
The interpreter is written for WIN32 only. I am having problems compiling it under Linux (I used some of C++11/C++0x goodies).

Peridot Interpreter - Usage
---------------------------

**Peridot.exe** can be started using filename as argument or using no arguments like so:

> Peridot.exe hello_world.p

When no arguments are provided **Peridot.exe** will look for *spoint.p* file to execute.

Peridot Language - Documentation
--------------------------------

Peridot language uses very simple model - you have access to one array of 65536 byte cells initialized to zero.

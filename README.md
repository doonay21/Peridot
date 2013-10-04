Peridot
=======

The Peridot programing language is an esoteric programming language based on [Brainfuck](http://en.wikipedia.org/wiki/Brainfuck) and fully compatible with it.
It was designed to extend the functionality of Brainfuck.

Uploaded interpreter (0.1a version) is covering 100% of Peridot commands, and just a few built-in system functions. The interpreter is written for WIN32 only. I am having problems compiling it under Linux (I used some of C++11/C++0x goodies).

Peridot Interpreter - Usage
---------------------------

**Peridot.exe** can be started using filename as argument or using no arguments like so:

> Peridot.exe hello_world.p

When no arguments are provided **Peridot.exe** will look for *spoint.p* file to execute.

Peridot Language - Documentation
--------------------------------

Peridot language uses very simple model - you have access to one data array of 65536 byte cells initialized to zero. There is also movable data pointer initialized to the leftmost byte of the array.
Apart from data array there is one more array called **Function Array** consists of 1024 byte cells initialized to zero, and its own movable pointer also initialized to the leftmost byte of the array.

Lets start coding!

**Peridot "Hello World!" example**

> ///////++.V///-./V---..i.z///++.I>i/+++++.<.V+++.i---.\++.z///+++.

I must admit it looks a bit more complicated comparing to Brainfuck, but yeah, we have less to write, and we do not use any loop!

**Pure Brainfuck "Hello World!" example**

> ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.

As I mentioned before both of examples above will work using **Peridot Interpreter** as Peridot is fully complatible with Brainfuck.

OK we need to dive in to the basics. In our data array we start with pointer pointing cell nr 0 (the very first one), let's play with our cell.
______________________________
**Changing value of the cell**
* Increase cell value

> +

Plus letter is **increasing cell's** value by **1**. When we will increase cell with value of 255 (maximum) it will round back to 0.

> /

Slash letter is **increasing cell's** value by **10**. If after the

## Peridot

The **Peridot** programing language is an esoteric programming language based on <a href="http://en.wikipedia.org/wiki/Brainfuck" target="_blank">Brainfuck</a> and fully compatible with it.
It was designed to extend the functionality of **Brainfuck**.

Uploaded **Live Interpreter** (0.11a version) is covering 100% of **Peridot's** (0.11 version) commands. The interpreter is written for **Windows** and **Linux** systems.

**Peridot** language and **Peridot Live Interpreter** are in alpha stage so far. I am planing to expand **Peridot's** functionalities, and create its own compilator.

**Changelog:**
```
* 0.1a Alpha version, initial release.
  * Full coverage of BrainFuck's 8 instructions (full compatibility)
  * 20 new instructions
  * Two loops. Basic BrainFuck's "[...]" if-not-zero-loop and additional "{...}" if-zero-loop
  * Four conditional statements (if equal; if not equal; if greater; if less)
* 0.11a Alpha version.
  * Help message added (-h, --help)
  * Error message will rise on unknown instructions
  * Minor optimizations
```
## Peridot instructions
Simple introduction and instruction list can be found on <a href="https://github.com/doonay21/Peridot/wiki" target="_blank">Peridot Wiki</a> page.
## Peridot Live Interpreter - Usage

**Peridot.exe**(Windows) and **peridot**(Linux) can be started using no arguments or filename as argument like so:
```
Peridot.exe hello_world.p
```
```
peridot hello_world.p
```
When no arguments are provided **Peridot** will look for *spoint.p* file to execute.

## Peridot Live Interpreter - Linux install instructions
Requirements for Peridot Live Interpreter:
* g++
* make

Best is to have "build-essential" package installed on Linux machine.

```
cd /usr/src
wget https://github.com/doonay21/Peridot/raw/master/Linux%20-%20Live%20Interpreter/peridot.tar.gz
tar zxvf peridot.tar.gz
cd peridot
make && make install
```

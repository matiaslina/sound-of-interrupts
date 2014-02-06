# Sound of interrupts

## Overview

Little program that makes your computer do some
sounds depending on the amount of interrupts in the cpus.

## Compilation.

You'll need the pulseaudio development libraries for the cli.
Graphical interface will need the Qt libraries.

```bash
mkdir build && cd build
cmake ..
make

# and you can launch it with

./src/play-cli
```
## QT interface

If you want to build a qt interface that shows a graphic with the
number of interruptions of the CPU and play sounds as well. Just run

```bash
mkdir build && cd build
WITH_QT=1 cmake ..
make

./src/qtgui/soi_qtgui
```

*Remember that you need the development files of qt4 to be able to
compile this*

## To do

* The gui need to be finished (doesn't play any sound :p)
* Put some output in the cli

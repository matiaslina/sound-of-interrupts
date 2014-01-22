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

## To do

* The gui need to be finished (doesn't play any sound :p)
* Do some defines in the CMakeFiles for the gui build
* Put some output in the cli

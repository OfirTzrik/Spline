# Spline Drawer (C + raylib)

Interactive spline drawing in C with [raylib](https://www.raylib.com/). Add and move control points. Render a smooth curve in real time.

## Demo

![](https://github.com/OfirTzrik/Spline/blob/main/demo2.gif)

## Features

- Interactive control points.
- Smooth curve rendering.
- Simple, portable C.

## Build

This repo uses a Makefile.

**Target:** `main`  
**Sources:** `spline.c functions.c`  
**Headers:** `functions.h definitions.h`  
**Link flags:** `-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -ansi -pedantic -s -O2`

### Linux (Debian/Ubuntu)
```bash
sudo apt-get update
sudo apt-get install -y build-essential pkg-config libraylib-dev libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev
git clone https://github.com/OfirTzrik/Spline.git
cd Spline
make
```

### Clean
```bash
make clean
```

> Note: The provided `LIBS` are Linux/X11 specific. On macOS or Windows you must adjust the libraries and frameworks for your toolchain.

## Controls

- Right click to add a point  
- Left click to move a point
- R to reset
- U to undo

## Roadmap

- Export to image

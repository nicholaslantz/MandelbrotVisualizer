# Mandelbrot Visualizer
## By Nicholas Lantz

A basic visualization of the Mandelbrot set written in C with the SDL2
framework. It uses doubles for calculations, so it does not have infinite
detail like the actual fractal does, but it does a decent job at giving a
high level overview

## Compilation

Make sure you have SDL2 development libraries installed on your machine, then
type the following in the directory where you downloaded it:

```
gcc main.c -o mandelbrot -lSDL2 -lm
```

This should build the program and output a binary that you can run with

```
./mandelbrot
```

This program has not been tested on OS X or Windows machines. SDL2 is a
multi-platform library, so it should work. But, I do not know how it would be
built on other platforms.

Also, if for some reason unsigned integers are not 32 bits on your machine, the
program will probably crash. I should fix that.
## Controls

* wasd, hjkl, or arrow keys to move in the appropriate direction
* e to zoom in
* q to zoom out
* r to reset viewing frame
  * This is useful for when you get lost or you bork your viewing frame because
    doubles don't have infinite precision.

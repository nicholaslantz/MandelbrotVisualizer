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
gcc main.c -o mandelbrot -lSDL2
```

This should build the program and output a binary that you can run with

```
./mandelbrot
```

## Controls

* wasd, hjkl, or arrow keys to move in the appropriate direction
* e to zoom in
* q to zoom out



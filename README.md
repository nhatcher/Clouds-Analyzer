Introduction
============

Do you have a picture and want to know if it is a fractal?
We might be able to help.

Clouds Analyzer is a graphical computer program that simulates clouds and tries to measure different properties of these clouds.

It started up as a tool to test if certain physical processes are happening in the interstellar medium, the sites of start creation. It is thus linked to big words such as turbulence...

But you can use it for simpler stuff too, I think.

Build instructions
=================

In any linux system, just

* `qmake`
* `make`

Dependencies:

* Qt4
* FFTW3 (sudo apt-get install libfftw3-dev on my linux box)

Images
======
A generated cloud with its Area-Perimeter dimension:

![clouds](images/clouds.png)

The same cloud, computing the box-counting dimension of the "border" of the cloud:

![box counting](images/boxcounting.png)

CREDITS
=======

It was made in 2008 by my student Sandra Ocando and by me.

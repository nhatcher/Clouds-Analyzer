Introduction
============

Do you have a picture and want to know if it is a [fractal](https://en.wikipedia.org/wiki/Fractal_dimension)?

We might be able to help you!

Clouds Analyzer is a graphical computer program that simulates clouds and tries to measure different properties of these clouds.

It started up as a tool to test if certain physical processes are happening in the [interstellar medium](https://en.wikipedia.org/wiki/Interstellar_medium), the sites of start creation. It is thus linked to big words such as [turbulence](https://en.wikipedia.org/wiki/Turbulence)...

But you can use it for simpler stuff too, I think.

What can I do
=============

1. Create some very basic fractals
  * [Koch curve](https://en.wikipedia.org/wiki/Koch_snowflake)
  * [Hénon attractor](https://en.wikipedia.org/wiki/H%C3%A9non_map)
  * [Fractional Brownian motion](https://en.wikipedia.org/wiki/Fractional_Brownian_motion)
  * Molecular clouds.

2. Measure fractal dimensions of these fractals:
  * [Box counting dimension](https://en.wikipedia.org/wiki/Minkowski%E2%80%93Bouligand_dimension)
  * [Correlation dimension](https://en.wikipedia.org/wiki/Correlation_dimension)
  * [Rényi entropic dimensions](https://en.wikipedia.org/wiki/R%C3%A9nyi_entropy)
  * Area-perimeter dimension.

3. Load some images (2D) and make some analysis on those images:
  * Convert the color image to a grey scale image
  * Make it black and white with a particular threshold
  * Detect borders
  * Measure fractal dimensions of this image


Build instructions
=================

In any Linux system, just change to the source directory and

* `qmake`
* `make`

Dependencies:

I use the wonderful QT for all the UI and FFTW3 for the Fast Fourier Transforms

* Qt4
* FFTW3 (`sudo apt-get install libfftw3-dev` on my Linux box)

Images
======
A generated cloud with its Area-Perimeter dimension:

![clouds](images/clouds.png)

The same cloud, computing the box-counting dimension of the "border" of the cloud:

![box counting](images/boxcounting.png)


TODO
====

Soooo many things.

1. ROADMAP!
2. Clean code. Well, I am a programmer now.
3. Improve UI
4. Add documentation
5. Add more test fractals. Maybe using Lua as an scripting language or javascript.
6. Documentation
7. ...

CREDITS
=======

This program started as part of the thesis of Sandra Ocando and is now maintained by N. Hatcher. If there is something that interest you here please contact me.

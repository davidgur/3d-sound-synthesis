## Algorithm for 3D sound localization

### David Gurevich

This repository documents the development and implementation of an algorithm for 3D sound localization.

There are two folders here: ``MATLAB``, which implements the algorithm in MATLAB, and ``CPP``, which implements the same algorithm in C++.

This algorithm takes an audio file, an azimuth (theta), and an elevation (phi) in order to modify the sound to make it sound as though it is coming from that particular azimuth and that particular elevation.

This was done using Head Related Impulse Response filters (HRIR), which are a set of FIR filters that are determined in a lab (I used the LISTEN HRTF DATABSE, from IRCAM).
In addition to the HRIR filters, I used the concept of the Interaural Time Delay, which is a consequence of the fact that sound arrives at each of the ears at slightly different times, allowing the brain to better localize the sound.

Given that the database used for this project is quite sparse, in that these filters are only available in 15 degree intervals along the azimuth, I employed bilinear interpolation in order to interpolate the filters for any arbitrary azimuth modulo 360, and any arbitrary elevation between -45 and 75 degrees.

I chose to implement this algorithm in MATLAB first because the toolbox lends itself well to this sort of mathematical and computationally intensive work.
It allowed me to develop this algorithm from scratch, and make small improvement along the way.

Once I was happy with the algorithm I had developed in MATLAB, I chose to re-implement it in C++, as it is commonly used in digital signal processing applications, and I wanted to try to emulate a modern digital signal processing workflow as much as I could.
Although the implementation in C++ was much more difficult, I found the process especially interesting, as I tried to find various optimizations for the process, and was able to learn more about computational methods for signal processing, such as the overlap-add algorithm for fast convolutions.

There are more details on how to build and use these applications inside their respective folders.

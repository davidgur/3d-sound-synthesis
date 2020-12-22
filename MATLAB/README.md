## MATLAB implementation of 3D sound localization
### David Gurevich

This is an algorithm I designed for 3D sound localization. I chose to implement it first in MATLAB because the toolbox lends itself well to this sort of work.

The function to focus on in this case is found in `localize.m`. It provides a function, `localize`, which makes it appear as though a sound is coming from a given azimuth and elevation.

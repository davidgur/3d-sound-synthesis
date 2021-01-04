## C++ implementation of 3D sound localization

### David Gurevich

This is a C++ implementation of an algorithm I designed for 3D sound localization.

#### Building

This program can be built using CMake. Note that this program requires two external libraries, which are ``sndfile``
and ``fftw3``. Both of these libraries have excellent documentation that you can take a look at for installation
instructions. On many Linux systems, they can be installed using your system package manager.

#### Running

When built, the program requires access to the ``data`` folder, which contains the HRIR reference functions.
**This program will not work without access to this folder.**

Running this program requires a very specific syntax. It is as follows:

    ./CPP [INPUT_FILE.wav] [AZIMUTH] [ELEVATION] [OUTPUT_FILE.wav]

An explanation of each input is given in order:

* ``INPUT_FILE.wav`` -- Location of the WAV file you wish to modify. Note that this program only accepts WAV files as
  input
* ``AZIMUTH`` -- Azimuth describes the angle (in degrees) on the horizontal plane from which the sound should come from.
  0 or 360 degrees is located behind your head, 180 degrees in front of your head. The values must be modulo 360
  degrees.
* ``ELEVATION`` -- Elevation describes the angle (in degrees) on the vertical plane from which the sound should come
  from. This value must be between -45 and 75 degrees, inclusive.
* ``OUTPUT_FILE.wav`` -- Location of the WAV file that the program should output. Note that this program only outputs
  WAV files.

Note that if the AZIMUTH and ELEVATION are both 0, then the program will be in "demo mode", which will make the audio
file appear as though it makes 5 revolutions around the listeners head with 0 elevation.

It is also worth noting that the output audio file should be listened to using headphones or earbuds. It is crucial that
they are capable of stereo (2 channel) sound.

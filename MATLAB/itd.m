function itd_samples = itd(theta, Fs)
% itd calculates the interaural time difference given some azimuth theta
%
% Inputs:
%   theta - Azimuth (in degrees)
%   Fs    - Sampling frequency (e.g. 44100)
%
% Output:
%   itd_samples - The number of samples representing the calculated ITD
%
% Example:
%     itd(30, 44100) -->  -12
%     itd(30, 21500) -->  -6
%     itd(190, 35)   -->  35
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: localize
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------

d = 0.0875; % radius of head (metres)
c = 343; % speed of sound (metres/second)

left_delay = 0;
right_delay = 0;

if theta == 360 || theta == 180
    left_delay = 0;
    right_delay = 0;
elseif 0 < theta  && theta < 180
    left_delay = Fs * (-d * sind(theta)) / c;
    right_delay = Fs* (d * deg2rad(theta)) / c;
elseif 180 < theta && theta < 360
    left_delay = Fs * (d * deg2rad(theta)) / c;
    right_delay = Fs * (-d * sind(theta)) / c;
end

itd_samples = round(left_delay - right_delay);
% -------------------- END CODE --------------------
end


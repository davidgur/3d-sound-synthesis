function localized_audio = localize(y, Fs, l_hrir, r_hrir, theta, phi)
% localize applies certain filters and delays to make it seem as though a
% sound, given by y, is coming from some given azimuth and elevation
% (theta, phi, respectively).
%
% This function assumes that y is a mono audio track with some sampling
% frequency Fs. The algorithm proceeds as follows:
% 1) Determine the left channel by convolving the audio track with the HRIR
%    given by the interpolation of the left HRIR dataset at theta and phi
%
% 2) Determine the right channel by convolving the audio track with the
%    HRIR given by the interpolation of the right HRIR dataset at theta
%    and phi.
%
% 3) Calculate the Interaural Time Difference (ITD) using the azimuth (theta)
%     and the sampling frequency (Fs).
% 
% 4a) If the ITD is less than or equal to 0, then the right channel is
%     delayed, and we pad the left and right channel accordingly.
%
% 4b) If the ITD is greater than 0, then the left channel is delayed, so we
%     pad the left and right channel accordingly.
%
% 5) Combine the left and right channel into a Nx2 matrix compatible with
%    MATLAB's audiowriter function.
%
% Inputs:
%   y - Mono audio track
%   Fs     - Sampling frequency (e.g. 44100)
%   l_hrir - Left ear HRIR dataset structure
%   r_hrir - Right ear HRIR dataset structure
%   theta  - Azimuth (degrees) theta = [0, 345]
%   phi    - Elevation (degrees) phi = [-45, 90]
%
% Output:
%   localized_audio - Stereo audio track localized to theta and phi
%
% Other m-files required: hrir_interpolate.m itd.m
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: hrir_interpolate itd conv
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------

    left = conv(y, hrir_interpolate(l_hrir, theta, phi));
    right = conv(y, hrir_interpolate(r_hrir, theta, phi));

    ITD = itd(theta, Fs);

    if ITD <= 0
        right = [zeros(ITD, 1); right];
        left = [left; zeros(ITD, 1)];
    else
        right = [right; zeros(ITD, 1)];
        left = [zeros(ITD, 1); left];
    end

    localized_audio = [left(:), right(:)];
% -------------------- END CODE --------------------
end


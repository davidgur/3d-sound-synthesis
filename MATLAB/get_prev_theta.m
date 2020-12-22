function prev_theta = get_prev_theta(orig_hrir, theta, phi)
% get_prev_theta - returns the nearest theta value smaller than the one
% provided.
%
% The HRIR dataset that is used provides only some values of theta. This
% function determines the closest possible value of theta to the one provided
% as an argument to this function.
%
% Inputs:
%   orig_hrir - One of the HRIR structs provided the MAT file
%   theta     - Azimuth (in degrees) to round to the nearest possible value
%               smaller than theta.
%   phi       - Elevation (in degrees) to locate possible values of theta
%               REQUIRED: phi must be a viable value of phi present in the
%               HRIR struct.
%
% Output:
%   prev_theta - The nearest viable value of theta smaller than the one
%                provided.
%
% Example:
%     get_prev_theta(l_hrir, 17, 30)  -->  15
%     get_prev_theta(r_hrir, 12, -30) -->  0
%     get_prev_theta(r_hrir, 39, 60)  -->  30
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: get_prev_phi, get_nearest_theta, get_next_theta
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    possible_theta = orig_hrir.azim_v(ismember(orig_hrir.elev_v, phi)==1);
    rev_possible_theta = flip(possible_theta);
    
    prev_theta = 0;
    
    for i = 1 : length(rev_possible_theta)
        if rev_possible_theta(i) <= theta
            prev_theta = rev_possible_theta(i);
            break;
        end
    end
% -------------------- END CODE --------------------
end

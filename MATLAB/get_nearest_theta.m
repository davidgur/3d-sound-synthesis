function nearest_theta = get_nearest_theta(orig_hrir, theta, phi)
% get_nearest_theta - returns the nearest theta value to the one provided.
%
% The HRIR dataset that is used provides only some values of theta. This
% function determines the closest possible value of theta to the one provided
% as an argument to this function.
%
% Inputs:
%   orig_hrir - One of the HRIR structs provided the MAT file
%   theta     - Azimuth (in degrees) to round to the nearest possible value
%   phi       - Elevation (in degrees) to locate possible values of theta
%               REQUIRED: phi must be a viable value of phi present in the
%               HRIR struct.
%
% Output:
%   nearest_theta - The nearest viable value of theta to the one provided
%
% Example:
%     get_nearest_theta(l_hrir, 17, 30)  -->  15
%     get_nearest_theta(r_hrir, 12, -30) -->  15
%     get_nearest_theta(r_hrir, 39, 60)  -->  45
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: get_nearest_phi, get_next_theta, get_prev_theta
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    possible_theta = orig_hrir.azim_v(ismember(orig_hrir.elev_v, phi)==1);
    
    [~, idx] = min(abs(possible_theta - theta));
    
    nearest_theta = possible_theta(idx);
% -------------------- END CODE --------------------
end

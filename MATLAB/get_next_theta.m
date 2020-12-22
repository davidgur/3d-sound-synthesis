function next_theta = get_next_theta(orig_hrir, theta, phi)
% get_next_theta - returns the nearest theta value greater than the one
% provided.
%
% The HRIR dataset that is used provides only some values of theta. This
% function determines the closest possible value of theta to the one provided
% as an argument to this function.
%
% Inputs:
%   orig_hrir - One of the HRIR structs provided the MAT file
%   theta     - Azimuth (in degrees) to round to the nearest possible value
%               greater than theta.
%   phi       - Elevation (in degrees) to locate possible values of theta
%               REQUIRED: phi must be a viable value of phi present in the
%               HRIR struct.
%
% Output:
%   next_theta - The nearest viable value of theta greater than the one
%                provided.
%
% Example:
%     get_next_theta(l_hrir, 17, 30)  -->  30
%     get_next_theta(r_hrir, 12, -30) -->  15
%     get_next_theta(r_hrir, 39, 60)  -->  45
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: get_nearest_theta, get_next_phi, get_prev_phi
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    poss_theta = orig_hrir.azim_v(find(ismember(orig_hrir.elev_v, phi)==1));
    
    next_theta = 0;
    
    for i= 1 : length(poss_theta)
       if poss_theta(i) >= theta
           next_theta = poss_theta(i);
           break;
       end
    end
% -------------------- END CODE --------------------
end
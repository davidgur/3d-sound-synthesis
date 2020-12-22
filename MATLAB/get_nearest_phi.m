function nearest_phi = get_nearest_phi(~, ~, phi)
% get_nearest_phi - returns the nearest phi value to the one provided.
%
% The HRIR dataset that is used provides only some values of phi. This
% function determines the closest possible value of phi to the one provided
% as an argument to this function.
%
% Inputs:
%   ~   - Empty Input (for style purposes)
%   ~   - Empty Input (for style purposes)
%   phi - Elevation angle (in degrees) to round to nearest possible value
%
% Output:
%   nearest_phi - The nearest viable value of phi to the one provided
%
% Example:
%     get_nearest_phi(l_hrir, 17, 32)  -->  30
%     get_nearest_phi(r_hrir, 12, -33) --> -30
%     get_nearest_phi(r_hrir, 39, 67)  --> 60
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: get_nearest_theta, get_next_phi, get_prev_phi
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    possible_phi = [-45 -30 -15 0 15 30 45 60 75];
    
    [~, idx] = min(abs(possible_phi - phi));
    nearest_phi = possible_phi(idx);
% -------------------- END CODE --------------------
end
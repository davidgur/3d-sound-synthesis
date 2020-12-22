function next_phi = get_next_phi(~, ~, phi)
% get_next_phi - returns the closest possible phi value greater than the
% one provided.
%
% The HRIR dataset that is used provides only some values of phi. This
% function determines the closest possible value of phi greater than the
% one provided as an argument to this function.
%
% Inputs:
%   ~   - Empty Input (for style purposes)
%   ~   - Empty Input (for style purposes)
%   phi - Elevation angle (in degrees) to round to nearest possible value
%         greater than phi.
%
% Output:
%   next_phi - The closest possible value of phi greater than the one given
%
% Example:
%     get_next_phi(l_hrir, 17, 32)  -->  45
%     get_next_phi(r_hrir, 12, -33) --> -15
%     get_next_phi(r_hrir, 39, 67)  -->  75
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: get_next_theta, get_nearest_phi, get_prev_phi
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    possible_phi = [-45 -30 -15 0 15 30 45 60 75];
    
    next_phi = 0;
    
    for i = 1: length(possible_phi)
        if possible_phi(i) > phi
            next_phi = possible_phi(i);
            break;
        end
    end
% -------------------- END CODE --------------------
end
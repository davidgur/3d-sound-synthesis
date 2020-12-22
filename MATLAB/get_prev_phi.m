function prev_phi = get_prev_phi(~, ~, phi)
% get_prev_phi - returns the closest possible phi value smaller than the
% one provided.
%
% The HRIR dataset that is used provides only some values of phi. This
% function determines the closest possible value of phi smaller than the
% one provided as an argument to this function.
%
% Inputs:
%   ~   - Empty Input (for style purposes)
%   ~   - Empty Input (for style purposes)
%   phi - Elevation angle (in degrees) to round to nearest possible value
%         smaller than phi.
%
% Output:
%   prev_phi - The closest possible value of phi smaller than the one given
%
% Example:
%     get_prev_phi(l_hrir, 17, 32)  -->  30
%     get_prev_phi(r_hrir, 12, -33) --> -45
%     get_prev_phi(r_hrir, 39, 67)  -->  60
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: get_prev_theta, get_nearest_phi, get_next_phi
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    possible_phi = [-45 -30 -15 0 15 30 45 60 75];
    rev_possible_phi = flip(possible_phi);
    
    prev_phi = 0;
    
    for i = 1: length(rev_possible_phi)
        if rev_possible_phi(i) < phi
            prev_phi = rev_possible_phi(i);
            break;
        end
    end
% -------------------- END CODE --------------------
end

function hrir = h(orig_hrir, theta, phi)
% h - determines the HRIR given an azimuth and elevation
%
% Inputs:
%   orig_hrir - One of the HRIR structs provided the MAT file
%   theta     - Azimuth (in degrees)
%   phi       - Elevation (in degrees)
%
%   REQUIRED: theta and phi must be viable values that are actually found
%   in the HRIR structure.
%
% Output:
%   hrir - The HRIR at the given azimuth and elevation
%
% Example:
%     h(l_hrir, 15, 30)  -->  [ARRAY OF LENGTH 512]
%     h(r_hrir, 0, -30)  -->  [ARRAY OF LENGTH 512]
%     h(r_hrir, 45, 60)  -->  [ARRAY OF LENGTH 512]
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: hrir_interpolate, localize
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------
    idxs = find(ismember(orig_hrir.elev_v, phi)==1);
    
    hrir_idx = 0;
    
    for i = 1 : length(idxs)
        if orig_hrir.azim_v(idxs(i)) == theta
            hrir_idx = idxs(i);
            break;
        end
    end
    
    hrir = orig_hrir.content_m(hrir_idx, :);
% -------------------- END CODE --------------------
end
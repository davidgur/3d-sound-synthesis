function hrir = hrir_interpolate(orig_hrir,theta,phi)
% hrir_interpolate gets an interpolated HRIR at an arbitrary theta and phi
%
% The dataset used in this project to get the HRIR is quite sparse.
% However, we want to be able to determine the HRIR at any given location.
% We are able to do this by interpolating the HRIR functions that are
% provided by our dataset. This is done using the generalized bilinear
% interpolation method as described in "Interpolation of Head-Related
% Transfer Functions (HRTFS): A Multi-Source approach" by Freeland,
% Biscainho, and Diniz.
%
% Freeland, F. P., Biscainho, L. W., & Diniz, P. S. (2004, September). 
% Interpolation of head-related transfer functions (HRTFs): A multi-source 
% approach. In 2004 12th European Signal Processing Conference 
% (pp. 1761-1764). IEEE.
%
% Inputs:
%   orig_hrir - One of the HRIR structs provided the MAT file
%   theta     - Azimuth (in degrees)
%   phi       - Elevation (in degrees)
%
%
% Output:
%   hrir - The interpolated HRIR for the given azimuth and elevation
%
% Example:
%     hrir_interpolate(l_hrir, 12, 37)   -->  [ARRAY OF LENGTH 512]
%     hrir_interpolate(r_hrir, -3, -39)  -->  [ARRAY OF LENGTH 512]
%     hrir_interpolate(r_hrir, 47, 62)   -->  [ARRAY OF LENGTH 512]
%
% Other m-files required: get_next_phi.m, get_prev_phi.m, get_next_theta.m,
%                         get_prev_theta.m, get_nearest_theta.m, h.m
% Subfunctions: none
% MAT-files required: IRC_1020_C_HRIR.mat
%
% See also: h, localize, get_next_phi, get_prev_phi, get_next_theta,
%           get_prev_theta, get_nearest_theta
%
% Author: David Gurevich, Hons. BMath Computer Science
%         University of Waterloo, 2025
% Email Address: dgurevic (at) uwaterloo (dot) ca
% December 2020

% ------------------- BEGIN CODE -------------------

A_phi = get_next_phi(orig_hrir, theta, phi);
B_phi = A_phi;
C_phi = get_prev_phi(orig_hrir, theta, A_phi);

A_theta = get_next_theta(orig_hrir, theta, A_phi);
B_theta = get_prev_theta(orig_hrir, theta, B_phi);
C_theta = get_nearest_theta(orig_hrir, theta, C_phi);

if A_theta == B_theta && B_theta == C_theta
    % This is a point already available
    hrir = h(orig_hrir, theta, phi);
else

    delta_theta_grid = B_theta - A_theta;
    delta_theta_A = theta - A_theta;
    delta_theta_AC = C_theta - A_theta;

    delta_phi_grid = C_phi - A_phi;
    delta_phi = phi - A_phi;

    W_C = delta_phi / delta_phi_grid;
    W_B = (delta_theta_A - W_C * delta_theta_AC) / delta_theta_grid;
    W_A = 1 - W_B - W_C;

    hrir = W_A * h(orig_hrir, A_theta, A_phi) + ... 
           W_B * h(orig_hrir, B_theta, B_phi) + ...
           W_C * h(orig_hrir, C_theta, C_phi);
end
% -------------------- END CODE --------------------
end











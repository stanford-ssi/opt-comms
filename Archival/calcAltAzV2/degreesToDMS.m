%test DMS
%converts degrees to DMS
function [DMS] = degreesToDMS(degrees)
    min = (degrees - floor(degrees))*60.0;
    sec = (min - floor(min))*60.0;
    
    deg = floor(degrees);
    min = floor(min);
    sec = floor(sec);
    
    DMS = [deg min sec];
end
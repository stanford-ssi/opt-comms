% converts DMS to degrees
function [degrees] = DMStoDegrees(DMS)
    deg = DMS(1);
    min = DMS(2);
    sec = DMS(3);
    
    if (deg/abs(deg) > 0)
        degrees = deg + min/60 + sec/3600;
    else
        deg = -1*deg;
        degrees = deg + min/60 + sec/3600;
        degrees = -1*degrees;
    end
end
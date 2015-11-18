function [targetAdjustAz, targetAdjustAlt] = calcAltAzSpherical_edits(invector)

    format long
    
    homev = [invector(1), invector(2), invector(3)];
    ref1v = [invector(4), invector(5), invector(6)];
    ref2v = [invector(7), invector(8), invector(9)];
    targetv = [invector(10), invector(11), invector(12)];
    azDiffBetweenRefsdegv = invector(13);
    altDiffBetweenRefsdegv = invector (14);
    
    cartHome = GPStoCartesian(homev);
    cartRef1 = GPStoCartesian(ref1v);
    cartRef2 = GPStoCartesian(ref2v);
    cartTarget = GPStoCartesian(targetv);
 
    azDiffBetweenRefs = toRadians(azDiffBetweenRefsdegv);
    altDiffBetweenRefs = toRadians(altDiffBetweenRefsdegv);
    
    vRef1 = vectorFromHome(cartHome,cartRef1);
    vRef2 = vectorFromHome(cartHome,cartRef2);
   
    vTarget = vectorFromHome(cartHome,cartTarget);
    
    % Calculate necessary alt/az adjustment to reach target by iteration
    aRef1Target = perceivedAngle(vRef1,vTarget);
    aRef1Ref2 = perceivedAngle(vRef1,vRef2);
    aRef2Target = perceivedAngle(vRef2,vTarget);
    
    azOffsetGuess = aRef2Target;
    aboveOrBelowRefs = dot(cross(vRef2,vRef1),vTarget);
    aboveOrBelowRefs = aboveOrBelowRefs/abs(aboveOrBelowRefs);
    tolerance = 0.01;
    step = 0.001;
    
    while(true)
        projectedAltOffset = aboveOrBelowRefs*acos((cos(aRef2Target))/(cos(azOffsetGuess)));
        projectedAzOffset = acos((cos(aRef1Target))/(cos(altDiffBetweenRefs + projectedAltOffset))) - azDiffBetweenRefs;
        if (abs(projectedAzOffset - azOffsetGuess) < tolerance)
            break
        end
        azOffsetGuess = azOffsetGuess - step;
    end
    
    % Display results
    projectedAltOffset = toDegrees(projectedAltOffset);
    projectedAzOffset = toDegrees(azOffsetGuess);
   
    
    if projectedAltOffset > 90
       projectedAltOffset = 180 - projectedAltOffset; 
    end
    if projectedAzOffset > 90
       projectedAzOffset = 180 - projectedAzOffset; 
    end
    
    targetAdjustAz =(projectedAzOffset + azDiffBetweenRefs);
    targetAdjustAlt =(projectedAltOffset + altDiffBetweenRefs);
end

% resetAxis takes three axis bounds and three new points, and redefines the
% plot bounds
function [xSet, ySet, zSet] = resetAxis(xSet,ySet,zSet,x,y,z)

    global skale

    xSet = sort(unique([xSet,(x/abs(x))*skale]));
        if length(xSet) == 3
          xSet = xSet(xSet~=0);
        end
    ySet = sort(unique([ySet,(y/abs(y))*skale]));
        if length(ySet) == 3
           ySet = ySet(ySet~=0);
        end
    zSet = sort(unique([zSet,(z/abs(z))*skale]));
        if length(zSet) == 3
             zSet = zSet(zSet~=0);
        end
end

% animation draws the intermediate lines between two points
function [] = animation(laser,v1,v2)
    
    nsteps = 20;
    
    xstep = (v2(1) - v1(1))/nsteps;
    ystep = (v2(2) - v1(2))/nsteps;
    zstep = (v2(3) - v1(3))/nsteps;
    
    for i = 1:nsteps
        addpoints(laser,0,0,0)
        addpoints(laser,(v1(1)+i*xstep),(v1(2)+i*ystep),(v1(3)+i*zstep));
        drawnow
        pause(0.02)
    end

end

% percievedAngle takes two position vectors, running from home to reference
% points, and calculates the angle between them in radians
function [theta] = perceivedAngle (v1,v2)
    theta = acos(dot(v1,v2)/(vectorDistance(v1)*vectorDistance(v2)));
end

% vectorDistance calculates the length of a position vector
function [length] = vectorDistance (vector)
    length = sqrt(vector(1)^2 + vector(2)^2 + vector(3)^2);
end

% vectorFromHome takes two [x,y,z] points, one for your home location, and
% one for a reference point, and creates a position vector running from
% home to the reference point
function [vector] = vectorFromHome(home,point)
    deltax = point(1) - home(1);
    deltay = point(2) - home(2);
    deltaz = point(3) - home(3);
    
    vector = [deltax,deltay,deltaz];
end

% GPStoCartesian takes a GPS vector [lat,long,alt], with latitude and longitude 
% in decimal degrees, and altitude in m, and converts to x, y, z coordinates with 
% the origin at the center of the Earth.
function [point] = GPStoCartesian (GPS)
    lat = GPS(1);
    long = GPS(2);
    alt = GPS(3);
    earthDiameter = 12738; %km at sea level, averaging to account for 43 km equatorial bulge
    
    % convert lat, long, and alt to spherical coordinates about Earth's center
    r = (earthDiameter*1000)/2 + alt;
    theta = toRadians(long);
    phi = toRadians(90 - lat);
    
    x = r*sin(phi)*cos(theta);
    y = r*sin(phi)*sin(theta);
    z = r*cos(phi);
    
    point = [x,y,z];
end

% converts degrees to radians
function [radians] = toRadians(degrees)
    radians = (degrees/360)*2*pi;
end

% converts radians to degrees
function [degrees] = toDegrees(radians)
    degrees = (radians/(2*pi))*360;
end

% converts degrees to DMS
function [DMS] = degreesToDMS(degrees)
    min = (degrees - floor(degrees))*60.0;
    sec = (min - floor(min))*60.0;
    
    deg = floor(degrees);
    min = floor(min);
    sec = floor(sec);
    
    DMS = [deg min sec];
end

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


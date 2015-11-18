function main
 
    clear
    clc
    format long g

    global skale
    skale = 1000; % m
    
    % Ask for home coordinates and plot
    dialog = inputdlg({'Latitude:','Longitude:','Altitude:'},...
              'Enter Home', [1 50; 1 50; 1 30]);   
    home = [str2num(dialog{1}),str2num(dialog{2}),str2num(dialog{3})];
    cartHome = GPStoCartesian(home);
    scatter3(cartHome(1)-cartHome(1),cartHome(2)-cartHome(2),cartHome(3)-cartHome(3),'r')
    axis([0 skale 0 skale 0 skale]), xlabel('x (m)'), ylabel('y (m)'), zlabel('z (m)')
    hold on
    
    % Ask for first reference coordinates and plot
    dialog = inputdlg({'Latitude:','Longitude:','Altitude:'},...
              'Enter Left Reference', [1 50; 1 50; 1 30]); 
    ref1 = [str2num(dialog{1}),str2num(dialog{2}),str2num(dialog{3})];
    cartRef1 = GPStoCartesian(ref1);
    x = cartRef1(1)-cartHome(1);
    y = cartRef1(2)-cartHome(2);
    z = cartRef1(3)-cartHome(3);
    scatter3(x,y,z,'g')
    xSet = sort([0 (x/abs(x))*skale]);
    ySet = sort([0 (y/abs(y))*skale]);
    zSet = sort([0 (z/abs(z))*skale]);
    axis([xSet ySet zSet])
    
    % Ask for second reference coordinates and plot
    dialog = inputdlg({'Latitude:','Longitude:','Altitude:'},...
              'Enter Right Reference', [1 50; 1 50; 1 30]); 
    ref2 = [str2num(dialog{1}),str2num(dialog{2}),str2num(dialog{3})];
    cartRef2 = GPStoCartesian(ref2);
    x = cartRef2(1)-cartHome(1);
    y = cartRef2(2)-cartHome(2);
    z = cartRef2(3)-cartHome(3);
    scatter3(x,y,z,'g')
    [xSet,ySet,zSet] = resetAxis(xSet,ySet,zSet,x,y,z);
    axis([xSet ySet zSet])
    
    % Ask for target coordinates and plot
    dialog = inputdlg({'Latitude:','Longitude:','Altitude:'},...
              'Enter Target', [1 50; 1 50; 1 30]); 
    target = [str2num(dialog{1}),str2num(dialog{2}),str2num(dialog{3})];
    cartTarget = GPStoCartesian(target);
    x = cartTarget(1)-cartHome(1);
    y = cartTarget(2)-cartHome(2);
    z = cartTarget(3)-cartHome(3);
    scatter3(x,y,z,'m')
    [xSet,ySet,zSet] = resetAxis(xSet,ySet,zSet,x,y,z);
    axis([xSet ySet zSet])
    laser = animatedline('MaximumNumPoints',2);
    laser.Color = 'blue';
    addpoints(laser,0,0,0);
    
    % Ask for user to measure delta alt/az between reference points
    pause(0.25)
    vRef1 = vectorFromHome(cartHome,cartRef1);
    addpoints(laser,vRef1(1),vRef1(2),vRef1(3));
    drawnow
    pause(0.25)
    waitfor(msgbox('Point towards first reference point and zero scale'))
    pause(0.25)
    
    vRef2 = vectorFromHome(cartHome,cartRef2);
    animation(laser,vRef1,vRef2);

    pause(0.25)
    waitfor(msgbox('Point towards second reference point and note delta alt/az between references'))
    pause(0.25)
    
    dialog = inputdlg({'Degrees:','Minutes:','Seconds:'},...
              'Enter Delta Azimuth', [1 40; 1 40; 1 40]);
    azDiffDeg = str2num(dialog{1});
    azDiffMin = str2num(dialog{2});
    azDiffSec = str2num(dialog{3});
    azDiffBetweenRefs = toRadians(DMStoDegrees([azDiffDeg azDiffMin azDiffSec]));
    dialog = inputdlg({'Degrees:','Minutes:','Seconds:'},...
              'Enter Delta Altitude', [1 40; 1 40; 1 40]);
    altDiffDeg = str2num(dialog{1});
    altDiffMin = str2num(dialog{2});
    altDiffSec = str2num(dialog{3});
    altDiffBetweenRefs = toRadians(DMStoDegrees([altDiffDeg altDiffMin altDiffSec]));
    
    vTarget = vectorFromHome(cartHome,cartTarget);
    
    % Calculate necessary alt/az adjustment to reach target by iteration
    aRef1Target = perceivedAngle(vRef1,vTarget);
    aRef1Ref2 = perceivedAngle(vRef1,vRef2)
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
    
    targetAdjustAz = degreesToDMS(projectedAzOffset + azDiffBetweenRefs);
    targetAdjustAlt = degreesToDMS(projectedAltOffset + altDiffBetweenRefs);
    
    h = msgbox({['Adjust Azimuth to: ',num2str(targetAdjustAz(1)),' degrees, ',num2str(targetAdjustAz(2)),' minutes, ',num2str(targetAdjustAz(3)),' seconds.'],['Adjust Altitude to: ',num2str(targetAdjustAlt(1)),' degrees, ',num2str(targetAdjustAlt(2)),' minutes, ',num2str(targetAdjustAlt(3)),' seconds.']})
    animation(laser,vRef2,vTarget);
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


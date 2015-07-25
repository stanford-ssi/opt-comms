%This script is rather slow and loads either the OSM server or a single 
%processor core
disp('starting')
DELTA = 0.0005; %degrees of lat/lon, approximately 55 meters (180ft) at SFO
MINDISTANCE = 20; %km, is arbitrary
RECORDDISTANCE = 278; %km
EARTHCIRCUMFERENCE = 40075; %km at equator

% P = gpxread('/SMP_20140921_0715.GPX'); %all of US and Canada
 P = gpxread('/SMP_20140921_1805.GPX'); %carolinas only
% P = gpxread('/SMP_20140921_1840.GPX'); %mississippi only (single peak)
disp(strcat(num2str(P.length), ' mountains loaded'))

%if xml directory is not present, create it and download xml files
if ~exist('osmxml','dir')
    mkdir('osmxml');
    disp('downloading OSM data');
    arrayfun(@(x) downloadosm(x, DELTA), P);
else
    disp('OSM data already present. Skipping download...');
end

display('Checking for roads near peaks. This may take awhile.');
%for every peak, check for presence of roads
%preallocate and parallelize for-loop this. xml2struct is the bottleneck.
hasroad = arrayfun(@(y) checkxmlforroad(y), P);

%loop through all peaks. If no roads present, remove both P entry and
%hasroad entry
n = 1;
while n <= P.length
    if hasroad(n) == 0;
        P(n) = [];
        hasroad(n) = [];
    else
        n = n+1;
    end
end
maxpairs = nchoosek(P.length, 2);
disp(strcat(num2str(P.length), ' mountains have roads near them'))
if P.length > 0
    disp(strcat(num2str(maxpairs), ' different ways mountains with roads can be paired'));
end

display('Verifying that each pair of mountins is within acceptable distance range');
%preallocate mountain pairs
%pairs = repmat(geopoint(),numpairs,2);

%preallocate and parallelize for-loop this.
numpairs = 0;
for i = 1:P.length - 1;
    j = i + 1;
    for j = i:P.length;
        dist = distance(P(i).Latitude, P(i).Longitude, P(j).Latitude, P(j).Longitude)/360 * EARTHCIRCUMFERENCE;        
        if dist > MINDISTANCE && dist < RECORDDISTANCE * 1.3
            numpairs = numpairs + 1;
        end
    end
end
disp(strcat(num2str(numpairs), ' useful pairs found'))

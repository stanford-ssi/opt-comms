function [ ] = downloadosm( geopoint, DELTA )
%downloadosm downloads highway tage within DELTA lat/lon of a geopoint
%   Detailed explanation goes here

s = geopoint.Latitude - DELTA;
w = geopoint.Longitude - DELTA;
n = geopoint.Latitude + DELTA;
e = geopoint.Longitude + DELTA;
boundingbox = strcat('(', num2str(s), ', ', num2str(w), ', ', num2str(n), ', ', num2str(e), ');');

apiquery = strcat('way["highway"]', boundingbox, 'out body;');
apiurl = strcat('http://overpass-api.de/api/interpreter?data=', urlencode(apiquery));
filename = strcat('osmxml/', strrep(geopoint.Name, '/', '-'), '.xml');

urlwrite(apiurl, filename);

end

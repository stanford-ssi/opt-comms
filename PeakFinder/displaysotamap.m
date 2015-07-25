function [ ] = displaysotamap( geopoint )
%Opens system web browser to summit page on sotamaps.org
%   Detailed explanation goes here

url = strcat('http://www.sotamaps.org/index.php?smt=',geopoint.Name);
web(url,'-browser')

end


function [ hasroad ] = checkxmlforroad( geopoint )
%checks xml file of geopoint for any entries. 
%   Returns 1 if entries preset
%   Returns 0 if no entries present

filename = strcat('osmxml/', strrep(geopoint.Name, '/', '-'), '.xml');
 result = xml2struct(filename);
 try
     result.osm.way;
     hasroad = 1;
 catch
     hasroad = 0;
     
end

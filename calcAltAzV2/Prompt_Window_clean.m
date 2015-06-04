function varargout = Prompt_Window_clean(varargin)
% PROMPT_WINDOW_CLEAN MATLAB code for Prompt_Window_clean.fig
%      PROMPT_WINDOW_CLEAN, by itself, creates a new PROMPT_WINDOW_CLEAN or raises the existing
%      singleton*.
%
%      H = PROMPT_WINDOW_CLEAN returns the handle to a new PROMPT_WINDOW_CLEAN or the handle to
%      the existing singleton*.
%
%      PROMPT_WINDOW_CLEAN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PROMPT_WINDOW_CLEAN.M with the given input arguments.
%
%      PROMPT_WINDOW_CLEAN('Property','Value',...) creates a new PROMPT_WINDOW_CLEAN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Prompt_Window_clean_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Prompt_Window_clean_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Prompt_Window_clean

% Last Modified by GUIDE v2.5 01-Jun-2015 17:41:50

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Prompt_Window_clean_OpeningFcn, ...
                   'gui_OutputFcn',  @Prompt_Window_clean_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Prompt_Window_clean is made visible.
function Prompt_Window_clean_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Prompt_Window_clean (see VARARGIN)

% Choose default command line output for Prompt_Window_clean
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

%Initial istructions at top of gui
set(handles.instructions,'String','Type value for Scale. Select coordinates for Home and press Enter Coordinates');


% --- Outputs from this function are returned to the command line.
function varargout = Prompt_Window_clean_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Submitleft.
function Submitleft_Callback(hObject, eventdata, handles)
% hObject    handle to Submitleft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Returns entered GPS data
ref1 = [str2double(get(handles.leftlat,'String')), str2double(get(handles.leftlong,'String')), str2double(get(handles.leftalt,'String'))];
homeset = [str2double(get(handles.homelat,'String')), str2double(get(handles.homelong,'String')), str2double(get(handles.homealt,'String'))];

%plots scatter points on figure
[cartRef1] = GPStoCartesian(ref1);
[cartHome] = GPStoCartesian(homeset);

%sets scale
skale = str2num(get(handles.scalevalue,'String'));
 
    
%Plots scatter points
hold on
scatter3(cartRef1(1)-cartHome(1),cartRef1(2)-cartHome(2),cartRef1(3)-cartHome(3),'g')

%Progresses instructions
set(handles.instructions,'String','Select coordinates for Right Reference and press Enter Coordinates');

% --- Executes on button press in Submithome.
function Submithome_Callback(hObject, eventdata, handles)
% hObject    handle to Submithome (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Returns entered GPS data
homeset = [str2double(get(handles.homelat,'String')), str2double(get(handles.homelong,'String')), str2double(get(handles.homealt,'String'))];

%plots scatter points on figure
[cartHome] = GPStoCartesian(homeset);
skale = str2num(get(handles.scalevalue,'String'));
scatter3(cartHome(1)-cartHome(1),cartHome(2)-cartHome(2),cartHome(3)-cartHome(3),'r')
   axis([-skale skale -skale skale -skale skale]), xlabel('x (m)'), ylabel('y (m)'), zlabel('z (m)')
    hold on
%Progresses Directions
set(handles.instructions,'String','Select coordinates for Target and press Enter Coordinates');

% --- Executes on button press in Submittarget.
function Submittarget_Callback(hObject, eventdata, handles)
% hObject    handle to Submittarget (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Returns entered GPS data
target = [str2double(get(handles.targetlat,'String')),str2double(get(handles.targetlong,'String')),str2double(get(handles.targetalt,'String'))];
homeset = [str2double(get(handles.homelat,'String')), str2double(get(handles.homelong,'String')), str2double(get(handles.homealt,'String'))];

%gets cartesian points
[cartHome] = GPStoCartesian(homeset);
[cartTarget] = GPStoCartesian(target);

%sets scale
skale = str2num(get(handles.scalevalue,'String'));

%Plots scatter points
hold on
scatter3(cartTarget(1)-cartHome(1),cartTarget(2)-cartHome(2),cartTarget(3)-cartHome(3),'k')
axis([-skale skale -skale skale -skale skale]), xlabel('x (m)'), ylabel('y (m)'), zlabel('z (m)')

%Progresses instructions
set(handles.instructions,'String','Select coordinates for Left Reference and press Enter Coordinates');

% --- Executes on button press in Submitright.
function Submitright_Callback(hObject, eventdata, handles)
% hObject    handle to Submitright (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% returns entered GPS data
ref2 = [str2double(get(handles.rightlat,'String')),str2double(get(handles.rightlong,'String')),str2double(get(handles.rightalt,'String'))];
homeset = [str2double(get(handles.homelat,'String')), str2double(get(handles.homelong,'String')), str2double(get(handles.homealt,'String'))];

%gets cartesian points
[cartRef2] = GPStoCartesian(ref2);
[cartHome] = GPStoCartesian(homeset);

%sets scale
skale = str2num(get(handles.scalevalue,'String'));
 
%graphs scatter points
hold on   
scatter3(cartRef2(1)-cartHome(1),cartRef2(2)-cartHome(2),cartRef2(3)-cartHome(3),'g')
axis([-skale skale -skale skale -skale skale]), xlabel('x (m)'), ylabel('y (m)'), zlabel('z (m)')
%Progresses instructions
set(handles.instructions,'String','Zero angle to Left Reference. Align to Right Reference. Type change in Azimuth and Altitude. Hit Enter Angles.');

% --- Executes on button press in Submitangles.
function Submitangles_Callback(hObject, eventdata, handles)
% hObject    handle to Submitangles (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%sets up vectors for calcAltAzSherical_edits
homeset = [str2double(get(handles.homelat,'String')), str2double(get(handles.homelong,'String')), str2double(get(handles.homealt,'String'))];
ref1 = [str2double(get(handles.leftlat,'String')), str2double(get(handles.leftlong,'String')), str2double(get(handles.leftalt,'String'))];
ref2 = [str2double(get(handles.rightlat,'String')), str2double(get(handles.rightlong,'String')), str2double(get(handles.rightalt,'String'))];
target = [str2double(get(handles.targetlat,'String')), str2double(get(handles.targetlong,'String')), str2double(get(handles.targetalt,'String'))];
azDiffBetweenRefsdeg = str2num(get(handles.deltaaz,'String'));
altDiffBetweenRefsdeg = str2num(get(handles.deltaalt,'String'));

%runs function calcAltAzSherical_edits
inputvector = [homeset,ref1,ref2,target,azDiffBetweenRefsdeg,altDiffBetweenRefsdeg];
[adjustaz,adjustalt] = calcAltAzSpherical_edits(inputvector);

%Converts to angle from zero
gotoaz = str2num(get(handles.deltaaz, 'String'))+ adjustaz;
gotoalt = str2num(get(handles.deltaalt, 'String')) + adjustalt;

%Makes all angles positive
if (gotoaz < 0)
    finalgotoaz = 360 + gotoaz;
else finalgotoaz = gotoaz;
end

if (gotoalt < 0)
    finalgotoalt = 360 + gotoalt;
else finalgotoalt = gotoalt;
end

%Dislays angles from zero in decimal
set(handles.outputazdeg,'String',finalgotoaz);
set(handles.outputaltdeg,'String',finalgotoalt);

%Converts to hex and displays in gui
gotoazhex = floor(finalgotoaz*(2^32)/360);
gotoalthex = floor(finalgotoalt*(2^32)/360);
outputazhex = sprintf('%08X',gotoazhex);
outputalthex = sprintf('%08X',gotoalthex);
set(handles.outputazhex,'String',outputazhex);
set(handles.outputalthex,'String',outputalthex);

%Progresses instructions
set(handles.instructions, 'String', 'Move to Output Azimuth and Altitude (Measured from Zero)');

function scalevalue_Callback(hObject, eventdata, handles)
% hObject    handle to scalevalue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%Sets Axes Scale
global skale
skale = str2double(get(handles.scalevalue,'String'));

% --- Executes during object creation, after setting all properties.
function scalevalue_CreateFcn(hObject, eventdata, handles)
% hObject    handle to scalevalue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function deltaalt_Callback(hObject, eventdata, handles)
% hObject    handle to deltaalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function deltaalt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to deltaalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in targetlist.
function targetlist_Callback(hObject, eventdata, handles)
% hObject    handle to targetlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Presents menu with common points, auto fills gps data
targetcoord = get(handles.targetlist,'Value');
if (targetcoord==1);
    set(handles.targetlat,'String','');
    set(handles.targetlong,'String','');
    set(handles.targetalt,'String','');
elseif (targetcoord==2);
    set(handles.targetlat,'String','37.42413545513234');
    set(handles.targetlong,'String','-122.1778012756289');
    set(handles.targetalt,'String','44.355');
elseif (targetcoord==3);
    set(handles.targetlat,'String','37.42302673007311');
    set(handles.targetlong,'String','-122.17407774918684');
    set(handles.targetalt,'String','40.976');
elseif (targetcoord==4);
    set(handles.targetlat,'String','37.32464813341786');
    set(handles.targetlong,'String','-122.2045127749443');
    set(handles.targetalt,'String','714.306');
elseif (targetcoord==5);
    set(handles.targetlat,'String','37.40285060555813');
    set(handles.targetlong,'String','-122.16551747918129');
    set(handles.targetalt,'String','139.703');
end


% --- Executes during object creation, after setting all properties.
function targetlist_CreateFcn(hObject, eventdata, handles)
% hObject    handle to targetlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function targetlat_Callback(hObject, eventdata, handles)
% hObject    handle to targetlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function targetlat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to targetlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function targetlong_Callback(hObject, eventdata, handles)
% hObject    handle to targetlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function targetlong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to targetlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function targetalt_Callback(hObject, eventdata, handles)
% hObject    handle to targetalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function targetalt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to targetalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in homelist.
function homelist_Callback(hObject, eventdata, handles)
% hObject    handle to homelist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% % Presents menu with common points, auto fills gps data
homecoord = get(handles.homelist,'Value');
if (homecoord==1);
    set(handles.homelat,'String','');
    set(handles.homelong,'String','');
    set(handles.homealt,'String','');
elseif (homecoord==2);
    set(handles.homelat,'String','37.42413545513234');
    set(handles.homelong,'String','-122.1778012756289');
    set(handles.homealt,'String','44.355');
elseif (homecoord==3);
    set(handles.homelat,'String','37.42302673007311');
    set(handles.homelong,'String','-122.17407774918684');
    set(handles.homealt,'String','40.976');
elseif (homecoord==4);
    set(handles.homelat,'String','37.32464813341786');
    set(handles.homelong,'String','-122.2045127749443');
    set(handles.homealt,'String','714.306');
elseif (homecoord==5);
    set(handles.homelat,'String','37.40285060555813');
    set(handles.homelong,'String','-122.16551747918129');
    set(handles.homealt,'String','139.703');
end


% --- Executes during object creation, after setting all properties.
function homelist_CreateFcn(hObject, eventdata, handles)
% hObject    handle to homelist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function homelat_Callback(hObject, eventdata, handles)
% hObject    handle to homelat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function homelat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to homelat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function homelong_Callback(hObject, eventdata, handles)
% hObject    handle to homelong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function homelong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to homelong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function homealt_Callback(hObject, eventdata, handles)
% hObject    handle to homealt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function homealt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to homealt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in rightlist.
function rightlist_Callback(hObject, eventdata, handles)
% hObject    handle to rightlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Presents menu with common points, auto fills gps data

rightcoord = get(handles.rightlist,'Value');
if (rightcoord==1);
    set(handles.rightlat,'String','');
    set(handles.rightlong,'String','');
    set(handles.rightalt,'String','');
elseif (rightcoord==2);
    set(handles.rightlat,'String','37.408589439699526');
    set(handles.rightlong,'String','-122.17960041760989');
    set(handles.rightalt,'String','148.309');
elseif (rightcoord==3);
    set(handles.rightlat,'String','37.42107550450937');
    set(handles.rightlong,'String','-122.17386719584056');
    set(handles.rightalt,'String','44.984');
elseif (rightcoord==4);
    set(handles.rightlat,'String','37.424183382358386');
    set(handles.rightlong,'String','-122.17614036791929');
    set(handles.rightalt,'String','43.350');
elseif (leftcoord==5);
    set(handles.rightlat,'String','37.423648725787935');
    set(handles.rightlong,'String','-122.17804937996789');
    set(handles.rightalt,'String','42.443');
elseif (leftcoord==6);
    set(handles.rightlat,'String','37.461018678799896');
    set(handles.rightlong,'String','-122.11524993181229');
    set(handles.rightalt,'String','0.854');
elseif (leftcoord==7);
    set(handles.rightlat,'String','37.51252393234854');
    set(handles.rightlong,'String','-122.25018315017223');
    set(handles.rightalt,'String','1.467');
elseif (leftcoord==8);
    set(handles.rightlat,'String','37.619377743137015');
    set(handles.rightlong,'String','-122.37389668822289');
    set(handles.rightalt,'String','1.914');
elseif (leftcoord==9);
    set(handles.rightlat,'String','37.710500127663714');
    set(handles.rightlong,'String','-122.22563557326794');
    set(handles.rightalt,'String','0.465');
elseif (leftcoord==10);
    set(handles.rightlat,'String','37.65835694479813');
    set(handles.rightlong,'String','-122.12151154875755');
    set(handles.rightalt,'String','10.468');
end


% --- Executes during object creation, after setting all properties.
function rightlist_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rightlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function rightlat_Callback(hObject, eventdata, handles)
% hObject    handle to rightlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function rightlat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rightlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function rightlong_Callback(hObject, eventdata, handles)
% hObject    handle to rightlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --- Executes during object creation, after setting all properties.
function rightlong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rightlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function rightalt_Callback(hObject, eventdata, handles)
% hObject    handle to rightalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function rightalt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rightalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in leftlist.
function leftlist_Callback(hObject, eventdata, handles)
% hObject    handle to leftlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Presents menu with common points, auto fills gps data
leftcoord = get(handles.leftlist,'Value');
if (leftcoord==1);
    set(handles.leftlat,'String','');
    set(handles.leftlong,'String','');
    set(handles.leftalt,'String','');
elseif (leftcoord==2);
    set(handles.leftlat,'String','37.408589439699526');
    set(handles.leftlong,'String','-122.17960041760989');
    set(handles.leftalt,'String','148.309');
elseif (leftcoord==3);
    set(handles.leftlat,'String','37.42107550450937');
    set(handles.leftlong,'String','-122.17386719584056');
    set(handles.leftalt,'String','44.984');
elseif (leftcoord==4);
    set(handles.leftlat,'String','37.424183382358386');
    set(handles.leftlong,'String','-122.17614036791929');
    set(handles.leftalt,'String','43.350');
elseif (leftcoord==5);
    set(handles.leftlat,'String','37.423648725787935');
    set(handles.leftlong,'String','-122.17804937996789');
    set(handles.leftalt,'String','42.443');
elseif (leftcoord==6);
    set(handles.leftlat,'String','37.461018678799896');
    set(handles.leftlong,'String','-122.11524993181229');
    set(handles.leftalt,'String','0.854');
elseif (leftcoord==7);
    set(handles.leftlat,'String','37.51252393234854');
    set(handles.leftlong,'String','-122.25018315017223');
    set(handles.leftalt,'String','1.467');
elseif (leftcoord==8);
    set(handles.leftlat,'String','37.619377743137015');
    set(handles.leftlong,'String','-122.37389668822289');
    set(handles.leftalt,'String','1.914');
elseif (leftcoord==9);
    set(handles.leftlat,'String','37.710500127663714');
    set(handles.leftlong,'String','-122.22563557326794');
    set(handles.leftalt,'String','0.465');
elseif (leftcoord==10);
    set(handles.leftlat,'String','37.65835694479813');
    set(handles.leftlong,'String','-122.12151154875755');
    set(handles.leftalt,'String','10.468');
end


% --- Executes during object creation, after setting all properties.
function leftlist_CreateFcn(hObject, eventdata, handles)
% hObject    handle to leftlist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function leftlat_Callback(hObject, eventdata, handles)
% hObject    handle to leftlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function leftlat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to leftlat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function leftlong_Callback(hObject, eventdata, handles)
% hObject    handle to leftlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function leftlong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to leftlong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function leftalt_Callback(hObject, eventdata, handles)
% hObject    handle to leftalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function leftalt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to leftalt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function outputaltdeg_Callback(hObject, eventdata, handles)
% hObject    handle to outputaltdeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function outputaltdeg_CreateFcn(hObject, eventdata, handles)
% hObject    handle to outputaltdeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function outputazhex_Callback(hObject, eventdata, handles)
% hObject    handle to outputazhex (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function outputazhex_CreateFcn(hObject, eventdata, handles)
% hObject    handle to outputazhex (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function outputazdeg_Callback(hObject, eventdata, handles)
% hObject    handle to outputazdeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function outputazdeg_CreateFcn(hObject, eventdata, handles)
% hObject    handle to outputazdeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function outputalthex_Callback(hObject, eventdata, handles)
% hObject    handle to outputalthex (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function outputalthex_CreateFcn(hObject, eventdata, handles)
% hObject    handle to outputalthex (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in convertminsec.
function convertminsec_Callback(hObject, eventdata, handles)
% hObject    handle to convertminsec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%Converts to Degrees Minutes Seconds returns in gui

indeg = str2double(get(handles.condec,'String'));
[dms] = degreesToDMS(indeg);
set(handles.condeg,'String',dms(1));
set(handles.conmin,'String',dms(2));
set(handles.consec,'String',dms(3));


% --- Executes on button press in convertdec.
function convertdec_Callback(hObject, eventdata, handles)
% hObject    handle to convertdec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%Converts to Degrees returns in gui
indms = [str2double(get(handles.condeg,'String')), str2double(get(handles.conmin,'String')), str2double(get(handles.consec,'String'))];
[dec] = DMStoDegrees(indms);
set(handles.condec,'String',dec);


function condeg_Callback(hObject, eventdata, handles)
% hObject    handle to condeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function condeg_CreateFcn(hObject, eventdata, handles)
% hObject    handle to condeg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function condec_Callback(hObject, eventdata, handles)
% hObject    handle to condec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function condec_CreateFcn(hObject, eventdata, handles)
% hObject    handle to condec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function conmin_Callback(hObject, eventdata, handles)
% hObject    handle to conmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function conmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to conmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function consec_Callback(hObject, eventdata, handles)
% hObject    handle to consec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function consec_CreateFcn(hObject, eventdata, handles)
% hObject    handle to consec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on mouse press over axes background.
function axes1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


function deltaaz_Callback(hObject, eventdata, handles)
% hObject    handle to deltaaz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function deltaaz_CreateFcn(hObject, eventdata, handles)
% hObject    handle to deltaaz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in clear.
function clear_Callback(hObject, eventdata, handles)
% hObject    handle to clear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%clears all text boxes, resets instructions
set(handles.leftlat,'String','');
set(handles.leftlong,'String','');
set(handles.leftalt,'String','');
set(handles.homelat,'String','');
set(handles.homelong,'String','');
set(handles.homealt,'String','');
set(handles.rightlat,'String','');
set(handles.rightlong,'String','');
set(handles.rightalt,'String','');
set(handles.targetlat,'String','');
set(handles.targetlong,'String','');
set(handles.targetalt,'String','');
set(handles.scalevalue,'String','');
set(handles.deltaaz,'String','');
set(handles.deltaalt,'String','');
set(handles.outputazdeg,'String','');
set(handles.outputaltdeg,'String','');
set(handles.outputazhex,'String','');
set(handles.outputalthex,'String','');
set(handles.condeg,'String','');
set(handles.conmin,'String','');
set(handles.consec,'String','');
set(handles.condec,'String','');
set(handles.instructions,'String','Type value for Scale. Select coordinates for Home and press Enter Coordinates');
cla;

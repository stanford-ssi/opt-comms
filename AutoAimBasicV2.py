"""
AutoAimBasicV2.py 

Developed by Cameron Ramos and Sasha Maldonado 

This program was created for the Stanford Student Space Initiative Optical Communications Team. 

AutoAimBasicV2 accepts a set of GPS coordinates and a set of corresponding elevations. 
The program generates the vertical angle and bearing that points from one coordinate to the other. 
Once connected to a serial controlled aiming mount, a section of the code can be uncommented 
to generate a hex output that commands the aiming mount to move to the calculated tilt and bearing.

The program also has several new features:

 ---->  Save your sessions! Navigate to File > Save. You will be prompted to save you current session as
        a .txt file. 

 ---->  Spiral Search! New buttons to execute a fine or coarse search pattern in increments of .005/.01 degrees.

 ---->  Keyboard control! Control the pan/tilt unit from the keyboard in increments of .005 degrees

This program requires you have installed pyserial. To install, go here: 
http://pyserial.sourceforge.net/pyserial.html#installation

This program also requires the basic built in Python gui class, Tkinter. 
You should not need to install this library

Run this program from Terminal (Mac) or Command Prompt (Windows) or Command Line (Linux)
First, navigate to the folder where the program file is stored. Then: 

Mac or Linux: $ python AutoAimBasicV2.py (and then click return)
Windows: python "D:/Folder name AutoAimGui.py" (and then click enter)

Created on Mar 23 2015 by Cameron Ramos
Last Edited on Mar 24 2015 by Cameron Ramos

---------LICENSING INFORMATION----------
    Copyright (C) 2015  Cameron Ramos

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    A copy of the GNU General Public License can be found at:
    <http://www.gnu.org/licenses/>.

"""

from Tkinter import *
# UNCOMMENT TO SEE GREAT CIRCLE DISTANCE
#from geopy.distance import vincenty
from cmath import *
from math import *
import serial
from ttk import Style
import tkFileDialog
from time import strftime, sleep


# Global Variables

currentAltitude = 0.0
currentAzimuth = 0.0
currentDeviation = 1
currentReading = " "
generations = 0
spiralStatus = "NO"
stopStatus = "NO"

def file_save():
    global generations
    global currentReading

    if generations == 0:
        print " PROGRAM HAS NOT BEEN EXECUTED "
        return

    f = tkFileDialog.asksaveasfile(mode='w', defaultextension=".txt")
    if f is None: # asksaveasfile return `None` if dialog closed with "cancel".
        return
    text2save = "Session started on: " + str(strftime("%Y-%m-%d %H:%M:%S")) + "\n"
    text2save += currentReading

    f.write(text2save)
    f.close() 

"""
def save_quit():
    global generations
    global currentReading

    if generations == 0:
        return

    f = tkFileDialog.asksaveasfile(mode='w', defaultextension=".txt")
    if f is None: # asksaveasfile return `None` if dialog closed with "cancel".
        return
    text2save = "Session started on: " + str(strftime("%Y-%m-%d %H:%M:%S")) + "\n"
    text2save += currentReading

    f.write(text2save)
    f.close() 
"""

def makeMenu(self):
    menu = Menu(self)
    self.config(menu=menu)
    filemenu = Menu(menu)
    menu.add_cascade(label="File", menu=filemenu)
    filemenu.add_separator()
    filemenu.add_command(label="Exit", command=self.quit)
    filemenu.add_command(label="Save", command=file_save)


def makeentry(parent, caption, width=None, **options):
    Label(parent, text=caption).pack(side = LEFT)
    entry = Entry(parent, **options)
    if width:
        entry.config(width=width)
    entry.pack(side=LEFT)
    return entry


def getEntries():
    global generations
    global currentReading
    generations = generations + 1
    currentReading += "Set #: " + str(generations) + "\n" + "-------LOCATION INFORMATION-------" + "\n"
    myNc = myCoordinateN.get()
    myWc = myCoordinateW.get()
    tNc = tCoordinateN.get()
    tWc = tCoordinateW.get()
    elevationI = myElevation.get()
    elevationT = targetElevation.get()
    currentReading += "Coordinates: " + myNc + " N, " + myWc + " W" + "\n" + "Elevation: " + elevationI + " feet" + "\n"
    currentReading += "Target Coordinates: " + tNc + " N, " + tWc + " W" + "\n" + "Target Elevation: " + elevationT + " feet" + "\n"
    doMath(myNc, myWc, tNc, tWc, elevationI, elevationT)

def telescopeHex(horizontal, vertical):
    building = 'B'

    # send horizontal to serial
    horizontal = horizontal/360 * 65536
    if horizontal < 0.0:
        horizontal += 65536
    horizontal = int(horizontal)

    a = horizontal / 4096
    b = (horizontal % 4096) /256
    c = (horizontal % 256)/16
    d = (horizontal % 16)
    building += hex(a)[2:]
    building += hex(b)[2:]
    building += hex(c)[2:]
    building += hex(d)[2:]
    
    building += ','

    # send vertical to serial
    vertical = vertical/360 * 65536
    if vertical < 0.0:
        vertical += 65536
    vertical = int(vertical)

    a = vertical / 4096
    b = (vertical % 4096) /256
    c = (vertical % 256)/16
    d = (vertical % 16)
    building += hex(a)[2:]
    building += hex(b)[2:]
    building += hex(c)[2:]
    building += hex(d)[2:]

    building = building.upper()
    print(building)

    #------UNCOMMENT TO INITIATE SERIAL COMMAND------
    # ensure you are connecting to the right serial port
    """
    ser = serial.Serial('/dev/tty.usbmodem1421', 9600)
    ser.write(building)
    ser.write("\n")
    """

def check(event):
    global spiralStatus
    global stopStatus

    if event.char == 'a':
        left()
    elif event.char == 'w':
        up()
    elif event.char == 'd':
        right()
    elif event.char == 's':
        down()
    elif event.chat == 'x':
        if spiralStatus == "YES":
            stopStatus = "YES"
    

def left():
    global currentAltitude
    global currentAzimuth
    currentAzimuth -= .005
    telescopeHex(currentAzimuth, currentAltitude)
    print "left"

def right():
    global currentAltitude
    global currentAzimuth
    currentAzimuth += .005
    telescopeHex(currentAzimuth, currentAltitude)
    print "right"

def down():
    global currentAltitude
    global currentAzimuth
    currentAltitude -= .005
    telescopeHex(currentAzimuth, currentAltitude)
    print "down"

def up():
    global currentAltitude
    global currentAzimuth
    currentAltitude += .005
    telescopeHex(currentAzimuth, currentAltitude)
    print "up"

def smallSpiral():
    #speed, azimuth, altitude
    global currentAltitude
    global currentAzimuth
    global currentReading
    global currentDeviation
    global stopStatus

    currentAltitude += .0025
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .0025*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude -= .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth -= .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude += .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .0025*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentDeviation += 1

    print "small"

def continuousSpiral():
    global currentAltitude
    global currentAzimuth
    global currentReading
    global currentDeviation
    global stopStatus

    while stopStatus == "NO":



    currentAltitude += .0025
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .0025*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude -= .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth -= .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude += .005*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .0025*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentDeviation += 1

    
def bigSpiral():
    #
    global currentAltitude
    global currentAzimuth
    global currentReading
    global currentDeviation
    global stopStatus

    #while stopStatus=="NO":
    currentAltitude += .01
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .01*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude -= .02*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth -= .02*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAltitude += .02*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentAzimuth += .01*currentDeviation
    telescopeHex(currentAzimuth, currentAltitude)
    sleep(1)
    currentDeviation += 1


    print "quick"

def doMath(mNc, mWc, tN, tW, mye, te):
    global currentAltitude
    global currentAzimuth
    global currentReading
    global currentDeviation

    # calculate distances in miles by calculating length of the hypotenuse between
    # the two given coordinates
    print
    print "-------DISTANCE INFORMATION-------" 
    print "Straight line distance in miles: "
    asquared = pow(float(mNc) - float(tN),2)
    bsquared = pow(float(mWc) - float(tW), 2)
    distance = sqrt(asquared + bsquared)
    distance *= 68.6863716 #convert from coordinate degrees to miles
    print distance
    print
    currentReading += "-------DISTANCE INFORMATION------- \n" + "Straight line distance in miles: \n" + str(distance) + "\n"

    # UNCOMMENT TO SEE GREAT CIRCLE DISTANCE
    """
    print "Great circle distance: "
    myLacation = (mNc, mWc)
    targetLocation = (tN, tW)
    print vincenty(myLacation, targetLocation).miles
    print
    """
    
    # calculate vertical difference in feet
    diff = float(te) - float(mye)
    print "At your distance, curvature of the earth accounts for a drop in feet of: "
    print (distance * 2/3) 
    print 
    diff -= (distance * 2/3) #adjust for the curvature of the earth
    print "Corrected elevation difference: "
    print diff

    currentReading += "At your distance, curvature of the earth accounts for a drop in feet of: " + str((distance * 2/3)) + "\n"
    currentReading += "Corrected elevation difference: " + str(diff) + "\n" + "-------CALCULATED ANGLES------- \n"

    print "-------CALCULATED ANGLES-------"

    #calculate angle of elevation by simply condicting arc tangent and converting to degrees
    vertTheta = atan((diff/5280)/distance) * 180/pi 
    print
    print "Adjust your module to this vertical angle: "
    print vertTheta
    currentAltitude = vertTheta
    currentReading +=  "Adjust your module to this vertical angle: " + str(vertTheta) + "\n"
    print
    print "Target team adjust to this vertical angle: "
    otherVert = 0 - vertTheta #calculate corresponging angle for the other unit
    print otherVert
    currentReading +=  "Adjust target module to this vertical angle: " + str(otherVert) + "\n"

    #calculate horizontal angle
    lat2 = float(tN)
    lat1 = float(mNc)
    lon2 = float(tW)
    lon1 = float(mWc)
    latDiff = lat2 - lat1
    longDiff = lon2 - lon1
    y = sin(lon2 - lon1)*cos(lat2)
    x = cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon2-lon1)
    if y > 0:
        if x > 0: tcl = -(180/pi* atan(y/x))
        if x < 0: tcl = 180 - (180/pi * atan(-y/x))
        if x ==0: tcl = 90
    if y < 0:
        if x > 0: tcl = -(180/pi * atan(-y/x))
        if x < 0: tcl = 180 - (180/pi * atan(y/x)) - 180
        if x ==0: tcl = 270
    if y == 0:
        if x > 0: tcl = 0
        if x < 0: tcl = 180
        if x ==0: print "You want to point at yourself? uhhh...idk how to do that"  


    horzTheta = (360 + (tcl+360)) % 360
    print
    print "Adjust to this bearing: "
    print horzTheta
    currentAzimuth = horzTheta
    currentReading +=  "Adjust to this bearing: " + str(horzTheta) + "\n" 
    print
    if horzTheta >= 180:
        otherHorz = horzTheta - 180
    else:
        otherHorz = horzTheta+ 180
    print "Target team adjust to this bearing: "
    print otherHorz
    print
    currentReading +=  "Adjust target module to this bearing: " + str(otherHorz) + "\n" + "\n"

    telescopeHex(horzTheta, vertTheta)


class AutoAim(Frame):
  
    def __init__(self, parent):
        Frame.__init__(self, parent)  
         
        self.parent = parent
        self.makeButtons()
        
    def makeButtons(self):

        self.parent.title("AutoAim")
        self.style = Style()
        self.style.theme_use("default")
        
        frame = Frame(self, relief=RAISED, borderwidth=1)
        frame.pack(fill=BOTH, expand=1)
        
        self.pack(fill=BOTH, expand=1)


        # put the option to generate in the bottom and the text entries in the lower left
        generate = Button(self, text="Generate", fg="red", command = getEntries)
        generate.pack(side=LEFT, padx=30, pady=30)

        emailTo = Button(self, text="Save Session", fg="red", command = file_save)
        emailTo.pack(side=LEFT, padx=30, pady=30)

        # put the option to generate a slow spiral
        slow = Button(self, text="Fine", fg="red", command = smallSpiral)
        slow.pack(side=RIGHT, padx=10, pady=20)

        # put the option to generate a quick spiral
        fast = Button(self, text="Coarse", fg="red", command = bigSpiral)
        fast.pack(side=RIGHT, padx=10, pady=10)

        

root = Tk()
root.geometry('700x500-200+40')
root.bind("<Key>",check)
makeMenu(root)

instructions = Label(root, text = "Enter auto aim parameters. Then click generate to continue.", font=("Helvetica", 16))
space = Label(root, text = " ")
instructions.pack()
space.pack(fill = X)

prompt = Label(root, text = "Your exact coordinates to North formatted as: 37*24'58.6\"N -> 37.24586)")
prompt.pack(fill = X)
myCoordinateN = Entry(root, width = 20)
myCoordinateN.insert(0, "36.988317") 
myCoordinateN.pack()

prompt2 = Label(root, text = "Your exact coordinates to West formatted as: 122*11'32.0\"W -> 122.11320)")
prompt2.pack(fill = X)
myCoordinateW = Entry(root, width = 20)
myCoordinateW.insert(0, "-122.065917") 
myCoordinateW.pack()

prompt3 = Label(root, text = "Your Elevation in feet")
prompt3.pack(fill = X)
myElevation = Entry(root, width = 20)
myElevation.insert(0, "575.768") 
myElevation.pack()

prompt4 = Label(root, text = "Exact target coordinates to North formatted as: 37*24'58.6\"N -> 37.24586)")
prompt4.pack(fill = X)
tCoordinateN = Entry(root, width = 20)
tCoordinateN.insert(0, "36.583299") 
tCoordinateN.pack()

prompt5 = Label(root, text = "Exact target coordinates to West formatted as: 122*11'32.0\"W -> 122.11320)")
prompt5.pack(fill = X)
tCoordinateW = Entry(root, width = 20)
tCoordinateW.insert(0, "-121.97179265") 
tCoordinateW.pack()

prompt6 = Label(root, text = "Target Elevation in feet")
prompt6.pack(fill = X)
targetElevation = Entry(root, width = 20)
targetElevation.insert(0, "23.205") 
targetElevation.pack()

# add section to control the tilt unit
space.pack(fill = X)
prompt7 = Label(root, text = "Fine/Coarse buttons will execute an outward spiral @ .005/.01 degrees deviation from target angle")
prompt7.pack(fill = X)
prompt8 = Label(root, text = "Press Stop to end sprial search. AWSD keys can be used for .005 degree manual adjustments")
prompt8.pack(fill = X)


app = AutoAim(root)
#root.wm_protocol("WM_DELETE_WINDOW", save_quit)
root.mainloop()



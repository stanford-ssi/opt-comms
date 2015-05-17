
Author: Elizabeth Hillstrom
Organization: Stanford Space Initiative, Optical Communications Team

ALTITUDE/AZIMUTH DETERMINATION SCRIPT:

This program takes a set of GPS points (your home location, two reference points, and a target location), and, given an observed altitude/azimuth offset between the two reference points, outputs the required additional offset to reach the target point from the last entered reference.  It was developed to be used with motorized altitude/azimuth mounts at two locations approximately 10km apart, with the intent of establishing a free-space optical communication system, requiring very precise alignment of both transmitter and receiver to a known GPS point.  

What follows are a set of evaluated test cases and two theoretically reasonable altitude and azimuth shifts between reference points, used solely to test the software capabilities.  The software has not yet been experimentally tested.

—-


SKYLINE DRIVE: 37.32439324324385,-122.20410292502493,717.402
HAM RADIO SHACK: 37.411664367607116,-122.17955907806754,140.090


TEST 1:
	SKYLINE DRIVE
	ref1 = [37.41254340788959,-122.22812533378601,94.397];  % arbitrary
	ref2 = [37.40218028276628,-122.19825625419617,104.592];  % arbitrary
	HAM RADIO SHACK

	Reasonable Shifts: 
		Alt: -4.28
		Az: 15

TEST 2:
	HAM RADIO SHACK
	ref1 = [37.40218028276628,-122.19825625419617,104.592];  % arbitrary
	ref2 = [37.41254340788959,-122.22812533378601,94.397];  % arbitrary
	SKYLINE DRIVE

	Reasonable Shifts:
		Alt: -16.5
		Az: 30

TEST 3:
	SKYLINE DRIVE
	ref1 = [37.405832254812985,-122.22094774246216,179.979];  % arbitrary
	ref2 = [37.39437716501892,-122.13717699050903,44.086,144.639];  % arbitrary
	HAM RADIO SHACK

	Reasonable Shifts: 
		Alt: -25.91
		Az: 40

TEST 4:
	SKYLINE DRIVE
	ref1 = [37.43543456786916,-122.16085821390152,18.186];  % Stanford Stadium
	ref2 = [37.41554299235967,-122.0530092716217,4.689];  % Moffet Airfield
	HAM RADIO SHACK

	Reasonable Shifts:
		Alt: -6.553
		Az: 35

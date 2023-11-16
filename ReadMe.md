# AStar  
  
Dungeon Map Pathfinding project created for GD1P02 Algorithms and Data Structures Assessment 4 (Assignment 2).  
  
  
## Table of Contents  
  
- [Description](#Description)  
- [Features](#Features)  
- [Requirements](#Requirements)  
- [Installation](#Installation)  
- [Controls](#Controls)  
- [Disclaimer](#Disclaimer)  
- [Credits](#Credits)  
  
  
## Description  
  
AStar is a small program that allows the user to load maps in the form of a .txt file with walls, a starting point, an ending point and 10 items from a-j.  
This program is designed with C++ in Visual Studio 2022 and to be operated with mouse and keyboard controls.  
  
  
## Features  
### File Loading  
AStar has a loading function for the use of .txt files. The user is promted to navigate through the Windows file selection system.  
.txt files may be imported from the local system with the format where:  
  
- The map is a 20x20 format  
- 'w' is a wall square  
- '.' indicates a clear square, or free space  
- 's' indicates a starting point  
- 'x' shows the exit point  
- letters 'a' through to 'j' are items to be collected  
  
- There can only be one starting point  
- There can only be one exit point  
  
Users will be notified if the map is invalid on load. Obstructed maps will still load where the exit is inaccessible, search functions will display that with the items they can collect.  
  
  
### Pathfinding Algorithms  
AStar's pathfinding operations include:  
- Depth-First Search  
- Breadth-First Search  
- AStar Pathfinding (Currently implemented but not working)  
  
  
## Requirements  
  
- Visual Studio 2022 (v143)  
- Windows SDK 10.0  
- C++ Language Standard: ISO C++20 Standard (/std:c++20)  
- C Language Standard: ISO C17 (2018) Standard (/std:c17)  
- Windows x64  
  
  
## Installation  
  
This program can also be downloaded and built in x64 (Debug or Release) with Visual Studio 2022 by opening the solution file.  
  
  
## Controls  
  
Standard keyboard controls and mouse can be used.  
  
  
## Disclaimer  
  
This program is semi-complete for submission. While this program may be "complete", bugs may be present.  
UI design is basic and have not had the time to implement a better design. As a result, clearing the screen etc. are not incorporated into the program.  
User input validation is very basic. Trying to break this will definitely break, however, following the displayed instructions should present no issues.  
AStar implementation was attempted, but does not work and unsure of how to address this. No time to get it working.  
All code was written by Shiko based off my own knowledge from classes and self driven research of the C++ coding language.  
.vs/AStar/v17/.suo is included for ease of solution loadup purposes since the solution has been manually configured. The solution should start with x64 Release, on main.cpp and DungeonMap.h in side by side docks.
  
  
## Credits

Shikomisen (Ayoub) 2023
Media Design School
GD1P02 - Algorithms and Data Structures
Written for Assessment 4 (Assignment 2)

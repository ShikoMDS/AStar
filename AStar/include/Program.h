/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Program.h
Description : Program UI IO declarations for AStar program
Author : Shikomisen (Ayoub)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once
#include "DungeonMap.h"

#include <iostream>
#include <Windows.h>

class Program
{
public:
	Program(); // Constructor

	void run();
	static std::string openFileDialog();

private:
	DungeonMap MDungeonMap;
	bool isMapLoaded; // Flag to track if a valid map is loaded
};

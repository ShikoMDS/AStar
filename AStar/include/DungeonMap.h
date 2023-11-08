#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

class DungeonMap
{
public:
	DungeonMap(); // Constructor

	bool loadMapFromFile(const std::string& Filename);
	void displayMap() const;

	void depthFirstSearch();

	void breadthFirstSearch() const;

private:
	std::vector<std::string> MMap;

	bool dfsHelper(int X, int Y, std::vector<std::vector<bool>>& Visited);
};

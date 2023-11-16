/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : DungeonMap.h
Description : Pathfinding declarations for AStar program
Author : Shikomisen (Ayoub)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// Represents a cell in the dungeon map
struct Cell
{
	int X, Y;
	char Value;
	float GCost{}, HCost{};
	Cell* Parent{};
	std::vector<Cell*> Neighbors; // Neighbors for graph traversal

	Cell(const int CellX, const int CellY, const char CellVal) : X(CellX), Y(CellY), Value(CellVal)
	{
	}
};

class DungeonMap
{
public:
	DungeonMap(); // Constructor

	bool loadMapFromFile(const std::string& Filename);
	void displayMap() const;
	[[nodiscard]] bool validateMap() const; // Validates the map for correctness
	void buildGraph(); // Converts the map into a graph representation

	void depthFirstSearch();
	void breadthFirstSearch() const;
	std::vector<Cell*> aStarPathfinding(Cell& Start, Cell& End);
	Cell& getStartCell();
	Cell& getEndCell();

private:
	std::vector<std::string> MapData; // Stores the raw map data
	std::vector<std::vector<Cell>> Graph; // Graph representation of the map
	std::pair<int, int> Start; // Starting point coordinates
	std::pair<int, int> End; // Ending point coordinates

	bool dfsHelper(int X, int Y, std::vector<std::vector<bool>>& Visited);
	void bfsHelper(int X, int Y, std::vector<std::vector<bool>>& Visited,
	               std::queue<std::pair<int, int>>& Queue) const; // Helper for BFS
	void findStartAndEnd(); // Locates the start and end points in the map
	std::vector<Cell*> getNeighbors(int X, int Y); // Retrieves the neighbors of a cell
	static std::vector<Cell*> reconstructPath(Cell& End); // Reconstructs the path from end to start
	[[nodiscard]] float calculateHCost(const Cell& A, const Cell& End) const; // Heuristic function for A*
	[[nodiscard]] float distanceBetween(const Cell& A, const Cell& B) const; // Calculates distance between two cells
	static Cell* findLowestFCostNode(const std::set<Cell*>& OpenSet);
};

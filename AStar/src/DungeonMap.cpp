/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : DungeonMap.cpp
Description : Pathfinding implementations for AStar program
Author : Shikomisen (Ayoub)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "DungeonMap.h"

DungeonMap::DungeonMap() = default;

bool DungeonMap::loadMapFromFile(const std::string& Filename)
{
	// Clear existing map data and reset any relevant state
	MapData.clear();

	std::ifstream File(Filename);
	if (!File.is_open())
	{
		std::cerr << "Error: Unable to open file " << Filename << std::endl;
		return false;
	}

	std::string Line;
	while (std::getline(File, Line))
	{
		MapData.push_back(Line);
	}
	File.close(); // Close the file after reading

	if (!validateMap())
	{
		std::cerr << "Error: Map validation failed" << std::endl;
		return false;
	}

	// Assuming the map is valid, build the graph
	buildGraph();

	return true;
}

void DungeonMap::displayMap() const
{
	for (const auto& Row : MapData)
	{
		std::cout << Row << std::endl;
	}
}

bool DungeonMap::validateMap() const
{
	int StartCount = 0;
	int ExitCount = 0;
	std::unordered_set<char> ItemsFound;

	for (const auto& Row : MapData)
	{
		for (const char Cell : Row)
		{
			if (Cell == 's')
			{
				StartCount++;
			}
			else if (Cell == 'x')
			{
				ExitCount++;
			}
			else if (Cell >= 'a' && Cell <= 'j')
			{
				ItemsFound.insert(Cell);
			}
			else if (Cell != '.' && Cell != 'w')
			{
				// If the cell is not a wall, empty space, item, start, or exit, it's invalid.
				return false;
			}
		}
	}

	// Check for exactly one start and one exit, and all items present.
	return StartCount == 1 && ExitCount == 1 && ItemsFound.size() == 10;
}

// Converts the dungeon map into a graph representation for traversal
void DungeonMap::buildGraph()
{
	// Resize the graph to match the map size
	Graph.resize(MapData.size(), std::vector<Cell>(MapData[0].size(), Cell(0, 0, ' ')));

	// Populate the graph with cells
	for (int I = 0; I < MapData.size(); ++I)
	{
		for (int J = 0; J < MapData[I].size(); ++J)
		{
			Graph[I][J] = Cell(I, J, MapData[I][J]);
		}
	}

	// Connect the cells
	for (int I = 0; I < MapData.size(); ++I)
	{
		for (int J = 0; J < MapData[I].size(); ++J)
		{
			Graph[I][J].Neighbors = getNeighbors(I, J);
		}
	}

	// Locate the start and end points
	findStartAndEnd();
}

void DungeonMap::depthFirstSearch()
{
	std::vector<std::vector<bool>> Visited(MapData.size(), std::vector<bool>(MapData[0].size(), false));
	dfsHelper(Start.first, Start.second, Visited);
}

void DungeonMap::breadthFirstSearch() const
{
	std::vector<std::vector<bool>> Visited(MapData.size(), std::vector<bool>(MapData[0].size(), false));
	std::queue<std::pair<int, int>> Queue;

	Queue.push({Start.first, Start.second});
	Visited[Start.first][Start.second] = true;

	while (!Queue.empty())
	{
		auto [x, y] = Queue.front();
		Queue.pop();

		bfsHelper(x, y, Visited, Queue);
	}
}

std::vector<Cell*> DungeonMap::aStarPathfinding(Cell& Start, Cell& End)
{
	std::set<Cell*> OpenSet;
	std::set<Cell*> ClosedSet;

	Start.GCost = 0;
	Start.HCost = calculateHCost(Start, End);
	Start.Parent = nullptr;
	OpenSet.insert(&Start);

	while (!OpenSet.empty())
	{
		Cell* Current = findLowestFCostNode(OpenSet);

		if (Current == &End)
		{
			return reconstructPath(End);
		}

		OpenSet.erase(Current);
		ClosedSet.insert(Current);

		for (Cell* Neighbor : Current->Neighbors)
		{
			if (ClosedSet.contains(Neighbor) || Neighbor->Value == 'w')
			{
				continue;
			}

			const float TentativeGCost = Current->GCost + distanceBetween(*Current, *Neighbor);
			if (TentativeGCost < Neighbor->GCost)
			{
				Neighbor->Parent = Current;
				Neighbor->GCost = TentativeGCost;
				Neighbor->HCost = calculateHCost(*Neighbor, End);

				if (!OpenSet.contains(Neighbor))
				{
					OpenSet.insert(Neighbor);
				}
			}
		}
	}

	return {}; // Return an empty path if no path is found
}

Cell& DungeonMap::getStartCell()
{
	return Graph[Start.first][Start.second];
}

Cell& DungeonMap::getEndCell()
{
	return Graph[End.first][End.second];
}

bool DungeonMap::dfsHelper(const int X, const int Y, std::vector<std::vector<bool>>& Visited)
{
	Visited[X][Y] = true;

	// Process the current cell
	if (Graph[X][Y].Value >= 'a' && Graph[X][Y].Value <= 'j')
	{
		std::cout << "Item " << Graph[X][Y].Value << " collected!" << std::endl;
	}

	// Recursive DFS on neighbors
	for (const Cell* Neighbor : Graph[X][Y].Neighbors)
	{
		if (!Visited[Neighbor->X][Neighbor->Y])
		{
			dfsHelper(Neighbor->X, Neighbor->Y, Visited);
		}
	}

	return true;
}

void DungeonMap::bfsHelper(const int X, const int Y, std::vector<std::vector<bool>>& Visited,
                           std::queue<std::pair<int, int>>& Queue) const
{
	// Process the current cell
	if (Graph[X][Y].Value >= 'a' && Graph[X][Y].Value <= 'j')
	{
		std::cout << "Item " << Graph[X][Y].Value << " collected!" << std::endl;
	}

	// Add unvisited neighbors to the queue
	for (Cell* Neighbor : Graph[X][Y].Neighbors)
	{
		if (!Visited[Neighbor->X][Neighbor->Y])
		{
			Queue.push({Neighbor->X, Neighbor->Y});
			Visited[Neighbor->X][Neighbor->Y] = true;
		}
	}
}

void DungeonMap::findStartAndEnd()
{
	for (int I = 0; I < MapData.size(); ++I)
	{
		for (int J = 0; J < MapData[I].size(); ++J)
		{
			if (MapData[I][J] == 's')
			{
				Start = {I, J};
			}
			else if (MapData[I][J] == 'x')
			{
				End = {I, J};
			}
		}
	}
}

std::vector<Cell*> DungeonMap::getNeighbors(const int X, const int Y)
{
	std::vector<Cell*> Neighbors;
	const std::vector<std::pair<int, int>> Offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
	for (const auto& [fst, snd] : Offsets)
	{
		const int NewX = X + fst;
		const int NewY = Y + snd;
		if (NewX >= 0 && NewX < Graph.size() && NewY >= 0 && NewY < Graph[NewX].size())
		{
			if (Graph[NewX][NewY].Value != 'w')
			{
				// Ensure the neighbor is not a wall
				Neighbors.push_back(&Graph[NewX][NewY]); // Adding pointer to Cell
			}
		}
	}
	return Neighbors;
}

std::vector<Cell*> DungeonMap::reconstructPath(Cell& End)
{
	std::vector<Cell*> Path;
	for (Cell* Cell = &End; Cell != nullptr; Cell = Cell->Parent)
	{
		Path.push_back(Cell);
	}
	std::ranges::reverse(Path);
	return Path;
}

float DungeonMap::calculateHCost(const Cell& A, const Cell& End) const
{
	return static_cast<float>(std::abs(A.X - End.X)) + static_cast<float>(std::abs(A.Y - End.Y));
}

float DungeonMap::distanceBetween(const Cell& A, const Cell& B) const
{
	// Diagonal movement
	if (A.X != B.X && A.Y != B.Y)
	{
		// Check if adjacent squares are free (not walls)
		if (MapData[A.X][B.Y] == 'w' || MapData[B.X][A.Y] == 'w')
		{
			return std::numeric_limits<float>::infinity(); // Block diagonal movement
		}
		return 1.414f; // Diagonal distance (sqrt(2))
	}
	// Horizontal or vertical movement
	return 1.0f;
}

Cell* DungeonMap::findLowestFCostNode(const std::set<Cell*>& OpenSet)
{
	Cell* LowestFCostNode = nullptr;
	float LowestFCost = std::numeric_limits<float>::infinity();

	for (Cell* Node : OpenSet)
	{
		const float FCost = Node->GCost + Node->HCost;
		if (FCost < LowestFCost)
		{
			LowestFCost = FCost;
			LowestFCostNode = Node;
		}
	}

	return LowestFCostNode;
}

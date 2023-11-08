#include "Program.h"

Program::Program()
{
	// Initialize any variables if needed
}

void Program::run()
{
	// Load a map (replace "naps/example_map.txt" map files)
	if (MDungeonMap.loadMapFromFile("maps/ValidMap1.txt"))
	{
		// Display the loaded map
		MDungeonMap.displayMap();

		// Perform Depth-First Search
		std::cout << "\nDFS Traversal:\n";
		MDungeonMap.depthFirstSearch();

		// Perform Breadth-First Search
		std::cout << "\nBFS Traversal:\n";
		MDungeonMap.breadthFirstSearch();

		// Perform A* Pathfinding
		//std::cout << "\nA* Pathfinding:\n";
		//dungeonMap.aStarPathfinding();
	}
	else
	{
		std::cerr << "Failed to load the map. Exiting program." << std::endl;
	}
}

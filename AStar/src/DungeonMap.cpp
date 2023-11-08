#include "DungeonMap.h"

DungeonMap::DungeonMap()
{
	// Initialize any variables if needed
}

bool DungeonMap::loadMapFromFile(const std::string& Filename)
{
	std::ifstream File(Filename);
	if (!File.is_open())
	{
		std::cerr << "Error: Unable to open file " << Filename << std::endl;
		return false;
	}

	// Read the file and validate the map
	std::string Line;
	while (std::getline(File, Line))
	{
		MMap.push_back(Line);
	}

	// Additional validation logic goes here

	return true;
}

void DungeonMap::displayMap() const
{
	for (const auto& Row : MMap)
	{
		std::cout << Row << std::endl;
	}
}

void DungeonMap::depthFirstSearch()
{
	// Initialize visited array
	std::vector<std::vector<bool>> Visited(MMap.size(), std::vector<bool>(MMap[0].size(), false));

	// Find the starting point 's' and initiate DFS
	for (int I = 0; I < MMap.size(); ++I)
	{
		for (int J = 0; J < MMap[I].size(); ++J)
		{
			if (MMap[I][J] == 's')
			{
				dfsHelper(I, J, Visited);
				return; // Only one starting point, so we can exit after the first 's' is found
			}
		}
	}
}

void DungeonMap::breadthFirstSearch() const
{
	// Initialize visited array
	std::vector<std::vector<bool>> Visited(MMap.size(), std::vector<bool>(MMap[0].size(), false));

	// Find the starting point 's' and initiate BFS
	for (int I = 0; I < MMap.size(); ++I)
	{
		for (int J = 0; J < MMap[I].size(); ++J)
		{
			if (MMap[I][J] == 's')
			{
				// Create a queue for BFS
				std::queue<std::pair<int, int>> Q;
				Q.push({I, J});
				Visited[I][J] = true;

				// Perform BFS
				while (!Q.empty())
				{
					const auto [fst, snd] = Q.front();
					Q.pop();
					const int X = fst;
					const int Y = snd;

					// Check for item at the current square
					if (MMap[X][Y] >= 'a' && MMap[X][Y] <= 'j')
					{
						std::cout << "Item " << MMap[X][Y] << " collected!" << std::endl;
					}

					// Define the possible moves (up, down, left, right)
					constexpr int Dx[] = {-1, 1, 0, 0};
					constexpr int Dy[] = {0, 0, -1, 1};

					// Explore neighbors
					for (int I = 0; I < 4; ++I)
					{
						int Nx = X + Dx[I];
						int Ny = Y + Dy[I];

						// Check if the neighbor is within bounds and not visited
						if (Nx >= 0 && Nx < MMap.size() && Ny >= 0 && Ny < MMap[0].size() && !Visited[Nx][Ny] && MMap[Nx][
							Ny] != 'w')
						{
							Q.push({Nx, Ny});
							Visited[Nx][Ny] = true;
						}
					}
				}

				return; // Only one starting point, so we can exit after the first 's' is found
			}
		}
	}
}

bool DungeonMap::dfsHelper(const int X, const int Y, std::vector<std::vector<bool>>& Visited)
{
	// Mark the current square as visited
	Visited[X][Y] = true;

	// Check for item at the current square
	if (MMap[X][Y] >= 'a' && MMap[X][Y] <= 'j')
	{
		std::cout << "Item " << MMap[X][Y] << " collected!" << std::endl;
	}

	// Define the possible moves (up, down, left, right)
	constexpr int Dx[] = {-1, 1, 0, 0};
	constexpr int Dy[] = {0, 0, -1, 1};

	// Explore neighbors
	for (int I = 0; I < 4; ++I)
	{
		const int Nx = X + Dx[I];
		const int Ny = Y + Dy[I];

		// Check if the neighbor is within bounds and not visited
		if (Nx >= 0 && Nx < MMap.size() && Ny >= 0 && Ny < MMap[0].size() && !Visited[Nx][Ny] && MMap[Nx][Ny] != 'w')
		{
			dfsHelper(Nx, Ny, Visited);
		}
	}

	return true;
}

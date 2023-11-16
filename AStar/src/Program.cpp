/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Program.cpp
Description : Program UI IO implementations for AStar program
Author : Shikomisen (Ayoub)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Program.h"

Program::Program(): isMapLoaded(false)
{
}

void Program::run()
{
	bool isRunning = true;
	while (isRunning)
	{
		std::cout << "\nMenu: \n";
		std::cout << "1. Load Map\n";
		if (isMapLoaded)
		{
			std::cout << "2. Perform DFS Traversal\n";
			std::cout << "3. Perform BFS Traversal\n";
			std::cout << "4. Run A* Pathfinding\n";
		}
		std::cout << "5. Exit\n";
		std::cout << "Enter your choice: ";

		int Choice;
		if (!(std::cin >> Choice))
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cerr << "Invalid input, please try again.\n";
			continue;
		}

		switch (Choice)
		{
		case 1:
			{
				std::string MapPath = openFileDialog();
				if (!MapPath.empty())
				{
					if (!MDungeonMap.loadMapFromFile(MapPath))
					{
						std::cerr << "Failed to load the map." << std::endl;
						isMapLoaded = false;
					}
					else
					{
						MDungeonMap.displayMap();
						isMapLoaded = true;
					}
				}
				else
				{
					std::cout << "No file selected." << std::endl;
				}
				break;
			}
		case 2:
			if (isMapLoaded)
			{
				std::cout << "\nDFS Traversal:\n";
				MDungeonMap.depthFirstSearch();
			}
			else
			{
				std::cout << "Please load a map first.\n";
			}
			break;
		case 3:
			if (isMapLoaded)
			{
				std::cout << "\nBFS Traversal:\n";
				MDungeonMap.breadthFirstSearch();
			}
			else
			{
				std::cout << "Please load a map first.\n";
			}
			break;
		case 4:
			if (isMapLoaded)
			{
				std::cout << "\nRunning A* Pathfinding...\n";

				Cell& StartCell = MDungeonMap.getStartCell();
				Cell& EndCell = MDungeonMap.getEndCell();

				std::vector<Cell*> Path = MDungeonMap.aStarPathfinding(StartCell, EndCell);

				if (!Path.empty())
				{
					std::cout << "Path found: \n";
					for (const Cell* Cell : Path)
					{
						std::cout << "(" << Cell->X << ", " << Cell->Y << ") ";
					}
					std::cout << std::endl;
				}
				else
				{
					std::cout << "No path found from start to end." << std::endl;
				}
			}
			else
			{
				std::cout << "Please load a map first.\n";
			}
			break;
		case 5:
			isRunning = false;
			break;
		default:
			std::cerr << "Invalid choice, please try again.\n";
		}
	}
}

std::string Program::openFileDialog()
{
	OPENFILENAME Ofn;
	wchar_t FileName[MAX_PATH] = L"";

	ZeroMemory(&Ofn, sizeof(Ofn));
	Ofn.lStructSize = sizeof(Ofn);
	Ofn.hwndOwner = nullptr;
	Ofn.lpstrFile = FileName;
	Ofn.nMaxFile = MAX_PATH;
	Ofn.lpstrFilter = L"All Files\0*.*\0";
	Ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&Ofn))
	{
		// Convert wide string (wchar_t) to narrow string (char) to address warning issues
		const int BufferSize = WideCharToMultiByte(CP_UTF8, 0, FileName, -1, nullptr, 0, nullptr, nullptr);
		std::string Str(BufferSize, 0);
		WideCharToMultiByte(CP_UTF8, 0, FileName, -1, &Str[0], BufferSize, nullptr, nullptr);
		return Str;
	}
	return "";
}

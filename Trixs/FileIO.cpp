#include "FileIO.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

namespace Trixs
{

	bool FileIO::writeFile(std::string path, std::string content)
	{
		std::ofstream myfile;
		myfile.open(path);
		if (myfile.is_open())
		{
			myfile << content;
			myfile.close();
			return true;
		}
		else
		{
			int index = path.find_last_of("/\\");
			createDir(path.substr(0, index));
			myfile.open(path);
			if (myfile.is_open())
			{
				myfile << content;
				myfile.close();
				return true;
			}
			else
				return false;
		}
		return false;
	}
	std::vector<std::string> FileIO::readFile(std::string path)
	{
		std::string line;
		std::vector<std::string> lines;
		std::ifstream myfile(path);
		if (myfile.is_open())
		{
			while (getline(myfile, line, '\n'))
			{
				lines.push_back(line);
			}
			myfile.close();
		}

		return lines;
	}
	bool FileIO::createDir(const std::string path)
	{
		std::wstring stemp = std::wstring(path.begin(), path.end());
		LPCWSTR sw = stemp.c_str();
		return CreateDirectory(sw, NULL);

	}
}
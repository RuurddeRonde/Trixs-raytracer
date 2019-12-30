#pragma once
#include <string>
namespace Trixs
{

class FileIO
{
public:
	static bool writeFile(std::string path, std::string content);
	static std::string readFile(std::string path);
	static bool createDir(const std::string path);
};

}

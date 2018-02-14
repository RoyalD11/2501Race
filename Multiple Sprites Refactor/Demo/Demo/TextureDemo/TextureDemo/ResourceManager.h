#pragma once

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

class ResourceManager {
public:
	static std::string LoadTextFile(const char *filename);
};
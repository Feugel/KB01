#include "ResourceDXSceneLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Scene.h"
#include "rapidxml.hpp"

ResourceDXSceneLoader::ResourceDXSceneLoader(void)
{
}


ResourceDXSceneLoader::~ResourceDXSceneLoader(void)
{
}

Scene* ResourceDXSceneLoader::LoadFile(std::string fileName)
{
	std::ifstream text (fileName.c_str());
	if(text.is_open())
	{
		rapidxml::xml_document<> doc;
		std::string line;
		std::stringstream contents;

		while(std::getline(text, line))
		{
			contents << line;
		}

	}
	


	return NULL;
}
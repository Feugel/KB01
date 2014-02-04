#include "ResourceDXSceneLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Scene.h"
#include "Terrain.h"
#include "EntityModel.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

//Constructor for ResourceDXSceneLoader
ResourceDXSceneLoader::ResourceDXSceneLoader(void)
{
}

//Destructor for ResourceDXSceneLoader
ResourceDXSceneLoader::~ResourceDXSceneLoader(void)
{
}

//Loadfile method, this method loads the .xml files and initializes them.
Scene* ResourceDXSceneLoader::LoadFile(std::string fileName)
{
	rapidxml::file<> xml(fileName.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xml.data());

	//Creates scenenode
	rapidxml::xml_node<>* sceneNode = doc.first_node("Scene");
	//Creates terrainNode
	rapidxml::xml_node<>* terrainNode = sceneNode->first_node("Terrain");
	//Creates entitiesNode
	rapidxml::xml_node<>* entitiesNode = sceneNode->first_node("Entities");
	//Creates entityNode
	rapidxml::xml_node<>* entityNode = entitiesNode->first_node("Entity");
	
	//Creates new scene
	Scene* scene = new Scene();
	//Sets a name for the Scene
	scene->SetName(sceneNode->first_attribute("Name")->value());

	//Creates a new Terrain
	Terrain* terrain = new Terrain();
	//Sets the Heightmap and gets the FileName
	terrain->SetHeightmap(terrainNode->first_node("Heightmap")->first_attribute("FileName")->value());
	//Sets the Texture and gets the FileName
	terrain->SetTexture(terrainNode->first_node("Texture")->first_attribute("FileName")->value());
	//scene sets the Terrain
	scene->SetTerrain(terrain);

	std::map<std::string, Entity*> entities;
	while(entityNode != NULL)
	{
		//Creates a new EntityModel
		EntityModel* model = new EntityModel(entityNode->first_attribute("Name")->value());
		model->SetModel(entityNode->first_node("Model")->first_attribute("FileName")->value());
		Matrix position;
		position.x = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("X")->value());
		position.y = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("Y")->value());
		position.z = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("Z")->value());
		position.rotation_h = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("Rotation_H")->value());
		position.rotation_h = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("Rotation_V")->value());
		position.scale = std::stof(entityNode->first_node("Model")->first_node("Model.Position")->first_attribute("Scale")->value());
		model->SetPosition(position);
		model->SetTexture(entityNode->first_node("Texture")->first_attribute("FileName")->value());
		
		scene->AddEntity(model);
		scene->AddModel(model); // this line should be deleted
		entityNode = entityNode->next_sibling("Entity");
	}
	

	return scene;
}
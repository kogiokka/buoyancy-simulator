#include "render/Render.h"


//  Static members must be defined again in source file.
std::unordered_map<std::string, ObjectData*> Render::objects;
std::unordered_map<int, Shader*> Render::programs;

Render::Render()
{ }

Render::~Render()
{
	for (auto o : objects) {
		delete o.second;
	}
	objects.clear();

	for (auto p : programs) {
		delete p.second;
	}
	programs.clear();
}

void Render::addObject(std::string name, VertexVec vtx, LayoutVec attrs)
{
#ifndef NDEBUG
	// Make sure the name is not in use.
	if (objects.find(name) != objects.end()) {
		std::cerr << "[ERROR] In Render::addObject: The object \'"
		          << name << "\' already exists. Please choose another name." << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "---------- Adding Object \'" << name << "\' (by std::vector) ----------" << std::endl;
#endif
	objects.emplace(std::make_pair(name, new ObjectData(vtx, attrs)));
}

void Render::addObject(std::string name, VertexPtr vtx, Count vtxN, LayoutPtr attrs, Count attrsN)
{
#ifndef NDEBUG
	if (objects.find(name) != objects.end()) {
		std::cerr << "[ERROR] In Render::addObject: The object \'"
		          << name << "\' already exists. Please choose another name." << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "---------- Adding Object \'" << name << "\' (by pointer) ----------" << std::endl;
#endif
	objects.emplace(std::make_pair(name, new ObjectData(vtx, vtxN, attrs, attrsN)));
}

void Render::addProgram(int mapID, const QString& vert, const QString& frag)
{
	if (programs.find(mapID) == programs.end()) {
		programs.emplace(std::make_pair(mapID, new Shader(vert, frag)));
	}
}

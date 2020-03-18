#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>

#include "render/Shader.h"
#include "render/ObjectData.h"

#include <QtCore/QString>


class Render
{
	typedef std::vector<float>    VertexVec;
	typedef std::vector<unsigned int>    LayoutVec;
	typedef float*    VertexPtr;
	typedef unsigned int*    LayoutPtr;
	typedef unsigned int    Count;
public:
	Render();
	~Render();
	static void addObject(std::string name, VertexVec vtx, LayoutVec attrs);
	static void addObject(std::string name, VertexPtr vtx, Count vtxN, LayoutPtr attrs, Count attrsN);
	static void addProgram(int mapID, const QString& vert, const QString& frag);
public:
	// Using unordered_map instead of vector to avoid copying.
	static std::unordered_map<std::string, ObjectData*> objects;
	static std::unordered_map<int, Shader*> programs;
};

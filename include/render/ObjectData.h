#pragma once

#include "glad/glad.h"

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "render/VertexArray.h"
#include "render/VertexBuffer.h"
#include "physics/World.h"


class ObjectData
{
	typedef std::vector<float>    VertexVec;
	typedef std::vector<unsigned int>    LayoutVec;
	typedef float*    VertexPtr;
	typedef unsigned int*    LayoutPtr;
	typedef unsigned int    Count;
public:
	ObjectData(VertexVec vtx, LayoutVec attrs);
	ObjectData(VertexPtr vtx, Count vtxN, LayoutPtr attrs, Count attrsN);
	~ObjectData();
	ObjectData(const ObjectData&) = delete;  // Forbid copying
	void paint();
	void setModelMatrix(glm::mat4 matrix);
	void updateVertexAttrs(VertexVec& vtx);
	void updateVertexAttrs(VertexPtr vtx, Count vtxN);

	glm::mat4 matrix() const;
private:
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	glm::mat4 m_ModelMat;
	const void* m_AttrData;
	unsigned int m_AttrSize;
	bool m_ShouldUpdateVertexAttrs;
};

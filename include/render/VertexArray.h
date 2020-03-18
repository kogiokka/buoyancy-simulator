#pragma once

#include "glad/glad.h"

#include <cstdint>
#include <vector>

#include "render/VertexBuffer.h"

#ifndef NDEBUG
#include <iostream>
#endif


class VertexArray
{
	unsigned int m_ID;

public:
	VertexArray();
	~VertexArray();
	VertexArray(const VertexArray&) = delete;  // delete copy constructor
	void addBuffer(VertexBuffer& buffer, std::vector<unsigned int> attrs);
	void addBuffer(VertexBuffer& buffer, unsigned int* attrs, unsigned int attrsN);
	void bind();
	void unbind();
private:
	void debug(unsigned int index, int size, unsigned int stride, uintptr_t offset) const;
};

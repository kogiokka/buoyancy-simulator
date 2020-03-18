#pragma once

#include "glad/glad.h"

#ifndef NDEBUG
#include<iostream>
#include<iomanip>
#endif


class VertexBuffer
{
	unsigned int m_ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();
	void bind();
	void unbind();

	unsigned int id() const;
	unsigned int count() const;

private:
	unsigned int m_Size;
};

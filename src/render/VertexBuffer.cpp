#include "render/VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	m_Size = size;

//#ifndef NDEBUG
//	float* bufferData = new float[size]() ;
//	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), bufferData);
//	for (unsigned int i = 0; i < size; i++) {
//		std::cout << std::setw(6) << bufferData[i] << (i % 6 == 5 ? "\n" : ", ");
//	}
//	std::cout << std::endl;
//	free(bufferData);
//#endif
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(GL_ARRAY_BUFFER, &m_ID);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::count() const
{
	return m_Size;
}

unsigned int VertexBuffer::id() const
{
	return m_ID;
}

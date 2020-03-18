#include "render/VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_ID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer& buffer, unsigned int* attrs, unsigned int attrsN)
{
	glBindVertexArray(m_ID);
	buffer.bind();

	uintptr_t offset = 0;
	unsigned int stride = 0;

	for (unsigned int i = 0; i < attrsN; i++) {
		stride += attrs[i] * sizeof(float);
	}

	for (unsigned int i = 0; i < attrsN; i++) {
		unsigned int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
		offset += size * sizeof(float);
		glEnableVertexAttribArray(i);
#ifndef NDEBUG
		debug(i, size, stride, offset);
#endif
	}
}

void VertexArray::addBuffer(VertexBuffer& buffer, std::vector<unsigned int> attrs)
{
	glBindVertexArray(m_ID);
	buffer.bind();

	uintptr_t offset = 0;
	unsigned int stride = 0;

	for (unsigned int attr : attrs) {
		stride += attr * sizeof(float);
	}

	for (unsigned int i = 0; i < attrs.size(); i++) {
		unsigned int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
		offset += size * sizeof(float);
		glEnableVertexAttribArray(i);
#ifndef NDEBUG
		debug(i, size, stride, offset);
#endif
	}
}

#ifndef NDEBUG
void VertexArray::debug(unsigned int index, int size, unsigned int stride, uintptr_t offset) const
{
	std::cout << "VertexAttrib ( "
	          << "Index: "  << index << "   "
	          << "Size: "   << size << "   "
	          << "Stride: " << stride << "   "
	          << "Offset: " << offset
	          << " )" << std::endl;
}
#endif

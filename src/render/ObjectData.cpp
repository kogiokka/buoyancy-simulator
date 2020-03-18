#include "render/ObjectData.h"


ObjectData::ObjectData(VertexVec vtx, LayoutVec attrs)
    : m_VAO(nullptr), m_VBO(nullptr), m_ModelMat(Matrix::I), m_AttrData(nullptr), m_AttrSize(0), m_ShouldUpdateVertexAttrs(false)
{
	if (vtx.empty()) {
		std::cerr << "[ERROR at ObjectData::ObjectData] Vertex and Index data should not be empty." << std::endl;
		exit(EXIT_FAILURE);
	}

	m_VAO = new VertexArray();
	m_VBO = new VertexBuffer(vtx.data(), vtx.size());
	m_VAO->addBuffer(*m_VBO, attrs);

}

ObjectData::ObjectData(VertexPtr vtx, Count vtxN, LayoutPtr attrs, Count attrsN)
    : m_VAO(nullptr), m_VBO(nullptr), m_ModelMat(Matrix::I), m_AttrData(nullptr), m_AttrSize(0), m_ShouldUpdateVertexAttrs(false)
{
	if (!vtx) {
		std::cerr << "[ERROR at ObjectData::ObjectData] Vertex and Index data should not be empty." << std::endl;
		exit(EXIT_FAILURE);
	}

	m_VAO = new VertexArray();
	m_VBO = new VertexBuffer(vtx, vtxN);
	m_VAO->addBuffer(*m_VBO, attrs, attrsN);
}

void ObjectData::paint()
{
	m_VAO->bind();

	if (m_ShouldUpdateVertexAttrs) {
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO->id());
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_AttrSize * sizeof(float), m_AttrData);
		m_ShouldUpdateVertexAttrs = false;
	}

	glDrawArrays(GL_TRIANGLES, 0, m_VBO->count());
}


glm::mat4 ObjectData::matrix() const
{
	return m_ModelMat;
}

void ObjectData::setModelMatrix(glm::mat4 matrix)
{
	m_ModelMat = matrix;
}

void ObjectData::updateVertexAttrs(VertexVec& vtx)
{
	m_AttrData = vtx.data();
	m_AttrSize = vtx.size();
	m_ShouldUpdateVertexAttrs = true;
}

void ObjectData::updateVertexAttrs(VertexPtr vtx, Count vtxN)
{
	m_AttrData = vtx;
	m_AttrSize = vtxN;
	m_ShouldUpdateVertexAttrs = true;
}

ObjectData::~ObjectData()
{
	delete m_VAO;
	delete m_VBO;
}

#include "physics/Polyhedron.h"


Polyhedron::Polyhedron(std::string name, glm::vec3 position, glm::vec3 dimension, Quaternion quaternion, float density)
    : RigidBody(position, quaternion), m_Name(name), m_Dimen(dimension), m_Density(density)
{ }

Polyhedron::~Polyhedron()
{
	// Render::~Render() destructs the ObjectData.
}

void Polyhedron::init()
{
	m_Verts.reserve(8);
	m_Faces.reserve(12);

	initBody();
	initPhysicalProperties();

	m_AttribArray.reserve(216);

	for (auto f : m_Faces) {
		auto norm = glm::normalize(glm::cross(glm::normalize(m_Verts[f.y] - m_Verts[f.x]),
		                           glm::normalize(m_Verts[f.z] - m_Verts[f.y])));
		m_AttribArray.push_back(m_Verts[f.x].x);
		m_AttribArray.push_back(m_Verts[f.x].y);
		m_AttribArray.push_back(m_Verts[f.x].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
		m_AttribArray.push_back(m_Verts[f.y].x);
		m_AttribArray.push_back(m_Verts[f.y].y);
		m_AttribArray.push_back(m_Verts[f.y].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
		m_AttribArray.push_back(m_Verts[f.z].x);
		m_AttribArray.push_back(m_Verts[f.z].y);
		m_AttribArray.push_back(m_Verts[f.z].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
	}


	std::vector<unsigned int> attrs;
	attrs.push_back(3);
	attrs.push_back(3);

	Render::addObject(m_Name, m_AttribArray, attrs);

	update();  // Let the object hang in the air.
}

void Polyhedron::update()
{
	float dt = Physics::time * 0.001f;

	m_F = glm::vec3(0.0f);
	m_Torque = glm::vec3(0.0f);

	// Set gravity force.
	m_F.y = -m_Mass * Physics::G;

	// Add buoyancy force.
	computeBuoyancy();

	// Update velocities first.
	m_V += (dt / m_Mass) * m_F;
	glm::vec3 tmp(m_Torque.x / m_I.x, m_Torque.y / m_I.y, m_Torque.z / m_I.z);
	m_W += dt * tmp;

	// Update positions using new velocities.
	Quaternion omegaQ(m_W.x, m_W.y, m_W.z, 0);
	m_Pos += dt * m_V;
	m_Q += (0.5f * dt) * omegaQ * m_Q;
	m_Q.normalize();

	// Update Model matrix
	Render::objects[m_Name]->setModelMatrix(Func::Translate(m_Pos, m_Q));
}

void Polyhedron::restart(bool rebuildBody)
{
	m_Pos = m_PosBegin;
	m_Q.reset();

	if (rebuildBody) {
		initBody();
	}
	initPhysicalProperties();
	update();
}

void Polyhedron::updateVertexAttrs()
{
	m_AttribArray.clear();
	m_AttribArray.reserve(216);

	for (auto f : m_Faces) {
		auto norm = glm::normalize(glm::cross(glm::normalize(m_Verts[f.y] - m_Verts[f.x]),
		                           glm::normalize(m_Verts[f.z] - m_Verts[f.y])));
		m_AttribArray.push_back(m_Verts[f.x].x);
		m_AttribArray.push_back(m_Verts[f.x].y);
		m_AttribArray.push_back(m_Verts[f.x].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
		m_AttribArray.push_back(m_Verts[f.y].x);
		m_AttribArray.push_back(m_Verts[f.y].y);
		m_AttribArray.push_back(m_Verts[f.y].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
		m_AttribArray.push_back(m_Verts[f.z].x);
		m_AttribArray.push_back(m_Verts[f.z].y);
		m_AttribArray.push_back(m_Verts[f.z].z);
		m_AttribArray.push_back(norm.x);
		m_AttribArray.push_back(norm.y);
		m_AttribArray.push_back(norm.z);
	}

	Render::objects[m_Name]->updateVertexAttrs(m_AttribArray);
}

void Polyhedron::initPhysicalProperties()
{
	m_Q.normalize();

	float hx = m_Dimen.x;
	float hy = m_Dimen.y;
	float hz = m_Dimen.z;

	// Approximate length
	m_Length = 1.0f;
	m_Volume = Func::ComputeVolume(m_Verts, m_Faces);

	m_Mass = m_Density * m_Volume;	// half the density of water
	//body.I = (4.0f * m_Mass / 12.0f) * glm::vec3 { hy*hz, hx*hz, hx*hy };
	m_I = (m_Mass / 12.0f) * glm::vec3 { (hy*hy + hz*hz), (hx*hx + hz*hz), (hx*hx + hy*hy) };
	// Setup initial conditions
	m_V = glm::vec3 { 0.0f, 0.0f, 0.0f };
	m_W = glm::vec3 { 0.0f, 0.0f, 0.0f };
	m_F = glm::vec3 { 0.0f, 0.0f, 0.0f };
	m_Torque = glm::vec3 { 0.0f, 0.0f, 0.0f };
}

void Polyhedron::initBody()
{
	if (!m_Verts.empty()) m_Verts.clear();
	if (!m_Faces.empty()) m_Faces.clear();

	m_NumVerts = 8;
	m_NumFaces = 12;
	m_Verts.reserve(m_NumVerts);
	m_Faces.reserve(m_NumFaces);

	float hx = m_Dimen.x;
	float hy = m_Dimen.y;
	float hz = m_Dimen.z;

	m_Verts.emplace_back(-hx, -hy, -hz);  // 0
	m_Verts.emplace_back(-hx, -hy,  hz);  // 1
	m_Verts.emplace_back(-hx,  hy, -hz);  // 2
	m_Verts.emplace_back(-hx,  hy,  hz);  // 3
	m_Verts.emplace_back( hx, -hy, -hz);  // 4
	m_Verts.emplace_back( hx, -hy,  hz);  // 5
	m_Verts.emplace_back( hx,  hy, -hz);  // 6
	m_Verts.emplace_back( hx,  hy,  hz);  // 7

//	m_Faces.emplace_back(3, 6, 2);
//	m_Faces.emplace_back(3, 7, 6);
//	m_Faces.emplace_back(1, 0, 4);
//	m_Faces.emplace_back(1, 4, 5);
//	m_Faces.emplace_back(0, 3, 2);
//	m_Faces.emplace_back(0, 1, 3);
//	m_Faces.emplace_back(4, 7, 6);
//	m_Faces.emplace_back(4, 5, 7);
//	m_Faces.emplace_back(3, 5, 7);
//	m_Faces.emplace_back(3, 1, 5);
//	m_Faces.emplace_back(4, 2, 6);
//	m_Faces.emplace_back(4, 0, 2);

	m_Faces.emplace_back(0, 1, 3);
	m_Faces.emplace_back(0, 3, 2);
	m_Faces.emplace_back(6, 3, 7);
	m_Faces.emplace_back(6, 2, 3);
	m_Faces.emplace_back(4, 6, 5);
	m_Faces.emplace_back(6, 7, 5);
	m_Faces.emplace_back(4, 5, 0);
	m_Faces.emplace_back(0, 5, 1);
	m_Faces.emplace_back(5, 7, 1);
	m_Faces.emplace_back(7, 3, 1);
	m_Faces.emplace_back(0, 6, 4);
	m_Faces.emplace_back(0, 2, 6);
}

// Compute the buoyancy and drag forces
void Polyhedron::computeBuoyancy()
{
	float volume;
	glm::vec3 center;

	std::tie(volume, center) = Func::SubmergedVolume(m_Verts, m_Faces, m_Pos, m_Q);
	//std::cout << "submerged volume : " << volume << std::endl;

	if (volume > 0) {
		// Buoyancy force = specific weight * volume
		glm::vec3 buoyancyForce = (Water::density * volume * Physics::G) * Water::Plane::normal;

		float partialMass = m_Mass * volume / m_Volume;
		glm::vec3 rc = center - m_Pos;
		glm::vec3 vc = m_V + glm::cross(m_W, rc);
		glm::vec3 dragForce = (partialMass * Water::linearDrag) * (Water::velocity - vc);

		glm::vec3 totalForce = buoyancyForce + dragForce;
		m_F += totalForce;
		m_Torque += glm::cross(rc, totalForce);

		float len = m_Length * m_Length;
		glm::vec3 dragTorque = (-partialMass * Water::angularDrag * len) * m_W;
		m_Torque += dragTorque;
	}
}

void Polyhedron::setQuaternion(QVector4D quaternion)
{
	m_Q.setInitials(Func::GlmVec4(quaternion));
}

void Polyhedron::setPosition(glm::vec3 pos)
{
	m_PosBegin = pos;
}

void Polyhedron::setDimension(glm::vec3 dimen)
{
	m_Dimen = dimen;
}

void Polyhedron::setDensity(float density)
{
	m_Density = density;
}

glm::vec3 Polyhedron::position() const
{
	return m_Pos;
}

glm::vec4 Polyhedron::quaternion() const
{
	return m_Q.initials();
}

glm::vec3 Polyhedron::dimension() const
{
	return m_Dimen;
}

float Polyhedron::density() const
{
	return m_Density;
}

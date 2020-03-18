#include "physics/PhysicsEngine.h"

long PhysicsEngine::m_CurrentObjectID = -1;
std::unordered_map<std::string, int> PhysicsEngine::m_Objects;
bool PhysicsEngine::m_ShouldUpdate = false;
bool PhysicsEngine::m_IsAtTheStart = true;
bool PhysicsEngine::m_RebuildObject = false;

PhysicsEngine::PhysicsEngine()
{ }

PhysicsEngine::~PhysicsEngine()
{ }

bool PhysicsEngine::shouldUpdate()
{
	return m_ShouldUpdate;
}

bool PhysicsEngine::isAtTheStart()
{
	return m_IsAtTheStart;
}

/**********************************************************************************************
 **********************     ADDING NEW OBJECT INTO THE ENGINE     *****************************
 ************     Please change init(), update(), restart() at the same time.     *************
 ************               And all the object related functions!!!               *************
 *********************************************************************************************/

Polyhedron PhysicsEngine::cuboid("Cuboid");

void PhysicsEngine::init(std::string initObjectName)
{
	cuboid.init();

	m_Objects.emplace(std::make_pair("Cuboid", 8));
	// m_Objects.emplace(std::make_pair(<object name>, <object ID>));
	m_CurrentObjectID = m_Objects[initObjectName];
}

void PhysicsEngine::update()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.update();
			break;
		}
		default: { noSuchObjectFailure(); }
	}
}

void PhysicsEngine::restart()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.restart(m_RebuildObject);
			break;
		}
		default: { noSuchObjectFailure(); }
	}

	m_RebuildObject = false;
}

QVector3D PhysicsEngine::objectPosition()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			return Func::QtVector3(cuboid.position());
			break;
		}
		default: { noSuchObjectFailure(); return QVector3D{-1,-1,-1}; }
	}
}

QVector3D PhysicsEngine::objectDimension()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			return Func::QtVector3(cuboid.dimension());
			break;
		}
		default: { noSuchObjectFailure(); return QVector3D{-1,-1,-1}; }
	}
}

qreal PhysicsEngine::objectDensity()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			return cuboid.density();
			break;
		}
		default: { noSuchObjectFailure(); return -1; }
	}
}

QVector4D PhysicsEngine::objectQuaternion()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			return Func::QtVector4(cuboid.quaternion());
			break;
		}
		default: { noSuchObjectFailure(); return QVector4D(-1.f, -1.f, -1.f, -1.f); }
	}
}

void PhysicsEngine::setObjectPosition(QVector3D pos)
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.setPosition(Func::GlmVec3(pos));
			break;
		}
		default: { noSuchObjectFailure(); }
	}
	emit(objectPositionChanged());
}

void PhysicsEngine::setObjectDimension(QVector3D dimen)
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.setDimension(Func::GlmVec3(dimen));
			break;
		}
		default: { noSuchObjectFailure(); }
	}
	emit(objectDimensionChanged());
}

void PhysicsEngine::setObjectDensity(qreal density)
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.setDensity(density);
			break;
		}
		default: { noSuchObjectFailure(); }
	}
	emit(objectDensityChanged());
}

void PhysicsEngine::setObjectQuaternion(QVector4D quaternion)
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.setQuaternion(quaternion);
			break;
		}
		default: { noSuchObjectFailure(); }
	}
	emit(objectQuaternionChanged());
}

void PhysicsEngine::updateAttrs()
{
	switch (m_CurrentObjectID)
	{
		case 8:
		{
			cuboid.updateVertexAttrs();
			break;
		}
		default: { noSuchObjectFailure(); }
	}
}
/**********************************************************************************************
 **********************     ADDING NEW OBJECT INTO THE ENGINE     *****************************
 ************     Please change init(), update(), restart() at the same time.     *************
 ************               And all the object related functions!!!               *************
 *********************************************************************************************/


void PhysicsEngine::setCurrentObject(QString objectName)
{
	m_CurrentObjectID = m_Objects[objectName.toStdString()];
}

void PhysicsEngine::setWaterVelocity(QVector3D velocity)
{
	Water::velocity.x = velocity.x();
	Water::velocity.y = velocity.y();
	Water::velocity.z = velocity.z();
}

void PhysicsEngine::setWaterDensity(qreal density)
{
	Water::density = density;
}

void PhysicsEngine::setWaterLinearDrag(qreal force)
{
	Water::linearDrag = force;
}

void PhysicsEngine::setWaterAngularDrag(qreal force)
{
	Water::angularDrag = force;
}

QVector3D PhysicsEngine::waterVelocity()
{
	return Func::QtVector3(Water::velocity);
}

qreal PhysicsEngine::waterDensity()
{
	return Water::density;
}

qreal PhysicsEngine::waterLinearDrag()
{
	return Water::linearDrag;
}

qreal PhysicsEngine::waterAngularDrag()
{
	return Water::angularDrag;
}

QString PhysicsEngine::currentObject()
{
	for (std::unordered_map<std::string, int>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it) {
		if (it->second == m_CurrentObjectID)
			return QString::fromStdString(it->first);
	}
	std::cerr << "[ERROR] In PhysicsEngine: Object not found. Fix me." << std::endl;
	exit(EXIT_FAILURE);
}

void PhysicsEngine::noSuchObjectFailure()
{
	std::cerr << "[ERROR] In PhysicsEngine: Current object doesn't exist. PhysicsEngine not initiated"
	             " or the Object ID is not in the switch-case statement." << std::endl;
}

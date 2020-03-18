#pragma once

#include "physics/World.h"
#include "physics/Polyhedron.h"

#include <unordered_map>
#include <string>
#include <iostream>
#include <QtCore/QObject>
#include <QtGui/QVector3D>


class PhysicsEngine : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool shouldUpdate MEMBER m_ShouldUpdate READ shouldUpdate NOTIFY shouldUpdateChanged)
	Q_PROPERTY(bool isAtTheStart MEMBER m_IsAtTheStart READ isAtTheStart NOTIFY isAtTheStartChanged)
	Q_PROPERTY(bool rebuildObject MEMBER m_RebuildObject)
	Q_PROPERTY(QString currentObject READ currentObject WRITE setCurrentObject NOTIFY currentObjectChanged)

	Q_PROPERTY(QVector3D waterVelocity READ waterVelocity WRITE setWaterVelocity NOTIFY waterVelocityChanged)
	Q_PROPERTY(qreal waterDensity READ waterDensity WRITE setWaterDensity NOTIFY waterDensityChanged)
	Q_PROPERTY(qreal waterLinearDrag READ waterLinearDrag WRITE setWaterLinearDrag NOTIFY waterLinearDragChanged)
	Q_PROPERTY(qreal waterAngularDrag READ waterAngularDrag WRITE setWaterAngularDrag NOTIFY waterAngularDragChanged)

	Q_PROPERTY(QVector3D objectDimension READ objectDimension WRITE setObjectDimension NOTIFY objectDimensionChanged)
	Q_PROPERTY(QVector3D objectPosition READ objectPosition WRITE setObjectPosition NOTIFY objectPositionChanged)
	Q_PROPERTY(qreal objectDensity READ objectDensity WRITE setObjectDensity NOTIFY objectDensityChanged)

	Q_PROPERTY(QVector4D objectQuaternion READ objectQuaternion WRITE setObjectQuaternion NOTIFY objectQuaternionChanged)

	static std::unordered_map<std::string, int> m_Objects;
	static long m_CurrentObjectID;
	static bool m_ShouldUpdate;
	static bool m_IsAtTheStart;
	static bool m_RebuildObject;

	static Polyhedron cuboid;
	static void noSuchObjectFailure();
public:
	PhysicsEngine();
	~PhysicsEngine();

	Q_INVOKABLE static void init(std::string initObjectName);
	Q_INVOKABLE static void update();
	Q_INVOKABLE static void restart();
	Q_INVOKABLE static void updateAttrs();

	static bool shouldUpdate();
	static bool isAtTheStart();
	QString currentObject();
	void setCurrentObject(QString objectName);
	void setWaterVelocity(QVector3D velocity);
	void setWaterDensity(qreal density);
	void setWaterLinearDrag(qreal force);
	void setWaterAngularDrag(qreal force);
	void setObjectDimension(QVector3D dimen);
	void setObjectPosition(QVector3D pos);
	void setObjectDensity(qreal density);
	void setObjectQuaternion(QVector4D quaternion);
	QVector3D waterVelocity() ;
	qreal waterDensity();
	qreal waterLinearDrag();
	qreal waterAngularDrag();
	QVector3D objectDimension();
	QVector3D objectPosition();
	qreal objectDensity();
	QVector4D objectQuaternion();
signals:
	void shouldUpdateChanged();
	void isAtTheStartChanged();
	void currentObjectChanged();
	void waterVelocityChanged();
	void waterDensityChanged();
	void waterLinearDragChanged();
	void waterAngularDragChanged();
	void objectDimensionChanged();
	void objectPositionChanged();
	void objectDensityChanged();
	void objectQuaternionChanged();
};

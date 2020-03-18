#include "render/Camera.h"


Camera::Camera()
  : m_Position{0.f, 12.f, 25.f},
    m_Forward(m_Position + QVector3D{0.f, 0.f, -1.f}),
    m_Up(QVector3D{0.f, 1.f, 0.f}),
    m_WorldUp(QVector3D{0.f, 1.f, 0.f}),
    m_Yaw(180.0),
    m_Pitch(-20.0),
    m_Zoom(45.0),
    m_UnitXZ(1.0, 0.0, 1.0),
    m_UnitY(0.0, 1.0, 0.0),
    m_RateSurgeByCursor(0.08f),
    m_RateSwayByCursor(0.08f),
    m_RateMoveByKey(0.6f)
{
	updateCameraVectors();
#ifndef NDEBUG
	debug();
#endif
}

Camera::~Camera() { }

// Caculates the forward vector from the Camera's (update) Euler Angles
void Camera::updateCameraVectors()
{
	// Caculate the new m_Forward vector
	QVector3D forward;
	forward.setX(qCos(qDegreesToRadians(m_Pitch)) * qSin(qDegreesToRadians(m_Yaw)));
	forward.setZ(qCos(qDegreesToRadians(m_Pitch)) * qCos(qDegreesToRadians(m_Yaw)));
	forward.setY(qSin(qDegreesToRadians(m_Pitch)));
	m_Forward = forward.normalized();
	// Also re-caculate the Right and m_Up vector
	m_Right = QVector3D::crossProduct(m_Forward, m_WorldUp).normalized(); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = QVector3D::crossProduct(m_Right, m_Forward).normalized(); // *A cross B != B cross A
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
QMatrix4x4 Camera::viewMatrix() const
{
	QMatrix4x4 view;
	view.lookAt(m_Position, m_Position + m_Forward, m_Up);
	return view;
}

QMatrix4x4 Camera::projMatrix() const
{
	QMatrix4x4 proj;
	proj.perspective(m_Zoom, (float)m_ViewportSize.width()/ m_ViewportSize.height(), 0.1f, 200.0f);
	return proj;
}

void Camera::cursorMoveBase(float mouseX, float mouseY)
{
	m_MoveBase = m_Position -
	(m_Right * mouseX * m_RateSwayByCursor + m_Forward * mouseY * m_RateSurgeByCursor) * m_UnitXZ;
}

void Camera::cursorMoveDest(float mouseX, float mouseY)
{
	m_Position = m_MoveBase +
	(m_Right * mouseX * m_RateSwayByCursor + m_Forward * mouseY * m_RateSurgeByCursor) * m_UnitXZ;

	emit(positionChanged());
}

void Camera::moveForward()
{
	m_Position += m_Forward * m_UnitXZ * m_RateMoveByKey;
	emit(positionChanged());
}

void Camera::moveBackward()
{
	m_Position -= m_Forward * m_UnitXZ * m_RateMoveByKey;
	emit(positionChanged());
}

void Camera::moveRight()
{
	m_Position += m_Right * m_UnitXZ * m_RateMoveByKey;
	emit(positionChanged());
}

void Camera::moveLeft()
{
	m_Position -= m_Right * m_UnitXZ * m_RateMoveByKey;
	emit(positionChanged());
}

void Camera::moveUp()
{
	m_Position += m_WorldUp * m_UnitY * m_RateMoveByKey;
	emit(positionChanged());
}

void Camera::moveDown()
{
	m_Position -= m_WorldUp * m_UnitY * m_RateMoveByKey;
	emit(positionChanged());
}

#ifndef NDEBUG
void Camera::debug() const
{
	std::cout << "\nCamera_Info\n====================" << std::endl;
	Debug::QVec3(m_Position, "Position");
	Debug::QVec3(m_Forward, "Forward");
	Debug::QVec3(m_Right, "Right");
	Debug::QVec3(m_Up, "Up");
	Debug::QVec3(m_WorldUp, "World_Up");
	Debug::QMat4(viewMatrix().transposed(), "Camera_View_Matrix");
	Debug::QMat4(projMatrix().transposed(), "Camera_Projection_Matrix");
}
#endif

#pragma once

#ifndef NDEBUG
#include <DebugFunctions.h>
#endif

#include <QtCore/QObject>
#include <QtCore/QtMath>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>


class Camera : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVector3D position MEMBER m_Position NOTIFY positionChanged)
	Q_PROPERTY(QVector3D forward MEMBER m_Forward NOTIFY forwardChanged)
	Q_PROPERTY(QVector3D right MEMBER m_Right NOTIFY rightChanged)
	Q_PROPERTY(QVector3D up MEMBER m_Up NOTIFY upChanged)
	Q_PROPERTY(QVector3D worldUP MEMBER m_WorldUp NOTIFY worldUpChanged)
	Q_PROPERTY(QMatrix4x4 viewMat READ viewMatrix NOTIFY viewMatChanged)
	Q_PROPERTY(QMatrix4x4 projMat READ projMatrix NOTIFY projMatChanged)
	Q_PROPERTY(QSize viewportSize MEMBER m_ViewportSize NOTIFY viewportSizeChanged)
	Q_PROPERTY(qreal yaw MEMBER m_Yaw NOTIFY yawChanged)
	Q_PROPERTY(qreal pitch MEMBER m_Pitch NOTIFY pitchChanged)
	Q_PROPERTY(qreal zoom MEMBER m_Zoom NOTIFY zoomChanged)

	Q_PROPERTY(float rateMoveByKey MEMBER m_RateMoveByKey NOTIFY rateMoveByKeyChanged)
	Q_PROPERTY(float rateSurgeByCursor MEMBER m_RateSurgeByCursor NOTIFY rateSurgeByCursorChanged)
	Q_PROPERTY(float rateSwayByCursor MEMBER m_RateSwayByCursor NOTIFY rateSwayByCursorChanged)

	QVector3D m_Position;
	QVector3D m_Forward;
	QVector3D m_Right;
	QVector3D m_Up;
	QVector3D m_WorldUp;
	QSize m_ViewportSize;
	qreal m_Yaw;
	qreal m_Pitch;
	qreal m_Zoom;
public:
	Camera();
	~Camera();
	QMatrix4x4 viewMatrix() const;  // Return View Matrix
	QMatrix4x4 projMatrix() const;  // Return Projection Matrix
	Q_INVOKABLE void updateCameraVectors();

	Q_INVOKABLE void moveForward();
	Q_INVOKABLE void moveBackward();
	Q_INVOKABLE void moveLeft();
	Q_INVOKABLE void moveRight();
	Q_INVOKABLE void moveUp();
	Q_INVOKABLE void moveDown();

	Q_INVOKABLE void cursorMoveBase(float mouseX, float mouseY);
	Q_INVOKABLE void cursorMoveDest(float mouseX, float mouseY);

private:
	QVector3D m_MoveBase;
	QVector3D m_UnitXZ;
	QVector3D m_UnitY;
	float m_RateSurgeByCursor;
	float m_RateSwayByCursor;
	float m_RateMoveByKey;

signals:
	void positionChanged();
	void forwardChanged();
	void rightChanged();
	void upChanged();
	void worldUpChanged();
	void viewMatChanged();
	void projMatChanged();
	void viewportSizeChanged();
	void yawChanged();
	void pitchChanged();
	void zoomChanged();

	void rateMoveByKeyChanged();
	void rateSurgeByCursorChanged();
	void rateSwayByCursorChanged();

#ifndef NDEBUG
private:
	void debug() const;
#endif
};

#pragma once

#include "glad/glad.h"

#include "physics/PhysicsEngine.h"
#include "render/Render.h"
#include "physics/World.h"
#include "DebugFunctions.h"

#include <glm/glm.hpp>
#include <QtCore/QObject>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLDebugLogger>


class Renderer : public QObject
{
	Q_OBJECT

	typedef std::vector<float>    VertexVec;
	typedef std::vector<unsigned short>    IndexVec;
	typedef std::vector<unsigned int>    LayoutVec;
	typedef float*    VertexPtr;
	typedef unsigned short*    IndexPtr;
	typedef unsigned int*    LayoutPtr;
	typedef unsigned int    Count;

	QQuickWindow* m_Window;

	std::string m_CurrentObject;
	glm::mat4 m_ViewMat;
	glm::mat4 m_ProjMat;
	QSize m_ViewportSize;

	QOpenGLDebugLogger m_Logger;
public slots:
	void loggingGLMsg(QOpenGLDebugMessage msg);

public slots:
	void openglRenderLoop();

public:
	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	void setWindow(QQuickWindow* window);
	void setViewMatrix(QMatrix4x4 viewMat);
	void setProjectionMatrix(QMatrix4x4 projMat);
	void setViewportSize(QSize size);
	void setCurrentObject(QString objectName);
	QMatrix4x4 viewMatrix() const;
	QMatrix4x4 projectionMatrix() const;
	QSize viewportSize() const;
	QString currentObject() const;
};

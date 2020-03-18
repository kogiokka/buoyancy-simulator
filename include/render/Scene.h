#pragma once

#include "render/Camera.h"
#include "render/Renderer.h"
#include "physics/World.h"
#include "physics/PhysicsEngine.h"

#include <QtCore/QTimer>
#include <QtQuick/QQuickItem>
#include <QtGui/QMatrix4x4>


class Scene : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(QString currentObject MEMBER m_CurrentObject WRITE setCurrentObject NOTIFY currentObjectChanged)
	Q_PROPERTY(QMatrix4x4 renderViewMat READ renderViewMat WRITE setRenderViewMat NOTIFY renderViewMatChanged)
	Q_PROPERTY(QMatrix4x4 renderProjMat READ renderProjMat WRITE setRenderProjMat NOTIFY renderProjMatChanged)
	Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
public:
	Scene();
	~Scene();
public slots:
	void sync();
	void cleanup();
	void setRenderViewMat(QMatrix4x4 viewMat);
	void setRenderProjMat(QMatrix4x4 projMat);
	void setViewportSize(QSize size);
	QMatrix4x4 renderViewMat() const;
	QMatrix4x4 renderProjMat() const;
	QSize viewportSize() const;
	Q_INVOKABLE void setCurrentObject(QString objectName);
private slots:
	void handleWindowChanged(QQuickWindow* window);
signals:
	void renderReady();
	void engineReady();
	void currentObjectChanged();
	void renderViewMatChanged();
	void renderProjMatChanged();
	void viewportSizeChanged();
private:
	Renderer* m_Renderer;
	QString m_CurrentObject;
	QTimer m_UpdateTimer;
};

#include "render/Scene.h"

Scene::Scene()
    : m_Renderer(nullptr), m_CurrentObject("Cuboid")
{
	connect(this, &QQuickItem::windowChanged, this, &Scene::handleWindowChanged);
}

void Scene::handleWindowChanged(QQuickWindow* window)
{
	if (window) {
		connect(&m_UpdateTimer, &QTimer::timeout, this->window(), &QQuickWindow::update);
		connect(window, &QQuickWindow::beforeSynchronizing, this, &Scene::sync, Qt::DirectConnection);
		connect(window, &QQuickWindow::sceneGraphInvalidated, this, &Scene::cleanup, Qt::DirectConnection);

		QQuickWindow::setTextRenderType(QQuickWindow::QtTextRendering);

		QSurfaceFormat glFormat;
		glFormat.setMajorVersion(4);
		glFormat.setMinorVersion(3);
		glFormat.setProfile(QSurfaceFormat::CoreProfile);
		glFormat.setSamples(2);
#ifndef NDEBUG
		glFormat.setOption(QSurfaceFormat::DebugContext);
#endif
		glFormat.setDepthBufferSize(1);
		glFormat.setStencilBufferSize(1);

		window->setFormat(glFormat);

		// If we allow QML to do the clearing, they would clear what we paint
		// and nothing would show.
		window->setClearBeforeRendering(false);

		m_UpdateTimer.setTimerType(Qt::PreciseTimer);
		m_UpdateTimer.setInterval(Physics::time);  // milliseconds
		m_UpdateTimer.start();
	}
}

void Scene::setRenderViewMat(QMatrix4x4 viewMat)
{
	m_Renderer->setViewMatrix(viewMat);
}

void Scene::setRenderProjMat(QMatrix4x4 projMat)
{
	m_Renderer->setProjectionMatrix(projMat);
}

void Scene::setViewportSize(QSize size)
{
	m_Renderer->setViewportSize(size);
}

QMatrix4x4 Scene::renderViewMat() const
{
	return m_Renderer->viewMatrix();
}

QMatrix4x4 Scene::renderProjMat() const
{
	return m_Renderer->projectionMatrix();
}

QSize Scene::viewportSize() const
{
	return m_Renderer->viewportSize();
}

void Scene::setCurrentObject(QString objectName)
{
	m_Renderer->setCurrentObject(objectName);
}

void Scene::sync()
{
	if (!m_Renderer) {

		m_Renderer = new Renderer();
		connect(window(), &QQuickWindow::beforeRendering, m_Renderer, &Renderer::openglRenderLoop,
		        Qt::DirectConnection);
		m_Renderer->setWindow(window());
		m_Renderer->setCurrentObject(m_CurrentObject);
		PhysicsEngine::init(m_CurrentObject.toStdString());

		emit(engineReady());
		emit(renderReady());
	}

	if (PhysicsEngine::shouldUpdate()) {
		PhysicsEngine::update();
	}
}

void Scene::cleanup()
{ }

Scene::~Scene()
{
	delete m_Renderer;
}

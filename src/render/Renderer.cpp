#include "render/Renderer.h"


Renderer::Renderer()
    : m_Window(nullptr), m_CurrentObject("")
{
#ifndef NDEBUG
//	connect(&m_Logger, &QOpenGLDebugLogger::messageLogged, this, &Renderer::loggingGLMsg, Qt::DirectConnection);
//	std::cout << (m_Logger.initialize() == true ?
//	             " ***  QOpenGLDebugLogger initialization success  ***\n" :
//	             " ***  QOpenGLDebugLogger needs GL_KHR_debug extension  ***\n" ) << std::endl;
//	m_Logger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
//	m_Logger.enableMessages();

	if (!gladLoadGL()) {
		std::cerr << "glad init failed!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << " ===== OpenGL init success! ====="
	          << "\nOpenGL Version: " << glGetString(GL_VERSION)
	          << "\nGLSL Version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION)
	          << "\nRenderer:       " << glGetString(GL_RENDERER)
	          << "\nVendor:         " << glGetString(GL_VENDOR) << "\n" << std::endl;
#endif

	namespace wm = Water::Model;
	Render::addObject("Water", wm::vertices, wm::attrs);
	Render::addProgram(0, ":/shaders/default.vert", ":/shaders/default.frag");
}

Renderer::~Renderer() { }

void Renderer::openglRenderLoop()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width = m_ViewportSize.width();
	int height = m_ViewportSize.height();

	Render::programs[0]->use();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	// Debug::Mat4(m_ViewMat, "View Matrix");
	Render::programs[0]->setVec4("light.position", 0.0f, 20.0f, 0.0f, 1.0f);
	Render::programs[0]->setVec4("light.intensity", 1.f, 1.f, 1.f, 1.f);
	Render::programs[0]->setFloat("light.ambientCoef", 0.3f);
	Render::programs[0]->setMat4("viewMat", m_ViewMat);
	Render::programs[0]->setMat4("projectMat", m_ProjMat);

	// Draw object
	Render::programs[0]->setMat4("modelMat", Render::objects[m_CurrentObject]->matrix());
	Render::programs[0]->setVec4("aColor", 1.0f, 0.8f, 0.31f, 1.0f);
	Render::objects[m_CurrentObject]->paint();

	// Draw water plane
	Render::programs[0]->setMat4("modelMat", Render::objects["Water"]->matrix());
	Render::programs[0]->setVec4("aColor", 0.0f, 0.85f, 0.95f, 0.3f);
	Render::objects["Water"]->paint();

	m_Window->resetOpenGLState();
}

void Renderer::setCurrentObject(QString objectName)
{
	m_CurrentObject = objectName.toStdString();
}

void Renderer::setViewMatrix(QMatrix4x4 viewMat)
{
	m_ViewMat = Func::QtMatrix4(viewMat);
}

void Renderer::setProjectionMatrix(QMatrix4x4 projMat)
{
	m_ProjMat = Func::QtMatrix4(projMat);
}

void Renderer::setViewportSize(QSize size)
{
	m_ViewportSize = size;
}

void Renderer::setWindow(QQuickWindow* window)
{
	m_Window = window;
}

QMatrix4x4 Renderer::viewMatrix() const
{
	return Func::GlmMat4(m_ViewMat);
}

QMatrix4x4 Renderer::projectionMatrix() const
{
	return Func::GlmMat4(m_ProjMat);
}

QSize Renderer::viewportSize() const
{
	return m_ViewportSize;
}

QString Renderer::currentObject() const
{
	return QString::fromStdString(m_CurrentObject);
}

void Renderer::loggingGLMsg(QOpenGLDebugMessage msg)
{
	qDebug() << msg;
}

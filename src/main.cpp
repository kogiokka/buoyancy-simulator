#include "render/Renderer.h"
#include "render/Camera.h"
#include "render/Cursor.h"
#include "physics/PhysicsEngine.h"
#include "render/Scene.h"

#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QGuiApplication>
#include <QtGui/QFontDatabase>
#include <QtQml/QQmlEngine>
#include <QtCore/QDebug>
#include <QtCore/QString>


int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);
	QStringList fontPaths {
		":/fonts/Ubuntu-Regular",
		":/fonts/Ubuntu-Light",
		":/fonts/Ubuntu-Medium",
		":/fonts/Ubuntu-Mono",
	};

	for (QString& s : fontPaths) {
		int fontID = QFontDatabase::addApplicationFont(s);
		if (fontID == -1) {
			qDebug() << "addApplicationFont failed.";
		}
	}


	qmlRegisterType<Cursor>("Cpp.Cursor", 1, 0, "Cursor");
	qmlRegisterType<Scene>("Buoyancy.OpenGL", 1, 0, "Simulation");
	qmlRegisterType<Camera>("Buoyancy.OpenGL", 1, 0, "Camera");
	qmlRegisterType<PhysicsEngine>("Buoyancy.OpenGL", 1, 0, "PhysicsEngine");

	QQmlApplicationEngine engine;
	engine.load(QUrl("qrc:/main.qml"));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

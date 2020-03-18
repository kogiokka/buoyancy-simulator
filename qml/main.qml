import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Buoyancy.OpenGL 1.0
import Cpp.Cursor 1.0

import "."

ApplicationWindow {
	id: app

	property ApplicationWindow appWindow: app
	property Panels panels
	property EngineComponent engine: physicsEngine
	property bool isPanelActive

	title: "Buoyancy Simulation"
	width: 1200
	height: 800
	minimumWidth: 800
	minimumHeight: 600
	visible: true

	// Simulation Viewport
	onHeightChanged: {
		scene.viewportSize = Qt.size(width, height)
		scene.camera.viewportSize = Qt.size(width, height)
	}

	onWidthChanged: {
		scene.viewportSize = Qt.size(width, height)
		scene.camera.viewportSize = Qt.size(width, height)
	}

	Cursor {
		id: cursor
	}

	Simulation {
		id: scene
		property CameraComponent camera

		onRenderReady: {
			var cameraComponent = Qt.createComponent("CameraComponent.qml")
			if (cameraComponent.status === Component.Ready) {
				camera = cameraComponent.createObject(parent, {
					viewportSize: Qt.size(app.contentItem.width, app.contentItem.height),
					enableWheel: Qt.binding(function () { return !app.isPanelActive }),
				})
				renderViewMat = camera.viewMat
				renderProjMat = camera.projMat
			}
		}

		onEngineReady: {
			var controlPanel = Qt.createComponent("Panels.qml")
			if (controlPanel.status === Component.Ready) {
				panels = controlPanel.createObject(parent, { z: 1 })
				isPanelActive = Qt.binding(function () { return panels.isActive })
			}
		}
	}

	EngineComponent {
		id: physicsEngine
	}

	/***     Application     ***/
	Shortcut {
		sequence: "Ctrl+Q"
		context: Qt.ApplicationShortcut
		onActivated: Qt.quit()
	}
}

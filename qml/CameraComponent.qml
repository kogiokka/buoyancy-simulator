import QtQuick 2.12
import Buoyancy.OpenGL 1.0

Item {
	id: cameraComponent

	property vector3d position: camera.position
	property matrix4x4 viewMat: camera.viewMat
	property matrix4x4 projMat: camera.projMat
	property real zoom: camera.zoom
	property real yaw: camera.yaw
	property real pitch: camera.pitch

	property size viewportSize
	property bool enableMouse: true
	property bool enableWheel: true

	anchors.fill: parent

	Camera {
		id: camera

		viewportSize: cameraComponent.viewportSize

		// C++: QMatrix4x4::lookAt => View Matrix
		onPositionChanged: {
			scene.renderViewMat = viewMat
		}

		onYawChanged: {
			updateCameraVectors()
			scene.renderViewMat = viewMat
		}

		onPitchChanged: {
			updateCameraVectors()
			scene.renderViewMat = viewMat
		}

		// C++: QMatrix4x4::perspective => Projection matrix
		onViewportSizeChanged: {
			scene.renderProjMat = projMat
		}

		onZoomChanged: {
			scene.renderProjMat = projMat
		}
	}

	MouseArea {
		id: cameraCursor

		property real thetaBase: 0.0
		property real phiBase: 0.0

		// Scaling theta by ((fovy * aspect ratio) / viewport width)
		// Scaling phi by (fovy / viewport height)
		property real rateTheta: (camera.zoom * (width / height)) / width
		property real ratePhi: camera.zoom / height

		enabled: enableMouse
		anchors.fill: parent
		hoverEnabled: false
		scrollGestureEnabled: true
		acceptedButtons: Qt.RightButton | Qt.LeftButton

		onPressed: {
			focus = true
			cursorShape = Qt.DragMoveCursor

			switch (cameraCursor.pressedButtons)
			{
			case Qt.RightButton:
				thetaBase = camera.yaw - mouseX * rateTheta
				phiBase = camera.pitch - mouseY * ratePhi
				break
			case Qt.LeftButton:
				camera.cursorMoveBase(width - mouseX, mouseY)
				break
			}
		}

		onReleased: {
			cursorShape = Qt.ArrowCursor
		}

		onPositionChanged: {
			switch (cameraCursor.pressedButtons)
			{
			case Qt.RightButton:
				camera.yaw = thetaBase + mouseX * rateTheta
				camera.pitch = phiBase + mouseY * ratePhi
				break
			case Qt.LeftButton:
				camera.cursorMoveDest(width - mouseX, mouseY)
				break
			}
		}

		onWheel: {
			if (enableWheel == false) return;
			var fovy = camera.zoom - (wheel.angleDelta.y / 100.0)
			if (fovy < 60.0 && fovy > 10.0)
				camera.zoom = fovy
		}
	}

	Keys.onPressed: {
		switch (event.modifiers)
		{
		case Qt.NoModifier:  // --- No modifiers
			switch (event.key)
			{
			case Qt.Key_W:
				camera.moveForward()
				break
			case Qt.Key_A:
				camera.moveLeft()
				break
			case Qt.Key_S:
				camera.moveBackward()
				break
			case Qt.Key_D:
				camera.moveRight()
				break
			}
			break
		case Qt.ShiftModifier:  // --- Shift + <key>
			switch (event.key)
			{
			case Qt.Key_W:
				camera.moveUp()
				break
			case Qt.Key_S:
				camera.moveDown()
				break
			}
			break
		}
	}
}

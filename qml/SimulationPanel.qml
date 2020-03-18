import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Pane {
	focusPolicy: Qt.ClickFocus
	background: Rectangle {
		radius: 16
		color: "#99ffffff"
	}

	ColumnLayout {
		id: col

		property real layoutMargin: 10.0

		visible: (width > 240)
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		spacing: -5

		Vector3Input {
			Layout.margins: col.layoutMargin
			label: "Position"
			dx: engine.objectPosition.x
			dy: engine.objectPosition.y
			dz: engine.objectPosition.z
			onEditedX: { engine.objectPosition.x = newX }
			onEditedY: { engine.objectPosition.y = newY }
			onEditedZ: { engine.objectPosition.z = newZ }
			validTop: Qt.vector3d(30.0, 30.0, 30.0)
			validBottom: Qt.vector3d(-30.0, -30.0, -30.0)
			unitX: "m"
			unitY: "m"
			unitZ: "m"
		}

		Vector4Input {
			Layout.margins: col.layoutMargin
			label: "Initial Rotation"
			dx: engine.objectQuaternion.x
			dy: engine.objectQuaternion.y
			dz: engine.objectQuaternion.z
			dw: engine.objectQuaternion.w
			onEditedX: { engine.objectQuaternion.x = newX }
			onEditedY: { engine.objectQuaternion.y = newY }
			onEditedZ: { engine.objectQuaternion.z = newZ }
			onEditedW: { engine.objectQuaternion.w = newW }
			validTop: Qt.vector4d(10.0, 10.0, 10.0, 10.0)
			validBottom: Qt.vector4d(-10.0, -10.0, -10.0, -10.0)
			unitX: "q"
			unitY: "q"
			unitZ: "q"
			unitW: "q"
		}
	}

	Behavior on Layout.preferredWidth {
		NumberAnimation { duration: 160 }
	}
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Cpp.Cursor 1.0

import "."

Pane {
	id: liquidPropPanel

	property bool expand: false

	width: 200
	height: appWindow.contentItem.height * 0.9
	focusPolicy: Qt.ClickFocus

	background: Rectangle {
		anchors.fill: liquidPropPanel
		radius: 16
		color: "#99ffffff"
	}

	// "&middot;" == "⋅"
	ColumnLayout {
		id: col

		property real layoutMargin: 10.0

		visible: liquidPropPanel.width > 250 ? true : false
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		spacing: -5

		Label {
			text: "Water Properties"
			Layout.fillWidth: true
			Layout.margins: col.layoutMargin
			horizontalAlignment: Text.AlignHCenter
			font.pointSize: 16
			font.family: "Ubuntu"
		}

		Vector3Input {
			label: "Velocity"

			Layout.margins: col.layoutMargin

			dx: engine.waterVelocity.x
			dy: engine.waterVelocity.y
			dz: engine.waterVelocity.z
			unitX: "m&middot;s<sup>-1</sup>"
			unitY: "m&middot;s<sup>-1</sup>"
			unitZ: "m&middot;s<sup>-1</sup>"

			onEditedX: {
				engine.waterVelocity.x = newX
			}
			onEditedY: {
				engine.waterVelocity.y = newY
			}
			onEditedZ: {
				engine.waterVelocity.z = newZ
			}
			validBottom: Qt.vector3d(-100.0, -100.0, -100.0)
		}

		ScalarInput {
			Layout.margins: col.layoutMargin

			label: "Density"
			value: engine.waterDensity
			onEditedValue: {
				engine.waterDensity = newValue
			}
			validTop: 3000
			unit: "kg&middot;m<sup>-3</sup>"
		}

		ScalarInput {
			Layout.margins: col.layoutMargin

			label: "Linear Drag"
			value: engine.waterLinearDrag
			onEditedValue: {
				engine.waterLinearDrag = newValue
			}
			unit: "kg&middot;m&middot;s<sup>-2</sup>"
		}

		ScalarInput {
			Layout.margins: col.layoutMargin

			label: "Angular Drag"
			value: engine.waterAngularDrag
			onEditedValue: {
				engine.waterAngularDrag = newValue
			}
			unit: "kg&middot;m&middot;s<sup>-2</sup>"
		}
	}

	states: [
		State {
			name: "collapsed"
			when: !expand
			PropertyChanges {
				target: liquidPropPanel
				visible: false
				width: 200
			}
		},
		State {
			name: "expanded"
			when: expand
			PropertyChanges {
				target: liquidPropPanel
				visible: true
				width: 320
			}
		}
	]

	Behavior on width {
		NumberAnimation { duration: 80 }
	}
}

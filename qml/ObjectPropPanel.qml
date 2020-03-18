import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "."

Pane {
	id: objectPropPanel

	property bool expand: false

	width: 200
	height: appWindow.contentItem.height * 0.9
	focusPolicy: Qt.ClickFocus

	background: Rectangle {
		anchors.fill: objectPropPanel
		radius: 16
		color: "#99ffffff"
	}

	ColumnLayout {
		id: col

		property real layoutMargin: 10.0

		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		visible: objectPropPanel.width > 250 ? true : false
		spacing: -5

		Label {
			text: engine.currentObject
			Layout.fillWidth: true
			Layout.margins: col.layoutMargin
			horizontalAlignment: Text.AlignHCenter
			font.pointSize: 16
			color: "#000000"
		}

		Vector3Input {
			Layout.margins: col.layoutMargin
			label: "Dimension"
			dx: engine.objectDimension.x
			dy: engine.objectDimension.y
			dz: engine.objectDimension.z
			onEditedX: { engine.objectDimension.x = newX }
			onEditedY: { engine.objectDimension.y = newY }
			onEditedZ: { engine.objectDimension.z = newZ }
			validTop: Qt.vector3d(200.0, 200.0, 200.0)
			validBottom: Qt.vector3d(0.1, 0.1, 0.1)
			unitX: "m"
			unitY: "m"
			unitZ: "m"
		}

		ScalarInput {
			Layout.margins: col.layoutMargin
			label: "Density"
			value: engine.objectDensity
			validTop: 9000
			validBottom: 0.1
			onEditedValue: {
				engine.objectDensity = newValue
			}
			unit: "kg&middot;m<sup>-3</sup>"
		}
	}

	states: [
		State {
			name: "collapsed"
			when: !expand
			PropertyChanges {
				target: objectPropPanel
				visible: false
				width: 200
			}
		},
		State {
			name: "expanded"
			when: expand
			PropertyChanges {
				target: objectPropPanel
				visible: true
				width: 320
			}
		}
	]

	Behavior on width {
		NumberAnimation { duration: 80 }
	}
}

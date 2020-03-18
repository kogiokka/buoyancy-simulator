import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "."

Pane {
	id: objectListPanel

	property bool expand: false

	width: 200
	height: appWindow.contentItem.height * 0.9
	focusPolicy: Qt.ClickFocus

	background: Rectangle {
		anchors.fill: objectListPanel
		radius: 16
		color: "#99ffffff"
	}

	ColumnLayout {
		id: col

		property real layoutMargin: 10.0

		anchors.top: parent.top
		anchors.right: parent.right
		anchors.left: parent.left
		spacing: -5

		Label {
			text: "Select Object"

			Layout.fillWidth: true
			Layout.margins: col.layoutMargin
			horizontalAlignment: Text.AlignHCenter
			font.pointSize: 16
			font.family: "Ubuntu"
		}
	}

	states: [
		State {
			name: "collapsed"
			when: !expand
			PropertyChanges {
				target: objectListPanel
				visible: false
				width: 200
			}
		},
		State {
			name: "expanded"
			when: expand
			PropertyChanges {
				target: objectListPanel
				visible: true
				width: 320
			}
		}
	]

	Behavior on width {
		NumberAnimation { duration: 80 }
	}

}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Pane {
	property int currentButton: -1
	property int size: buttons.children.length

	function adjustButtonStyle () {
		for (var i = 0; i < size; i++) {
			if (currentButton !== i) buttons.children[i].active = false
		}
	}

	Component.onCompleted: {
		for (var i = 0; i < size; i++) {
			buttons.children[i].index = i
		}
	}

	background: Rectangle {
		color: "#aaeff0f1"
		radius: 16
		anchors.fill: parent
	}

	ColumnLayout {
		id: buttons
		anchors.horizontalCenter: parent.horizontalCenter
		spacing: 8

		PanelButton {
			iconSrc: "icons/waves"
			Layout.alignment: Qt.AlignHCenter
			Layout.minimumWidth: btnSize
			Layout.minimumHeight: btnSize

			onClicked: {
				active = !active
				currentButton = active ? index : -1
			}
		}

		PanelButton {
			iconSrc: "icons/bookmarks"
			Layout.alignment: Qt.AlignHCenter
			Layout.minimumWidth: btnSize
			Layout.minimumHeight: btnSize

			onClicked: {
				active = !active
				currentButton = active ? index : -1
			}
		}

		PanelButton {
			iconSrc: "icons/edit-attributes"
			Layout.alignment: Qt.AlignHCenter
			Layout.minimumWidth: btnSize
			Layout.minimumHeight: btnSize

			onClicked: {
				active = !active
				currentButton = active ? index : -1
			}
		}
	}
}

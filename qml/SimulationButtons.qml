import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Row {
	property bool updating: engine.shouldUpdate
	property real buttonOpacity: updating ? 0.35 : 1.0
	property bool expanded: expandSwitch.active
	property bool show: (spacing > -buttonSize)

	property real buttonSize

	opacity: buttonOpacity
	layoutDirection: Qt.RightToLeft
	spacing: expanded ? 20 : -buttonSize

	StyledButton {
		id: expandSwitch

		implicitWidth: buttonSize
		implicitHeight: buttonSize
		btnRadius: buttonSize
		iconSrc: "icons/games"
		activeColor: "#ffc107"

		onClicked: {
			active = !active
		}
	}

	StyledButton {
		visible: show

		implicitWidth: buttonSize
		implicitHeight: buttonSize
		btnRadius: buttonSize
		iconSrc: "icons/replay"

		onClicked: {
			engine.shouldUpdate = false
			engine.isAtTheStart = true
			engine.restart()
		}
	}

	StyledButton {
		visible: show

		implicitWidth: buttonSize
		implicitHeight: buttonSize
		btnRadius: buttonSize
		iconSrc: updating ? "icons/pause" : "icons/play"

		onClicked:{
			engine.isAtTheStart = false
			engine.shouldUpdate = !engine.shouldUpdate
		}
	}

	Behavior on spacing {
		NumberAnimation { duration: 120 }
	}
}

import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
	property string iconSrc
	property string activeColor: "#0077be"

	property real btnRadius: 16
	property bool active: false

	hoverEnabled: true
	icon.source: iconSrc
	icon.color: active ? "#ffffff" : "#000000"

	background: Rectangle {
		color: active ? activeColor : "#f5f5f5"
		radius: btnRadius
		antialiasing: true

		Behavior on color {
			ColorAnimation { duration: 120 }
		}
	}

	onHoveredChanged: {
		scale = hovered ? 1.15 : 1
	}

	Behavior on scale {
		NumberAnimation { duration: 120 }
	}
}

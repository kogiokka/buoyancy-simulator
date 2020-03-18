import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "."

GridLayout {
	id: vec3input

	property string label
	property real dx
	property real dy
	property real dz

	property string unitX: ""
	property string unitY: ""
	property string unitZ: ""
	property string hint: ""

	property vector3d validTop: Qt.vector3d(100.0, 100.0, 100.0)
	property vector3d validBottom: Qt.vector3d(0.0, 0.0, 0.0)

	signal editedX(real newX)
	signal editedY(real newY)
	signal editedZ(real newZ)

	property real labelFontSize: 14
	property real fontSize: 14

	columns: 3
	columnSpacing: 15
	rowSpacing: 6

	LabelWithLine {
		Layout.columnSpan: 3
		name: label
		fontPointSize: labelFontSize
	}

// -----   Field X -----
	Label {
		text: "X"
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

	BlenderStyleInputHandler {
		Layout.fillWidth: true

		defaultValue: dx
		hint: vec3input.hint
		fontPointSize: vec3input.fontSize
		fontFamily: "Ubuntu"
		validTop: vec3input.validTop.x
		validBottom: vec3input.validBottom.x

		onAccepted: {
			vec3input.dx = value
			vec3input.editedX(value)
		}
	}

	Label {
		textFormat: Text.RichText
		text: unitX
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

// -----   Field Y -----
	Label {
		text: "Y"
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

	BlenderStyleInputHandler {
		Layout.fillWidth: true

		defaultValue: dy
		hint: vec3input.hint
		fontPointSize: vec3input.fontSize
		fontFamily: "Ubuntu"
		validTop: vec3input.validTop.y
		validBottom: vec3input.validBottom.y

		onAccepted: {
			vec3input.dy = value
			vec3input.editedY(value)
		}
	}

	Label {
		textFormat: Text.RichText
		text: unitY
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

// -----   Field Z -----
	Label {
		text: "Z"
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

	BlenderStyleInputHandler {
		Layout.fillWidth: true

		defaultValue: dz
		hint: vec3input.hint
		fontPointSize: vec3input.fontSize
		fontFamily: "Ubuntu"
		validTop: vec3input.validTop.z
		validBottom: vec3input.validBottom.z

		onAccepted: {
			vec3input.dz = value
			vec3input.editedZ(value)
		}
	}

	Text {
		textFormat: Text.RichText
		text: unitZ
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

GridLayout {
	id: vec4input

	property string label
	property real dx
	property real dy
	property real dz
	property real dw

	property string unitX: ""
	property string unitY: ""
	property string unitZ: ""
	property string unitW: ""

	property vector4d validTop: Qt.vector4d(100.0, 100.0, 100.0, 100.0)
	property vector4d validBottom: Qt.vector4d(0.0, 0.0, 0.0, 0.0)

	signal editedX(real newX)
	signal editedY(real newY)
	signal editedZ(real newZ)
	signal editedW(real newW)

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
		defaultValue: dx
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignCenter
		fontPointSize: fontSize
		fontFamily: "Ubuntu"
		validTop: vec4input.validTop.x
		validBottom: vec4input.validBottom.x

		onAccepted: {
			vec4input.dx = value
			vec4input.editedX(value)
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
		defaultValue: dy
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignCenter
		fontPointSize: fontSize
		fontFamily: "Ubuntu"
		validTop: vec4input.validTop.y
		validBottom: vec4input.validBottom.y

		onAccepted: {
			vec4input.dy = value
			vec4input.editedY(value)
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
		defaultValue: dz
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignCenter
		fontPointSize: fontSize
		fontFamily: "Ubuntu"
		validTop: vec4input.validTop.z
		validBottom: vec4input.validBottom.z

		onAccepted: {
			vec4input.dz = value
			vec4input.editedZ(value)
		}
	}
	Text {
		textFormat: Text.RichText
		text: unitZ
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

// -----   Field W -----
	Label {
		text: "W"
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}
	BlenderStyleInputHandler {
		defaultValue: dw
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignCenter
		fontPointSize: fontSize
		fontFamily: "Ubuntu"
		validTop: vec4input.validTop.w
		validBottom: vec4input.validBottom.w

		onAccepted: {
			vec4input.dw = value
			vec4input.editedW(value)
		}
	}
	Text {
		textFormat: Text.RichText
		text: unitW
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "."

GridLayout {
	id: scalarinput

	property string label
	property string unit

	property real value
	property real validTop: 100.0
	property real validBottom: 0.0

	signal editedValue(real newValue)

	property real labelFontSize: 14
	property real fontSize: 12

	columns: 2
	columnSpacing: 15
	rowSpacing: 6

	LabelWithLine {
		Layout.columnSpan: 2
		name: label
		fontPointSize: labelFontSize
	}

	BlenderStyleInputHandler {
		defaultValue: scalarinput.value
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignCenter
		fontFamily: "Ubuntu"
		validTop: scalarinput.validTop
		validBottom: scalarinput.validBottom
		onAccepted: {
			scalarinput.value = value
			scalarinput.editedValue(value)
		}
	}

	Text {
		textFormat: Text.RichText
		text: unit
		font.pointSize: fontSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}
}

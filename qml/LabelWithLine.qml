import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
	property string name
	property real fontPointSize

	spacing: fontPointSize

	Label {
		Layout.alignment: Qt.AlignCenter
		textFormat: Text.RichText
		text: name
		font.pointSize: fontPointSize
		font.weight: Font.Normal
		font.family: "Ubuntu"
	}

	Rectangle {
		color: "transparent"
		Layout.fillWidth: true
		Layout.fillHeight: true

		Rectangle {
			color: "#000000"
			anchors.centerIn: parent
			height: 1.2
			width: parent.width * 0.9
		}
	}
}

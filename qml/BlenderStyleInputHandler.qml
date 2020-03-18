import QtQuick 2.12
import QtQuick.Controls 2.12

Row {
	property real validTop: 100.0
	property real validBottom: 0.1
	property real stepDrag: 0.01
	property real stepClick: 0.01

	property real fontPointSize: 14.0
	property string fontFamily: ""
	property string hint: ""

	property real btnRadius: 16.0
	property bool handlerPressed: false
	property bool handlerHovered: false
	property string colorIdle: handlerPressed ? Qt.tint("#eff0f1", "#10000000") : "#eff0f1"
	property string colorHovered: Qt.tint(colorIdle, "#11000000")

	property string prevValue
	property real defaultValue: 10.0
	property real currentValue: Number.parseFloat(field.text)
	property real newValue

	signal accepted(real value);

	function send()
	{
		/*
		 *  This function will only be called in three circumstances:
		 *   - TextField loses focus
		 *   - Button is clicked
		 *   - MouseArea is operating
		 */
		accepted(currentValue)
	}

	function fixedString(num, fix) // Accept float and return string
	{
		if (typeof fix == 'undefined') fix = 2;
		return num.toFixed(fix).toString()
	}

	function setPrevValue()
	{
		prevValue = fixedString(currentValue)
	}

	function addToCurrentValue(num)
	{
		newValue = currentValue + num

		if (newValue > validTop) {
			field.text = fixedString(validTop)
		} else if (newValue < validBottom) {
			field.text = fixedString(validBottom)
		} else {
			field.text = fixedString(newValue)
		}
	}

	spacing: -btnRadius
	layoutDirection: Qt.LeftToRight

	Button {
		id: down
		text: handlerHovered ? "\u2212" : ""
		font.pointSize: fontPointSize
		font.weight: Font.Normal
		font.family: fontFamily
		height: field.height
		width: field.height + btnRadius
		hoverEnabled: true

		contentItem: Text {
			text: down.text
			font: down.font
			opacity: enabled ? 1.0 : 0.3
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			leftPadding: 0.0
			rightPadding: btnRadius
		}

		background: Rectangle {
			anchors.fill: down
			color: down.hovered ? colorHovered : colorIdle
			radius: btnRadius
			antialiasing: true

			Behavior on color {
				ColorAnimation { duration: 90 }
			}
		}

		onHoveredChanged: {
			handlerHovered = hovered
		}

		onPressed: {
			handlerPressed = true
		}

		onReleased: {
			handlerPressed = false
		}

		onClicked: {
			addToCurrentValue(-stepClick)
			setPrevValue()
			send()
		}
	}

	TextField {
		id: field

		text: fixedString(defaultValue)
		placeholderText: hint

		implicitHeight: 40
		implicitWidth: 100
		z: 1
		selectionColor: "#0087d8"
		selectByMouse: true
		font.pointSize: fontPointSize
		font.weight: Font.Normal
		font.family: fontFamily
		inputMethodHints: Qt.ImhDigitsOnly
		horizontalAlignment: activeFocus ? TextInput.AlignLeft : TextInput.AlignHCenter
		hoverEnabled: true

		validator: DoubleValidator {
			top: validTop
			bottom: validBottom
			notation: DoubleValidator.StandardNotation
		}

		Component.onCompleted: {
			setPrevValue()
		}

		onHoveredChanged: {
			handlerHovered = hovered
		}

		background: Rectangle {
			anchors.fill: field
			color: field.hovered ? colorHovered : colorIdle
			antialiasing: true

			Behavior on color {
				ColorAnimation { duration: 90 }
			}
		}  // TextField.background

		MouseArea {
			id: mousearea

			property real prevX
			property bool moved: false

			anchors.fill: field
			cursorShape: Qt.SizeHorCursor
			hoverEnabled: false
			z: 2

			onPositionChanged: {
				cursor.restorePos()
				moved = true

				addToCurrentValue((mouseX - prevX) * stepDrag)
				send()
			}

			onPressed: {
				prevX = mouseX
				cursor.recordPos()
				cursor.shapeBlank()  // --- hiding the cursor

				handlerPressed = true
			}

			onReleased: {
				cursor.shapeRestore()  // --- revealing the cursor

				handlerPressed = false
				if (moved) {
					moved = false
					setPrevValue()
				} else if (!moved) {
					field.forceActiveFocus(Qt.MouseFocusReason)
				}
			}
		}

		onFocusChanged: {
			if (!focus) {
				mousearea.enabled = true
				mousearea.cursorShape = Qt.SizeHorCursor

				if (!field.acceptableInput) {
					field.text = prevValue
				} else {
					field.text = fixedString(currentValue)
					send()
				}
			} else {
				mousearea.enabled = false
				mousearea.cursorShape = Qt.IBeamCursor
				field.selectAll()
			}
		}

		Keys.onPressed: {
			switch (event.key)
			{
			    case Qt.Key_Escape:
				{
					field.text = prevValue
					focus = false
					break
				}
				case Qt.Key_Return:
				{
					if (field.acceptableInput) {
						field.text = fixedString(currentValue)
						setPrevValue()
					} else {
						field.text = currentValue > validTop ?
									 fixedString(validTop) : fixedString(validBottom)
						setPrevValue()
					}
					focus = false
					break
				}
			}
		}
	}  // TextField

	Button {
		id: up
		text: handlerHovered ? "\u002b" : ""
		font.pointSize: fontPointSize
		font.weight: Font.Normal
		font.family: fontFamily
		height: field.height
		width: field.height + btnRadius
		hoverEnabled: true

		contentItem: Text {
			text: up.text
			font: up.font
			opacity: enabled ? 1.0 : 0.3
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			leftPadding: btnRadius
			rightPadding: 0.0
		}

		background: Rectangle {
			anchors.fill: up
			color: up.hovered ? colorHovered : colorIdle
			radius: btnRadius
			antialiasing: true

			Behavior on color {
				ColorAnimation { duration: 90 }
			}
		}

		onHoveredChanged: {
			handlerHovered = hovered
		}

		onPressed: {
			handlerPressed = true
		}

		onReleased: {
			handlerPressed = false
		}

		onClicked: {
			addToCurrentValue(stepClick)
			setPrevValue()
			send()
		}
	}
}

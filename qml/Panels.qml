import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Item {
	id: panels

	property real defaultWidth: 80
	property real btnSize: defaultWidth * 0.8
	property int activeIndex: -1
	property int count: panelList.children.length
	property bool isActive: (activeIndex != -1)
	property bool beginning: engine.isAtTheStart
	property bool managerExpanded: manager.expanded

	state: managerExpanded ? "simulationPanel" : "buttonList"

	function buttonHandler (index) {
		if (index === activeIndex)
			activeIndex = -1
		else
			activeIndex = index
	}

	function collapseAll () {
		for (var i = 0; i < count; i++) {
			panelList.children[i].expand = false;
		}
	}

	onActiveIndexChanged: {
		collapseAll()
		if (activeIndex != -1) {
			panelList.children[activeIndex].expand = true
		}
	}

	width: managerExpanded ? 300 : defaultWidth
	height: parent.height * 0.9

	anchors {
		verticalCenter: parent.verticalCenter
		right: parent.right
		rightMargin: 24
	}

	Behavior on width {
		NumberAnimation { duration: 120 }
	}

	ColumnLayout {
		id: mainPanel

		anchors.fill: parent
		spacing: 30

		Item {
			id: upperPanelLoader

			Layout.alignment: Qt.AlignHCenter
			Layout.fillWidth:  true
			Layout.fillHeight: true

			PanelButtonList {
				visible: beginning && (panels.state === "buttonList")
				anchors.fill: upperPanelLoader

				onCurrentButtonChanged: {
					buttonHandler(currentButton)
					adjustButtonStyle()
				}

				onVisibleChanged: {
					currentButton = -1
				}
			}

			SimulationPanel {
				visible: beginning && (panels.state === "simulationPanel")
				anchors.fill: upperPanelLoader
			}
		}

		SimulationButtons {
			id: manager
			Layout.alignment: Qt.AlignHCenter
			Layout.fillWidth: true

			buttonSize: panels.defaultWidth

			onExpandedChanged: {
				collapseAll()
			}
		}
	}


	Item {
		id: panelList

		property real marginToButtons: 12

		anchors.fill: parent

		LiquidPropPanel {
			anchors {
				right: parent.left
				rightMargin: parent.marginToButtons
				verticalCenter: parent.verticalCenter
			}
		}

		ObjectListPanel {
			anchors {
				right: parent.left
				rightMargin: parent.marginToButtons
				verticalCenter: parent.verticalCenter
			}
		}

		ObjectPropPanel {
			anchors {
				right: parent.left
				rightMargin: parent.marginToButtons
				verticalCenter: parent.verticalCenter
			}
		}
	}

	states: [
		State {
			name: "buttonList"
		},
		State {
			name: "simulationPanel"
		}

	]
}

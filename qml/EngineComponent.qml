import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Buoyancy.OpenGL 1.0

PhysicsEngine {
	id: engine

	onShouldUpdateChanged: {
	}

	onObjectDensityChanged: {
		this.shouldUpdate = false
		this.restart()
	}

	onObjectDimensionChanged: {
		this.shouldUpdate = false
		this.rebuildObject = true
		this.restart()
		this.updateAttrs()
	}

	onObjectPositionChanged: {
		this.shouldUpdate = false
		this.restart()
	}

	onObjectQuaternionChanged: {
		this.shouldUpdate = false
		this.restart()
		this.updateAttrs()
	}
}

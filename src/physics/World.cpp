#include "physics/World.h"


float Physics::G = 9.8f;
int Physics::time = 16;  // milliseconds

glm::mat4 Matrix::I {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f,
};

glm::vec3 Water::velocity { 0.0f, 0.0f, 0.0f };
float Water::density = 1000.0f;
float Water::linearDrag = 5.0f;
float Water::angularDrag = 0.5f;

glm::vec3 Water::Plane::normal { 0.0f, 1.0f, 0.0f };
float Water::Plane::offset = 0.0f;

std::vector<float> Water::Model::vertices {
	-200.0f, 0.0f,  200.0f, 0.0f, 1.0f, 0.0f, // top
	 200.0f, 0.0f, -200.0f, 0.0f, 1.0f, 0.0f,
	-200.0f, 0.0f, -200.0f, 0.0f, 1.0f, 0.0f,
	 200.0f, 0.0f, -200.0f, 0.0f, 1.0f, 0.0f,
	-200.0f, 0.0f,  200.0f, 0.0f, 1.0f, 0.0f,
	 200.0f, 0.0f,  200.0f, 0.0f, 1.0f, 0.0f,

	-200.0f, -200.0f,  200.0f, 0.0f, 1.0f, 0.0f, // bottom
	 200.0f, -200.0f, -200.0f, 0.0f, 1.0f, 0.0f,
	-200.0f, -200.0f, -200.0f, 0.0f, 1.0f, 0.0f,
	-200.0f, -200.0f,  200.0f, 0.0f, 1.0f, 0.0f,
	 200.0f, -200.0f,  200.0f, 0.0f, 1.0f, 0.0f,
	 200.0f, -200.0f, -200.0f, 0.0f, 1.0f, 0.0f,

	-200.0f, -200.0f, -200.0f, -1.0f, 0.0f, 0.0f, // left
	-200.0f,   0.0f,  200.0f, -1.0f, 0.0f, 0.0f,
	-200.0f,   0.0f, -200.0f, -1.0f, 0.0f, 0.0f,
	-200.0f, -200.0f, -200.0f, -1.0f, 0.0f, 0.0f,
	-200.0f, -200.0f,  200.0f, -1.0f, 0.0f, 0.0f,
	-200.0f,   0.0f,  200.0f, -1.0f, 0.0f, 0.0f,

	200.0f, -200.0f, -200.0f, 1.0f, 0.0f, 0.0f, // right
	200.0f,   0.0f, -200.0f, 1.0f, 0.0f, 0.0f,
	200.0f,   0.0f,  200.0f, 1.0f, 0.0f, 0.0f,
	200.0f, -200.0f, -200.0f, 1.0f, 0.0f, 0.0f,
	200.0f,   0.0f,  200.0f, 1.0f, 0.0f, 0.0f,
	200.0f, -200.0f,  200.0f, 1.0f, 0.0f, 0.0f,

	-200.0f, -200.0f, 200.0f, 0.0f, 0.0f, 1.0f, // front
	200.0f,   0.0f,  200.0f, 0.0f, 0.0f, 1.0f,
	-200.0f,  0.0f,  200.0f, 0.0f, 0.0f, 1.0f,
	-200.0f, -200.0f, 200.0f, 0.0f, 0.0f, 1.0f,
	200.0f, -200.0f, 200.0f,  0.0f, 0.0f, 1.0f,
	200.0f,   0.0f,  200.0f, 0.0f, 0.0f, 1.0f,

	200.0f,   0.0f,  200.0f, 0.0f, 0.0f, -1.0f, // back
	-200.0f, -200.0f, 200.0f, 0.0f, 0.0f, -1.0f,
	-200.0f,  0.0f,  200.0f, 0.0f, 0.0f, -1.0f,
	200.0f, -200.0f, 200.0f,  0.0f, 0.0f, -1.0f,
	-200.0f, -200.0f, 200.0f, 0.0f, 0.0f, -1.0f,
	200.0f,   0.0f,  200.0f, 0.0f, 0.0f, -1.0f,
};

std::vector<unsigned int> Water::Model::attrs { 3, 3 };

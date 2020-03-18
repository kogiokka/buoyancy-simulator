#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace Physics
{
    extern float G;  // gravity
	extern int time;

}  // Physics

namespace Matrix
{
    extern glm::mat4 I;
}  // Matrix

namespace Water
{
    extern glm::vec3 velocity;
	extern float density;
	extern float linearDrag;
	extern float angularDrag;

	namespace Model
	{
		extern std::vector<float> vertices;
		extern std::vector<unsigned int> attrs;
	}  // Water::Model

	namespace Plane
	{
	    extern glm::vec3 normal;
		extern float offset;
	};  // Water::Plane

};  // Water

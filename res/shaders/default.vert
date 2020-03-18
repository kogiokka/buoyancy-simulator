#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform vec4 aColor;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectMat;

out vec4 vNormal;
out vec4 vColor;
out vec4 fragPos;

void main()
{
	vColor = aColor;

	fragPos = modelMat * vec4(aPos, 1.0f);
	vNormal = normalize(modelMat * vec4(aNormal, 0.0f));
	gl_Position = projectMat * viewMat * modelMat * vec4(aPos, 1.0f);
}

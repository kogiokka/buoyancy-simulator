#version 430 core

in vec4 vColor;
in vec4 vNormal;
in vec4 fragPos;

out vec4 finalColor;

uniform struct Light {
	vec4 position;
	vec4 intensity;
	float attenuation;
	float ambientCoef;
} light;


void main()
{
	vec4 toLight = normalize(light.position - fragPos);
	float diffuseCoef = max(dot(vNormal, toLight), 0.0f);
	vec3 diffusion = diffuseCoef * light.intensity.rgb * vColor.rgb;

	vec3 ambient = light.ambientCoef * light.intensity.rgb * vColor.rgb;
	finalColor = vec4(diffusion + ambient, vColor.a);
}

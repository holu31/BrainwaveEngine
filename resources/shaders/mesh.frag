#version 460

#define MAX_LIGHTS 1280

in vec3 fPos;
in vec2 fUv;
in vec3 fNormal;
in vec3 fFragPos;

struct DirectionalLight {
	vec3 viewPos;
	float ambientStrength;
	float specularStrength;
	vec3 color;
	vec3 pos;
};

uniform mat4 projMat, viewMat, transMat;
uniform sampler2D textureSampler;
uniform vec3 color;
uniform int dir_lights_count;
uniform DirectionalLight dir_lights[MAX_LIGHTS];

out vec4 fragmentColor;

void main() {
	vec3 result = vec3(0,0,0);
	for(int i = 0; i < dir_lights_count; i++){
		vec3 ambient = dir_lights[i].ambientStrength * dir_lights[i].color;

		vec3 norm = normalize(fNormal);
		vec3 lightDir = normalize(dir_lights[i].pos - fFragPos);  

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * dir_lights[i].color;

		vec3 viewDir = normalize(dir_lights[i].viewPos - fFragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = dir_lights[i].specularStrength * spec * dir_lights[i].color;  

		result += (ambient + diffuse + specular) * color;
	}

	fragmentColor = textureSize(textureSampler, 0) == ivec2(1, 1) ? vec4(result, 1.0) : vec4(result, 1.0) + texture(textureSampler, fUv);
}

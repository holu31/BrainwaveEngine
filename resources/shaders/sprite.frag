#version 460

#define MAX_LIGHTS 1280

in vec3 fPos;
in vec2 fUv;
in vec3 fNormal;

uniform mat4 projMat, viewMat, transMat;
uniform sampler2D textureSampler;
uniform vec3 color;

out vec4 fragmentColor;

void main() {
	fragmentColor = textureSize(textureSampler, 0) == ivec2(1, 1) ? vec4(color, 1.0) : texture(textureSampler, fUv);
}

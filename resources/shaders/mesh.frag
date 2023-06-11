#version 430

in vec3 fPos;
in vec4 fCol;
in vec2 fUv;

uniform mat4 projMat, viewMat, transMat;
uniform sampler2D textureSampler;

out vec4 fragmentColor;

void main() {
	fragmentColor = textureSize(textureSampler, 0) == ivec2(1, 1) ? fCol : texture(textureSampler, fUv);
}

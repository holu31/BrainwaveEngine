#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec4 vCol;
layout (location = 2) in vec2 vUv;

uniform mat4 projMat, viewMat, transMat;

out vec3 fPos;
out vec4 fCol;
out vec2 fUv;

void main() {
    gl_Position = projMat * viewMat * transMat * vec4(vPos, 1.0f);
//	gl_Position = vec4(vPos, 1.0f);
	
	fPos = vPos;
	fCol = vCol;
	fUv = vUv;
}

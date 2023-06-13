#version 460

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUv;
layout (location = 2) in vec3 vNormal;

uniform mat4 projMat, viewMat, transMat;

out vec3 fPos;
out vec2 fUv;
out vec3 fNormal;
out vec3 fFragPos;

void main() {
    gl_Position = projMat * viewMat * transMat * vec4(vPos, 1.0f);
	
	fPos = vPos;
	fUv = vUv;
	fNormal = mat3(transpose(inverse(transMat))) * vNormal;  
	fFragPos = vec3(transMat * vec4(vPos, 1.0));
}

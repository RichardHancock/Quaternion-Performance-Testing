#version 430 core
						
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormalIn;
layout(location = 2) in vec2 vTexture;

uniform mat4 modelMat;
uniform mat4 invModelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform vec4 worldSpaceLightPos = {1,0.8,1,1};

out vec2 vTexCoord;
out vec3 vNormalV;
out vec3 lightDirV;

void main()
{
	gl_Position = projMat * viewMat * modelMat * vPosition;

	vec4 eyeSpaceVertPos = viewMat * modelMat * vPosition;
	vec4 eyeSpaceLightPos = viewMat * worldSpaceLightPos;
	
	lightDirV =  normalize( vec3(eyeSpaceLightPos) - vec3(eyeSpaceVertPos) );
	
	vNormalV = mat3(viewMat * modelMat) * vNormalIn;
	
	vTexCoord = vTexture;
}
#version 430 core

in vec2 vTexCoord;

uniform sampler2D gSampler;
uniform lowp float textureFlag;
uniform vec4 colour;

out vec4 fragColour;

void main()
{
	fragColour = texture2D(gSampler, vTexCoord);
	
	//fragColour = (textureFlag * texture2D(gSampler, vTexCoord)) + ((1.0 - textureFlag) * colour);
}
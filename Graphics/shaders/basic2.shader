#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexTexCoord;

out vec2 texCoord;
uniform mat4 rotationMat;

void main(){
   texCoord = vertexTexCoord;
	gl_Position = rotationMat * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform sampler2D planetTexture;
in vec2 texCoord;
void main(){
    vec4 texCol = texture(planetTexture, texCoord);
    color = texCol;
};

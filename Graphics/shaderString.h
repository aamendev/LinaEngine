std::string stringShaderVert =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec4 position;\n"
"layout(location = 1) in vec2 vertexTexCoord;\n"
"\n"
"out vec2 texCoord;\n"
"uniform mat4 rotationMat;\n"
"\n"
"void main(){\n"
"   texCoord = vertexTexCoord;\n"
"	gl_Position = rotationMat * position;\n"
"};\n";

std::string stringShaderFrag=
"#version 330 core\n"
"\n"
"layout(location = 0) out vec4 color;\n"
"uniform sampler2D planetTexture;\n"
"in vec2 texCoord;\n"
"void main(){\n"
"    vec4 texCol = texture(planetTexture, texCoord);\n"
"    color = texCol;\n"
"};\n";

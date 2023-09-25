#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../glad.h"
#include "../shaders.h"
#include "../../main/LinaMath.h"
namespace Lina{	namespace Graphics{
	Shader::Shader(const std::string& filepath): mFilepath(filepath), mRenderId(0){
		shaderProgramSource source = parseShader(filepath);
		mRenderId = createShader(source.vertexSource, source.fragmentSource);
	}
	Shader::~Shader(){
		glDeleteProgram(mRenderId);
	}

	shaderProgramSource Shader::parseShader(const std::string& filepath){
		std::ifstream stream(filepath);

		enum class shaderType{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		shaderType type = shaderType::NONE;
		while (getline(stream, line)){
			if(line.find("#shader") != std::string::npos){
				if(line.find("vertex") != std::string::npos){
					type = shaderType::VERTEX;
				}else if (line.find("fragment") != std::string::npos){
					type = shaderType::FRAGMENT;
				}
			}else{
				ss[(int)type] << line <<'\n';
			}
		}
		return {ss[0].str(), ss[1].str()};
	}

	unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader){
		unsigned int program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	unsigned int Shader::compileShader(unsigned int type, const std::string& source){
		unsigned int id = glCreateShader(type);
		const char *src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		int compilationResult;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);
		if (!compilationResult){
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char * message = (char *)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout<<"Failed to compile the shader\n"<<message<<'\n';
			glDeleteShader(id);
			return 0;
		}
		return id;
	}
	void Shader::bind() const{
		glUseProgram(mRenderId);
	}
	void Shader::unbind() const{
		glUseProgram(0);
	}
	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
		glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	}
	void Shader::setUniform1i(const std::string& name, int texUnit){
		glUniform1i(getUniformLocation(name), texUnit);
	}
	int Shader::getUniformLocation(const std::string& name){
		return glGetUniformLocation(mRenderId, name.c_str());
	}
    void Shader::setUniformMat4(const std::string& name, Math::Matrix4D& program){
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &program[0].x);
    }
    void Shader::setUniformMat3(const std::string& name, Math::Matrix3D& program){
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &program[0].x);
    }
    void Shader::setUniformVec3(const std::string& name, Math::Vector3D& program){
        glUniform3f(getUniformLocation(name), program.x, program.y, program.z);
    }
    void Shader::setUniformVec4(const std::string& name, Math::Vector4D& program){
        glUniform4f(getUniformLocation(name), program.x, program.y, program.z, program.w);
    }

}}

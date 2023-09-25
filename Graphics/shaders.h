#pragma once
#include <string>
#include <iostream>
#include "../main/LinaMath.h"
namespace Lina{namespace Graphics{
	struct shaderProgramSource{
		std::string vertexSource;
		std::string fragmentSource;
	};
	class Shader{
	private:
		std::string mFilepath;
		unsigned int mRenderId;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void bind() const;
		void unbind() const;

		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniform1i(const std::string& name, int textUnit);
        void setUniformVec4(const std::string& name, Math::Vector4D& program);
        void setUniformVec3(const std::string& name, Math::Vector3D& program);

        void setUniformMat4(const std::string& name, Math::Matrix4D& program);
        void setUniformMat3(const std::string& name, Math::Matrix3D& program);
	private:
		shaderProgramSource parseShader(const std::string& filepath);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int compileShader(unsigned int type, const std::string& source);
		int getUniformLocation(const std::string& name);
	};
}}

#pragma once

#include <GL/glew.h>

#include <string>

namespace GTEngine {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentSaderFilePath);
		void linkShaders();
		void compileShader(const std::string &filePath, GLuint id);
		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		int m_numAttributes{ 0 };
		GLuint m_programID{ 0 };
		GLuint m_vertexShaderID{ 0 };
		GLuint m_fragmentShaderID{ 0 };

	};

}


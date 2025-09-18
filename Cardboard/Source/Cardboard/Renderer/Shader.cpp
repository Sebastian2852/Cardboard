#include "Shader.hpp"

#include <vector>
#include "../Logger.hpp"
#include "glad/glad.h"

namespace Cardboard
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		CARDBOARD_TRACE("Compiling shaders");

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);

			CARDBOARD_ERROR("Vertex shader compilation FAILED");
			CARDBOARD_ERROR("{0}", infoLog.data());

			return;
		}

		CARDBOARD_TRACE("Compiled vertex shader");

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			CARDBOARD_ERROR("Fragment shader compilation FAILED");
			CARDBOARD_ERROR("{0}", infoLog.data());

			return;
		}

		CARDBOARD_TRACE("Compiled fragment shader");

		CARDBOARD_TRACE("Linking shaders");
		m_RendererId = glCreateProgram();
		glAttachShader(m_RendererId, vertexShader);
		glAttachShader(m_RendererId, fragmentShader);
		glLinkProgram(m_RendererId);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(m_RendererId);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CARDBOARD_ERROR("FAILED to link shader program");
			CARDBOARD_ERROR("{0}", infoLog.data());

			return;
		}

		glDetachShader(m_RendererId, vertexShader);
		glDetachShader(m_RendererId, fragmentShader);
		CARDBOARD_TRACE("Detached shaders");

		CARDBOARD_INFO("Shaders compiled and link successfully");
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererId);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererId);
	}
}
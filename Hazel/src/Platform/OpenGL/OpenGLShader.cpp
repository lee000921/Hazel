#include "hzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Hazel {
	
	std::string ReadSourceCodeFromFile(const std::string& path) {
		std::string code;
		std::ifstream file;
		// 保证ifstream对象可以抛出异常：
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			file.open(path);
			std::stringstream stream;
			// 读取文件的缓冲内容到数据流中
			stream << file.rdbuf();
			// 关闭文件处理器
			file.close();
			// 转换数据流到string
			code = stream.str();
		}
		catch (std::ifstream::failure e) {
			HZ_CORE_ERROR("file {0} not successfully read", path);
		}
		return code;
	}

	unsigned int CompileShader(const std::string& srcCode, unsigned int type) {
		unsigned int shader = glCreateShader(type);

		const char* source = srcCode.c_str();
		glShaderSource(shader, 1, &source, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			// We don't need the shader anymore.
			glDeleteShader(shader);
			HZ_CORE_ERROR("{0}", infoLog.data());
			std::string errMessage = (type == GL_VERTEX_SHADER) ? "Vertex shader compilation failure!"
																: "Fragment shader compilation failure!";
			HZ_CORE_ASSERT(false, errMessage);
			return 0;
		}
		return shader;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath) {

		std::string vertexSrc = ReadSourceCodeFromFile(vertexPath);
		std::string fragmentSrc = ReadSourceCodeFromFile(fragmentPath);

		// Create an empty vertex shader handle
		GLuint vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
		GLuint fragmentShader = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
			
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
#include "evpch.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Render/Renderer.h"
#include "OpenGLShader.h"

namespace Envii
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		m_Id = CreateShaderProgram(ParseShaders(filepath));
        
        // Create name by extracting filename wihout extension
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
	}

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
        : m_Name(name)
    {
        m_Id = CreateShaderProgram(vertSrc, fragSrc);
    }

	OpenGLShader::~OpenGLShader()
	{
	}

    void OpenGLShader::Bind() const
    {
        GlApiCall(glUseProgram(m_Id));
    }

    void OpenGLShader::Unbind() const
    {
        GlApiCall(glUseProgram(0));
    }

    GLuint OpenGLShader::CreateShaderProgram(const std::unordered_map<ShaderType, std::string> sourceMap)
    {
        EV_CORE_ASSERT(sourceMap.size() > 0, "Empty shader sources from parser.");
        GlApiCall(GLuint program = glCreateProgram());
        std::vector<GLuint> shaderHandles;
        for (const auto& mapEntry : sourceMap)
        {
            shaderHandles.push_back(
                CompileShader(shaderTypeMap[mapEntry.first], mapEntry.second)
            );
            GlApiCall(glAttachShader(program, shaderHandles.back()));
        }

        GlApiCall(glLinkProgram(program));

        GLint isLinked = 0;
        GlApiCall(glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked));
        if (isLinked == GL_FALSE)
        {
            GLint msgLen;
            GlApiCall(glGetShaderiv(program, GL_INFO_LOG_LENGTH, &msgLen));
            char* msg = (char*)_malloca(msgLen * sizeof(char));
            GlApiCall(glGetShaderInfoLog(program, msgLen, &msgLen, msg));

            // We don't need the program anymore.
            glDeleteProgram(program);

            for (auto id : shaderHandles)
                glDeleteShader(id);

            EV_CORE_ERROR("{0}", msg);
            EV_CORE_ASSERT(false, "Shader link failure!");
            return 0;
        }

        GlApiCall(glValidateProgram(program));

        for (GLuint handle : shaderHandles)
        {
            GlApiCall(glDeleteShader(handle));
            GlApiCall(glDetachShader(program, handle));
        }

        return program;
    }

    GLuint OpenGLShader::CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc)
    {
        GlApiCall(GLuint program = glCreateProgram());
        GLuint vertId = CompileShader(GL_VERTEX_SHADER, vertSrc);
        GLuint fragId = CompileShader(GL_FRAGMENT_SHADER, fragSrc);
        GlApiCall(glAttachShader(program, vertId));
        GlApiCall(glAttachShader(program, fragId));
        GlApiCall(glLinkProgram(program));
        GlApiCall(glValidateProgram(program));

        GlApiCall(glDeleteShader(vertId));
        GlApiCall(glDeleteShader(fragId));

        GlApiCall(glDetachShader(program, vertId));
        GlApiCall(glDetachShader(program, fragId));

        return program;
    }

    // This function handles a combination of shaders in a single file
    std::unordered_map<ShaderType, std::string> OpenGLShader::ParseShaders(const std::string& srcPath)
    {
        std::ifstream instr(srcPath, std::ios::in | std::ios::binary);
        EV_CORE_ASSERT(instr, "Cannot open file input stream.");
        std::stringstream sources[(int)ShaderType::NUM_TYPES];
        std::unordered_map<ShaderType, std::string> retMap;
        ShaderType type(ShaderType::NONE);

        std::string line;
        while (getline(instr, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::GEOMETRY;
            }
            else
            {
                sources[(int)type] << line << std::endl;
            }
        }

        for (int i = 0; i < (int)ShaderType::NUM_TYPES; i++)
            if (!sources[i].str().empty())
                retMap[(ShaderType)i] = sources[i].str();

        return retMap;
    }

    GLuint OpenGLShader::CompileShader(GLenum shaderType, const std::string& src)
    {
        GlApiCall(GLuint shaderId = glCreateShader(shaderType));
        const char* source = src.c_str();
        GlApiCall(glShaderSource(shaderId, 1, &source, nullptr));
        GlApiCall(glCompileShader(shaderId));

        GLint status;
        GlApiCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLint msgLen;
            GlApiCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLen));
            char* msg = (char*)_malloca(msgLen * sizeof(char));
            GlApiCall(glGetShaderInfoLog(shaderId, msgLen, &msgLen, msg));
            //std::string typeStr = shaderTypeStringMap[shaderType];// (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
            EV_CORE_ERROR("{0} Shader compilation failed: {1}", shaderTypeStringMap[shaderType], msg);
            GlApiCall(glDeleteShader(shaderId));

            return 0;
        }

        return shaderId;
    }

    void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    void OpenGLShader::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform4f(loc, f1, f2, f3, f4));
    }

    void OpenGLShader::SetUniform3f(const std::string& name, float f1, float f2, float f3)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform3f(loc, f1, f2, f3));
    }

    void OpenGLShader::SetUniform2f(const std::string& name, float f1, float f2)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform2f(loc, f1, f2));
    }

    void OpenGLShader::SetUniform1f(const std::string& name, float f1)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform1f(loc, f1));
    }

    void OpenGLShader::SetUniform1i(const std::string& name, unsigned int val)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform1i(loc, val));
    }

    void OpenGLShader::SetUniform1iv(const std::string& name, unsigned int size, int* vals)
    {
        GLint loc = GetUniformLocation(name);
        GlApiCall(glUniform1iv(loc, size, vals));
    }

    const int OpenGLShader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocCache.find(name) != m_UniformLocCache.end())
            return m_UniformLocCache[name];

        GlApiCall(GLint loc = glGetUniformLocation(m_Id, name.c_str()));
        // Uniform may exist in shader, but not have a location due to being unused
        if (loc == -1)
            std::cout << "Warning: Uniform '" << name << "' has no location." << std::endl;

        m_UniformLocCache[name] = loc;
        return loc;
    }
}

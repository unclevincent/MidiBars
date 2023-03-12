#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"



Shader::Shader(std::string const& filepath) :
	  _filepath(filepath)
    , _rendererID(0)
{
    ShaderProgramSource shaderProgramSource = parseShader(filepath);
    _rendererID = createShader(shaderProgramSource.vertexSource, shaderProgramSource.fragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(_rendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(std::string const& name, float v0, float v1, float v2, float v3)
{
    
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

Shader::ShaderProgramSource Shader::parseShader(std::string const& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)shaderType] << line << "\n";
        }
    }
    return ShaderProgramSource{ ss[0].str(), ss[1].str() };
}


unsigned int Shader::compileShader(unsigned int type, std::string const& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


unsigned int Shader::createShader(std::string const& vertexShader, std::string const& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::getUniformLocation(std::string const& name)
{
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
        return _uniformLocationCache[name];
    }
    GLCall(unsigned int location = glGetUniformLocation(_rendererID, "u_Color"));
    if (location == -1) {
        std::cout << "Warning: uniform " << name << " does not exist " << std::endl;
    }
    _uniformLocationCache[name] = location;
    return location;
}

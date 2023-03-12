#pragma once
#include <string>
#include <unordered_map>

class Shader {
public:

	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	Shader(std::string const& filename);
	~Shader();

	void bind() const;
	void unbind() const;

	// set uniforms
	void setUniform4f(std::string const& name, float v0, float v1, float v2, float v3);
	
private:
	unsigned int _rendererID;
	std::string _filepath;
	std::unordered_map<std::string, unsigned int> _uniformLocationCache;
	ShaderProgramSource parseShader(std::string const& filepath);
	unsigned int compileShader(unsigned int type, std::string const& source);
	unsigned int createShader(std::string const& vertexShader, std::string const& fragmentShader);
	unsigned int getUniformLocation(std::string const& name);
	bool compileShader();
	// caching for uniforms
};
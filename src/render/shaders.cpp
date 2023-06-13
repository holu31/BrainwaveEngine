#include <render/shaders.hpp>

#include <core/engine.hpp>

#include <fstream>
#include <stdexcept>
#include <iostream>

Render::Shaders::Shaders(const std::string &vertFilepath,
    const std::string &fragFilepath)
{
    vertCode = this->readFile(vertFilepath);
    fragCode = this->readFile(fragFilepath);

    LOG(setSource(vShader, vertCode.data()), "INFO", "loading shader vertex code");
    LOG(setSource(fShader, fragCode.data()), "INFO", "loading shader fragment code");
}

std::vector<char> Render::Shaders::readFile(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open()){
        throw LOG(file.is_open(), "ERROR", ("failed to open file: " + filepath).c_str());
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize+1);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    buffer[fileSize] = '\0';
    return buffer;
}

void Render::Shaders::setSource(int id, const char *source){
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

    int success;
    char infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);	
    if (success == GL_FALSE) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        throw LOG( glGetProgramiv(program, GL_LINK_STATUS, &success) , \
            "ERROR", ("failed to compile shader" \
            + std::to_string(id) + " " + infoLog).c_str());
    }
		
	glAttachShader(program, id);
	glLinkProgram(program);
		
    glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw LOG( glGetProgramiv(program, GL_LINK_STATUS, &success) , \
            "ERROR", ("failed to link program " \
            + std::to_string(id) + " " + infoLog).c_str());
    }
		
	glDeleteShader(id);
}

void Render::Shaders::Bind(){
    glUseProgram(program);
}

void Render::Shaders::Unbind(){
    glUseProgram(GL_FALSE);
}

void Render::Shaders::setUniform(
    std::string uniform, glm::mat4 value
) {
    int matrixLocation = glGetUniformLocation(program, uniform.c_str());
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(value));
}

int Render::Shaders::getULoc(std::string uname){
    return glGetUniformLocation(program, uname.c_str());
}

void Render::Shaders::setUInt(std::string uname, int value){
    glUniform1i(getULoc(uname), value);
}
#include <render/shaders.hpp>

#include <fstream>
#include <stdexcept>
#include <iostream>

Render::Shaders::Shaders(const std::string &vertFilepath,
    const std::string &fragFilepath)
{
    vertCode = this->readFile(vertFilepath);
    fragCode = this->readFile(fragFilepath);

    std::cout << "vert size - " << vertCode.size() << \
        "\nfrag size - " << fragCode.size() << std::endl;

    setSource(vShader, vertCode.data());
    setSource(fShader, fragCode.data());
}

std::vector<char> Render::Shaders::readFile(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open()){
        throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
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
		std::cout << "failed to compile shader " << id \
                    << " " << infoLog << std::endl;
    }
		
	glAttachShader(program, id);
	glLinkProgram(program);
		
    glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "failed to link program " << id \
                    << " " << infoLog << std::endl;
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
#include <stdexcept>
#include <render/mesh.hpp>
#include <render/camera.hpp>

Core::Mesh::Mesh(Core::MeshType type,
    Core::Shaders *shader)
{
    if(type == MESH_CUBE){
        this->m_pShader = shader;
        this->positions = {
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,

			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f
        };

        this->indices = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20,
        };

        this->colors = {
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
        };
    }

	this->Init();
}

void Core::Mesh::updateBuffers() {
	glBindVertexArray(vao);

	setArrayBuffer(0, 3, m_posBuffer, positions);
	setElementArrayBuffer(m_indexBuffer, indices);
	setArrayBuffer(1, 4, m_colBuffer, colors);
	//setArrayBuffer(2, 2, uvBuffer, uv);

	glBindVertexArray(GL_FALSE);
}

void Core::Mesh::setArrayBuffer(
	int pos, int size, unsigned int id, std::vector<float> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, size, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, GL_FALSE);
}

void Core::Mesh::setElementArrayBuffer(
	unsigned int id, std::vector<int> data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
}


void Core::Mesh::Init(){
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &m_posBuffer);
	glGenBuffers(1, &m_indexBuffer);
	glGenBuffers(1, &m_colBuffer);

	this->updateBuffers();
}

void Core::Mesh::draw(){
	m_pShader->Bind();
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	if(Core::Camera::current != nullptr){

		m_pShader->setUniform("projMat", Core::Camera::current->projMatGet());
		m_pShader->setUniform("viewMat", Core::Camera::current->viewMatGet());
	}

	transMat = glm::mat4(1.0f);

	transMat = glm::translate(transMat, pos);
	
	transMat = glm::rotate(transMat, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transMat = glm::scale(transMat, scale);

	m_pShader->setUniform("transMat", transMat);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

	m_pShader->Unbind();

	glBindVertexArray(GL_FALSE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
}

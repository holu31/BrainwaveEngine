#include <stdexcept>
#include <render/sprite2d.hpp>
#include <render/camera.hpp>

#include <core/engine.hpp>

#include <vector>

Render::Sprite2D::Sprite2D(Render::Shaders *shader,
	Render::Texture *texture)
{
    this->m_pShader = shader;
	this->m_pTexture = texture;

    this->positions = {
		-50.0f, -50.0f, 0.0f,
		-50.0f, 50.0f, 0.0f,
		50.0f, 50.0f, 0.0f,
		50.0f, -50.0f, 0.0f,
    };
	
    this->indices = {
		0, 1, 2,
		2, 3, 0,
    };
	
	this->normals = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
    };
	
	this->uv = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
    };

	LOG(glGenVertexArrays(1, &vao), "INFO", "generating vertex arrays");
	LOG(glGenBuffers(1, &m_posBuffer), "INFO", "generating positions buffers");
	LOG(glGenBuffers(1, &m_indexBuffer), "INFO", "generating indices buffers");
	LOG(glGenBuffers(1, &m_uvBuffer), "INFO", "generating uv buffers");
	LOG(glGenBuffers(1, &m_norBuffer), "INFO", "generating normals buffers");

	m_pShader->Bind();
	LOG(m_pTexture->import(), "INFO", "rebinding shaders, import texture");
	m_pShader->Unbind();

	LOG(this->updateBuffers(), "INFO", "updating buffers");
}

void Render::Sprite2D::updateBuffers() {
	glBindVertexArray(vao);

	setArrayBuffer(0, 3, m_posBuffer, positions);
	setElementArrayBuffer(m_indexBuffer, indices);
	setArrayBuffer(1, 2, m_uvBuffer, uv);
	setArrayBuffer(2, 3, m_norBuffer, normals);

	glBindVertexArray(GL_FALSE);
}

void Render::Sprite2D::setArrayBuffer(
	int pos, int size, unsigned int id, std::vector<float> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, size, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, GL_FALSE);
}

void Render::Sprite2D::setElementArrayBuffer(
	unsigned int id, std::vector<int> data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
}

void Render::Sprite2D::draw(){
	m_pShader->Bind();
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	if(m_pTexture != nullptr) m_pTexture->bind();

	if(Render::Camera::current != nullptr){

		m_pShader->setUniform("projMat", Render::Camera::current->projMatGet());
		m_pShader->setUniform("viewMat", Render::Camera::current->viewMatGet());
	}
	
	glUniform3f(m_pShader->getULoc("color"), 0, 0, 0);

	transMat = glm::mat4(1.0f);

	transMat = glm::translate(transMat, glm::vec3(this->pos, 0));
	
	transMat = glm::rotate(transMat, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));

	transMat = glm::scale(transMat, glm::vec3(this->scale, 1.0f));

	m_pShader->setUniform("transMat", transMat);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

	if(m_pTexture != nullptr) m_pShader->Unbind();

	glBindVertexArray(GL_FALSE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
	m_pTexture->unbind();
}

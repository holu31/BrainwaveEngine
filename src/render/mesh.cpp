#include <stdexcept>
#include <render/mesh.hpp>
#include <render/camera.hpp>
#include <render/light.hpp>

#include <core/engine.hpp>

#include <vector>

Render::Mesh::Mesh(std::vector<float> positions,
    std::vector<int> indices,
    std::vector<float> uv,
	std::vector<float> normals,
    Render::Shaders *shader,
    Render::Texture *texture)
{
	this->m_pShader = shader;
	this->m_pTexture = texture;
	this->positions = positions;
	this->uv = uv;
	this->normals = normals;
    this->indices = indices; 

	LOG(this->Init(), "INFO", "initialize mesh object");
}

Render::Mesh::Mesh(Render::MeshType type,
    Render::Shaders *shader,
	Render::Texture *texture)
{
    if(type == MESH_CUBE){
        this->m_pShader = shader;
		this->m_pTexture = texture;

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
		
		this->normals = {
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,

			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
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

		this->uv = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
		};
    }

	this->Init();
}

void Render::Mesh::updateBuffers() {
	glBindVertexArray(vao);

	setArrayBuffer(0, 3, m_posBuffer, positions);
	setElementArrayBuffer(m_indexBuffer, indices);
	setArrayBuffer(1, 2, m_uvBuffer, uv);
	setArrayBuffer(2, 3, m_norBuffer, normals);

	glBindVertexArray(GL_FALSE);
}

void Render::Mesh::setArrayBuffer(
	int pos, int size, unsigned int id, std::vector<float> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, size, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, GL_FALSE);
}

void Render::Mesh::setElementArrayBuffer(
	unsigned int id, std::vector<int> data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
}


void Render::Mesh::Init(){
	LOG(glGenVertexArrays(1, &vao), "INFO", "generating vertex arrays");
	LOG(glGenBuffers(1, &m_posBuffer), "INFO", "generating positions buffers");
	LOG(glGenBuffers(1, &m_indexBuffer), "INFO", "generating indices buffers");
	LOG(glGenBuffers(1, &m_uvBuffer), "INFO", "generating uv buffers");
	LOG(glGenBuffers(1, &m_norBuffer), "INFO", "generating normals buffers");

	if(m_pTexture != nullptr){
		m_pShader->Bind();
		LOG(m_pTexture->import(), "INFO", "rebinding shaders, import texture");
		m_pShader->Unbind();
	}

	LOG(this->updateBuffers(), "INFO", "updating buffers");
}

void Render::Mesh::draw(){
	m_pShader->Bind();
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	if(m_pTexture != nullptr) m_pTexture->bind();

	if(Render::Camera::current != nullptr){

		m_pShader->setUniform("projMat", Render::Camera::current->projMatGet());
		m_pShader->setUniform("viewMat", Render::Camera::current->viewMatGet());
	}
	if(Render::lights.size() != 0){
		for(int light = 0; light < Render::lights.size(); ++light){
			glUniform3f(m_pShader->getULoc("dir_lights["+std::to_string(light)+"].viewPos"),
																	Render::Camera::current->pos.x,
																	Render::Camera::current->pos.y,
																	Render::Camera::current->pos.z);
			glUniform1f(m_pShader->getULoc("dir_lights["+std::to_string(light)+"].specularStrength"), Render::lights[light]->specularStrength);													
			glUniform1f(m_pShader->getULoc("dir_lights["+std::to_string(light)+"].ambientStrength"), Render::lights[light]->ambientStrength);
			glUniform3f(m_pShader->getULoc("dir_lights["+std::to_string(light)+"].pos"),
															Render::lights[light]->pos.x,
															Render::lights[light]->pos.y,
															Render::lights[light]->pos.z);
			glUniform3f(m_pShader->getULoc("dir_lights["+std::to_string(light)+"].color"),
																Render::lights[light]->lightColor.x,
																Render::lights[light]->lightColor.y,
																Render::lights[light]->lightColor.z);
		}
		glUniform1i(m_pShader->getULoc("dir_lights_count"), Render::lights.size());
	} else {
		glUniform3f(m_pShader->getULoc("dir_lights[0].viewPos"), 0.0f, 0.0f, 0.0f);
		glUniform1f(m_pShader->getULoc("dir_lights[0].specularStrength"), 0.0f);													
		glUniform1f(m_pShader->getULoc("dir_lights[0].ambientStrength"), 1.0f);
		glUniform3f(m_pShader->getULoc("dir_lights[0].pos"), 0.0f, 0.0f, 0.0f);
		glUniform3f(m_pShader->getULoc("dir_lights[0].color"), 1.0f, 1.0f, 1.0f);
		glUniform1i(m_pShader->getULoc("dir_lights_count"), 1);
	}
	glUniform3f(m_pShader->getULoc("color"), color.x, color.y, color.z);

	transMat = glm::mat4(1.0f);

	transMat = glm::translate(transMat, pos);
	
	transMat = glm::rotate(transMat, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transMat = glm::scale(transMat, scale);

	m_pShader->setUniform("transMat", transMat);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

	if(m_pTexture != nullptr) m_pShader->Unbind();

	glBindVertexArray(GL_FALSE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_FALSE);
	m_pTexture->unbind();
}

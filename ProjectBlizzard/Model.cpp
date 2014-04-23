#include "Model.h"

Model::Model(){
	m_scale = 1;
	m_pos.x = m_pos.y = m_pos.z = 0;
	m_collider = new BoxCollider();
}

Model::Model(float scale){
	m_scale = scale;
	m_pos.x = m_pos.y = m_pos.z = 0;
	m_collider = new BoxCollider();
}

Model::~Model(){
	if (&m_VAO){
		glDeleteVertexArrays(1, &m_VAO);
	}

	if (m_buffers){
		glDeleteBuffers(3, m_buffers);
	}

	if (m_collider){
		delete m_collider;
	}
}

Vector Model::getPos(){
	return m_pos;
}

Vector Model::getColor(){
	return m_color;
}

float Model::getScale(){
	return m_scale;
}

float Model::getWidth(){
	return m_width;
}

float Model::getHeight(){
	return m_height;
}

float Model::getLength(){
	return m_length;
}

GLuint Model::getVAO(){
	return m_VAO;
}

GLuint* Model::getBuffer(){
	return m_buffers;
}

Collider* Model::getCollider(){
	return m_collider;
}

void Model::setScale(float scale){
	if (scale <= 0){
		return;
	}

	m_scale = scale;

	m_collider->setDimension(m_width * m_scale, m_height * m_scale, m_length * m_scale);
}

void Model::setDimensions(float width, float height, float length){
	m_width = width;
	m_height = height;
	m_length = length;

	m_collider->setDimension(width * m_scale, height * m_scale, length * m_scale);
}

void Model::setPos(Vector pos){
	m_pos = pos;

	m_collider->setPos(m_pos);
}

void Model::setPos(float x, float y, float z){
	setPos(Vector(x, y, z));
}

void Model::setColor(float r, float g, float b){
	if (r < 0 || r > 1 || b < 0 || b > 1 || g < 0 || g > 1){
		return;
	}

	m_color = Vector(r, g, b);
}

void Model::setVAO(GLuint vao){
	m_VAO = vao;
}

void Model::setBuffer(GLuint* buffers){
	*m_buffers = *buffers;
}

void Model::Render(){
}
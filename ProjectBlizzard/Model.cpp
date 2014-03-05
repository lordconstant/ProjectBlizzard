#include "Model.h"


Model::Model(){
	m_scale = 1;
	m_pos.x = m_pos.y = m_pos.z = 0;
}

Model::Model(float scale){
	m_scale = scale;
	m_pos.x = m_pos.y = m_pos.z = 0;
}

Model::~Model(){
}

Vector Model::getPos(){
	return m_pos;
}

float Model::getScale(){
	return m_scale;
}

void Model::setScale(float scale){
	if (scale <= 0){
		return;
	}

	m_scale = scale;
}

void Model::setPos(Vector pos){
	m_pos = pos;
}

void Model::setPos(float x, float y, float z){
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Model::Render(){
}
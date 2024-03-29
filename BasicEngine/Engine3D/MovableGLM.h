#pragma once
#include "../res/includes/glm/glm.hpp"

class MovableGLM 
{
public:
	MovableGLM();
	glm::mat4 MakeTrans(const glm::mat4 &prevTransformations) const;
	glm::mat4 MakeTrans() const;
	void MyTranslate(glm::vec3 delta, int mode);
	void MyRotate(float angle, const glm::vec3 &vec, int mode);
	void MyLocRot(float angle, const glm::vec3 &vec, int mode);
	void MyScale(glm::vec3 scale);
	void ZeroTrans();

	glm::mat4 getTrans();
	glm::mat4 getRot();
	glm::mat4 getLocalRot();
	glm::mat4 getScale();
private:
	glm::mat4 trans;
	glm::mat4 rot;
	glm::mat4 scl;
	glm::mat4 localRot;
};
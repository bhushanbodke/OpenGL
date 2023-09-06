#pragma once
#include<glm/glm.hpp>
#include<vector>
#include"ShaderClass.h"
#include"VAO.h"

struct Particle
{
public:
	float size = 0; 
	glm::vec4 PColor = glm::vec4{ 1.0 };
	glm::vec3 Position = glm::vec3{ 0,0,0 };
	float LifeTime = 0;
	glm::vec3 velocity = glm::vec3(0);
};

class ParticlesSystem
{
private:
	glm::vec3 Origin = { 0,0,0 };
	int ParticleCount = 0 ;

	std::vector<Particle> Particals;

public:
	ParticlesSystem(int count , float size, glm::vec3 origin, glm::vec4 color);
	void Update(float deltatime);
	void render(Shader& shader,glm::mat4 PV,VAO& vao);

};


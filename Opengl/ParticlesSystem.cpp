#include <glm/gtc/matrix_transform.hpp>
#include "ParticlesSystem.h"

ParticlesSystem::ParticlesSystem(int count ,float Size, glm::vec3 origin, glm::vec4 color)
	:ParticleCount(count),Origin(origin)
{
	Particals.resize(ParticleCount);
	for (int i = 0; i < ParticleCount; i++)
	{
		Particle p;
		p.PColor = color;
		p.size = Size;
		p.Position = origin;
		p.LifeTime = rand() % 1;
		p.velocity.x = rand() % 21 - 10;
		p.velocity.y = rand() % 21 - 10;
		p.velocity.z = rand() % 21 - 10;
		Particals[i] = p;
	}
}

void ParticlesSystem::Update(float deltatime)
{
	for (Particle& p : Particals)
	{
		if (p.LifeTime > 0)
		{
			p.LifeTime -= deltatime;
			p.Position.x = p.Position.x + (p.velocity.x * deltatime);
			p.Position.y = p.Position.y + (p.velocity.y * deltatime);
			p.Position.z = p.Position.z + (p.velocity.z * deltatime);
		}
		else
		{
			p.LifeTime = rand() % 60;
			p.Position.x = Origin.x;
			p.Position.y = Origin.y;
			p.Position.z = Origin.z;
		}
	}
}

void ParticlesSystem::render(Shader& shader, glm::mat4 PV,VAO& vao)
{
	shader.Activate();
	vao.bind();
	for (Particle& p : Particals)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), p.Position);
		model = glm::scale(model, glm::vec3(p.size));
		glm::mat4 MVP = PV * model;
		shader.SetUniformMat4("MVP", MVP);
		shader.SetUniform4f("Color", p.PColor.r , p.PColor.g , p.PColor.b,1.0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

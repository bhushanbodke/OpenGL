#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	glm::vec3 CamPos;
	glm::vec3 CamFront;
	glm::vec3 CamUp;
	float CamSpeed;
	float FOV;
	float CamSensitivity;
	
	float Yaw;
	float Pitch;

	float AspectRatio;
	float FarPlane;
	float NearPlane;

public:

	Camera(glm::vec3 pos, float speed, float aspect_ratio, float fov, float Near , float Far);

	glm::mat4 GetLookAt();
	glm::mat4 GetPerspective();
	void MoveFront(float deltaTime);
	void MoveBack(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);

	void UpdateCameraDir(double dx, double dy);
	void UpdateZoom(double Scroll);
};


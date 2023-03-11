#include "Camera.h"

Camera::Camera(glm::vec3 pos,float speed,float aspect_ratio, float fov = 45.0f, float Near = 0.1f , float Far = 100.0f)
	:CamPos(pos),
	CamFront({0.0f,0.0f,-1.0f}),
	CamUp({0.0f,1.0f,0.0f}),
	CamSpeed(speed),Yaw(-90.0f), Pitch(0.0f),
	CamSensitivity(0.1f),
	FOV(fov),
	AspectRatio(aspect_ratio),
	FarPlane(Far),
	NearPlane(Near)
{

}

glm::mat4 Camera::GetLookAt()
{
	return glm::lookAt(CamPos, CamPos + CamFront, CamUp);
}

glm::mat4 Camera::GetPerspective()
{
	return glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane);
}

void Camera::MoveFront(float deltaTime)
{
	CamPos += CamFront * CamSpeed * deltaTime;
}

void Camera::MoveBack(float deltaTime)
{
	CamPos -= CamFront * CamSpeed * deltaTime;
}

void Camera::MoveLeft(float deltaTime)
{
	CamPos -= glm::normalize(glm::cross(CamFront, CamUp)) * CamSpeed * deltaTime;
}


void Camera::MoveRight(float deltaTime)
{
	CamPos += glm::normalize(glm::cross(CamFront, CamUp)) * CamSpeed * deltaTime;
}

void Camera::MoveUp(float deltaTime)
{
	glm::vec3 CamRight = glm::normalize(glm::cross(CamFront, CamUp));
	CamPos -= glm::normalize(glm::cross(CamFront, CamRight)) * CamSpeed * deltaTime;
}
void Camera::MoveDown(float deltaTime)
{
	glm::vec3 CamRight = glm::normalize(glm::cross(CamFront, CamUp));
	CamPos += glm::normalize(glm::cross(CamFront, CamRight)) * CamSpeed * deltaTime;
}

void Camera::UpdateCameraDir(double dx, double dy)
{
	dx *= CamSensitivity;
	dy *= CamSensitivity;
	Yaw += dx;
	Pitch += dy;
	// limit Pitch to 90 degress
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	else if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	CamFront = glm::normalize(direction);
}

void Camera::UpdateZoom(double Scroll)
{
	FOV -= Scroll;
	if (FOV < 1.0f)
		FOV = 1.0f;
	else if (FOV > 45.0f)
		FOV = 45.0f;
}


#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Entity.hpp"


class Camera2D
{
public:
	glm::vec2 Position; 
	glm::vec3 Origin; 
	glm::vec2 Velocity;

	GLfloat MovementSpeed;
	//GLfloat Zoom; 
	//GLfloat Rotation;

	Entity* FollowingEntity;

	Camera2D(Entity* followingEntity, const glm::vec2 position = glm::vec2(0.0f, 0.0f))
		: MovementSpeed(3.0f)//, Zoom(1.0f)
	{
		this->FollowingEntity = followingEntity;
		this->Position = position;
		this->Origin = glm::vec3(400.0f, 300.0f, 0.0f);
		//this->Rotation = 0.0f;
	}

	glm::mat4 GetViewMatrix(const glm::vec2 parralaxFactor) const
	{
		/*glm::mat4 view = glm::lookAt(glm::vec3(Position.x * parralaxFactor.x, Position.y * parralaxFactor.y, 0.0f), 
			glm::vec3(Position.x, Position.y, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), 
			glm::vec3(0.0f, 1.0f, 0.0f));*/
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(-Position.x * parralaxFactor.x, -Position.y * parralaxFactor.y, 0.0f));
		/*view = glm::translate(view, glm::vec3(-Origin.x, -Origin.y, 0.0f));
		view = glm::rotate(view, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::scale(view, glm::vec3(Zoom, Zoom, 0.0f));
		view = glm::translate(view, glm::vec3(Origin.x, Origin.y, 0.0f));*/
		return view;
	}

	glm::mat4 GetViewMatrix() const
	{
		return GetViewMatrix(glm::vec2(1.0, 1.0));
	}

	glm::mat4 GetInvertedViewMatrix() const
	{
		return glm::inverse(GetViewMatrix());
	}

	void LookAt(const glm::vec2 position)
	{
		glm::vec2 offset(position.x - Origin.x, position.y - Origin.y);
		Position = offset;
	}

	void MoveTo(const glm::vec2 to)
	{
		//Velocity += (to - Position);
		Move(glm::normalize(to - Position));
	}

	void Move(const glm::vec2 direction)
	{
		Velocity += direction;
	}

	void FollowEntity(const Entity* entityToFollow)
	{
		LookAt(entityToFollow->GetPosition().ToGlmVec2());
	}

	void Update(const double dt)
	{
		/*auto transform = [](glm::vec2 pos, glm::mat4 mat) -> glm::vec2
		{
			float da[16] = { 0.0 };

			const float *pSource = static_cast<const float*>(glm::value_ptr(mat));
			for (int i = 0; i < 16; ++i)
				da[i] = pSource[i];

			float m11 = da[0];
			float m12 = da[1];
			float m21 = da[4];
			float m22 = da[5];
			float m41 = da[12];
			float m42 = da[13];

			return glm::vec2((pos.x * m11) + (pos.y * m21) + m41, (pos.x * m12) + (pos.y * m22) + m42);
		};*/

		if (FollowingEntity)
			FollowEntity(FollowingEntity);

		Velocity *= 0.96f;
		Position += (Velocity * MovementSpeed * float(dt));
	}
};

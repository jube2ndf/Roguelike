#include "pch.h"

#include "TransformComponent.h"
namespace GameEngine
{
	void TransformComponent::SetWorldPosition(sf::Vector2f& newPosition)
	{
		this->_position = newPosition;
	}
	void TransformComponent::Update(float deltaTime)
	{
	
	}
	void TransformComponent::MoveBy(const sf::Vector2f& offset)
	{
		this->_position += offset;
	}

	void TransformComponent::RotateBy(float offset)
	{
		this->_rotation = this->_rotation + offset;
		while (this->_rotation >= 360)
		{
			this->_rotation -= 360;
		}
		while (this->_rotation < 0)
		{
			this->_rotation += 360;
		}
	}

	void TransformComponent::ScaleBy(const sf::Vector2f& scaleOffset)
	{
		this->_scale = scaleOffset;
	}

	sf::Vector2f TransformComponent::GetWorldPosition() const
	{
		return this->_position;
	}

	float TransformComponent::GetWorldRotation() const
	{
		return this->_rotation;
	}

	sf::Vector2f TransformComponent::GetWorldScale() const
	{
		return this->_scale;
	}
}
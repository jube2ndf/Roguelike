#pragma once
#include "Component.h"
namespace Engine {
    class TransformComponent :
        public Component
    {
	/*public:
		TransformComponent(GameObject* gameObject);

		void Update(float deltaTime) override;

		void MoveBy(const Vector2D& offset);
		void RotateBy(float offset);
		void ScaleBy(const Vector2Df& scaleOffset);

		const Vector2Df GetWorldPosition() const;
		const float GetWorldRotation() const;
		const Vector2Df GetWorldScale() const;

	private:
		mutable Vector2Df position = { 0, 0 };
		mutable float rotation = 0.f;
		mutable Vector2Df scale = { 1, 1 };*/
    };
}

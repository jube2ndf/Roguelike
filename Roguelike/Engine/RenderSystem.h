#pragma once

namespace GameEngine {
    class Scene;
	class RenderSystem
	{
    public:
        void Render(
            sf::RenderWindow& window,
            Scene* scene);
	};
}

#ifndef ENGINE_H
#define ENGINE_H
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif// !ENGINE_EXPORTS
namespace GameEngine {
	class SceneManager;
}
class Scene;

class CollisionSystem;
class PhysicsSystem;
class RenderSystem;
class UpdateSystem;


class ENGINE_API Engine {
public:
	Engine();
	void Initialize();
	void Run(GameEngine::SceneManager& scenes);
};
#endif // !ENGINE_H


#include "PlayerAttackComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include "CombatAction.h"
#include "HealthComponent.h"
#include <EventBus.h>
#include <Logger.h>
#include "EntityVision.h"

void Roguelike::PlayerAttackComponent::Update(float dt)
{
    if (timer >= 0.f)
    {
        timer = std::max<float>(0, timer - dt);
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        return;

    if (!this->CanAttack())
    {
        return;
    }

    auto* vision = GetGameObject()->GetComponent<EntityVision>();
    if (!vision) {
        LOG_ERROR("Player", "Player has no vision trigger");
        return;
    }
    auto* selfTr = GetGameObject()->GetComponent<GameEngine::TransformComponent>();

    if (!selfTr) {
        LOG_ERROR("Player", "Player has no TransformComponent");
        return;
    }
    float closestDist = std::numeric_limits<float>::max();
    GameEngine::GameObject* closest = nullptr;
    for (auto* obj : this->targets)
    {
        auto* tr =
            obj->GetComponent<GameEngine::TransformComponent>();

        if (!tr)
            continue;

        sf::Vector2f d =
        {
            tr->GetWorldPosition().x - selfTr->GetWorldPosition().x,
            tr->GetWorldPosition().y - selfTr->GetWorldPosition().y
        };

        float dist = d.x * d.x + d.y * d.y;
        if (!obj->GetComponent<HealthComponent>()) {
            continue;
        }
        if (dist < closestDist)
        {
            closestDist = dist;
            closest = obj;
        }
    }

    if (!closest)
        return;
    CombatAction action;
    action.type = CombatActionType::Damage;
    action.source = GetGameObject();
    action.target = closest;
    action.value = this->damage;
    LOG_INFO("PlayerPressAttack",
        "target: " + std::to_string(reinterpret_cast<uintptr_t>(action.target)));
    GameEngine::EventBus::Emit(action);

    this->ResetCooldown();
}

#include "DoorTrigget.h"
#include <TagComponent.h>
#include <EventBus.h>
#include "SceneSwitch.h"
void Roguelike::DoorTrigget::OnTriggerEnter(GameEngine::Collider* other)
{
    for (auto iter: other->GetGameObject()->GetComponents<GameEngine::TagComponent>())
    {
        if (iter->GetTag() == "Player")
        {
            SwitchScene event;
            event.openedLVL = this->door2LVL;
            GameEngine::EventBus::Emit(event);
        }
    }
    return;
}

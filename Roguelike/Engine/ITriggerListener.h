#pragma once
#include "Collider.h"

namespace GameEngine {
    class ITriggerListener
    {
    public:
        virtual ~ITriggerListener() = default;

        virtual void OnTriggerEnter(Collider* other) {}
        virtual void OnTriggerStay(Collider* other) {}
        virtual void OnTriggerExit(Collider* other) {}
    };
}
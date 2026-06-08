#pragma once
#include "EngineAPI.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

namespace GameEngine
{
    class ENGINE_API EventBus
    {
    public:
        using HandlerId = size_t;

        struct IContainer
        {
            virtual ~IContainer() = default;
        };

        template<typename T>
        struct Container : IContainer
        {
            std::vector<std::pair<HandlerId, std::function<void(const T&)>>> handlers;
        };

        template<typename T>
        static HandlerId Subscribe(std::function<void(const T&)> handler)
        {
            auto& container = GetContainer<T>();

            HandlerId id = ++_idCounter;
            container.handlers.emplace_back(id, std::move(handler));

            return id;
        }

        template<typename T>
        static void Unsubscribe(HandlerId id)
        {
            auto& container = GetContainer<T>();

            auto& vec = container.handlers;

            vec.erase(
                std::remove_if(vec.begin(), vec.end(),
                    [&](auto& p)
                    {
                        return p.first == id;
                    }),
                vec.end());
        }

        template<typename T>
        static void Emit(const T& event)
        {
            auto& container = GetContainer<T>();

            for (auto& [id, handler] : container.handlers)
                handler(event);
        }

        static void Clear()
        {
            _containers.clear();
        }

    private:
        template<typename T>
        static Container<T>& GetContainer()
        {
            std::type_index type = typeid(T);

            auto it = _containers.find(type);
            if (it == _containers.end())
            {
                auto container = std::make_unique<Container<T>>();
                auto ptr = container.get();

                _containers[type] = std::move(container);
                return *ptr;
            }

            return *static_cast<Container<T>*>(it->second.get());
        }

    private:
        inline static std::unordered_map<
            std::type_index,
            std::unique_ptr<IContainer>
        > _containers;

        inline static HandlerId _idCounter = 0;
    };
}
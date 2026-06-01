#pragma once
#include <functional>
#include <vector>

namespace GameEngine
{
    class ENGINE_API EventBus
    {
    public:
        template<typename T>
        using Handler = std::function<void(const T&)>;

        template<typename T>
        static void Subscribe(Handler<T> handler)
        {
            GetList<T>().push_back(handler);
        }

        template<typename T>
        static void Emit(const T& event)
        {
            for (auto& h : GetList<T>())
                h(event);
        }

    private:
        template<typename T>
        static std::vector<Handler<T>>& GetList()
        {
            static std::vector<Handler<T>> handlers;
            return handlers;
        }
    };
}
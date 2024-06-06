#pragma once
#include <vector>
#include <functional>


//����ί��
template<typename R = void,typename... Args>
class UnicastDelegate
{
    std::function<R(Args...)> callback;

public:
    void Bind(std::function<R(Args...)> callback) { this->callback = callback; }

    template<typename T>
    void Bind(T* obj, void(T::* func)(Args...))
    {
        std::function<R(Args...)> callback = [=](Args... args) { (obj->*func)(args...); };
        Bind(callback);
    }

    void Unbind() { callback = nullptr; }

    R Execute(Args... args);

    R operator()(Args... args) { return Execute(args...); }
};


//�ಥί��
template<typename... Args>
class MulticastDelegate
{
    std::vector<std::function<void(Args...)>> callbacks;

public:
    void Add(std::function<void(Args...)> callback); 

    template<typename T>
    void Add(T* obj, void(T::* func)(Args...))
    {
        std::function<void(Args...)> callback = [=](Args... args) { (obj->*func)(args...); };
        Add(callback);
    }

    void Remove(std::function<void(Args...)> callback);

    template<typename T>
    void Remove(T* obj, void(T::* func)(Args...))
    {
        std::function<void(Args...)> callback = [=](Args... args) { (obj->*func)(args...); };
        Remove(callback);
    }

    void BroadCast(Args... args);

    void operator()(Args... args){BroadCast(args...);}

#define AddDynamic(obj, func) Add(obj, func)
#define RemoveDynamic Remove(obj, func) Remove(obj, func)
#define AddLambda(callback) Add(callback)
#define RemoveLambda(callback) Remove(callback)
};




#define DECLARE_MULTI_PARAM_WITH_RETURN_UNICAST_DELEGATE_CLASS(Name, R, ...) class Name : public UnicastDelegate<R,__VA_ARGS__> {};
#define DECLARE_NO_PARAM_WITH_RETURN_UNICAST_DELEGATE_CLASS(Name, R) class Name : public UnicastDelegate<R> {};

#define DECLARE_MULTI_PARAM_UNICAST_DELEGATE_CLASS(Name, ...) class Name : public UnicastDelegate<void,__VA_ARGS__> {};
#define DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(Name) class Name : public UnicastDelegate<void> {};

#define DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(Name, ...) class Name : public MulticastDelegate<__VA_ARGS__> {};
#define DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(Name) class Name : public MulticastDelegate<> {};






template<typename R, typename ...Args>
inline R UnicastDelegate<R, Args...>::Execute(Args ...args)
{
    if (callback)
    {
        return callback(args...);
    }
    return R();
}



template<typename ...Args>
inline void MulticastDelegate<Args...>::Add(std::function<void(Args...)> callback)
{
    for (auto it = callbacks.begin(); it != callbacks.end(); ++it)
    {
        if (it->target<void(Args...)>() == callback.target<void(Args...)>())
        {
            return;
        }
    }
    callbacks.push_back(callback);
}

template<typename ...Args>
inline void MulticastDelegate<Args...>::Remove(std::function<void(Args...)> callback)
{
    for (auto it = callbacks.begin(); it != callbacks.end(); ++it)
    {
        if (it->target<void(Args...)>() == callback.target<void(Args...)>())
        {
            callbacks.erase(it); break;
        }
    }
}

template<typename ...Args>
inline void MulticastDelegate<Args...>::BroadCast(Args ...args)
{
    for (auto& callback : callbacks)
    {
        callback(args...);
    }
}


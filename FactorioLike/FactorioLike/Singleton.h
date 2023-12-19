#pragma once

template <class Class>
class Singleton
{
protected:
    static Class instance;

public:
    static Class& GetInstance()
    {
        return instance;
    }

public:
    Singleton() {}
};

template <class Class> Class Singleton<Class>::instance = Class();
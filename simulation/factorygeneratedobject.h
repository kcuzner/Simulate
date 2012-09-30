#ifndef FACTORYGENERATEDOBJECT_H
#define FACTORYGENERATEDOBJECT_H

template <class T>
class FactoryGeneratedObject
{
public:
    T* generate()
    {
        return new T();
    }
};

#endif // FACTORYGENERATEDOBJECT_H

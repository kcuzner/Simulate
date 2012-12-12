#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "icomponenttracker.h"

/**
 * @brief Class from which all components of simulation derive from. Components
 * have an engine-unique identifier and should not be transfered between engines
 * except through the serialization things. The unique numbers are per-instance
 * unique to an individual run of a program. These numbers should not be serialized
 * and are mainly meant to be used internally to redirect pointers. Components
 * have no way of knowing if they were created using the same tracker so it is up
 * to the programmer to ensure that they use the same tracker.
 */
class IComponent
{
public:
    virtual ~IComponent() { }

    /**
     * @brief Returns the UID of this component. This UID should be guaranteed
     * to be safe on a per-engine per-program-instance basis.
     * @return
     */
    long getUID();
};

#endif // ICOMPONENT_H

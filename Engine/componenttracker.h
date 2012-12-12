#ifndef COMPONENTTRACKER_H
#define COMPONENTTRACKER_H

#include "interfaces/icomponenttracker.h"

class ComponentTracker : public IComponentTracker
{
public:
    ComponentTracker();

    /**
     * @brief Returns a new id unique to this instance of the component tracker
     * @return
     */
    virtual long getNewId();
private:
    long nextId;
};

#endif // COMPONENTTRACKER_H

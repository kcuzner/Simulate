#ifndef ICOMPONENTTRACKER_H
#define ICOMPONENTTRACKER_H

class IComponentTracker
{
public:
    virtual ~IComponentTracker() { }

    /**
     * @brief Returns a new id unique to this instance of the component tracker
     * @return
     */
    virtual long getNewId() = 0;
};

#endif // ICOMPONENTTRACKER_H

#include "componenttracker.h"

ComponentTracker::ComponentTracker()
{
    this->nextId = 0;
}

long ComponentTracker::getNewId()
{
    return this->nextId++;
}

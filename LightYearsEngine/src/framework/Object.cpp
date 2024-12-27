#include "framework/Object.h"

namespace ly
{
    unsigned int  Object::uniqueIdCounter{0};
    Object::Object()
        : mIsPendingDestroy(false),
        mUniqueID{GetNextAvailableId()}
    {

    }

    Object::~Object()
    {
        // LOG("Object Destroyed");
    }

    void Object::Destroy()
    {
        // onDestroy.Broadcast(this);
        mIsPendingDestroy = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    weak<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }

    unsigned int Object::GetNextAvailableId()
    {
        return uniqueIdCounter++;
    }
}

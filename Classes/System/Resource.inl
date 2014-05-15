////////////////////////////////////////////////////////////
template <typename T>
Resource<T>::Resource()
{
    // Nothing to do
}


////////////////////////////////////////////////////////////
template <typename T>
Resource<T>::Resource(const Resource<T>&)
{
    // Nothing to do, we don't want to copy observers
}


////////////////////////////////////////////////////////////
template <typename T>
Resource<T>::~Resource()
{
    // Notify all observers
    for (typename std::set<ResourcePtr<T>*>::iterator i = myObservers.begin(); i != myObservers.end(); ++i)
    {
        (*i)->OnResourceDestroyed();
    }
}


////////////////////////////////////////////////////////////
template <typename T>
Resource<T>& Resource<T>::operator =(const Resource<T>&)
{
    // Nothing to do, we don't want to copy observers
    return *this;
}


////////////////////////////////////////////////////////////
template <typename T>
void Resource<T>::Connect(ResourcePtr<T>& observer) const
{
    System::Lock lock(myMutex);
    myObservers.insert(&observer);
}


////////////////////////////////////////////////////////////
template <typename T>
void Resource<T>::Disconnect(ResourcePtr<T>& observer) const
{
    System::Lock lock(myMutex);
    myObservers.erase(&observer);
}

////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>::ResourcePtr() :
myResource(NULL)
{

}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>::ResourcePtr(const T* resource) :
myResource(resource)
{
    if (myResource)
        myResource->Connect(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>::ResourcePtr(const ResourcePtr<T>& copy) :
myResource(copy.myResource)
{
    if (myResource)
        myResource->Connect(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>::~ResourcePtr()
{
    if (myResource)
        myResource->Disconnect(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>& ResourcePtr<T>::operator =(const ResourcePtr<T>& right)
{
    if (myResource)
        myResource->Disconnect(*this);

    myResource = right.myResource;

    if (myResource)
        myResource->Connect(*this);

    return *this;
}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>& ResourcePtr<T>::operator =(const T* resource)
{
    if (myResource)
        myResource->Disconnect(*this);

    myResource = resource;

    if (myResource)
        myResource->Connect(*this);

    return *this;
}


////////////////////////////////////////////////////////////
template <typename T>
ResourcePtr<T>::operator const T*() const
{
    return myResource;
}


////////////////////////////////////////////////////////////
template <typename T>
const T& ResourcePtr<T>::operator *() const
{
    return *myResource;
}


////////////////////////////////////////////////////////////
template <typename T>
const T* ResourcePtr<T>::operator ->() const
{
    return myResource;
}


////////////////////////////////////////////////////////////
template <typename T>
void ResourcePtr<T>::OnResourceDestroyed()
{
    myResource = NULL;
}

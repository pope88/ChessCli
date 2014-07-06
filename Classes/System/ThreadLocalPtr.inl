namespace System
{
////////////////////////////////////////////////////////////
template <typename T>
ThreadLocalPtr<T>::ThreadLocalPtr(T* value) :
ThreadLocal(value)
{
}


////////////////////////////////////////////////////////////
template <typename T>
T& ThreadLocalPtr<T>::operator *() const
{
    return *static_cast<T*>(GetValue());
}


////////////////////////////////////////////////////////////
template <typename T>
T* ThreadLocalPtr<T>::operator ->() const
{
    return static_cast<T*>(GetValue());
}


////////////////////////////////////////////////////////////
template <typename T>
ThreadLocalPtr<T>::operator T*() const
{
    return static_cast<T*>(GetValue());
}


////////////////////////////////////////////////////////////
template <typename T>
ThreadLocalPtr<T>& ThreadLocalPtr<T>::operator =(T* value)
{
    SetValue(value);
    return *this;
}


////////////////////////////////////////////////////////////
template <typename T>
ThreadLocalPtr<T>& ThreadLocalPtr<T>::operator =(const ThreadLocalPtr<T>& right)
{
    SetValue(right.GetValue());
    return *this;
}

} // namespace System

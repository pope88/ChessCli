#ifndef SYSTEM_RESOURCE_H
#define SYSTEM_RESOURCE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/Lock.h>
#include <System/Mutex.h>
#include <set>
#include <cstddef>


namespace System
{
////////////////////////////////////////////////////////////
// These two classes are defined in the same header because
// they depend on each other. And as they're template classes,
// they must be entirely defined in header files, which
// prevents from proper separate compiling
////////////////////////////////////////////////////////////

template <typename> class ResourcePtr;

////////////////////////////////////////////////////////////
/// \brief Base class for resources that need to notify
///        dependent classes about their destruction
///
////////////////////////////////////////////////////////////
template <typename T>
class Resource
{
protected :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Resource();

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    Resource(const Resource<T>& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Resource();

    ////////////////////////////////////////////////////////////
    /// \brief Assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    Resource<T>& operator =(const Resource<T>& right);

private :

    friend class ResourcePtr<T>;

    ////////////////////////////////////////////////////////////
    /// \brief Connect a ResourcePtr to this resource
    ///
    /// A connected ResourcePtr will be notified of the
    /// destruction of this instance.
    ///
    /// \param observer ResourcePtr to connect
    ///
    ////////////////////////////////////////////////////////////
    void Connect(ResourcePtr<T>& observer) const;

    ////////////////////////////////////////////////////////////
    /// \brief Disconnect a ResourcePtr from this resource
    ///
    /// The disconnected ResourcePtr will no longer be notified
    /// if this instance is destroyed.
    ///
    /// \param observer ResourcePtr to disconnect
    ///
    ////////////////////////////////////////////////////////////
    void Disconnect(ResourcePtr<T>& observer) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    mutable std::set<ResourcePtr<T>*> myObservers; ///< List of pointers to this resource
    mutable Mutex                     myMutex;     ///< Mutex for preventing concurrent access to the pointer list
};


////////////////////////////////////////////////////////////
/// \brief Safe pointer to a System::Resource<T>
///
////////////////////////////////////////////////////////////
template <typename T>
class ResourcePtr
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// A default constructed ResourcePtr is empty (null).
    ///
    ////////////////////////////////////////////////////////////
    ResourcePtr();

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a raw pointer
    ///
    /// \param resource Raw pointer to the resource to wrap
    ///
    ////////////////////////////////////////////////////////////
    ResourcePtr(const T* resource);

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// The new ResourcePtr will share the same resource as \a copy.
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    ResourcePtr(const ResourcePtr<T>& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~ResourcePtr();

    ////////////////////////////////////////////////////////////
    /// \brief Assignment operator for a ResourcePtr parameter
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    ResourcePtr<T>& operator =(const ResourcePtr<T>& right);

    ////////////////////////////////////////////////////////////
    /// \brief Assignment operator for a raw pointer parameter
    ///
    /// \param resource Resource to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    ResourcePtr<T>& operator =(const T* resource);

    ////////////////////////////////////////////////////////////
    /// \brief Cast operator to implicitely convert the resource
    ///        pointer to its raw pointer type (T*)
    ///
    /// This might be dangerous in the general case, but in this context
    /// it is safe enough to define this operator.
    ///
    /// \return Read-only pointer to the actual resource
    ///
    ////////////////////////////////////////////////////////////
    operator const T*() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator *
    ///
    /// Like raw pointers, applying the * operator returns a
    /// reference to the pointed object.
    ///
    /// \return Reference to the pointed resource
    ///
    ////////////////////////////////////////////////////////////
    const T& operator *() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of operator ->
    ///
    /// Like raw pointers, applying the -> operator returns the
    /// pointed object.
    ///
    /// \return Pointed resource
    ///
    ////////////////////////////////////////////////////////////
    const T* operator ->() const;

    ////////////////////////////////////////////////////////////
    /// \brief Function called when the observed resource
    ///        is about to be destroyed
    ///
    /// This functions is called by the destructor of the pointed
    /// resource. It allows this instance to reset its internal pointer
    /// when the resource is destroyed, and avoid dangling pointers.
    ///
    ////////////////////////////////////////////////////////////
    void OnResourceDestroyed();

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    const T* myResource; /// Pointer to the actual resource
};

#include <System/Resource.inl>
#include <System/ResourcePtr.inl>

} // namespace System


#endif // SYSTEM_RESOURCE_H


////////////////////////////////////////////////////////////
/// \class System::Resource
/// \ingroup system
///
/// System::Resource is a base for classes that want to be
/// compatible with the System::ResourcePtr safe pointer.
///
/// See System::ResourcePtr for a complete explanation.
///
/// \see System::ResourcePtr
///
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// \class System::ResourcePtr
/// \ingroup system
///
/// System::ResourcePtr is a special kind of smart pointer for
/// resources. Its main feature is to automatically
/// reset its internal pointer to 0 when the resource
/// gets destroyed, so that pointers to a resource never
/// become invalid when the resource is destroyed. Instead,
/// it properly returns 0 when the resource no longer exists.
///
/// Its usage is completely transparent, so that it is similar
/// to manipulating the raw resource directly (like any smart pointer).
///
/// For System::ResourcePtr<T> to work, T must inherit from
/// the System::Resource class.
///
/// These two classes are heavily used internally in library
/// to safely handle resources and the classes that use them:
/// \li System::Image / System::Sprite
/// \li System::Font / System::String
/// \li System::SoundBuffer / System::Sound
///
/// System::Resource and System::ResourcePtr are designed for internal use,
/// but if you feel like they would fit well in your implementation
/// there's no problem to use them.
///
/// \see System::Resource
///
////////////////////////////////////////////////////////////

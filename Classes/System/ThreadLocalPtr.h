#ifndef SYSTEM_THREADLOCALPTR_H
#define SYSTEM_THREADLOCALPTR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <System/ThreadLocal.h>


namespace System
{
////////////////////////////////////////////////////////////
/// \brief Pointer to a thread-local variable
///
////////////////////////////////////////////////////////////
template <typename T>
class ThreadLocalPtr : private ThreadLocal
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param value Optional value to initalize the variable
    ///
    ////////////////////////////////////////////////////////////
    ThreadLocalPtr(T* value = NULL);

    ////////////////////////////////////////////////////////////
    /// \brief Overload of unary operator *
    ///
    /// Like raw pointers, applying the * operator returns a
    /// reference to the pointed object.
    ///
    /// \return Reference to the pointed object
    ///
    ////////////////////////////////////////////////////////////
    T& operator *() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of operator ->
    ///
    /// Like raw pointers, applying the -> operator returns the
    /// pointed object.
    ///
    /// \return Pointed object
    ///
    ////////////////////////////////////////////////////////////
    T* operator ->() const;

    ////////////////////////////////////////////////////////////
    /// \brief Cast operator to implicitely convert the
    ///        pointer to its raw pointer type (T*)
    ///
    /// \return Pointer to the actual object
    ///
    ////////////////////////////////////////////////////////////
    operator T*() const;

    ////////////////////////////////////////////////////////////
    /// \brief Assignment operator for a raw pointer parameter
    ///
    /// \param value Pointer to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    ThreadLocalPtr<T>& operator =(T* value);

    ////////////////////////////////////////////////////////////
    /// \brief Assignment operator for a ThreadLocalPtr parameter
    ///
    /// \param right ThreadLocalPtr to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    ThreadLocalPtr<T>& operator =(const ThreadLocalPtr<T>& right);
};

} // namespace System

#include <System/ThreadLocalPtr.inl>


#endif // SYSTEM_THREADLOCALPTR_H


////////////////////////////////////////////////////////////
/// \class System::ThreadLocalPtr
/// \ingroup system
///
/// System::ThreadLocalPtr is a type-safe wrapper for storing
/// pointers to thread-local variables. A thread-local
/// variable holds a different value for each different
/// thread, unlike normal variable that are shared.
///
/// Its usage is completely transparent, so that it is similar
/// to manipulating the raw pointer directly (like any smart pointer).
///
/// Usage example:
/// \code
/// MyClass object1;
/// MyClass object2;
/// System::ThreadLocalPtr<MyClass> objectPtr;
///
/// void Thread1(void*)
/// {
///     objectPtr = &object1; // doesn't impact Thread2
///     ...
/// }
///
/// void Thread1(void*)
/// {
///     objectPtr = &object2; // doesn't impact Thread1
///     ...
/// }
///
/// int main()
/// {
///     // Create and launch the two threads
///     System::Thread thread1(&Thread1);
///     System::Thread thread2(&Thread2);
///     thread1.Launch();
///     thread2.Launch();
///
///     return 0;
/// }
/// \endcode
///
/// ThreadLocalPtr is designed for internal use; however you
/// can use it if you feel like it fits well your implementation.
///
////////////////////////////////////////////////////////////

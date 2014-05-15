namespace priv
{
// Base class for abstract thread functions
struct ThreadFunc
{
    virtual ~ThreadFunc() {}
    virtual void Run() = 0;
};

// Specialization using a functor (including free functions) with no argument
template <typename T>
struct ThreadFunctor : ThreadFunc
{
    ThreadFunctor(T functor) : myFunctor(functor) {}
    virtual void Run() {myFunctor();}
    T myFunctor;
};

// Specialization using a functor (including free functions) with one argument
template <typename F, typename A>
struct ThreadFunctorWithArg : ThreadFunc
{
    ThreadFunctorWithArg(F function, A arg) : myFunction(function), myArg(arg) {}
    virtual void Run() {myFunction(myArg);}
    F myFunction;
    A myArg;
};

// Specialization using a member function
template <typename C>
struct ThreadMemberFunc : ThreadFunc
{
    ThreadMemberFunc(void(C::*function)(), C* object) : myFunction(function), myObject(object) {}
    virtual void Run() {(myObject->*myFunction)();}
    void(C::*myFunction)();
    C* myObject;
};

} // namespace priv


////////////////////////////////////////////////////////////
template <typename F>
Thread::Thread(F functor) :
myImpl    (NULL),
myFunction(new priv::ThreadFunctor<F>(functor))
{
}


////////////////////////////////////////////////////////////
template <typename F, typename A>
Thread::Thread(F function, A argument) :
myImpl    (NULL),
myFunction(new priv::ThreadFunctorWithArg<F, A>(function, argument))
{
}


////////////////////////////////////////////////////////////
template <typename C>
Thread::Thread(void(C::*function)(), C* object) :
myImpl    (NULL),
myFunction(new priv::ThreadMemberFunc<C>(function, object))
{
}

#ifndef _SINGLETON_H_
#define _SINGLETON_H_
namespace Utils
{
/**
 * @notes: 所有继承该模板的类，均需设置MMSCMibSingleton<type>作为友元类，并将自身的构造函数设置为私有
 */
template <class T>
class Singleton
{
public:

    /**
     * get the global sole instance object. If it is null, create it.
     */
    static inline T* instance()
    {
        if (NULL == _instance.get())                     
        {
		    _instance.reset(new T());
        }
        return _instance.get();
    }
 
private:

    Singleton(void) { }

    virtual ~Singleton(){ }

	Singleton(const Singleton&){}

	Singleton &operator=(const Singleton &){}

private:

    static std::auto_ptr<T> _instance;
};

template<class T>
std::auto_ptr<T> Singleton<T>::_instance;
	
#define DECLARE_SINGLETON_CLASS(type)\
	friend class std::auto_ptr<type>;\
	friend class Singleton<type>;

}
#endif


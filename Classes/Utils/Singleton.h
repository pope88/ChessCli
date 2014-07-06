#ifndef _SINGLETON_H_
#define _SINGLETON_H_
namespace Utils
{
/**
 * @notes: ���м̳и�ģ����࣬��������MMSCMibSingleton<type>��Ϊ��Ԫ�࣬��������Ĺ��캯������Ϊ˽��
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


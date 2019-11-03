//
// Created by elrond on 11/1/19.
//

#ifndef MYSINGLETON_SINGLETON_H
#define MYSINGLETON_SINGLETON_H

#include <stdexcept>
#include <cstdlib>

template <class T>
class SingleThreadModel
{
public:
	struct Lock{};
	using Type = T;
};

template <class T>
class StandartCLifetime
{
public:
	static void OnDeadReference(){
		throw std::runtime_error("StandartCLifetime::OnDeadReference()");
	};
	static void ShedulleCall(void(*f)()){
		std::atexit(f);
	}
};

template <class T>
class CreateUsingNew
{
public:
	static T* Create()
	{
		return new T;
	}
	
	static void Destroy(T* t)
	{
		delete t;
	}
};

template <class T>
class CreateStatic
{
	static T* Create()
	{
		static T t;
		return &t;
	}
};

/////////////////////////////////////////////////////////////////////////
/// \class	SingletonHolder
///
///
/////////////////////////////////////////////////////////////////////////
template <class T,
		template <class> class CreationPolicy = CreateUsingNew,
		template <class> class LifetimePolicy = StandartCLifetime,
		template <class> class ThreadingModel = SingleThreadModel>
class SingletonHolder
{
public:
	using InstanceType = typename ThreadingModel<T>::Type;
	
	static T& Instance(){
		if(pInstance_ == nullptr){
			typename ThreadingModel<T>::Lock lockguard;
			if(pInstance_ == nullptr){
				if(destroyed_){
					LifetimePolicy<T>::OnDeadReference();
					destroyed_ = false;
				}
				pInstance_ = CreationPolicy<T>::Create();
				LifetimePolicy<T>::ShedulleCall(&Destroy);
			}
		}
		return *pInstance_;
	}
	
	SingletonHolder() = delete;
	SingletonHolder(const SingletonHolder&) = delete;
private:
	static void Destroy(){
		CreationPolicy<T>::Destroy(pInstance_);
		pInstance_ = nullptr;
		destroyed_ = true;
	}
	
	static InstanceType *pInstance_;
	static bool destroyed_;
};

//////
/// Initialise static members
template <class T, template <class> class CP, template <class> class LtP, template <class> class ThmP>
typename SingletonHolder<T, CP, LtP, ThmP>::InstanceType* SingletonHolder<T, CP, LtP, ThmP>::pInstance_ = nullptr;
template <class T, template <class> class CP, template <class> class LtP, template <class> class ThmP>
bool SingletonHolder<T, CP, LtP, ThmP>::destroyed_ = false;
//////

#endif //MYSINGLETON_SINGLETON_H

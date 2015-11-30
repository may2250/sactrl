//文件名 qevent.h
//时间  2005.3.25
//功能  委托库 QLib::Event<>
//版本  1.0.
//编译器支持 VC60 VC70 VC71
//声明形式 以相同方式声明0-9个参数的任意委托
// QLib::Event<int> ev0; 
// QLib::Event<int,int> ev1;
// QLib::Event<void,int,int> ev2;
//构造函数 支持Event,Event中的单个成员[],普通函数，仿函数，类成员函数，
// QLib::Event<int,int> ev1(&Test1), e1(&Test1),v1;
// QLib::Event<int,int> ev1((Hello()));
// QLib::Event<int,int> ev1(&h,&H::Test1);
// QLib::Event<int,int> ev1(e1); 
// QLib::Event<int,int> ev1(e1[0]); 
//绑定函数  bind 支持普通函数，仿函数，类成员函数, Event
// ev1.bind(&Test1); 
// ev1.bind((Hello())); 
// ev1.bind(&h,&H::Test1);
//解除函数绑定 unbind
//获得已绑定函数的数目 hasbind
//重载运算符 +=, -= 对应 bind, unbind ，支持普通函数，仿函数，类成员函数和 Event
// ev1 += &Test1; 
// ev1 += Hello(); 
// ev1 += QLib::Event(&h,&H::Test1);
// ev1 += e1; 
// ev1 += ev1[0]; 
//重载运算符 ==, != 判断两个Event是否相同，也可判断单一委托时是否与函数相同
// bool b = (ev1 == ev1); 
// bool b = (ev1 == &Test1);
//重载 = 运算符 用于复制Event或单一委托
// ev1 = ev; 
// ev1 = &Test1; ....
//辅助函数
// QLib::Event::param 参数个数
// ev1.size() 委托的函数数目
// ev1.empty() 是否为空
// ev1.clear() 清空
// ev1.removesame() 去除重复的函数
//将Event当作为一个函数进行委托时
// ev1.bind(&e1,&ev::operator());
//将Event中函数传递给另一个Event时
// ev1 += e1;
// ev1.bind(e1);
//调用形式 支持全部调用和单个委托函数的调用
// ev1(10);
// for (int i = 0; i < ev1.size(); i++)
//        ev1[i](10);

#ifndef _QEVENT_20050320_H_
#define _QEVENT_20050320_H_

#pragma warning(disable:4715)
#pragma warning(disable:4786)

#include <vector>
#include <typeinfo>

namespace QLib
{

struct QLib_Event
{

struct NullType;

template <typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
struct Length
{
	template <typename T1 = NullType> 
	struct Len
	{
		enum{value = 1};
	};
	template<> 
	struct Len<NullType>
	{
		enum {value = 0};
	};	
	enum enum_len {value = Len<T1>::value + Len<T2>::value+Len<T3>::value+Len<T4>::value+Len<T5>::value+Len<T6>::value+Len<T7>::value+Len<T8>::value+Len<T9>::value};
};
//模仿Loki库实现is_function区分普通函数和仿函数
template <typename T>
struct is_function
{
	struct PointerHelper
	{
		PointerHelper(const volatile void*);
	};

	static char IsPointer(PointerHelper);
	static int  IsPointer(...);
	static T MakeT();

	enum { value = (sizeof(char) == sizeof(IsPointer(MakeT()))) };
};

struct MemberFuncBase{
	virtual MemberFuncBase * Clone() = 0;
	virtual bool Equals(MemberFuncBase*) = 0;
};

template <typename CLS, typename PMFC>
struct MemberFuncImpl : public MemberFuncBase
{
	CLS * pcls;
	PMFC  pmf;
	virtual MemberFuncBase * Clone()
	{
		MemberFuncImpl<CLS,PMFC> * p = new MemberFuncImpl<CLS,PMFC>;
		p->pcls = pcls;
		p->pmf = pmf;
		return p;
	}
	virtual bool Equals(MemberFuncBase * base)
	{
		MemberFuncImpl<CLS,PMFC> * p = static_cast<MemberFuncImpl<CLS,PMFC>*>(base);
		return (pcls == p->pcls && pmf == p->pmf);
	}
};

struct EventPtr
{
	enum { any_obj, any_mem, any_fun};
	union any_ptr
	{
		void * obj_ptr;	
		const void * const_obj_ptr;
		MemberFuncBase * mem_ptr;
	};
	inline void set_function_ptr(void * obj_ptr)
	{
		clear();
		vt = any_fun;
		any.obj_ptr = obj_ptr;
	}
	inline void set_function_obj(void * obj_ptr)
	{
		clear();
		vt = any_obj;
		any.obj_ptr = obj_ptr;
	}
	inline void set_function_obj(const void * obj_ptr)
	{
		clear();
		vt = any_obj;
		any.const_obj_ptr = obj_ptr;
	}
	inline void set_member_func(MemberFuncBase * mem_ptr)
	{
		clear();
		vt = any_mem;
		any.mem_ptr = mem_ptr;
	}
	EventPtr(const EventPtr & ptr)
	{
		clear();
		vt = ptr.vt;
		if (vt == any_mem)
		{
			any.mem_ptr = ptr.any.mem_ptr->Clone();
		}
		else
		{
			any.obj_ptr = ptr.any.obj_ptr;
		}
	}
	inline bool operator == (const EventPtr & ptr)
	{
		if (vt != ptr.vt)
			return false;
		if (vt == any_fun)
			return bool(any.obj_ptr == ptr.any.obj_ptr);
		else if (vt == any_mem)
			return bool(any.mem_ptr->Equals(ptr.any.mem_ptr));
		else if (vt == any_obj)
			return bool((typeid(any.obj_ptr) == typeid(ptr.any.obj_ptr) != 0));
		return false;
	}
	inline bool operator != (const EventPtr & ptr)
	{
		return !(*this == ptr);
	}
	EventPtr():vt(any_obj) 
	{
	}
	~EventPtr()
	{
		clear();
	}
	inline void clear()
	{
		if(vt == any_mem) 
			delete any.mem_ptr;
	}
	any_ptr any;
	char	vt;
};

template <unsigned int n> 
struct EventHelper;

template<>
struct EventHelper<0>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T0 = NullType>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*);
				inline R operator()()
				{
					return invoke(&ptr);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;
		
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)();
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun();
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return (p->pcls->*p->pmf)();
				}
			};
			R operator()()
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr);				
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T0 = NullType>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*);
				inline R operator()()
				{
					invoke(&ptr);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;
			
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)();
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun();
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)();
				}
			};
			R operator()()
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<>
	{
	};
};

template<>
struct EventHelper<1>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1);
				inline R operator()(T1 t1)
				{
					return invoke(&ptr,t1);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;
			
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1);
				}
			};
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				inline static R Invoke(EventPtr * ptr, T1 t1)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls)->*(p->pmf))(t1);
				}
			};
			inline R operator()(T1 t1)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1);				
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1);
				inline R operator()(T1 t1)
				{
					invoke(&ptr,t1);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;
			
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1);
				}
			};
			R operator()(T1 t1)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1>//,T2,T3,T4,T5,T6,T7,T8,T9>
	{
	};
};

template<>
struct EventHelper<2>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2);
				inline R operator()(T1 t1, T2 t2)
				{
					return invoke(&ptr,t1,t2);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;
			
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2));
				}
			};
			R operator()(T1 t1, T2 t2)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2);				
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2);
				inline R operator()(T1 t1, T2 t2)
				{
					invoke(&ptr,t1,t2);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2);
				}
			};
			R operator()(T1 t1, T2 t2)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2>
	{
	};
};

template<>
struct EventHelper<3>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3);
				inline R operator()(T1 t1, T2 t2, T3 t3)
				{
					return invoke(&ptr,t1,t2,t3);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3);				
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3);
				inline R operator()(T1 t1, T2 t2, T3 t3)
				{
					invoke(&ptr,t1,t2,t3);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3>
	{
	};
};

template<>
struct EventHelper<4>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
				{
					return invoke(&ptr,t1,t2,t3,t4);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4);				
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
				{
					invoke(&ptr,t1,t2,t3,t4);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4>
	{
	};
};

template<>
struct EventHelper<5>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4,t5);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5);
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4,t5);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					invoke(&ptr,t1,t2,t3,t4,t5);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5>
	{
	};
};

template<>
struct EventHelper<6>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4,t5,t6);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6);
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4,t5,t6);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6);				
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6>
	{
	};
};

template<>
struct EventHelper<7>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4,t5,t6,t7);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7);
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7);		
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7>
	{
	};
};

template<>
struct EventHelper<8>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7,t8);		
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7,T8>
	{
	};
};

template<>
struct EventHelper<9>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8,T9);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8,T9 t9)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8,t9));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
			{
				int size = lst.size();
				if (size == 1)
				{
					return lst[0]->invoke(&lst[0]->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
				if (size != 0)
				{
					for (int i = 0; i < size-1; i++)
					{
						lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
					}
					return lst[size-1]->invoke(&lst[size-1]->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct Param
		{
			struct InImpl
			{
				EventPtr	ptr;
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8,T9);
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			std::vector<InImpl*>	lst;
			typedef typename std::vector<InImpl*>::iterator it;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
			{
				int size = lst.size();
				for (int i = 0; i < size; i++)
				{
					lst[i]->invoke(&lst[i]->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);		
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7,T8,T9>
	{
	};
};

}; //QLib_Event

/*template <typename R, typename T1 = QLib_Event::NullType, typename T2 = QLib_Event::NullType, typename T3 = QLib_Event::NullType, typename T4 = QLib_Event::NullType, typename T5 = QLib_Event::NullType, typename T6 = QLib_Event::NullType, typename T7 = QLib_Event::NullType, typename T8 = QLib_Event::NullType, typename T9 = QLib_Event::NullType>
class Event : public QLib_Event::EventHelper<QLib_Event::Length<T1,T2,T3,T4,T5,T6,T7,T8,T9>::value>::EventBase<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>
{
public:
	enum enum_param {param = QLib_Event::Length<T1,T2,T3,T4,T5,T6,T7,T8,T9>::value};

	typedef typename QLib_Event::EventPtr EventPtr;
	typedef typename QLib_Event::EventHelper<param>::EventBase<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>::InImpl InImpl;
	typedef typename R	ResultType;
	typedef typename T1 Param1Type;
	typedef typename T2 Param2Type;
	typedef typename T3 Param3Type;
	typedef typename T4 Param4Type;
	typedef typename T5 Param5Type;
	typedef typename T6 Param6Type;
	typedef typename T7 Param7Type;
	typedef typename T8 Param8Type;
	typedef typename T9 Param9Type;
public:
	//空构造函数
	Event()
	{
	}
	//构造函数 Event
	Event(Event & ev)
	{
		clear();
		copy(ev);	
	}
	//构造函数 普通函数,仿函数,InImpl
	template <typename T>
	struct is_event
	{
		enum {value = 0};
	};
	template<>
	struct is_event<Event>
	{
		enum {value = 1};
	};
	template <typename T>
		Event(const T & t)
	{
		clear();
		copy_helper<T>::copy(this,t);
	}
	//构造函数  类成员函数
	template <typename CLS, typename PMFC>
		Event(CLS * pcls, const PMFC & pmf)
	{
		clear();
		bind(pcls,pmf);
	}
	//析构函数
	~Event()
	{
		clear();
	}
	//赋值函数
	inline Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> operator = (const Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		clear();
		copy(ev);
		return *this;
	}
	//[]运算符,支持 operator[]()形式
	inline InImpl & operator[] (int i) const
	{
		return (*lst[i]);
	}
	//+=运算符 
	inline void operator += (const Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		int size = ev.lst.size();
		for (int i = 0; i < size; i++)
		{
			lst.push_back(new InImpl(*ev.lst[i]));
		}
	}
	//-=运算符
	inline void operator -= (const Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		if (*this == ev)
		{
			clear();
			return;
		}
		int size = ev.lst.size();
		for (int i = 0; i < size; i++)
		{
			for (it j = lst.begin(); j != lst.end(); j++)
			{
				if ((*j)->ptr == ev.lst[i]->ptr && (*j)->invoke == ev.lst[i]->invoke)
				{
					delete *j;
					lst.erase(j);
					break;
				}
			}
		}
	}
	// == 运算符
	inline bool operator == (const Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		if (lst.size() != ev.lst.size())
			return false;
		for (int i = 0; i < size(); i++)
		{
			if (lst[i]->ptr != ev.lst[i]->ptr ||
				lst[i]->invoke != ev.lst[i]->invoke)
			{
				return false;
			}
		}
		return true;
	}
	// -= 运算符
	inline bool operator != (const Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		return !(*this == ev);
	}
	//交换
	inline void swap(Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> & ev)
	{
		Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> tmp = ev;
		ev = *this;
		*this = tmp;
	}
	//去除重复元素
	inline void removesame()
	{
		Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> ev;
		for (int i = 0; i < (int)lst.size(); i++)
		{
			if (ev.find((*lst[i])) == -1)
			{
				ev.lst.push_back(new InImpl(*lst[i]));
			}
		}
		*this = ev;
	}
	//是否为空
	inline bool empty()
	{
		return lst.empty();
	}
	//大小 元素个数
	inline int size()
	{
		return (int)lst.size();
	}
	//清空
	inline void clear()
	{
		for (int i = 0; i < (int)lst.size(); i++)
		{
			delete lst[i];
		}
		lst.clear();
	}
	//bind 普通函数,仿函数
	template <typename Fun>
		inline void bind(const Fun & fun)
	{
		if (is_event<Fun>::value == true)
			*this += fun;
		else
			lst.push_back(bind_helper<QLib_Event::is_function<Fun>::value>::bind(fun));
	}
	//hasbind 普通函数,仿函数
	template <typename Fun>
		inline int hasbind(const Fun & fun)
	{
		int n = 0;
		for (it i = lst.begin(); i != lst.end(); i++)
		{
			if (bind_helper<QLib_Event::is_function<Fun>::value>::ifbind(*i,fun))
			{
				n++;
				continue;
			}
		}
		return n;
	}
	//unbind 普通函数,仿函数
	template <typename Fun>
		inline bool unbind(const Fun & fun)
	{
		if (is_event<Fun>::value == true)
		{
			int size = lst.size();
			*this -= fun;
			return size != lst.size();
		}
		for (it i = lst.begin(); i != lst.end(); i++)
		{
			if (bind_helper<QLib_Event::is_function<Fun>::value>::ifbind(*i,fun))
			{
				delete *i;
				lst.erase(i);
				return true;
			}
		}
		return false;
	}
	//bind 类成员函数
	template <typename CLS, typename PMFC>
		inline void bind(CLS * pcls, const PMFC & pmf)
	{
		MemberFunc<CLS,PMFC> * pmem = new MemberFunc<CLS,PMFC>;
		pmem->pcls = pcls;
		pmem->pmf = pmf;
		InImpl * in = new InImpl;
		in->ptr.set_member_func(pmem);
		in->invoke = &MemberFunc<CLS,PMFC>::Invoke;
		lst.push_back(in);
	}
	//hasbind 类成员函数
	template <typename CLS, typename PMFC>
		inline int hasbind(CLS * pcls, PMFC pmf)
	{
		int n = 0;
		for (it i = lst.begin(); i != lst.end(); i++)
		{
			if ((*i)->ptr.vt == EventPtr::any_mem)
			{
				MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>((*i)->ptr.any.mem_ptr);
				if (p->pcls == pcls &&
					p->pmf == pmf)
				{	
					n++;
					continue;
				}
			}
		}
		return n;
	}
	//unbind 类成员函数
	template <typename CLS, typename PMFC>
		inline bool unbind(CLS * pcls, PMFC pmf)
	{
		for (it i = lst.begin(); i != lst.end(); i++)
		{
			if ((*i)->ptr.vt == EventPtr::any_mem)
			{
				MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>((*i)->ptr.any.mem_ptr);
				if (p->pcls == pcls &&
					p->pmf == pmf)
				{	
					delete *i;
					lst.erase(i);
					return true;
				}
			}
		}
		return false;
	}
	//辅助拷贝函数
	inline void copy(const Event & ev)
	{
		for (int i = 0; i < (int)ev.lst.size(); i++)
		{
			lst.push_back(new InImpl(*ev.lst[i]));
		}
	}
protected:
	//查找元素
	inline int find(const InImpl & in, int start = 0)
	{
		for (int i = start; i < (int)lst.size(); i++)
		{
			if (lst[i]->ptr == in.ptr && lst[i]->invoke == in.invoke)
				return i;
		}
		return -1;
	}
	//bind 辅助函数
	template <bool>
	struct bind_helper
	{
		template <typename Fun>
		static InImpl * bind(const Fun & fun)
		{
			InImpl * in = new InImpl;
			in->ptr.set_function_obj(static_cast<const void*>(&fun));
			in->invoke = &FunctionObj<Fun>::Invoke;
			return in;
		};
		template <typename Fun>
		static bool ifbind(InImpl * in, const Fun & fun)
		{
			if (in->ptr.vt == EventPtr::any_obj &&
				typeid(reinterpret_cast<Fun&>(in->ptr.any.obj_ptr)) == typeid(fun) )
				return true;
			return false;
		}
	};
	template<>
	struct bind_helper<true>
	{
		template <typename Fun>
		static InImpl * bind(const Fun & fun)
		{
			InImpl * in = new InImpl;
			in->ptr.set_function_ptr(static_cast<void*>(fun));
			in->invoke = &FunctionPtr<Fun>::Invoke;
			return in;
		};
		template <typename Fun>
		static bool ifbind(InImpl * in, const Fun & fun)
		{
			if (in->ptr.vt == EventPtr::any_fun &&
				static_cast<Fun>(in->ptr.any.obj_ptr) == fun )
				return true;
			return false;
		}
	};
	//辅助拷贝函数
	template <typename Fun>
	struct copy_helper
	{
		static void copy(Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> * pEv,const Fun & fun)
		{
			pEv->bind(fun);
		}
	};
	template<>
	struct copy_helper<Event>
	{
		static void copy(Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> * pEv,const Event & ev)
		{
			pEv->copy(ev);
		}
	};
	template<>
	struct copy_helper<InImpl>
	{
		static void copy(Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> * pEv, const InImpl & in)
		{
			pEv->lst.push_back(new InImpl(in));
		}
	};
};
*/

}; // namespace QLib


#endif
#ifndef _Z_ALLOCATOR_H
#define _Z_ALLOCATOR_H

#include "./common/interface.h"
#include <new>
#include <cstddef>
#include <cstdlib> //for exit abort
#include <climits> //for UINT_MAX
#include <iostream>

namespace ZAV
{

template <class T>
INLINE T *_allocate(ptrdiff_t size, T *)
{
    std::set_new_handler(0); // 设置内存分配处理器，可传func
    T *tmp = (T *)(::operator new((size_t)(size * sizeof(T))));
    if (tmp == 0) {
        ZLOGE("out of memory");
        exit(1);
    }
    ZLOGD("allocate sucessfully, %p", tmp);
    return tmp;
}

template <class T>
INLINE void _deallocate(T* buffer)
{
    ::operator delete(buffer);
}

template <class T1, class T2>
INLINE void _construct(T1* p,const T2& value) 
{
    new(p) T1(value); //placement new. invoke ctor of T1; 不申请内存，构造对象
}

template <class T>
INLINE void _destory(T* ptr)
{
    ptr->~T();
}

template <class T>
class allocator {
public:
    typedef T         value_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    struct rebind
    {
        typedef allocator<U> other;
    };

    pointer allocate(size_type n, const void* hint=0)
    {
        ZLOGD("allocat size=[%ld]", n);
        return _allocate((difference_type)(n), (pointer)(0));
    }

    void deallocate(pointer p, size_type n)
    {
        ZLOGD("deallocate size=[%ld]", n);
        _deallocate(p);
    }

    void construct(pointer p, const T& value)
    {
        ZLOGD("construct");
        _construct(p, value);
    }

    void destory(pointer p)
    {
        ZLOGD("destory");
        _destory(p);
    }

    pointer address(reference x)
    {
        return (pointer)(&x);
    }

    const_pointer const_address(const_reference x)
    {
        return (const_pointer)(&x);
    }

    size_type max_size() const
    {
        return size_type(UINT_MAX / sizeof(T));
    }

};

/*********************************************************************************
    将alloctor传进容器时，可能的步骤
    1. alloctor构造，这时去申请内存，返回的alloctor类似的指针，大小为实际size
    2. 执行placement构造，这时不额外申请内存，单纯构造对象
    3. 当当前size不满足push后的大小时，会释放之前的内存
*********************************************************************************/

} // namespace ZAV
#endif // end of _Z_ALLOCATOR_H

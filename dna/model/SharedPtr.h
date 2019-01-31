//
// Created by mlevin on 12/6/18.
//

#ifndef SMARTPTR_SHAREDPTR_H
#define SMARTPTR_SHAREDPTR_H

#include <cstddef>
#include <iostream>

#ifdef TESTING
#define PRINT(X)(std::cout << X << std::endl)
#else
#define PRINT(X)
#endif

template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr = NULL);
    SharedPtr(SharedPtr const&);
    template <typename U>
    friend class SharedPtr;
    template <typename U>

    SharedPtr(SharedPtr<U> const& s){
        PRINT("SharedPtr :: COPY CTOR FOR INHERITANCE");
        m_ptr = s.m_ptr;
        m_counter = s.m_counter;
        ++ *m_counter;
    }

    ~SharedPtr();

    T* operator->() const;
    T& operator*()  const;
    operator bool() const;

    SharedPtr& operator=(SharedPtr const&);
    SharedPtr& operator= (T* other);

    bool operator==(SharedPtr const&);
    bool operator!=(SharedPtr const&);

    T* get() const;
    size_t getCounter() const ;

private:
    size_t* m_counter;
    T*      m_ptr;

    void release();
    void swap(SharedPtr& other);
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
{
    PRINT("SharedPtr :: CTOR");
    m_counter = new size_t;
    *m_counter = 1;
    m_ptr = ptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr const& other)
{
    PRINT("SharedPtr :: COPY CTOR");
    m_ptr = other.get();
    m_counter = other.m_counter;
    ++ *m_counter;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if(*m_counter > 1)
    {
        -- *m_counter;
        PRINT("SharedPtr :: DTOR - not deleted");
    }
    else
    {
        PRINT("SharedPtr :: DTOR - deleted");
        delete m_counter;
        delete m_ptr;
    }
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    if(m_ptr)
        return true;
    return false;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    SharedPtr<T> copyOfMe(other);
    swap(copyOfMe);
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(T* other)
{
    release();
    m_ptr = other;
    m_counter = new size_t(1);
    return *this;
}

template <typename T>
bool SharedPtr<T>::operator==(SharedPtr const& other)
{
    return m_ptr == other.get();
}

template <typename T>
bool SharedPtr<T>::operator!=(SharedPtr const& other)
{
    return m_ptr != other.get();
}

template <typename T>
T* SharedPtr<T>::get() const
{
    return m_ptr;
}

template <typename T>
size_t SharedPtr<T>::getCounter() const
{
    return *m_counter;
}


template<typename T>
void SharedPtr<T>::release()
{
    --(*m_counter);
    if (*m_counter == 0)
    {
        delete (m_ptr);
        delete (m_counter);
    }
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr<T>& other)
{
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_counter, other.m_counter);
}

#endif //SMARTPTR_SHAREDPTR_H

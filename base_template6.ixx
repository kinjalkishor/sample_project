//#include <memory>
//#include <vector>
#include "base_def.h"
#include "base_iostream.h"
#include "base_debug.h"

#include <limits>
#include <algorithm>
#include <type_traits>

export module base_template6;

import base_def;

export namespace ft
{

template<class T>
void element_construct(T* ptr) { new (ptr) T(); }
template<class T>
void element_copy_construct(T* ptr, const T& value) { new (ptr) T(value); }
template<class T>
void element_destruct(T* ptr) { ptr->~T(); }


template<class T>
class IAllocator
{
    virtual T* allocate(size_t cnt) = 0;
    virtual void deallocate(T* ptr) = 0;
};

template<class T>
class SysAlloc : public IAllocator<T>
{
public:	
	T* allocate(size_t cnt) { return scast<T*>(malloc(cnt* sizeof(T))); }	
	void deallocate(T* ptr) { free(ptr); }
};


template<class T>
class vector
{
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    //using size_type       = intsz;
    //using difference_type = ptrdiff_t;

	pointer m_data = nullptr;
	intsz m_size = 0;
    intsz m_capacity = 0;
	SysAlloc<T> m_allocator;

	vector() {}
    virtual ~vector() { clear_memory(); }

	const_reference operator[] (intsz i) const	    { return m_data[i]; }
	reference operator[] (intsz i)				    { return m_data[i]; }

    const_pointer data() const					    { return &m_data[0]; }
	pointer data()								    { return &m_data[0]; }
    const_pointer begin() const					    { return m_data(); }
	pointer begin()								    { return m_data(); }
	const_pointer end() const						{ return m_data() + m_size; }
	pointer end()									{ return m_data() + m_size; }	

    intsz size() const          { return m_size; }
	intsz capacity() const      { return m_capacity; }	
    
    bool empty() { return scast<bool>(m_size); }

    void clear_memory() 
    {
		if (m_data) 
        {       
            for (intsz i=0; i<m_size; ++i) { element_destruct(&m_data[i]); }
            m_allocator.deallocate(m_data);
            m_data = nullptr; 
        }        
        m_size = 0;
        m_capacity = 0;
    }

    bool check_range(intsz index) { if (index < 0 || index >= std::numeric_limits<intsz>::max()) { return false; } }

    void reserve_exact(intsz new_capacity)
    {
        q_assert(check_range(new_capacity));

        if (capacity() == new_capacity) { return; }

        if (new_capacity == 0) { clear_memory(); return; }

        // Allocate new memory block till new capacity
        pointer new_vec = m_allocator.allocate(new_capacity);

        if (!empty())
        {
            intsz curr_size = size();
            // Construct elements till old size in new vector
            for (intsz i=0; i<curr_size; ++i) { element_construct(&new_vec[i]); }

            // Copy old elements till old size in new vector
            for (intsz i=0; i<curr_size; ++i) { new_vec[i] = m_data[i]; }
            //std::copy(m_data, m_data + m_size, new_vec); 

            // Destruct old elements till old size in old vector
            for (intsz i=0; i<curr_size; ++i) { element_destruct(&m_data[i]); }
        }

        // Dellocate old memory block
        m_allocator.deallocate(m_data);
        // Point data to new memory block
        m_data = new_vec;
        new_vec = nullptr;

        // No change in size
        // Set new capacity
        m_capacity = new_capacity;
        
    }

    void resize_exact(intsz new_size)
    {
        q_assert(check_range(new_size));

        if (size() == new_size) { return; }

        if (new_size == 0) { clear_memory(); return; }

        const intsz new_capacity = new_size;
        // Allocate new memory block till new capacity
        pointer new_vec = m_allocator.allocate(new_capacity);

        if (!empty())
        {
            const intsz curr_size = size();
            intsz copy_size = 0;

            if(curr_size < new_size) 
            {
                // size < new_size
                copy_size = curr_size;
            } 
            else 
            {
                // size > new_size. Drop extra elemnts.
                copy_size = new_size;
            }


            // Construct elements till new size in new vector
            for (intsz i=0; i<new_size; ++i) { element_construct(&new_vec[i]); }

            // Copy old elements till copy size in new vector
            for (intsz i=0; i<copy_size; ++i) { new_vec[i] = m_data[i]; }
            //std::copy(m_data, m_data + m_size, new_vec); 

            // Destruct old elements till old size in old vector
            for (intsz i=0; i<curr_size; ++i) { element_destruct(&m_data[i]); }
        }

        // Dellocate old memory block
        m_allocator.deallocate(m_data);
        // Point data to new memory block
        m_data = new_vec;
        new_vec = nullptr;

        // Set new size
        m_size = new_size;
        // Set new capacity
        m_capacity = new_capacity;
        
    }



};


template<class T>
void vec_print_sc(vector<T> a) { print("{}, {}\n", a.size(), a.capacity()); }



}
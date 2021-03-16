#pragma once

#include "base_logger.h"
#include <vector>

//#define TRACK
class iw
{
public:
    int e=0;
    iw() { 
#ifdef TRACK
        gout << "iw consructor called" << sdf; 
#endif
    }
    ~iw() { 
        e=0;
#ifdef TRACK
        gout << "iw destructor called" << sdf; 
#endif
    }  
    iw(int i) : e(i) { 
#ifdef TRACK
        gout << "iw consructor_i called" << sdf; 
#endif
    }
    iw(const iw& v) : e(v.e) { 
#ifdef TRACK
        gout << "iw consructor_cpy called" << sdf; 
#endif
    }
    operator int() { return e; }
    //iw& operator = (int i) { e = i; }
};


//---------------------------------
#include "base_ft_def.h"
namespace ft
{

template<class T>
void element_construct(T* ptr) { new (ptr) T(); }
template<class T>
void element_construct(T* ptr, const T& value) { new (ptr) T(value); }
template<class T>
void element_destruct(T* ptr) { ptr->~T(); }

//template<class T>
//class memory_resource2
//{
//public:
//    virtual ~memory_resource2() {}
//    virtual T* allocate(size_t cnt) { return scast<T*>(malloc(cnt * sizeof(T))); }	
//	virtual void deallocate(T* ptr) { free(ptr); }
//};

class memory_resource
{
public:
    virtual ~memory_resource() {}
    virtual void* allocate(size_t size_bytes) { return malloc(size_bytes); }	
	virtual void deallocate(void* ptr) { free(ptr); }
};

class memory_resource_d : public memory_resource
{
public:
    virtual ~memory_resource_d() {}
    virtual void* allocate(size_t size_bytes) { gout << "memory_resource_d: allocate" << sdf; return malloc(size_bytes); }	
	virtual void deallocate(void* ptr) { gout << "memory_resource_d: deallocate" << sdf; free(ptr); }
};

static memory_resource gs_allocator;

// wrap void* memory_resource in typesafe template
template<class T>
class polymorphic_allocator 
{
private:
    memory_resource* m_resource = &gs_allocator; 

public:
    polymorphic_allocator() = default;

    polymorphic_allocator(memory_resource* resource)
    : m_resource{resource} { q_assert2(resource, "Cannot initialize polymorphic_allocator with null resource"); }

    polymorphic_allocator(const polymorphic_allocator&) = default;

    template<class T>
    polymorphic_allocator(const polymorphic_allocator<T>& other)
    : m_resource{other.m_resource} {} 

    polymorphic_allocator* operator= (const polymorphic_allocator* other) { this = other; }

    T* allocate(const size_t count) {
        T* vp = static_cast<T*>(m_resource->allocate(count * sizeof(T)));
        return vp;
    }

    void deallocate(T* const ptr) {
        m_resource->deallocate(ptr);
    }
};

template<class T>
class vector
{
public:    
    T* m_data = nullptr;
	isize m_size = 0;
    isize m_capacity = 0;
    //memory_resource2<T> ms_allocator;
    //memory_resource2<T>* m_allocator = &ms_allocator;
    //memory_resource ms_allocator; memory_resource* m_allocator = &ms_allocator;
    //memory_resource* m_allocator = nullptr;    //&gs_allocator;
    polymorphic_allocator<T> m_allocator;

    vector() {}
    vector(memory_resource& allocator) { m_allocator = &allocator; }
    virtual ~vector() { delete_data(); }

    const T* data() const					{ return m_data; }
	T* data()								{ return m_data; }
    const T& operator[] (isize i) const	    { return m_data[i]; }
	T& operator[] (isize i)				    { return m_data[i]; }
    const T* begin() const					{ return m_data; }
	T* begin()								{ return m_data; }
	const T* end() const					{ return m_data + m_size; }
	T* end()								{ return m_data + m_size; }	
    isize size() const          { return m_size; }
	isize capacity() const      { return m_capacity; }	
    
    void delete_data()
	{ 
		if (m_data) 
        {       
            for (isize i=0; i<m_size; ++i) { element_destruct(&m_data[i]); }
            m_allocator.deallocate(m_data);
            m_data = nullptr; 
        }        
        m_size = 0;
        m_capacity = 0;
	}

    bool is_valid_index(isize i) const { return (i>=0 && i<m_size); }
    bool is_capacity_increase_needed(isize new_capacity) const { return (new_capacity > m_capacity); }
    isize get_next_alloc_size(isize new_size) const { return calculate_growth1_5(new_size, m_capacity); }


    void resize_or_reserve_exact(isize new_alloc_capacity, isize new_alloc_size, bool is_resize)
    {
        if (is_resize) {
            gout << "vector resize_exact: " << new_alloc_capacity << sdf; 
        } else {
            gout << "vector reserve_exact: " << new_alloc_capacity << sdf; 
        }

		isize old_size = m_size;
		if (is_resize) { m_size = new_alloc_size;}

		// Allocate new memory block till new capacity
        T* temp = m_allocator.allocate(new_alloc_capacity);
        //T* temp = scast<T*>(m_allocator->allocate(new_alloc_capacity * sizeof(T)));
        // Construct elements till new size
        for (isize i=0; i<m_size; ++i) { element_construct(&temp[i]); }
        
        // Copy old elements till old size
        for (isize i=0; i<old_size; ++i) { temp[i] = m_data[i]; }
        //std::copy(m_data, m_data + m_size, temp);        

        // Destruct old elements till old size
        for (isize i=0; i<old_size; ++i) { element_destruct(&m_data[i]); }
		// Dellocate old memory block
        m_allocator.deallocate(m_data);
        
        // Set new capacity
        m_capacity = new_alloc_capacity;

        // Point data to new memory block
        m_data = temp;
        temp = nullptr;
    }

    void resize_exact(isize new_alloc_capacity, isize new_alloc_size) {
		resize_or_reserve_exact(new_alloc_capacity, new_alloc_size, true);
	}

	void reserve_exact(isize new_alloc_capacity) {
		resize_or_reserve_exact(new_alloc_capacity, m_size, false);
	}

    void resize(isize new_alloc_size)
	{
        //ft::validate_index(new_alloc_size, m_size);
		isize new_capacity = new_alloc_size;
		// Do not decrease capacity
		if (!is_capacity_increase_needed(new_capacity)) 
		{ 
			// Destruct extra old elements
			for (isize i=new_alloc_size; i<m_size; ++i) { m_allocator->destruct(&m_data[i]); }
			// Change size only
			m_size = new_alloc_size; 
			return; 
		}

		new_capacity = get_next_alloc_size(new_capacity);
		//gout << new_alloc_size << qcs << new_capacity << sdf;		

		resize_exact(new_capacity, new_alloc_size);
	}

	void shrink_to_fit() {
		if (m_size < capacity()) { resize_exact(m_size, m_size); }
	}

	void reserve(isize new_alloc_size)
	{
		//ft::validate_index(new_alloc_size, m_size);
		isize new_capacity = new_alloc_size;
		// Do not resize to smaller size
		if (!is_capacity_increase_needed(new_capacity)) { return; }

		new_capacity = get_next_alloc_size(new_capacity);
		//gout << new_alloc_size << qcs << new_capacity << sdf;		

		reserve_exact(new_capacity);
	}

	void push_back(const T& value)
	{
		isize new_size = m_size + 1;
		if (is_capacity_increase_needed(new_size)) { reserve(new_size); }
        // Last element
        //element_construct(&m_data[new_size-1]); m_data[new_size-1] = value;
		element_construct(&m_data[new_size-1], value);        
		m_size = new_size;
	}

    void pop_back()
    {
        if (m_size > 0)
        {            
            element_destruct(&m_data[m_size-1]);
            m_size--;
        }
    }


    const T& at(isize pos) const
    {
        if (!is_valid_index(pos)) {
            gout << __FUNCTION__ ": access at invalid index" << sdf;
            throw std::out_of_range("vector access at invalid index");            
        }
        return m_data[pos];
    }

    T& at(isize pos)
    {
        if (!is_valid_index(pos)) {
            gout << __FUNCTION__ ": access at invalid index" << sdf;
            throw std::out_of_range("vector access at invalid index");                    
        }
        return m_data[pos];
    }
    
    void erase(isize start, isize end) 
    {
        if (end > start) {
            isize num = end -start;
            for (isize i=start; i<size(); ++i) {
                m_data[i] = m_data[i+num];
            }
            for (isize i=m_size-num; i<size(); ++i) { 
                element_destruct(&m_data[i]);
            }
            m_size = m_size-num;
        }
    }

    void clear() { 
        for (isize i=0; i<m_size; ++i) { element_destruct(&m_data[i]); m_size = 0; } 
    }

    //bool is_empty() { return (size() == 0); }
};



template<class T>
bool is_empty(const vector<T>& v) { return (v.size() == 0); }

template<class T>
void cf_print_sc(const vector<T>& v) { gout << "size: " << v.size() << ", capacity: " << v.capacity() << sdf; }
template<class T>
void cf_print_all(const vector<T>& v) { 
    if (is_empty(v)) { gout << "vector is empty" << sdf; }
    else { for (isize i=0; i<v.size(); ++i) { gout << v[i] << sdf; } }
}

template<class T>
void cf_print_sc(const std::pmr::vector<T>& v) { gout << "size: " << v.size() << ", capacity: " << v.capacity() << sdf; }
template<class T>
void cf_print_all(const std::pmr::vector<T>& v) { 
    if (v.empty()) { gout << "vector is empty" << sdf; }
    else { for (isize i=0; i<v.size(); ++i) { gout << v[i] << sdf; } }
}

}


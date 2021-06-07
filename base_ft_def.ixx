#include <limits>

export module base_ft_def;


import base_def;


export namespace ft 
{
template<class T>
bool inrange(const T& x, const T& min_val, const T& max_val)
{
	if ((x < min_val) || (x >= max_val)) { return false; }
	return true;
}


inline void validate_index(intsz& i, intsz max_size) { flib::clamp<intsz>(i, 0, max_size); }

//gcc
// Called by _M_fill_insert, _M_insert_aux etc.
//intsz _M_check_len(intsz __n, const char* __s)
//{
//    if (max_size() - size() < __n)
//    __throw_length_error(__N(__s));

//    const intsz __len = size() + (std::max)(size(), __n);
//    return (__len < size() || __len > max_size()) ? max_size() : __len;
//}

inline intsz calculate_growth1_5(intsz new_size, intsz old_capacity)
{
    // given old_capacity and new_size, calculate geometric growth
    //const intsz old_capacity = capacity();
    constexpr intsz max = std::numeric_limits<intsz>::max();

    if (old_capacity > max - old_capacity/2) 
	{
        return max; // geometric growth would overflow
    }

    const intsz geometric = old_capacity + old_capacity/2;

    if (geometric < new_size)
	{
        return new_size; // geometric growth would be insufficient
    }

    return geometric; // geometric growth is sufficient
}

inline intsz calculate_growthi(intsz new_size, intsz old_capacity, intsz growth_factor)
{
    // given old_capacity and new_size, calculate geometric growth
    //const intsz old_capacity = capacity();
    constexpr intsz max = std::numeric_limits<intsz>::max();

    if (old_capacity > max - old_capacity/2) 
	{
        return max; // geometric growth would overflow
    }

    const intsz geometric = old_capacity*growth_factor;

    if (geometric < new_size)
	{
        return new_size; // geometric growth would be insufficient
    }

    return geometric; // geometric growth is sufficient
}
	
#if 0
inline intsz calculate_growthf(intsz new_size, intsz old_capacity, double gowth_factor)
{
    // given old_capacity and new_size, calculate geometric growth
    //const intsz old_capacity = capacity();
    const intsz max = std::numeric_limits<intsz>::max();

    if (old_capacity > max - old_capacity/2) 
	{
        return max; // geometric growth would overflow
    }

    const double geometric = old_capacity*gowth_factor;

    if (geometric < new_size)
	{
        return new_size; // geometric growth would be insufficient
    }

    return scast<intsz>(std::ceil(geometric)); // geometric growth is sufficient
}
#endif

}

export namespace ft
{

template<class T>
class IAllocator
{
public:
    virtual ~IAllocator() {}
	void construct(T* ptr) { new (ptr) T(); }
	void destruct(T* ptr) { ptr->~T(); }
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

}



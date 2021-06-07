#include "base_def.h"
#include "base_debug.h"

export module base_math_arrayfunc;


import base_def;
import base_math;

export namespace flib
{

//#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
//#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
//#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
//#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
//#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
//#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
//
//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//#define GetRValue(rgb)      (LOBYTE(rgb))
//#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

constexpr float GF_COLOR_1_255		= scast<float>(0.00392156862745098039);		//1.0/255.0

inline void uint32_to_fcolor(float& f1, float& f2, float& f3, float& f4, uint32 uc)
{
	f1 = GF_COLOR_1_255 * (float) (uint8) (uc >> 24);
	f2 = GF_COLOR_1_255 * (float) (uint8) (uc >> 16);
	f3 = GF_COLOR_1_255 * (float) (uint8) (uc >>  8);
	f4 = GF_COLOR_1_255 * (float) (uint8) (uc >>  0);
}

inline uint32 fcolor_to_uint32(float f1, float f2, float f3, float f4)
{
	uint32 ur = f1 >= 1.0f ? 0xff : f1 <= 0.0f ? 0x00 : (uint32) (f1 * 255.0f + 0.5f);
	uint32 ug = f2 >= 1.0f ? 0xff : f2 <= 0.0f ? 0x00 : (uint32) (f2 * 255.0f + 0.5f);
	uint32 ub = f3 >= 1.0f ? 0xff : f3 <= 0.0f ? 0x00 : (uint32) (f3 * 255.0f + 0.5f);
	uint32 ua = f4 >= 1.0f ? 0xff : f4 <= 0.0f ? 0x00 : (uint32) (f4 * 255.0f + 0.5f);

	return ((ur << 24) | (ug << 16) | (ub << 8) | ua);
}

#if 0
//check for f > 1 and f < 0
uint32 ColorBytes3(float r, float g, float b)
{
	uint32        i;

	((uint8 *) & i)[0] = r * 255;
	((uint8 *) & i)[1] = g * 255;
	((uint8 *) & i)[2] = b * 255;

	return i;
}

uint32 ColorBytes4(float r, float g, float b, float a)
{
	uint32        i;

	((uint8 *) & i)[0] = r * 255;
	((uint8 *) & i)[1] = g * 255;
	((uint8 *) & i)[2] = b * 255;
	((uint8 *) & i)[3] = a * 255;

	return i;
}
#endif

} //flib


export namespace gm
{

//========================================================================================================================
// Vector Array functions
//========================================================================================================================
constexpr int k_arr_float_precision = 6;

// 1d array element index from row and column position. assumes matrix in row major order same as C and C++ multi dimensional arrays
inline int arr_erc(int row, int col, int num_col) { return ((row*4) + col); } 

inline void arr_negate(float* out, const float* a, int arr_len)  { forloopi(i, arr_len) { out[i] = -a[i]; } }
inline void arr_add(float* out, const float* a, const float* b, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] + b[i]; } }
inline void arr_sub(float* out, const float* a, const float* b, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] - b[i]; } }
inline void arr_mul(float* out, const float* a, const float* b, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] * b[i]; } }
inline void arr_div(float* out, const float* a, const float* b, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] / b[i]; } }
inline void arr_add_s(float* out, const float* a, float s, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] + s; } }
inline void arr_sub_s(float* out, const float* a, float s, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] - s; } }
inline void arr_mul_s(float* out, const float* a, float s, int arr_len) { forloopi(i, arr_len) { out[i] = a[i] * s; } }
inline void arr_div_s(float* out, const float* a, float s, int arr_len) { float inv_s = scast<float>(1)/s; forloopi(i, arr_len) { out[i] = a[i] * inv_s; } }
inline bool arr_is_equal(const float* a, const float* b, int arr_len) { forloopi(i, arr_len) { if (!(a[i] == b[i])) { return false; } }	return true; }
inline bool arr_is_equal_ep(const float* a, const float* b, float epsilon, int arr_len) { forloopi(i, arr_len) { if (!(mf::equals(a[i], b[i], epsilon))) { return false; } }	return true; }
inline bool arr_is_not_equal(const float* a, const float* b, int arr_len) { return !(arr_is_equal(a, b, arr_len)); }
inline bool arr_is_not_equal_ep(const float* a, const float* b, float epsilon, int arr_len) { return !(arr_is_equal_ep(a, b, epsilon, arr_len)); }
inline bool arr_is_greater(const float* a, const float* b, int arr_len)			{ forloopi(i, arr_len) { if (!(a[i] > b[i])) { return false; } }		return true; }
inline bool arr_is_less(const float* a, const float* b, int arr_len)			{ forloopi(i, arr_len) { if (!(a[i] < b[i])) { return false; } }		return true; }
inline bool arr_is_greater_equal(const float* a, const float* b, int arr_len)	{ forloopi(i, arr_len) { if (!(a[i] >= b[i])) { return false; } }	return true; }
inline bool arr_is_less_equal(const float* a, const float* b, int arr_len)		{ forloopi(i, arr_len) { if (!(a[i] <= b[i])) { return false; } }	return true; }	

//#include <cstdio>
//export const char* to_str(const vec3& a) {
//    char buffer[512];
//    sprintf(buffer, "%.6f, %.6f, %.6f", a.x, a.y, a.z);
//    return buffer;
//}

//---
//#include <iostream>
// errors
//inline std::ostream& operator << (std::ostream& o, const vec3& a)
//{
//    o << std::format("{:.6f}, {:.6f}, {:.6f},", a.x, a.y, a.z);
//    return o;
//}

//export void vec3_print(const vec3& a) {
//    std::cout << a.x << ", " << a.y << ", " << a.z << "\n"; 
//}
//---
//inline std::ostream& arr_print(std::ostream& o, const float* a, int arr_len)
//{
//	std::ostringstream os; 
//	os << std::setprecision(k_arr_float_precision) << std::fixed; 
//	forloopi(i, arr_len) { os << a[i] << qcs; } 
//	o << os.str();
//	return o;
//}

//inline std::ostream& arr_print_rc(std::ostream& o, const float* a, int num_arr_row, int num_arr_col)
//{
//	std::ostringstream os; 
//	os << std::setprecision(k_arr_float_precision) << std::fixed; 
//
//	forloopi(i, num_arr_row) 
//	{ 
//		//forloopi(j, num_arr_col) { os << a.r[i][j] << qcs; }
//		//forloopi(j, num_arr_col) { os << a[i + (num_arr_col*j)] << qcs; }
//		forloopi(j, num_arr_col) { os << a[arr_erc(i, j, num_arr_col)] << qcs; }
//		os << "\n";
//	}
//
//	o << os.str(); 
//	return o;
//}

inline float arr_dot(const float* a, const float* b, int arr_len) 
{
	//a.x*b.x + a.y*b.y + a.z*b.z

	float t = scast<float>(0);
	forloopi(i, arr_len)
	{
		t += a[i] * b[i];
	}
	return t;
}

inline float arr_length_sq(const float* a, int arr_len) 
{
	//a.x*a.x + a.y*a.y + a.z*a.z
	//return arr_dot(a, a);

	float t = scast<float>(0);
	forloopi(i, arr_len)
	{
		t += a[i] * a[i];
	}
	return t;
}

inline float arr_length(const float* a, int arr_len) 
{ 
	return mf::sqrt(arr_length_sq(a, arr_len)); 
}


inline void arr_lerp(float* out, const float* a, const float* b, float s, int arr_len)
{
	forloopi(i, arr_len)
	{
		out[i] = mf::lerp(a[i], b[i], s);
	}
}

inline void arr_minf(float* out, const float* a, const float* b, int arr_len)
{
	forloopi(i, arr_len)
	{
		out[i] = flib::minf(a[i], b[i]);
	}
}


inline void arr_maxf(float* out, const float* a, const float* b, int arr_len)
{
	forloopi(i, arr_len)
	{
		out[i] = flib::maxf(a[i], b[i]);
	}
}

inline void arr_clamp(float* out, const float* min, const float* max, int arr_len)
{
	forloopi(i, arr_len)
	{
		flib::clamp(out[i], min[i], max[i]);
	}
}

// Passing zero vector will make length or norm 0, and divide by zero exception will occur
// for a zero vector this will let the zero vector remain zero
// for zero length vector or if length is too small it is x/0 (infinity). Should throw exception or return NaN.
// check norm with epsilon, as for zero or too small vector length will approach infinity
inline void arr_normalize(float* out, const float* a, int arr_len)
{
	float norm, inv_norm;
	norm = arr_length(a, arr_len);

	if (norm)
	{
		inv_norm = scast<float>(1)/norm;

		forloopi(i, arr_len)
		{
			out[i] = a[i] * inv_norm;
		}
	}
	else 
	{
		// t is already zero. If t is used error will propogate
		//t = vec3::k_zero();	
		q_debug("Cannot normalize zero length vector.\n");
	}
		
	//return norm;
}

// v - end points
// t - tangent directions at end points
// s (alpha) - distance along spline
// cubic interpolation
inline void arr_hermite(float* out, const float* v1, const float* t1, const float* v2, const float* t2, float s, int arr_len)
{
    float h1, h2, h3, h4;

    //set_hermite_coeffcients(h1, h2, h3, h4, s);

    float s3 = mf::cube(s);
	float s2 = mf::square(s); 

    //h1 = (2.0f * s*s*s) - (3.0f * s*s) + 1.0f;
    //h2 = (s*s*s) - (2.0f * s*s) + s;
    //h3 = -(2.0f * s*s*s) + (3.0f * s*s);
    //h4 = (s*s*s) - (s*s);

    h1 = (scast<float>(2) * s3) - (scast<float>(3) * s2) + scast<float>(1);
    h2 = (s3) - (scast<float>(2) * s2) + s;
    h3 = (-scast<float>(2) * s3) + (scast<float>(3) * s2);
    h4 = (s3) - (s2);    

    forloopi(i, arr_len)
    {
        out[i] = h1 * v1[i] + h2 * t1[i] + h3 * v2[i] + h4 * t2[i];
    }
}


inline void arr_catmull_rom(float* out, const float* v0, const float* v1, const float* v2, const float* v3, float s, int arr_len)
{
    float s3 = mf::cube(s);
	float s2 = mf::square(s); 

    forloopi(i, arr_len)
    {
        out[i] = scast<float>(0.5) * (scast<float>(2) * v1[i] + (v2[i] - v0[i]) * s + (scast<float>(2) * v0[i] - scast<float>(5) * v1[i] 
            + scast<float>(4) * v2[i] - v3[i]) * s2 + (v3[i] -scast<float>(3) * v2[i] + scast<float>(3) * v1[i] - v0[i]) * s3);
    }
}


inline void arr_bary_centric(float* out, const float* v1, const float* v2, const float* v3, float f, float g, int arr_len)
{
    forloopi(i, arr_len)
    {
        out[i] = (scast<float>(1)-f-g) * v1[i] + f * v2[i] + g * v3[i];
    }
}


//------------------------------------

inline void arr_mul_matrix(float* out, const float* a, const float* b, int r1, int c1, int r2, int c2)
{ 
	//if (c1!=r2) { q_debug_log("Error: column of first matrix not equal to row of second.\n"); }

	// for square matrix
	//const int& c = c1;
	//forloopi(i, r1) 
	//{ 
	//	forloopi(j, c) 
	//	{ 
	//		float sum = 0; 
	//		forloopi(n, 4) { sum += a[arr_erc(i, n, c)] * b[arr_erc(n, j, c)]; }
	//		out[arr_erc(i, j, c)] = sum; 
	//	} 
	//}	

	forloopi(i, r1)
	{
        forloopi(j, c2)
		{
            forloopi(k, c1)
            {
                //out[i][j] += a[i][k] * b[k][j];
				out[arr_erc(i, j, c1)] += a[arr_erc(i, k, c1)] * b[arr_erc(k, j, c1)];
            }
		}
	}
}

inline void arr_transpose_matrix(float* out, const float* a, int row, int col)
{
	const int& c = col;
	forloopi(i, row) 
	{ 
		forloopi(j, c) 
		{ 
			out[arr_erc(i, j, c)] = a[arr_erc(j, i, c)];
		} 
	}
}

} //gm
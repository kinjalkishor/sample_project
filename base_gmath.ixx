#include "base_def.h"
#include "base_debug.h"
#include <format>
#include "base_iostream.h"

export module base_gmath;

import base_def;
import base_math;
import base_math_arrayfunc;


export namespace gm
{

//===================================================================================
// All classes are POD data types having
// constructor, destructor, copy constructor, assignment, move constructor, move assignment = default;	

class viewport
{
public:
    float x;
    float y;
    float w;
    float h;
    float zn;
    float zf;
};



//========================================================================================================================
// Vectors
//========================================================================================================================


//---------------------------------------------------------
inline const vec2 k_vec2_zero = vec2(scast<float>(0));
inline const vec2 k_vec2_one = vec2(scast<float>(1));

vec2 operator - (const vec2& a)  { vec2 t = k_vec2_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

vec2 operator + (const vec2& a, const vec2& b) { vec2 t = k_vec2_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
vec2 operator - (const vec2& a, const vec2& b) { vec2 t = k_vec2_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
vec2 operator * (const vec2& a, const vec2& b) { vec2 t = k_vec2_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
vec2 operator / (const vec2& a, const vec2& b) { vec2 t = k_vec2_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

vec2 operator + (const vec2& a, float s) { vec2 t = k_vec2_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
vec2 operator - (const vec2& a, float s) { vec2 t = k_vec2_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
vec2 operator * (const vec2& a, float s) { vec2 t = k_vec2_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
vec2 operator / (const vec2& a, float s) { vec2 t = k_vec2_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

vec2 operator + (float s, const vec2& a) { return (a + s); }
vec2 operator - (float s, const vec2& a) { return (a - s); }
vec2 operator * (float s, const vec2& a) { return (a * s); }
vec2 operator / (float s, const vec2& a) { return (a / s); }

bool vec2_equals(const vec2& a, const vec2& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool vec2_equals_ep(const vec2& a, const vec2& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const vec2& a, const vec2& b) { return vec2_equals(a, b); }
bool operator != (const vec2& a, const vec2& b) { return !(a == b); }

bool operator > (const vec2& a, const vec2& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const vec2& a, const vec2& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const vec2& a, const vec2& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const vec2& a, const vec2& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }




//-------------------------
// POD types
//print("gm::vec3 is is_trivial: {}\n", std::is_trivial<gm::vec3>::value);
//print("gm::vec3 is is_standard_layout: {}\n", std::is_standard_layout<gm::vec3>::value);

inline const vec3 k_vec3_zero = vec3(scast<float>(0));
inline const vec3 k_vec3_one = vec3(scast<float>(1));
inline const vec3 k_vec3_origin = vec3(scast<float>(0));

vec3 operator - (const vec3& a)  { vec3 t = k_vec3_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

vec3 operator + (const vec3& a, const vec3& b) { vec3 t = k_vec3_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
vec3 operator - (const vec3& a, const vec3& b) { vec3 t = k_vec3_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
vec3 operator * (const vec3& a, const vec3& b) { vec3 t = k_vec3_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
vec3 operator / (const vec3& a, const vec3& b) { vec3 t = k_vec3_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

vec3 operator + (const vec3& a, float s) { vec3 t = k_vec3_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
vec3 operator - (const vec3& a, float s) { vec3 t = k_vec3_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
vec3 operator * (const vec3& a, float s) { vec3 t = k_vec3_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
vec3 operator / (const vec3& a, float s) { vec3 t = k_vec3_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

vec3 operator + (float s, const vec3& a) { return (a + s); }
vec3 operator - (float s, const vec3& a) { return (a - s); }
vec3 operator * (float s, const vec3& a) { return (a * s); }
vec3 operator / (float s, const vec3& a) { return (a / s); }

bool vec3_equals(const vec3& a, const vec3& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool vec3_equals_ep(const vec3& a, const vec3& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const vec3& a, const vec3& b) { return vec3_equals(a, b); }
bool operator != (const vec3& a, const vec3& b) { return !(a == b); }

bool operator > (const vec3& a, const vec3& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const vec3& a, const vec3& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const vec3& a, const vec3& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const vec3& a, const vec3& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }




//-------------------------
inline const vec4 k_vec4_zero = vec4(scast<float>(0));
inline const vec4 k_vec4_one = vec4(scast<float>(1));

vec4 operator - (const vec4& a)  { vec4 t = k_vec4_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

vec4 operator + (const vec4& a, const vec4& b) { vec4 t = k_vec4_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
vec4 operator - (const vec4& a, const vec4& b) { vec4 t = k_vec4_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
vec4 operator * (const vec4& a, const vec4& b) { vec4 t = k_vec4_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
vec4 operator / (const vec4& a, const vec4& b) { vec4 t = k_vec4_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

vec4 operator + (const vec4& a, float s) { vec4 t = k_vec4_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
vec4 operator - (const vec4& a, float s) { vec4 t = k_vec4_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
vec4 operator * (const vec4& a, float s) { vec4 t = k_vec4_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
vec4 operator / (const vec4& a, float s) { vec4 t = k_vec4_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

vec4 operator + (float s, const vec4& a) { return (a + s); }
vec4 operator - (float s, const vec4& a) { return (a - s); }
vec4 operator * (float s, const vec4& a) { return (a * s); }
vec4 operator / (float s, const vec4& a) { return (a / s); }

bool vec4_equals(const vec4& a, const vec4& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool vec4_equals_ep(const vec4& a, const vec4& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const vec4& a, const vec4& b) { return vec4_equals(a, b); }
bool operator != (const vec4& a, const vec4& b) { return !(a == b); }

bool operator > (const vec4& a, const vec4& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const vec4& a, const vec4& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const vec4& a, const vec4& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const vec4& a, const vec4& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }



//-----------------------------

inline const colorf k_colorf_zero = colorf(scast<float>(0));

colorf operator - (const colorf& a)  { colorf t = k_colorf_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

colorf operator + (const colorf& a, const colorf& b) { colorf t = k_colorf_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
colorf operator - (const colorf& a, const colorf& b) { colorf t = k_colorf_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
colorf operator * (const colorf& a, const colorf& b) { colorf t = k_colorf_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
colorf operator / (const colorf& a, const colorf& b) { colorf t = k_colorf_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

colorf operator + (const colorf& a, float s) { colorf t = k_colorf_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
colorf operator - (const colorf& a, float s) { colorf t = k_colorf_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
colorf operator * (const colorf& a, float s) { colorf t = k_colorf_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
colorf operator / (const colorf& a, float s) { colorf t = k_colorf_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

colorf operator + (float s, const colorf& a) { return (a + s); }
colorf operator - (float s, const colorf& a) { return (a - s); }
colorf operator * (float s, const colorf& a) { return (a * s); }
colorf operator / (float s, const colorf& a) { return (a / s); }

bool colorf_equals(const colorf& a, const colorf& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool colorf_equals_ep(const colorf& a, const colorf& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const colorf& a, const colorf& b) { return colorf_equals(a, b); }
bool operator != (const colorf& a, const colorf& b) { return !(a == b); }

bool operator > (const colorf& a, const colorf& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const colorf& a, const colorf& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const colorf& a, const colorf& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const colorf& a, const colorf& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }



//========================================================================================================================
// Matrix
//========================================================================================================================
#if 0
// column major matrix: math books, opengl: coumn major data is stored internally in memory in row major form
class mat4cm
{
public:
	union
    {
		// input matrix values in column major form like
		// { m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 }
		struct 
		{ 
			float m00, m10, m20, m30,
				 m01, m11, m21, m31,
				 m02, m12, m22, m32,
				 m03, m13, m23, m33;
		};

		float e[16];

		float r[4][4];
	};

	constexpr int size() const	{ return 16; }	
	constexpr int dim() const	{ return 4; }	



	mat4cm() = default;
	~mat4cm() = default;
	mat4cm(const base& a) = default;
	base& operator = (const base& a) = default;
	mat4cm(base&& a) noexcept = default;
	base& operator = (base&& a) noexcept = default;	


	//tmat4cm( float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33 ) 
	//	:   m00(m00), m10(m10), m20(m20), m30(m30), m01(m01), m11(m11), m21(m21), m31(m31), m02(m02), m12(m12), m22(m22), m32(m32), m03(m03), m13(m13), m23(m23), m33(m33) {}	

	// Multiplying in reverse order like in glsl and glm, for vec4*mat4 and mat4*vec4 interchange the functions definitions
	// This gives result of b * a, when you pre-multiply like (mb * ma) in source code you get result of ma * mb (as done in post-multiply)
	//friend base operator * (const base& a, const base& b)	
	//{ 
	//	base t = k_zero();
	//	forloopi(j, dim()) { forloopi(i, dim()) { float sum = 0; forloopi(n, t.dim()) { sum += a.r[n][i] * b.r[j][n]; } t.r[j][i] = sum; } }
	//	return t;
	//}
};
#endif

class mat2
{
public:
	union
    {
		float e[4];
		float r[2][2];
	};

	constexpr int size() const	{ return 4; }	
	constexpr int dim() const	{ return 2; }	

	mat2() = default;

	//mat4() : e { {scast<float>(0)}, {scast<float>(0)},
	//			 {scast<float>(0)}, {scast<float>(0)}, } {}

	explicit mat2(float f) : e { {f}, {f},
								 {f}, {f}, } {}

	mat2(float m00, float m01, float m10, float m11) 
		:   
		e { {m00}, {m01},
			{m10}, {m11}, } {}	

	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }
};

class mat3
{
public:
	union
    {
		float e[9];
		float r[3][3];
	};

	constexpr int size() const	{ return 9; }	
	constexpr int dim() const	{ return 3; }	

	mat3() = default;

	//mat3()  :
	//	m00(scast<float>(0)),	m01(scast<float>(0)),	m02(scast<float>(0)),
	//	m10(scast<float>(0)),	m11(scast<float>(0)),	m12(scast<float>(0)),
	//	m20(scast<float>(0)),	m21(scast<float>(0)),	m22(scast<float>(0)) {}

	explicit mat3(float f) : e { {f}, {f}, {f},
								 {f}, {f}, {f},
								 {f}, {f}, {f}, } {}

	mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) 
		:   
		e { {m00}, {m01}, {m02},
			{m10}, {m11}, {m12},
			{m20}, {m21}, {m22}, } {}	

	mat3(const float* arr)			{ q_assert(arr); forloopi(i, size()) { (*this)[i] = arr[i]; } }	

	
	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }
};

inline const mat3 k_mat3_zero = mat3(scast<float>(0));
inline const mat3 k_mat3_identity = mat3(scast<float>(1));


//======================================================================================================================
//======================================================================================================================
// row major matrix: d3d
// input matrix values in row major form like
// { m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 }
class mat4
{
public:
	union
    {
		float e[16];
		float r[4][4];
	};

	constexpr int size() const	{ return 16; }	
	constexpr int dim() const	{ return 4; }	

	mat4() = default;

	//mat4() : e { {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)},
	//			 {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)},
	//			 {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)},
	//			 {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)}, {scast<float>(0)}, } {}


	// can make identity by: mat4 a(1.0f);
	explicit mat4(float f) : e { {f}, {f}, {f}, {f},
								 {f}, {f}, {f}, {f},
								 {f}, {f}, {f}, {f},
								 {f}, {f}, {f}, {f}, } {}


	mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) 
		:   
		e { {m00}, {m01}, {m02}, {m03},
			{m10}, {m11}, {m12}, {m13},
			{m20}, {m21}, {m22}, {m23},
			{m30}, {m31}, {m32}, {m33}, } {}		


	mat4(const float* arr)			{ q_assert(arr); forloopi(i, size()) { (*this)[i] = arr[i]; } }	

	
	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }

	//------------------------------------------
	////const float& operator() (int row, int col) const { return e[(row*4) + col]; }	//if only get function is desired
	//float& operator() (int row, int col) { return e[(row*4) + col]; }
	//float operator() (int row, int col) const { return e[(row*4) + col]; }
};

inline const mat4 k_mat4_zero = mat4(scast<float>(0));
inline const mat4 k_mat4_identity = mat4(scast<float>(1));


mat4 operator - (const mat4& a)  { mat4 t = k_mat4_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

mat4 operator + (const mat4& a, const mat4& b) { mat4 t = k_mat4_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
mat4 operator - (const mat4& a, const mat4& b) { mat4 t = k_mat4_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }



// Multiplying in forward order like d3d
// for row order matrix storage
// The result represents the transformation B followed by the transformation A. (result = A * B)
// T(R(S(v))) = v*S*R*T = v*SRT
#if 0
mat4 operator * (const mat4& a, const mat4& b)	
{ 
	mat4 t = k_mat4_zero;
	//forloopi(j, dim()) { forloopi(i, dim()) { float sum = 0; forloopi(n, dim()) { sum += b.r[n][i] * a.r[j][n]; } t.r[j][i] = sum; } }
	forloopi(i, a.dim()) { forloopi(j, a.dim()) { t.r[i][j] = a.r[i][0] * b.r[0][j] + a.r[i][1] * b.r[1][j] + a.r[i][2] * b.r[2][j] + a.r[i][3] * b.r[3][j]; } }
	return t;
}
#else

mat4 operator * (const mat4& a, const mat4& b)	
{ 
	mat4 t = k_mat4_zero;
	arr_mul_matrix(t.data(), a.data(), b.data(), a.dim(), a.dim(), a.dim(), a.dim());
	return t;
}
#endif


mat4 operator + (const mat4& a, float s) { mat4 t = k_mat4_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
mat4 operator - (const mat4& a, float s) { mat4 t = k_mat4_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
mat4 operator * (const mat4& a, float s) { mat4 t = k_mat4_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
mat4 operator / (const mat4& a, float s) { mat4 t = k_mat4_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

mat4 operator + (float s, const mat4& a) { return (a + s); }
mat4 operator - (float s, const mat4& a) { return (a - s); }
mat4 operator * (float s, const mat4& a) { return (a * s); }
mat4 operator / (float s, const mat4& a) { return (a / s); }

bool mat4_equals(const mat4& a, const mat4& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool mat4_equals_ep(const mat4& a, const mat4& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const mat4& a, const mat4& b) { return mat4_equals(a, b); }
bool operator != (const mat4& a, const mat4& b) { return !(a == b); }

bool operator > (const mat4& a, const mat4& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const mat4& a, const mat4& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const mat4& a, const mat4& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const mat4& a, const mat4& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }



//=================================================================================
//=================================================================================
//-----------------------
// Quaternion class for representing rotations.
// It provides cheap combinations and avoids gimbal locks. Also useful for interpolations. 
class quat
{
public:
	union
    {
		struct 
		{ 
			vec3 axis;			// (x, y, z) axis about which a rotation will occur, imaginary part
			float rotation;		// (w) amount of rotation which will occur about this axis, real part
		};

		// (x, y, z, w)
		struct { float x, y, z, w; };
		float e[4];        
    };	

	constexpr int size() const { return 4; }	

	quat() = default;
	//quat() : x(scast<float>(0)), y(scast<float>(0)), z(scast<float>(0)), w(scast<float>(0)) {}
	explicit quat(float f) : x(f), y(f), z(f), w(f) {}	
	quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}	

	quat(const vec3& axis, float rotation) : axis(axis), rotation(rotation) {}

	// Constructor which converts euler angles (radians) to a quaternion
	quat(float x, float y, float z) : x(x), y(y), z(z), w(scast<float>(1)) {}	
	quat(const vec3& a) : x(a.x), y(a.y), z(a.z), w(scast<float>(1)) {}

	
	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }

	//base& operator *= (const base& a) { (*this) = (*this) * a; return (*this); }
};

inline const quat k_quat_zero = quat(scast<float>(0));
// (0, 0, 0, 1)
inline const quat k_quat_identity = quat(scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(1));


quat operator - (const quat& a)  { quat t = k_quat_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

quat operator + (const quat& a, const quat& b) { quat t = k_quat_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
quat operator - (const quat& a, const quat& b) { quat t = k_quat_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
//quat operator * (const quat& a, const quat& b) { quat t = k_quat_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
//quat operator / (const quat& a, const quat& b) { quat t = k_quat_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

quat operator + (const quat& a, float s) { quat t = k_quat_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
quat operator - (const quat& a, float s) { quat t = k_quat_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
quat operator * (const quat& a, float s) { quat t = k_quat_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
quat operator / (const quat& a, float s) { quat t = k_quat_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

quat operator + (float s, const quat& a) { return (a + s); }
quat operator - (float s, const quat& a) { return (a - s); }
quat operator * (float s, const quat& a) { return (a * s); }
quat operator / (float s, const quat& a) { return (a / s); }

bool quat_equals(const quat& a, const quat& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool quat_equals_ep(const quat& a, const quat& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const quat& a, const quat& b) { return quat_equals(a, b); }
bool operator != (const quat& a, const quat& b) { return !(a == b); }

bool operator > (const quat& a, const quat& b)	{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const quat& a, const quat& b)	{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const quat& a, const quat& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const quat& a, const quat& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }


// Quaternion multiplication. The result represents the rotation b followed by the rotation a. (out = b * a)
quat operator * (const quat& a, const quat& b) 
{ 
	quat t = k_quat_zero;		
	t.x = (b.w * a.x) + (b.x * a.w) + (b.y * a.z) - (b.z * a.y);
	t.y = (b.w * a.y) - (b.x * a.z) + (b.y * a.w) + (b.z * a.x);
	t.z = (b.w * a.z) + (b.x * a.y) - (b.y * a.x) + (b.z * a.w);
	t.w = (b.w * a.w) - (b.x * a.x) - (b.y * a.y) - (b.z * a.z);	
	return t; 
}

quat quat_mul(const quat& a, const quat& b)
{
    return (a * b);
}



//=================================================================================
class plane
{
public:
	union
    {		
		struct 
		{ 
			vec3 normal;	// (a, b, c) Normal vector of the plane
			float dist;		// (d) distance of the plane normal (from origin)
		};

		struct { float a, b, c, d; };
		float e[4];        
    };	

	constexpr int size() const { return 4; }	

	plane() = default;
	//plane() : a(scast<float>(0)), b(scast<float>(0)), c(scast<float>(0)), d(scast<float>(0)) {}
	explicit plane(float f) : a(f), b(f), c(f), d(f) {}	
	plane(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}	

	plane(const vec3& normal, float dist) : normal(normal), dist(dist) {}

	//float recalculate_dist(const vec3& point) { return -vec3_dot(point, (*this).normal); }
	//static const base k_default()	{ return base(scast<float>(0), scast<float>(1), scast<float>(0), 
	//	-vec3_dot(k_vec3_zero(), vec3(scast<float>(0), scast<float>(1), scast<float>(0)))); }		
	//plane(float a, float b, float c) : a(a), b(b), c(c) { d = recalculate_dist(vec3(a, b, c)); }	

	
	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }
};

inline const plane k_plane_zero = plane(scast<float>(0));


plane operator - (const plane& a)  { plane t = k_plane_zero;		arr_negate(t.data(), a.data(), a.size());	return t; }

//plane operator + (const plane& a, const plane& b) { plane t = k_plane_zero;	arr_add(t.data(), a.data(), b.data(), a.size());	return t; }
//plane operator - (const plane& a, const plane& b) { plane t = k_plane_zero;	arr_sub(t.data(), a.data(), b.data(), a.size());	return t; }
//plane operator * (const plane& a, const plane& b) { plane t = k_plane_zero;	arr_mul(t.data(), a.data(), b.data(), a.size());	return t; }
//plane operator / (const plane& a, const plane& b) { plane t = k_plane_zero;	arr_div(t.data(), a.data(), b.data(), a.size());	return t; }

plane operator + (const plane& a, float s) { plane t = k_plane_zero;	arr_add_s(t.data(), a.data(), s, a.size());		return t; }
plane operator - (const plane& a, float s) { plane t = k_plane_zero;	arr_sub_s(t.data(), a.data(), s, a.size());		return t; }
plane operator * (const plane& a, float s) { plane t = k_plane_zero;	arr_mul_s(t.data(), a.data(), s, a.size());		return t; }
plane operator / (const plane& a, float s) { plane t = k_plane_zero;	arr_div_s(t.data(), a.data(), s, a.size());		return t; }

plane operator + (float s, const plane& a) { return (a + s); }
plane operator - (float s, const plane& a) { return (a - s); }
plane operator * (float s, const plane& a) { return (a * s); }
plane operator / (float s, const plane& a) { return (a / s); }

bool plane_equals(const plane& a, const plane& b) { return arr_is_equal(a.data(), b.data(), a.size()); }
bool plane_equals_ep(const plane& a, const plane& b, float epsilon) { return arr_is_equal_ep(a.data(), b.data(), epsilon, a.size()); }

bool operator == (const plane& a, const plane& b) { return plane_equals(a, b); }
bool operator != (const plane& a, const plane& b) { return !(a == b); }

bool operator > (const plane& a, const plane& b)		{ return arr_is_greater(a.data(), b.data(), a.size()); }
bool operator < (const plane& a, const plane& b)		{ return arr_is_less(a.data(), b.data(), a.size()); }
bool operator >= (const plane& a, const plane& b)	{ return arr_is_greater_equal(a.data(), b.data(), a.size()); }
bool operator <= (const plane& a, const plane& b)	{ return arr_is_less_equal(a.data(), b.data(), a.size()); }


//====================================================================
//------------------------------------------------------------------
// Functions
//------------------------------------------------------------------


//---------------------------------------------------
// vec2
//---------------------------------------------------
vec2 vec2_add(const vec2& a, const vec2& b)
{
	return (a + b);
}

vec2 vec2_sub(const vec2& a, const vec2& b)
{
	return (a - b);
}


float vec2_dot(const vec2& a, const vec2& b)
{
	return arr_dot(a.data(), b.data(), a.size());
}


float vec2_length_sq(const vec2& a) 
{ 
	return arr_length_sq(a.data(), a.size());
}	

float vec2_length(const vec2& a) 
{ 
	return arr_length(a.data(), a.size());
}


vec2 vec2_scale(const vec2& a, float s)
{
	return (a * s);
}

vec2 vec2_lerp(const vec2& a, const vec2& b, float s)
{
	vec2 t = k_vec2_zero;
	arr_lerp(t.data(), a.data(), b.data(), s, a.size());
	return t;
}


vec2 vec2_minf(const vec2& a, const vec2& b)
{
	vec2 t = k_vec2_zero;
	arr_minf(t.data(), a.data(), b.data(), a.size());
	return t;
}

vec2 vec2_maxf(const vec2& a, const vec2& b)
{
	vec2 t = k_vec2_zero;
	arr_maxf(t.data(), a.data(), b.data(), a.size());
	return t;
}


vec2 vec3_normalize(const vec2& a)
{
	vec2 t = k_vec2_zero;
	arr_normalize(t.data(), a.data(), a.size());
	return t;
}


float vec2_ccw(const vec2& a, const vec2& b)
{
    return (a.x*b.y - a.y*b.x);
}

//---------------------------------------------------
// vec3
//---------------------------------------------------

vec3 vec3_add(const vec3& a, const vec3& b)
{
	return (a + b);
}

vec3 vec3_sub(const vec3& a, const vec3& b)
{
	return (a - b);
}

//vec3 vec3_mul(const vec3& a, const vec3& b)
//{
//	return (a * b);
//}
//
//vec3 vec3_div(const vec3& a, const vec3& b)
//{
//	return (a / b);
//}



float vec3_dot(const vec3& a, const vec3& b)
{
	return arr_dot(a.data(), b.data(), a.size());
}

float vec3_length_sq(const vec3& a) 
{ 
	return arr_length_sq(a.data(), a.size());
}	

// vector length, magnitude
float vec3_length(const vec3& a) 
{ 
	return arr_length(a.data(), a.size());
}


// Linear interpolation. V1 + s(V2-V1)
vec3 vec3_lerp(const vec3& a, const vec3& b, float s)
{
	vec3 t = k_vec3_zero;
	arr_lerp(t.data(), a.data(), b.data(), s, a.size());
	return t;
}

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
vec3 vec3_minf(const vec3& a, const vec3& b)
{
	vec3 t = k_vec3_zero;
	arr_minf(t.data(), a.data(), b.data(), a.size());
	return t;
}

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
vec3 vec3_maxf(const vec3& a, const vec3& b)
{
	vec3 t = k_vec3_zero;
	arr_maxf(t.data(), a.data(), b.data(), a.size());
	return t;
}

vec3 vec3_normalize(const vec3& a)
{
	vec3 t = k_vec3_zero;
	arr_normalize(t.data(), a.data(), a.size());
	return t;
}


vec3 vec3_cross(const vec3& a, const vec3& b)
{
	vec3 t = k_vec3_zero;

	t[0] = a.y*b.z - a.z*b.y;
	t[1] = a.z*b.x - a.x*b.z;
	t[2] = a.x*b.y - a.y*b.x;

	//t[0] = a[1]*b[2] - a[2]*b[1];
	//t[1] = a[2]*b[0] - a[0]*b[2];
	//t[2] = a[0]*b[1] - a[1]*b[0];

	return t;
}
//---

vec3 vec3_negate(const vec3& a)
{
	return -a;
}

vec3 vec3_clamp(vec3& a, const vec3& min, const vec3& max)
{
	arr_clamp(a.data(), min.data(), max.data(), a.size());
}


//---------------------------------------------------
// vec4
//---------------------------------------------------


vec4 vec4_add(const vec4& a, const vec4& b)
{
	return (a + b);
}

vec4 vec4_sub(const vec4& a, const vec4& b)
{
	return (a - b);
}


float vec4_dot(const vec4& a, const vec4& b)
{
	return arr_dot(a.data(), b.data(), a.size());
}


float vec4_length_sq(const vec4& a) 
{ 
	return arr_length_sq(a.data(), a.size());
}	

float vec4_length(const vec4& a) 
{ 
	return arr_length(a.data(), a.size());
}


vec4 vec4_scale(const vec4& a, float s)
{
	return (a * s);
}

vec4 vec4_lerp(const vec4& a, const vec4& b, float s)
{
	vec4 t = k_vec4_zero;
	arr_lerp(t.data(), a.data(), b.data(), s, a.size());
	return t;
}


vec4 vec4_minf(const vec4& a, const vec4& b)
{
	vec4 t = k_vec4_zero;
	arr_minf(t.data(), a.data(), b.data(), a.size());
	return t;
}

vec4 vec4_maxf(const vec4& a, const vec4& b)
{
	vec4 t = k_vec4_zero;
	arr_maxf(t.data(), a.data(), b.data(), a.size());
	return t;
}


vec4 vec3_normalize(const vec4& a)
{
	vec4 t = k_vec4_zero;
	arr_normalize(t.data(), a.data(), a.size());
	return t;
}


//---------------------------------------------------
// quat
//---------------------------------------------------
quat quat_mul_angles(const quat& a, const quat& b, float s)
{
    quat t = k_quat_zero;
    forloopi(i, a.size())
    {
        t[i] = a[i] + s*b[i];
    }
    return t;
}

quat vec3_to_quat(const vec3& a, float w)
{ 
	return quat(a.x, a.y, a.z, w);
}


float quat_dot(const quat& a, const quat& b)
{
	return arr_dot(a.data(), b.data(), a.size());
}

// Length squared, or "norm"
float quat_length_sq(const quat& a) 
{ 
	return arr_length_sq(a.data(), a.size());
}	

float quat_length(const quat& a) 
{ 
	return arr_length(a.data(), a.size());
}


//void quat_set_identity(quat& a)
//{
//	a = quat::k_identity();
//}
//
//bool quat_is_identity(const quat& a)
//{
//	return (a == quat::k_identity());
//}

// (-x, -y, -z, w)
quat quat_conjugate(const quat& a)
{
	return quat(-a.x, -a.y, -a.z, a.w);
}


//---------------------------------------------------
// plane
//---------------------------------------------------
plane vec3_to_plane(const vec3& a, float d)
{ 
	return plane(a.x, a.y, a.z, d);
}

float plane_dot_vec4(const plane& p, const vec4& a)
{
	// ax + by + cz + dw
    return (p.a*a.x + p.b*a.y + p.c*a.z + p.d*a.w);
}


float plane_dot_coord(const plane& p, const vec3& a)
{
	// ax + by + cz + d
    return (p.a*a.x + p.b*a.y + p.c*a.z + p.d);
}


float plane_dot_normal(const plane& p, const vec3& a)
{
	// ax + by + cz
    return (p.a*a.x + p.b*a.y + p.c*a.z);
}


plane plane_scale(const plane& a, float s)
{
	return (a * s);
}


//---------------------------------------------------
// colorf
//---------------------------------------------------
colorf colorf_from_argb(uint32 uc)
{
	colorf t = k_colorf_zero;
	//const float f = scast<float>(1.0) / scast<float>(255.0);
	//t.r = f * (float) (uint8) (uc >> 16);
	//t.g = f * (float) (uint8) (uc >>  8);
	//t.b = f * (float) (uint8) (uc >>  0);
	//t.a = f * (float) (uint8) (uc >> 24);

	flib::uint32_to_fcolor(t.a, t.r, t.g, t.b, uc);
	return t;
}


colorf colorf_from_rgba(uint32 uc)
{
	colorf t = k_colorf_zero;
	//const float f = scast<float>(1.0) / scast<float>(255.0);
	//t.r = f * (float) (uint8) (uc >> 24);
	//t.g = f * (float) (uint8) (uc >> 16);
	//t.b = f * (float) (uint8) (uc >>  8);
	//t.a = f * (float) (uint8) (uc >>  0);
	flib::uint32_to_fcolor(t.r, t.g, t.b, t.a, uc);
	return t;
}

uint32 argb_from_colorf(const colorf& a)
{
	//uint32 ur = a.r >= 1.0f ? 0xff : a.r <= 0.0f ? 0x00 : (uint32) (a.r * 255.0f + 0.5f);
	//uint32 ug = a.g >= 1.0f ? 0xff : a.g <= 0.0f ? 0x00 : (uint32) (a.g * 255.0f + 0.5f);
	//uint32 ub = a.b >= 1.0f ? 0xff : a.b <= 0.0f ? 0x00 : (uint32) (a.b * 255.0f + 0.5f);
	//uint32 ua = a.a >= 1.0f ? 0xff : a.a <= 0.0f ? 0x00 : (uint32) (a.a * 255.0f + 0.5f);
	//return (ua << 24) | (ur << 16) | (ug << 8) | ub;

	return flib::fcolor_to_uint32(a.a, a.r, a.g ,a.b);
}

uint32 rgba_from_colorf(const colorf& a)
{
	//uint32 ur = a.r >= 1.0f ? 0xff : a.r <= 0.0f ? 0x00 : (uint32) (a.r * 255.0f + 0.5f);
	//uint32 ug = a.g >= 1.0f ? 0xff : a.g <= 0.0f ? 0x00 : (uint32) (a.g * 255.0f + 0.5f);
	//uint32 ub = a.b >= 1.0f ? 0xff : a.b <= 0.0f ? 0x00 : (uint32) (a.b * 255.0f + 0.5f);
	//uint32 ua = a.a >= 1.0f ? 0xff : a.a <= 0.0f ? 0x00 : (uint32) (a.a * 255.0f + 0.5f);
	//return (ur << 24) | (ug << 16) | (ub << 8) | ua;

	return flib::fcolor_to_uint32(a.r, a.g, a.b ,a.a);
}



colorf colorf_add(const colorf& a, const colorf& b)
{
	return (a + b);
}

colorf colorf_sub(const colorf& a, const colorf& b)
{
	return (a - b);
}

colorf colorf_scale(const colorf& a, float s)
{
	return (a * s);
}

colorf colorf_lerp(const colorf& a, const colorf& b, float s)
{
	colorf t = k_colorf_zero;
	arr_lerp(t.data(), a.data(), b.data(), s, a.size());
	return t;
}


// (1-r, 1-g, 1-b, a)
colorf colorf_negative(const colorf& a)
{
    return colorf(scast<float>(1) - a.r, scast<float>(1) - a.g, scast<float>(1) - a.b, a.a);
}

// (r1*r2, g1*g2, b1*b2, a1*a2)
colorf colorf_modulate(const colorf& a, const colorf& b)
{
    return (a * b);
}



//---------------------------------------------------
// mat4
//---------------------------------------------------
mat4 mat4_mul(const mat4& a, const mat4& b)
{
    return (a * b);
}

//void mat4_set_identity(mat4& a)
//{
//	a = k_mat4_identity;
//}

bool mat4_is_identity(const mat4& a)
{
	return (a == k_mat4_identity);
}


mat4 mat4_transpose(const mat4& a)
{
	mat4 t = k_mat4_zero;
	//forloopi(i, a.dim()) { forloopi(j, a.dim()) { t.r[i][j] = a.r[j][i]; } }
	arr_transpose_matrix(t.data(), a.data(), a.dim(), a.dim());
	return t;
}

// Matrix multiplication, followed by a transpose. (result = T(a * b))
mat4 mat4_mul_transpose(const mat4& a, const mat4& b)
{
	//forloopi(i, 4) { forloopi(j, 4) { result.m[j][i] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j]; } }

	return mat4_transpose(a * b);
}


//---------------------------------------------------
//--------------------------
// Hybrid Functions
//--------------------------

vec3 vec2_to_vec3(const vec2& a, float z)
{ 
	return vec3(a.x, a.y, z);
}

vec3 vec4_to_vec3(const vec4& a)
{ 
	return vec3(a.x, a.y, a.z);
}

vec3 quat_to_vec3(const quat& a)
{ 
	return vec3(a.x, a.y, a.z);
}

vec3 plane_to_vec3(const plane& p)
{ 
	return vec3(p.a, p.b, p.c);
}

vec4 vec3_to_vec4(const vec3& a, float w)
{ 
	return vec4(a.x, a.y, a.z, w);
}



//================================================================================================
//------------------------------------------------------------------
// Non Inline Functions
//------------------------------------------------------------------

// Hermite interpolation between position V1, tangent T1 (when s == 0) and position V2, tangent T2 (when s == 1).
vec2 vec2_hermite(const vec2& v1, const vec2& t1, const vec2& v2, const vec2& t2, float s)
{
    vec2 t = k_vec2_zero;
    arr_hermite(t.data(), v1.data(), t1.data(), v2.data(), t2.data(), s, t.size());
    return t;
}


// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
vec2 vec2_catmull_rom(const vec2& v0, const vec2& v1, const vec2& v2, const vec2& v3, float s)
{
    vec2 t = k_vec2_zero;
    arr_catmull_rom(t.data(), v0.data(), v1.data(), v2.data(), v3.data(), s, t.size());
    return t;
}


// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
vec2 vec2_bary_centric(const vec2& v1, const vec2& v2, const vec2& v3, float f, float g)
{
    vec2 t = k_vec2_zero;
    arr_bary_centric(t.data(), v1.data(), v2.data(), v3.data(), f, g, t.size());
    return t;
}



//----------------------

// v - end points
// t - tangent directions at end points
// s (alpha) - distance along spline
// cubic interpolation
// Hermite interpolation between position V1, tangent T1 (when s == 0) and position V2, tangent T2 (when s == 1).
vec3 vec3_hermite(const vec3& v1, const vec3& t1, const vec3& v2, const vec3& t2, float s)
{
    vec3 t = k_vec3_zero;
    arr_hermite(t.data(), v1.data(), t1.data(), v2.data(), t2.data(), s, t.size());
    return t;
}


// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
vec3 vec3_catmull_rom(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3, float s)
{
    vec3 t = k_vec3_zero;
    arr_catmull_rom(t.data(), v0.data(), v1.data(), v2.data(), v3.data(), s, t.size());
    return t;
}


// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
vec3 vec3_bary_centric(const vec3& v1, const vec3& v2, const vec3& v3, float f, float g)
{
    vec3 t = k_vec3_zero;
    arr_bary_centric(t.data(), v1.data(), v2.data(), v3.data(), f, g, t.size());
    return t;
}

//----------------------
// Cross-product in 4 dimensions.
vec4 vec4_cross(const vec4& a, const vec4& b, const vec4& c)
{
    vec4 t = k_vec4_zero;

    t.x = a.y * (b.z * c.w - c.z * b.w) - a.z * (b.y * c.w - c.y * b.w) + a.w * (b.y * c.z - b.z *c.y);
    t.y = -(a.x * (b.z * c.w - c.z * b.w) - a.z * (b.x * c.w - c.x * b.w) + a.w * (b.x * c.z - c.x * b.z));
    t.z = a.x * (b.y * c.w - c.y * b.w) - a.y * (b.x *c.w - c.x * b.w) + a.w * (b.x * c.y - c.x * b.y);
    t.w = -(a.x * (b.y * c.z - c.y * b.z) - a.y * (b.x * c.z - c.x *b.z) + a.z * (b.x * c.y - c.x * b.y));

    return t;
}


// Hermite interpolation between position V1, tangent T1 (when s == 0) and position V2, tangent T2 (when s == 1).
vec4 vec4_hermite(const vec4& v1, const vec4& t1, const vec4& v2, const vec4& t2, float s)
{
    vec4 t = k_vec4_zero;
    arr_hermite(t.data(), v1.data(), t1.data(), v2.data(), t2.data(), s, t.size());
    return t;
}


// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
vec4 vec4_catmull_rom(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3, float s)
{
    vec4 t = k_vec4_zero;
    arr_catmull_rom(t.data(), v0.data(), v1.data(), v2.data(), v3.data(), s, t.size());
    return t;
}


// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
vec4 vec4_bary_centric(const vec4& v1, const vec4& v2, const vec4& v3, float f, float g)
{
    vec4 t = k_vec4_zero;
    arr_bary_centric(t.data(), v1.data(), v2.data(), v3.data(), f, g, t.size());
    return t;
}


//----------------------
// Conjugate and re-norm
quat quat_inverse(const quat& a)
{
    quat t = k_quat_zero;
    float norm;
    float inv_norm;

    norm = quat_length_sq(a);
    inv_norm = scast<float>(1)/norm;

    t.x = -a.x * inv_norm;
    t.y = -a.y * inv_norm;
    t.z = -a.z * inv_norm;
    t.w = a.w * inv_norm;

    return t;
}


quat quat_normalize(const quat& a)
{
    quat t = k_quat_zero;
	arr_normalize(t.data(), a.data(), t.size());
    return t;
}

// A unit quaternion, is defined by:
// Q == (cos(theta), sin(theta) * a) where |a| = 1
// The natural logarithm of Q is, ln(Q) = (0, theta * a)

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * a); ln(q) = (0, theta * a)
quat quat_ln(const quat& a)
{
    quat t = k_quat_zero;
    float tf;

    if ((a.w >= scast<float>(1)) || (a.w == -scast<float>(1)))
    {
        tf = scast<float>(1);
    }
    else
    {
        tf = mf::acos(a.w) / mf::sqrt(scast<float>(1) - a.w*a.w);
    }

    t.x = tf * a.x;
    t.y = tf * a.y;
    t.z = tf * a.z;
    t.w = scast<float>(0);

    return t;
}

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * a); exp(q) = (cos(theta), sin(theta) * a)
quat quat_exp(const quat& a)
{
    quat t = k_quat_identity;
    float norm;
    float inv_norm;

    // only first 3 members used
    norm = mf::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);    

    if (norm)
    {
        inv_norm = scast<float>(1)/norm;
        float snorm = mf::sin(norm);
        float cnorm = mf::cos(norm);

        t.x = snorm * a.x * inv_norm;
        t.y = snorm * a.y * inv_norm;
        t.z = snorm * a.z * inv_norm;
        t.w = cnorm;
    }

    return t;
}
      
// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// s (time)
// Expects unit quaternions.
quat quat_slerp(const quat& a, const quat& b, float s)
{
    const float threshold = 0.001f;
    quat t = k_quat_zero;
	// dot (angle)
    float dot;
    float invs;

    invs = scast<float>(1) - s;
    dot = quat_dot(a, b);

	// make sure we use the short rotation
    if (dot < scast<float>(0))
    {
        s = -s;
        dot = -dot;
    }

	// spherical interpolation
    if (scast<float>(1) - dot > threshold)
    {
        float theta = mf::acos(dot);

        invs = mf::sin(theta * invs) / mf::sin(theta);
        s = mf::sin(theta * s) / mf::sin(theta);
    }
	// else linear interploation (s and invscale set)

    forloopi(i, t.size())
    {
        t[i] = invs * a[i] + s * b[i];
    }

    return t;
}

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, Q4, s), Slerp(Q2, Q3, s), 2s(1-s))
quat quat_squad(const quat& pq1, const quat& pq2, const quat& pq3, const quat& pq4, float s)
{
    quat t = k_quat_zero;
    quat temp1 = quat_slerp(pq1, pq4, s);
    quat temp2 = quat_slerp(pq2, pq3, s);

    t = quat_slerp(temp1, temp2, scast<float>(2) * s * (scast<float>(1) - s));
    return t;
}


// Setup control points for spherical quadrangle interpolation from Q1 to Q2.  
// The control points are chosen in such a way to ensure the continuity of tangents with adjacent segments.
void quat_squad_setup(quat& aout, quat& bout, quat& cout, const quat& pq0, const quat& pq1, const quat& pq2, const quat& pq3)
{
    quat q = k_quat_zero;
    quat temp1 = k_quat_zero;
    quat temp2 = k_quat_zero;
    quat temp3 = k_quat_zero;
    quat tzero = k_quat_zero;


    if (quat_dot(pq0, pq1) < scast<float>(0))
    {
        temp2 = quat_mul_angles(tzero, pq0, -scast<float>(1));
    }
    else
    {
        temp2 = pq0;
    }

    if (quat_dot(pq1, pq2) < scast<float>(0))
    {
        cout = quat_mul_angles(tzero, pq2, -scast<float>(1));
    }
    else
    {
        cout = pq2;
    }

    if (quat_dot(cout, pq3) < scast<float>(0))
    {
        temp3 = quat_mul_angles(tzero, pq3, -scast<float>(1));
    }
    else
    {
        temp3 = pq3;
    }

    temp1 = quat_inverse(pq1);
    temp2 = quat_mul(temp1, temp2);
    temp2 = quat_ln(temp2);
    q = quat_mul(temp1, cout);
    q = quat_ln(q);
    temp1 = quat_mul_angles(temp2, q, scast<float>(1));
    temp1 = temp1 * (-scast<float>(0.25));
    temp1 = quat_exp(temp1);
    aout = quat_mul(pq1, temp1);

    temp1 = quat_inverse(cout);
    temp2 = quat_mul(temp1, pq1);
    temp2 = quat_ln(temp2);
    q = quat_mul(temp1, temp3);
    q = quat_ln(q);
    temp1 = quat_mul_angles(temp2, q, scast<float>(1));
    temp1 = temp1 * (-scast<float>(0.25));
    temp1 = quat_exp(temp1);
    bout = quat_mul(cout, temp1);
}

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
quat quat_bary_centric(const quat& pq1, const quat& pq2, const quat& pq3, float f, float g)
{
    quat t = k_quat_zero;
    quat temp1 = quat_slerp(pq1, pq2, f + g);
    quat temp2 = quat_slerp(pq1, pq3, f+g);

    quat_slerp(temp1, temp2, g/(f + g));
    return t;
}



//----------------------
// Normalize plane (so that |a, b, c| == 1)
plane plane_normalize(const plane& a)
{
    plane t = k_plane_zero;
    float norm;
    float inv_norm;
    // only first 3 members used
    //norm = mf::sqrt(a.a*a.a + a.b*a.b + a.c*a.c);
    norm = vec3_length(a.normal);

    if (norm)
    {
        inv_norm = scast<float>(1)/norm;

        forloopi(i, t.size())
		{
			t[i] = a[i] * inv_norm;
		}
    }
    else
    {
        //t = k_plane_zero();	
		q_debug("Cannot normalize zero length vector.\n");
    }

    return t;
}



//----------------------
// CHECK: Use glm values
// Approximate values for each component's contribution to luminance.
// Based upon the NTSC standard described in ITU-R Recommendation BT.709.
// r = g = b = 0.2125*r + 0.7154*g + 0.0721*b
// Interpolate r,g,b between desaturated color and color.
// DesaturatedColor + s(Color - DesaturatedColor)
colorf colorf_adjust_saturation(const colorf& a, float s)
{
    colorf t = k_colorf_zero;
    const float grey = a.r * scast<float>(0.2125) + a.g * scast<float>(0.7154) + a.b * scast<float>(0.0721);

    t.r = grey + s * (a.r - grey);
    t.g = grey + s * (a.g - grey);
    t.b = grey + s * (a.b - grey);
    t.a = a.a;
    return t;
}


// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
colorf colorf_adjust_contrast(const colorf& a, float s)
{
    colorf t = k_colorf_zero;
    const float factor = scast<float>(0.5);
    
    t.r = factor + s * (a.r - factor);
    t.g = factor + s * (a.g - factor);
    t.b = factor + s * (a.b - factor);
    t.a = a.a;
    return t;
}



//----------------------
#if 0

// D3D Row Major Matrices
// Identity matrix
1, 0, 0, 0
0, 1, 0, 0
0, 0, 1, 0
0, 0, 0, 1

// Matrix Transforms -
// Translate:
1, 	0, 	0, 	0
0, 	1, 	0, 	0
0, 	0, 	1, 	0
tx, ty, tz, 1

// Scale:
sx, 0, 	0, 	0
0, 	sy, 0, 	0
0, 	0, 	sz, 0
0, 	0, 	0, 	1

// Rotate:
// x-axis
1, 	0, 		0, 		0
0, 	cos a, 	sin a, 	0
0, 	-sin a, cos a, 	0
0, 	0, 		0, 		1
// y-axis
cos a, 	0, 	-sin a, 0
0, 		1, 	0, 		0
sin a, 	0, 	cos a, 	0
0, 		0, 	0, 		1
// z-axis
cos a, 	sin a, 	0, 0
-sin a, cos a, 	0, 0
0, 		0, 		1, 0
0, 		0, 		0, 1

// D3D Viewport Transform
// Applications typically set MinZ and MaxZ to 0.0 and 1.0 respectively to 
// cause the system to  render to the entire depth range.
w/2, 		0, 			0, 			0
0, 			-h/2, 		0, 			0
0, 			0, 			maxz-minz, 	0
x + w/2, 	h/2 + y, 	minz, 		1

// ZERO
mat4 t(
        scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(0),
        scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(0),
        scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(0),
        scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(0)
        );

// IDENTITY
mat4 t(
        scast<float>(1), scast<float>(0), scast<float>(0), scast<float>(0),
        scast<float>(0), scast<float>(1), scast<float>(0), scast<float>(0),
        scast<float>(0), scast<float>(0), scast<float>(1), scast<float>(0),
        scast<float>(0), scast<float>(0), scast<float>(0), scast<float>(1)
        );
#endif

// Build a matrix which translates by (tx, ty, tz)
mat4 mat4_translation(float tx, float ty, float tz)
{
    //mat4 t(scast<float>(1));
    //t.r[3][0] = tx;
    //t.r[3][1] = ty;
    //t.r[3][2] = tz;

    mat4 t(
        scast<float>(1),    scast<float>(0),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(1),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(1),    scast<float>(0),
        tx,                 ty,                 tz,                 scast<float>(1)
        );

    return t;
}

mat4 mat4_translation(const vec3& a)
{
    return mat4_translation(a.x, a.y, a.z);
}




// Build a matrix which scales by (sx, sy, sz)
mat4 mat4_scaling(float sx, float sy, float sz)
{
    //mat4 t(scast<float>(1));
    //t.r[0][0] = sx;
    //t.r[1][1] = sy;
    //t.r[2][2] = sz;

    mat4 t(
        sx,                 scast<float>(0),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    sy,                 scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    sz,                 scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(0),    scast<float>(1)
        );

    return t;
}

mat4 mat4_scaling(const vec3& a)
{
    return mat4_scaling(a.x, a.y, a.z);
}





// Build a matrix which rotates around the X axis
mat4 mat4_rotation_x(float angle)
{
    //mat4 t(scast<float>(1));
    //t.r[1][1] = mf::cos(angle);
    //t.r[2][2] = mf::cos(angle);
    //t.r[1][2] = mf::sin(angle);
    //t.r[2][1] = -mf::sin(angle);

    const float sin_a = mf::sin(angle);
    const float cos_a = mf::cos(angle);

    mat4 t(
        scast<float>(1),    scast<float>(0),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    cos_a,              sin_a,              scast<float>(0),
        scast<float>(0),    -sin_a,             cos_a,              scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(0),    scast<float>(1)
        );

    return t;
}

// Build a matrix which rotates around the Y axis
mat4 mat4_rotation_y(float angle)
{
    //mat4 t(scast<float>(1));
    //t.r[0][0] = mf::cos(angle);
    //t.r[2][2] = mf::cos(angle);
    //t.r[0][2] = -mf::sin(angle);
    //t.r[2][0] = mf::sin(angle);

    const float sin_a = mf::sin(angle);
    const float cos_a = mf::cos(angle);

    mat4 t(
        cos_a,              scast<float>(0),    -sin_a,             scast<float>(0),
        scast<float>(0),    scast<float>(1),    scast<float>(0),    scast<float>(0),
        sin_a,              scast<float>(0),    cos_a,              scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(0),    scast<float>(1)
        );

    return t;
}

// Build a matrix which rotates around the Z axis
mat4 mat4_rotation_z(float angle)
{
    //mat4 t(scast<float>(1));
    //t.r[0][0] = mf::cos(angle);
    //t.r[1][1] = mf::cos(angle);
    //t.r[0][1] = mf::sin(angle);
    //t.r[1][0] = -mf::sin(angle);

    const float sin_a = mf::sin(angle);
    const float cos_a = mf::cos(angle);
    
    mat4 t(
        cos_a,              sin_a,              scast<float>(0),    scast<float>(0),
        -sin_a,             cos_a,              scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(1),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(0),    scast<float>(1)
        );

    return t;
}


// Yaw around the Y axis, Pitch around the X axis, Roll around the Z axis.
mat4 mat4_rotation_yaw_pitch_roll(float yaw, float pitch, float roll)
{
    const float sy = mf::sin(yaw);
    const float cy = mf::cos(yaw);
    const float sp = mf::sin(pitch);
    const float cp = mf::cos(pitch);
    const float sr = mf::sin(roll);
    const float cr = mf::cos(roll);    

    //mat4 t;
    //t.r[0][0] = sr*sp*sy + cr*cy;
    //t.r[0][1] = sr*cp;
    //t.r[0][2] = sr*sp*cy - cr*sy;
    //t.r[0][3] = scast<float>(0);
    //t.r[1][0] = cr*sp*sy - sr*cy;
    //t.r[1][1] = cr*cp;
    //t.r[1][2] = cr*sp*cy + sr*sy;
    //t.r[1][3] = scast<float>(0);
    //t.r[2][0] = cp*sy;
    //t.r[2][1] = -sp;
    //t.r[2][2] = cp*cy;
    //t.r[2][3] = scast<float>(0);
    //t.r[3][0] = scast<float>(0);
    //t.r[3][1] = scast<float>(0);
    //t.r[3][2] = scast<float>(0);
    //t.r[3][3] = scast<float>(1);


    mat4 t(
        sr*sp*sy + cr*cy,   sr*cp,              sr*sp*cy - cr*sy,   scast<float>(0),
        cr*sp*sy - sr*cy,   cr*cp,              cr*sp*cy + sr*sy,   scast<float>(0),
        cp*sy,              -sp,                cp*cy,              scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(0),    scast<float>(1)
        );

    return t;
}


//--------------------
float mat4_determinant(const mat4& a)
{
    float ta[3] = {};
    float tb[4] = {};    

    ta[0] = a.r[2][2] * a.r[3][3] - a.r[2][3] * a.r[3][2];
    ta[1] = a.r[1][2] * a.r[3][3] - a.r[1][3] * a.r[3][2];
    ta[2] = a.r[1][2] * a.r[2][3] - a.r[1][3] * a.r[2][2];
    tb[0] = a.r[1][1] * ta[0] - a.r[2][1] * ta[1] + a.r[3][1] * ta[2];
    tb[1] = -a.r[1][0] * ta[0] + a.r[2][0] * ta[1] - a.r[3][0] * ta[2];

    ta[0] = a.r[1][0] * a.r[2][1] - a.r[2][0] * a.r[1][1];
    ta[1] = a.r[1][0] * a.r[3][1] - a.r[3][0] * a.r[1][1];
    ta[2] = a.r[2][0] * a.r[3][1] - a.r[3][0] * a.r[2][1];
    tb[2] = a.r[3][3] * ta[0] - a.r[2][3] * ta[1] + a.r[1][3] * ta[2];
    tb[3] = -a.r[3][2] * ta[0] + a.r[2][2] * ta[1] - a.r[1][2] * ta[2];

    return a.r[0][0] * tb[0] + a.r[0][1] * tb[1] + a.r[0][2] * tb[2] + a.r[0][3] * tb[3];
}



// Calculate inverse of matrix.  Inversion may fail, in which case NULL will be returned.
// The determinant of pM is also returned it pfDeterminant is non-NULL.
//mat4 mat4_inverse(float& pdeterminant, const mat4& pm)
mat4 mat4_inverse(const mat4& a)
{
    mat4 t = k_mat4_zero;    
    float det;
    float ta[3] = {};
    float tb[16] = {};    

    ta[0] = a.r[2][2] * a.r[3][3] - a.r[2][3] * a.r[3][2];
    ta[1] = a.r[1][2] * a.r[3][3] - a.r[1][3] * a.r[3][2];
    ta[2] = a.r[1][2] * a.r[2][3] - a.r[1][3] * a.r[2][2];
    tb[0] = a.r[1][1] * ta[0] - a.r[2][1] * ta[1] + a.r[3][1] * ta[2];
    tb[4] = -a.r[1][0] * ta[0] + a.r[2][0] * ta[1] - a.r[3][0] * ta[2];

    ta[0] = a.r[1][0] * a.r[2][1] - a.r[2][0] * a.r[1][1];
    ta[1] = a.r[1][0] * a.r[3][1] - a.r[3][0] * a.r[1][1];
    ta[2] = a.r[2][0] * a.r[3][1] - a.r[3][0] * a.r[2][1];
    tb[8] = a.r[3][3] * ta[0] - a.r[2][3] * ta[1] + a.r[1][3] * ta[2];
    tb[12] = -a.r[3][2] * ta[0] + a.r[2][2] * ta[1] - a.r[1][2] * ta[2];

    det = a.r[0][0] * tb[0] + a.r[0][1] * tb[4] + a.r[0][2] * tb[8] + a.r[0][3] * tb[12];
   
    if (det == scast<float>(0))
    {
        q_debug("Matrix is not invertible. Zero Matrix returned. Error will propogate.\n");
        return t;
    }
    else
    {
        //hr.set_ok();
    }

    //if (pdeterminant)
    //    *pdeterminant = det;

    ta[0] = a.r[2][2] * a.r[3][3] - a.r[2][3] * a.r[3][2];
    ta[1] = a.r[0][2] * a.r[3][3] - a.r[0][3] * a.r[3][2];
    ta[2] = a.r[0][2] * a.r[2][3] - a.r[0][3] * a.r[2][2];
    tb[1] = -a.r[0][1] * ta[0] + a.r[2][1] * ta[1] - a.r[3][1] * ta[2];
    tb[5] = a.r[0][0] * ta[0] - a.r[2][0] * ta[1] + a.r[3][0] * ta[2];

    ta[0] = a.r[0][0] * a.r[2][1] - a.r[2][0] * a.r[0][1];
    ta[1] = a.r[3][0] * a.r[0][1] - a.r[0][0] * a.r[3][1];
    ta[2] = a.r[2][0] * a.r[3][1] - a.r[3][0] * a.r[2][1];
    tb[9] = -a.r[3][3] * ta[0] - a.r[2][3] * ta[1]- a.r[0][3] * ta[2];
    tb[13] = a.r[3][2] * ta[0] + a.r[2][2] * ta[1] + a.r[0][2] * ta[2];

    ta[0] = a.r[1][2] * a.r[3][3] - a.r[1][3] * a.r[3][2];
    ta[1] = a.r[0][2] * a.r[3][3] - a.r[0][3] * a.r[3][2];
    ta[2] = a.r[0][2] * a.r[1][3] - a.r[0][3] * a.r[1][2];
    tb[2] = a.r[0][1] * ta[0] - a.r[1][1] * ta[1] + a.r[3][1] * ta[2];
    tb[6] = -a.r[0][0] * ta[0] + a.r[1][0] * ta[1] - a.r[3][0] * ta[2];

    ta[0] = a.r[0][0] * a.r[1][1] - a.r[1][0] * a.r[0][1];
    ta[1] = a.r[3][0] * a.r[0][1] - a.r[0][0] * a.r[3][1];
    ta[2] = a.r[1][0] * a.r[3][1] - a.r[3][0] * a.r[1][1];
    tb[10] = a.r[3][3] * ta[0] + a.r[1][3] * ta[1] + a.r[0][3] * ta[2];
    tb[14] = -a.r[3][2] * ta[0] - a.r[1][2] * ta[1] - a.r[0][2] * ta[2];

    ta[0] = a.r[1][2] * a.r[2][3] - a.r[1][3] * a.r[2][2];
    ta[1] = a.r[0][2] * a.r[2][3] - a.r[0][3] * a.r[2][2];
    ta[2] = a.r[0][2] * a.r[1][3] - a.r[0][3] * a.r[1][2];
    tb[3] = -a.r[0][1] * ta[0] + a.r[1][1] * ta[1] - a.r[2][1] * ta[2];
    tb[7] = a.r[0][0] * ta[0] - a.r[1][0] * ta[1] + a.r[2][0] * ta[2];

    tb[11] = -a.r[0][0] * (a.r[1][1] * a.r[2][3] - a.r[1][3] * a.r[2][1]) +
        a.r[1][0] * (a.r[0][1] * a.r[2][3] - a.r[0][3] * a.r[2][1]) -
        a.r[2][0] * (a.r[0][1] * a.r[1][3] - a.r[0][3] * a.r[1][1]);

    tb[15] = a.r[0][0] * (a.r[1][1] * a.r[2][2] - a.r[1][2] * a.r[2][1]) -
        a.r[1][0] * (a.r[0][1] * a.r[2][2] - a.r[0][2] * a.r[2][1]) +
        a.r[2][0] * (a.r[0][1] * a.r[1][2] - a.r[0][2] * a.r[1][1]);

    det = scast<float>(1) / det;

    for (int i = 0; i < a.dim(); i++)
    {
        for (int j = 0; j < a.dim(); j++)
        {
            t.r[i][j] = tb[a.dim() * i + j] * det;
        }
    }

    return t;
}



//-------------------------------------------------------------------------------------------------------
//--------------------------
// Hybrid Functions
//--------------------------

// Transform (x, y, 0, 1) by matrix.
vec4 vec2_transform(const vec2& a, const mat4& ma)
{
    vec4 t = k_vec4_zero;

    forloopi(i, a.size())
    {
        t[i] = ma.r[0][i] * a.x + ma.r[1][i] * a.y  + ma.r[3][i];
    }

    return t;
}


// Transform (x, y, 0, 1) by matrix, project result back into w=1.
vec2 vec2_transform_coord(const vec2& a, const mat4& ma)
{
    vec2 t = k_vec2_zero;
    float norm;
    float inv_norm;

    norm = ma.r[0][3] * a.x + ma.r[1][3] * a.y + ma.r[3][3];
    inv_norm = scast<float>(1)/norm;

    forloopi(i, a.size())
    {
        t[i] = (ma.r[0][i] * a.x + ma.r[1][i] * a.y + ma.r[3][i]) * inv_norm;
    }

    return t;
}


// Transform (x, y, 0, 0) by matrix.
vec2 vec2_transform_normal(const vec2& a, const mat4& ma)
{
    vec2 t = k_vec2_zero;

    forloopi(i, a.size())
    {
        t[i] = ma.r[0][i] * a.x + ma.r[1][i] * a.y;
    }

    return t;
}




//--------------------------
// Transform (x, y, z, 1) by matrix.
vec4 vec3_transform(const vec3& a, const mat4& ma)
{
    vec4 t = k_vec4_zero;

    forloopi(i, a.size())
    {
        t[i] = ma.r[0][i] * a.x + ma.r[1][i] * a.y + ma.r[2][i] * a.z + ma.r[3][i];
    }

    return t;
}

// Transform (x, y, z, 1) by matrix, project result back into w=1.
vec3 vec3_transform_coord(const vec3& a, const mat4& ma)
{
    vec3 t = k_vec3_zero;
    float norm;
    float inv_norm;

    norm = ma.r[0][3] * a.x + ma.r[1][3] * a.y + ma.r[2][3] *a.z + ma.r[3][3];
    inv_norm = scast<float>(1)/norm;

    forloopi(i, a.size())
    {
        t[i] = (ma.r[0][i] * a.x + ma.r[1][i] * a.y + ma.r[2][i] * a.z + ma.r[3][i]) * inv_norm;
    }

    return t;
}

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
vec3 vec3_transform_normal(const vec3& a, const mat4& ma)
{
    vec3 t = k_vec3_zero;

    forloopi(i, a.size())
    {
        t[i] = ma.r[0][i] * a.x + ma.r[1][i] * a.y + ma.r[2][i] * a.z;
    }

    return t;
}    
    



      


//--------------------------
// Transform vector by matrix.
vec4 vec4_transform(const vec4& a, const mat4& ma)
{
    vec4 t = k_vec4_zero;

    forloopi(i, a.size())
    {
        t[i] = ma.r[0][i] * a.x + ma.r[1][i] * a.y + ma.r[2][i] * a.z + ma.r[3][i] * a.w;
    }

    return t;
}
    




//--------------------------
// Yaw around the Y axis, Pitch around the X axis, Roll around the Z axis.
quat quat_rotation_yaw_pitch_roll(float yaw, float pitch, float roll)
{
    quat t = k_quat_zero;

    const float sy = mf::sin(yaw  /scast<float>(2));
    const float cy = mf::cos(yaw / scast<float>(2));
    const float sp = mf::sin(pitch / scast<float>(2));
    const float cp = mf::cos(pitch / scast<float>(2));
    const float sr = mf::sin(roll / scast<float>(2));
    const float cr = mf::cos(roll / scast<float>(2));

    t.x = sy*cp*sr + cy*sp*cr;
    t.y = sy*cp*cr - cy*sp*sr;
    t.z = cy*cp*sr - sy*sp*cr;
    t.w = cy*cp*cr + sy*sp*sr;

    return t;
}

// Compute a quaternian's axis and angle of rotation. Expects unit quaternions.
void quat_to_axis_angle(const quat& q, vec3& axis, float& angle)
{
    axis = quat_to_vec3(q);
    angle = scast<float>(2) * mf::acos(q.w);
}

// Build a quaternion from a rotation matrix.
quat quat_rotation_matrix(const mat4& ma)
{
    quat t = k_quat_zero;
    float s;
    float trace;

    // get scale (trace) from diagonal
    trace = ma.r[0][0] + ma.r[1][1] + ma.r[2][2] + scast<float>(1);
    if (trace > scast<float>(1))
    {
        s = scast<float>(2) * mf::sqrt(trace);
        t.x = (ma.r[1][2] - ma.r[2][1]) / s;
        t.y = (ma.r[2][0] - ma.r[0][2]) / s;
        t.z = (ma.r[0][1] - ma.r[1][0]) / s;
        t.w = scast<float>(0.25) * s;
    }
    else
    {
        int maxi = 0;

        for (int i = 1; i < 3; i++)
        {
            if (ma.r[i][i] > ma.r[maxi][maxi])
            {
                maxi = i;
            }
        }

        switch (maxi)
        {
            case 0:
                s = scast<float>(2) * mf::sqrt(scast<float>(1) + ma.r[0][0] - ma.r[1][1] - ma.r[2][2]);
                t.x = scast<float>(0.25) * s;
                t.y = (ma.r[0][1] + ma.r[1][0]) / s;
                t.z = (ma.r[0][2] + ma.r[2][0]) / s;
                t.w = (ma.r[1][2] - ma.r[2][1]) / s;
                break;

            case 1:
                s = scast<float>(2) * mf::sqrt(scast<float>(1) + ma.r[1][1] - ma.r[0][0] - ma.r[2][2]);
                t.x = (ma.r[0][1] + ma.r[1][0]) / s;
                t.y = scast<float>(0.25) * s;
                t.z = (ma.r[1][2] + ma.r[2][1]) / s;
                t.w = (ma.r[2][0] - ma.r[0][2]) / s;
                break;

            case 2:
                s = scast<float>(2) * mf::sqrt(scast<float>(1) + ma.r[2][2] - ma.r[0][0] - ma.r[1][1]);
                t.x = (ma.r[0][2] + ma.r[2][0]) / s;
                t.y = (ma.r[1][2] + ma.r[2][1]) / s;
                t.z = scast<float>(0.25) * s;
                t.w = (ma.r[0][1] - ma.r[1][0]) / s;
                break;
        }
    }

    return t;
}

// Rotation about arbitrary axis.
quat quat_rotation_axis(const vec3& a, float angle)
{
    quat t = k_quat_zero;
    vec3 temp = vec3_normalize(a);

    const float sha = mf::sin(angle / scast<float>(2));
    const float cha = mf::cos(angle / scast<float>(2));

    t.x = sha * temp.x;
    t.y = sha * temp.y;
    t.z = sha * temp.z;
    t.w = cha;

    return t;
}



//--------------------------
void mat4_decompose(vec3& out_scale, quat& out_rotation, vec3& out_translation, const mat4& ma)
{
    mat4 normalized = k_mat4_zero;
    vec3 tvec = k_vec3_zero;


    // Calculate the scaling part.
    forloopi(i, tvec.size())
    {
        tvec[i] = ma.r[0][i];
    }
    out_scale.x = vec3_length(tvec);

    forloopi(i, tvec.size())
    {
        tvec[i] = ma.r[1][i];
    }
    out_scale.y = vec3_length(tvec);

    forloopi(i, tvec.size())
    {
        tvec[i] = ma.r[2][i];
    }
    out_scale.z = vec3_length(tvec);

    // Calculate the translation part.
    forloopi(i, tvec.size())
    {
        out_translation[i] = ma.r[3][i];
    }

    // Calculate the rotation.
    if ((out_scale.x == scast<float>(0)) || (out_scale.y == scast<float>(0)) || (out_scale.z == scast<float>(0))) 
    {
        q_debug("Cannot Decompose Matrix.\n");
    }
    else
    {
        //hr.set_ok();
    }

    forloopi(i, tvec.size())
    {
        forloopi(j, tvec.size())
        {
            normalized.r[i][j] = ma.r[i][j]/out_scale[i];
        }
    }

    out_rotation = quat_rotation_matrix(normalized);
}


// Build a matrix which rotates around an arbitrary axis
mat4 mat4_rotation_axis(const vec3& a, float angle)
{    
    vec3 nv = vec3_normalize(a);

    const float sa = mf::sin(angle);
    const float ca = mf::cos(angle);
    const float cd = scast<float>(1) - ca;

    //mat4 t = k_mat4_identity;
    //t.r[0][0] = cd*nv.x*nv.x + ca;
    //t.r[1][0] = cd*nv.x*nv.y - sa*nv.z;
    //t.r[2][0] = cd*nv.x*nv.z + sa*nv.y;
    //t.r[3][0] = scast<float>(0);
    //t.r[0][1] = cd*nv.y*nv.x + sa*nv.z;
    //t.r[1][1] = cd*nv.y*nv.y + ca;
    //t.r[2][1] = cd*nv.y*nv.z - sa*nv.x;
    //t.r[3][1] = scast<float>(0);
    //t.r[0][2] = cd*nv.z*nv.x - sa*nv.y;
    //t.r[1][2] = cd*nv.z*nv.y + sa*nv.x;
    //t.r[2][2] = cd*nv.z*nv.z + ca;
    //t.r[3][2] = scast<float>(0);
    //t.r[0][3] = scast<float>(0);
    //t.r[1][3] = scast<float>(0);
    //t.r[2][3] = scast<float>(0);
    //t.r[3][3] = scast<float>(1);

    mat4 t(
        cd*nv.x*nv.x + ca,          cd*nv.y*nv.x + sa*nv.z,     cd*nv.z*nv.x - sa*nv.y,     scast<float>(0),
        cd*nv.x*nv.y - sa*nv.z,     cd*nv.y*nv.y + ca,          cd*nv.z*nv.y + sa*nv.x,     scast<float>(0),
        cd*nv.x*nv.z + sa*nv.y,     cd*nv.y*nv.z - sa*nv.x,     cd*nv.z*nv.z + ca,          scast<float>(0),
        scast<float>(0),            scast<float>(0),            scast<float>(0),            scast<float>(1)
        );

    return t;
}

// Build a matrix from a quaternion
mat4 mat4_rotation_quaternion(const quat& q)
{
    //mat4 t = k_mat4_identity;
    //t.r[0][0] = scast<float>(1) - scast<float>(2)*(q.y*q.y + q.z*q.z);
    //t.r[0][1] = scast<float>(2)*(q.x*q.y + q.z*q.w);
    //t.r[0][2] = scast<float>(2)*(q.x*q.z - q.y*q.w);
    //t.r[1][0] = scast<float>(2)*(q.x*q.y - q.z*q.w);
    //t.r[1][1] = scast<float>(1) - scast<float>(2)*(q.x*q.x + q.z*q.z);
    //t.r[1][2] = scast<float>(2)*(q.y*q.z + q.x*q.w);
    //t.r[2][0] = scast<float>(2)*(q.x*q.z + q.y*q.w);
    //t.r[2][1] = scast<float>(2)*(q.y*q.z - q.x*q.w);
    //t.r[2][2] = scast<float>(1) - scast<float>(2)*(q.x*q.x + q.y*q.y);

    mat4 t(
        scast<float>(1) - scast<float>(2)*(q.y*q.y + q.z*q.z),  scast<float>(2)*(q.x*q.y + q.z*q.w),  
            scast<float>(2)*(q.x*q.z - q.y*q.w),                  scast<float>(0),

        scast<float>(2)*(q.x*q.y - q.z*q.w),                  scast<float>(1) - scast<float>(2)*(q.x*q.x + q.z*q.z), 
            scast<float>(2)*(q.y*q.z + q.x*q.w),                  scast<float>(0),

        scast<float>(2)*(q.x*q.z + q.y*q.w),                  scast<float>(2)*(q.y*q.z - q.x*q.w), 
            scast<float>(1) - scast<float>(2)*(q.x*q.x + q.y*q.y),  scast<float>(0),

        scast<float>(0),                                        scast<float>(0), 
            scast<float>(0),                                        scast<float>(1)
        );

    return t;
}

	
// Build transformation matrix. Pass identity for NULL arguments.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
mat4 mat4_transformation(const vec3& scaling_center, const quat& scaling_rotation, const vec3& scaling, const vec3& rotation_center, const quat& rotation, const vec3& translation)
{
    mat4 t = k_mat4_identity;
    mat4 m1 = k_mat4_identity;
    mat4 m2 = k_mat4_identity;
    mat4 m3 = k_mat4_identity; 
    mat4 m4 = k_mat4_identity; 
    mat4 m5 = k_mat4_identity; 
    mat4 m6 = k_mat4_identity; 
    mat4 m7 = k_mat4_identity;

    quat qrc = k_quat_identity;
    vec3 vsc;
    vec3 vtr;
    
    vsc = scaling_center;
    qrc = vec3_to_quat(rotation_center, scast<float>(1));
    vtr = translation;


    m1 = mat4_translation(-vsc);
    m4 = mat4_rotation_quaternion(scaling_rotation);
    m2 = mat4_inverse(m4);    
    m3 = mat4_scaling(scaling); 
    m6 = mat4_rotation_quaternion(rotation);

    // subtraction and addition of quat and vec3
    m5 = mat4_translation(vsc.x - qrc.x,  vsc.y - qrc.y,  vsc.z - qrc.z);
    m7 = mat4_translation(qrc.x + vtr.x, qrc.y + vtr.y, qrc.z + vtr.z);

    m1 = mat4_mul(m1, m2);
    m1 = mat4_mul(m1, m3);
    m1 = mat4_mul(m1, m4);
    m1 = mat4_mul(m1, m5);
    m1 = mat4_mul(m1, m6);
    t = mat4_mul(m1, m7);

    return t;
}

// Build 2D transformation matrix in XY plane. Pass identity for NULL arguments.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
mat4 mat4_transformation_2d(const vec2& scaling_center, float scaling_rotation, const vec2& scaling, const vec2& rotation_center, float rotation, const vec2& translation)
{
    mat4 t = k_mat4_identity;
    quat qrot = k_quat_zero;
    quat qsrot = k_quat_zero;

    vec3 vs = k_vec3_one; 

    vec3 vrc = k_vec3_zero;     
    vec3 vsc = k_vec3_zero; 
    vec3 vt = k_vec3_zero;


    vsc = vec2_to_vec3(scaling_center, scast<float>(0));
    vs = vec2_to_vec3(scaling, scast<float>(1));
    vrc = vec2_to_vec3(rotation_center, scast<float>(0));
    vt = vec2_to_vec3(translation, scast<float>(0));

    const float hrot = rotation/scast<float>(2);
    const float hsrot = scaling_rotation/scast<float>(2);

    qrot.x = scast<float>(0);
    qrot.y = scast<float>(0);
    qrot.z = mf::sin(hrot);
    qrot.w = mf::cos(hrot);
    
    qsrot.x = scast<float>(0);
    qsrot.y = scast<float>(0);
    qsrot.z = mf::sin(hsrot);
    qsrot.w = mf::cos(hsrot);

    t = mat4_transformation(vsc, qsrot, vs, vrc, qrot, vt);

    return t;
}


// Build affine transformation matrix. Pass identity for NULL arguments.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
mat4 mat4_affine_transformation(float scaling, const vec3& rotation_center, const quat& rotation, const vec3& translation)
{
    mat4 t = k_mat4_identity;

    //if (rotation)
    //{
        float temp00, temp01, temp02, temp10, temp11, temp12, temp20, temp21, temp22;

        temp00 = scast<float>(1) - scast<float>(2)*(rotation.y * rotation.y + rotation.z * rotation.z);
        temp01 = scast<float>(2)*(rotation.x * rotation.y + rotation.z * rotation.w);
        temp02 = scast<float>(2)*(rotation.x * rotation.z - rotation.y * rotation.w);
        temp10 = scast<float>(2)*(rotation.x * rotation.y - rotation.z * rotation.w);
        temp11 = scast<float>(1) - scast<float>(2)*(rotation.x * rotation.x + rotation.z * rotation.z);
        temp12 = scast<float>(2)*(rotation.y * rotation.z + rotation.x * rotation.w);
        temp20 = scast<float>(2)*(rotation.x * rotation.z + rotation.y * rotation.w);
        temp21 = scast<float>(2)*(rotation.y * rotation.z - rotation.x * rotation.w);
        temp22 = scast<float>(1) - scast<float>(2)*(rotation.x * rotation.x + rotation.y * rotation.y);

        t.r[0][0] = scaling * temp00;
        t.r[0][1] = scaling * temp01;
        t.r[0][2] = scaling * temp02;
        t.r[1][0] = scaling * temp10;
        t.r[1][1] = scaling * temp11;
        t.r[1][2] = scaling * temp12;
        t.r[2][0] = scaling * temp20;
        t.r[2][1] = scaling * temp21;
        t.r[2][2] = scaling * temp22;

        //if (rotation_center)
        //{
            t.r[3][0] = rotation_center.x * (scast<float>(1) - temp00) - rotation_center.y * temp10 - rotation_center.z * temp20;
            t.r[3][1] = rotation_center.y * (scast<float>(1) - temp11) - rotation_center.x * temp01 - rotation_center.z * temp21;
            t.r[3][2] = rotation_center.z * (scast<float>(1) - temp22) - rotation_center.x * temp02 - rotation_center.y * temp12;
        //}
    //}
    //else
    //{
    //    t.r[0][0] = scaling;
    //    t.r[1][1] = scaling;
    //    t.r[2][2] = scaling;
    //}

    //if (translation)
    //{
        t.r[3][0] += translation.x;
        t.r[3][1] += translation.y;
        t.r[3][2] += translation.z;
    //}

    return t;
}

// Build 2D affine transformation matrix in XY plane. Pass identity for NULL arguments.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
mat4 mat4_affine_transformation_2d(float scaling, const vec2& rotation_center, float rotation, const vec2& translation)
{
    mat4 t = k_mat4_identity;
    float tmp1, tmp2, s;

    s = mf::sin(rotation / scast<float>(2));
    tmp1 = scast<float>(1) - scast<float>(2)*s*s;
    tmp2 = scast<float>(2)*s*mf::cos(rotation/scast<float>(2));


    t.r[0][0] = scaling * tmp1;
    t.r[0][1] = scaling * tmp2;
    t.r[1][0] = -scaling * tmp2;
    t.r[1][1] = scaling * tmp1;

    //if (rotation_center)
    //{
        t.r[3][0] = rotation_center.y * tmp2    - rotation_center.x * tmp1  + rotation_center.x;
        t.r[3][1] = -rotation_center.x * tmp2   - rotation_center.y * tmp1  + rotation_center.y;
    //}

    //if (translation)
    //{
        t.r[3][0] += translation.x;
        t.r[3][1] += translation.y;
    //}

    return t;
}



//P = normalize(Plane);
//L = Light;
//d = -dot(P, L)    
//P.a * L.x + d  P.a * L.y      P.a * L.z      P.a * L.w  
//P.b * L.x      P.b * L.y + d  P.b * L.z      P.b * L.w  
//P.c * L.x      P.c * L.y      P.c * L.z + d  P.c * L.w  
//P.d * L.x      P.d * L.y      P.d * L.z      P.d * L.w + d

// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light.
mat4 mat4_shadow(const vec4& light, const plane& pa)
{
#if 1
    const plane p = plane_normalize(pa);    
    const vec4& l = light;
    float d = -plane_dot_vec4(p, l);

    mat4 t(
        p.a * l.x + d,  p.a * l.y,      p.a * l.z,      p.a * l.w,  
        p.b * l.x,      p.b * l.y + d,  p.b * l.z,      p.b * l.w,  
        p.c * l.x,      p.c * l.y,      p.c * l.z + d,  p.c * l.w,  
        p.d * l.x,      p.d * l.y,      p.d * l.z,      p.d * l.w + d
    );

#else
    plane norm;
    float dot;
    
    norm = plane_normalize(pa);    
    dot = plane_dot(norm, light);

    //mat4 t = k_mat4_identity;
    //t.r[0][0] = dot - norm.a * light.x;
    //t.r[0][1] = -norm.a * light.y;
    //t.r[0][2] = -norm.a * light.z;
    //t.r[0][3] = -norm.a * light.w;
    //t.r[1][0] = -norm.b * light.x;
    //t.r[1][1] = dot - norm.b * light.y;
    //t.r[1][2] = -norm.b * light.z;
    //t.r[1][3] = -norm.b * light.w;
    //t.r[2][0] = -norm.c * light.x;
    //t.r[2][1] = -norm.c * light.y;
    //t.r[2][2] = dot - norm.c * light.z;
    //t.r[2][3] = -norm.c * light.w;
    //t.r[3][0] = -norm.d * light.x;
    //t.r[3][1] = -norm.d * light.y;
    //t.r[3][2] = -norm.d * light.z;
    //t.r[3][3] = dot - norm.d * light.w;


    mat4 t(
        dot - norm.a * light.x, -norm.a * light.y,      -norm.a * light.z,      -norm.a * light.w,
        -norm.b * light.x,      dot - norm.b * light.y, -norm.b * light.z,      -norm.b * light.w,
        -norm.c * light.x,      -norm.c * light.y,      dot - norm.c * light.z, -norm.c * light.w,
        -norm.d * light.x,      -norm.d * light.y,      -norm.d * light.z,      dot - norm.d * light.w
        );
#endif

    return t;
}


//P = normalize(Plane);    
//-2 * P.a * P.a + 1  -2 * P.b * P.a      -2 * P.c * P.a        0
//-2 * P.a * P.b      -2 * P.b * P.b + 1  -2 * P.c * P.b        0
//-2 * P.a * P.c      -2 * P.b * P.c      -2 * P.c * P.c + 1    0
//-2 * P.a * P.d      -2 * P.b * P.d      -2 * P.c * P.d        1

// Build a matrix which reflects the coordinate system about a plane
mat4 mat4_reflect(const plane& pa)
{
    plane p;
    
    p = plane_normalize(pa);    

#if 1
    //d3dx documentation

    mat4 t(
        -scast<float>(2)*p.a*p.a + scast<float>(1), -scast<float>(2)*p.b*p.a,                 -scast<float>(2)*p.c*p.a,                 scast<float>(0),
        -scast<float>(2)*p.a*p.b,                 -scast<float>(2)*p.b*p.b + scast<float>(1), -scast<float>(2)*p.c*p.b,                 scast<float>(0),
        -scast<float>(2)*p.a*p.c,                 -scast<float>(2)*p.b*p.c,                 -scast<float>(2)*p.c*p.c + scast<float>(1), scast<float>(0),
        -scast<float>(2)*p.a*p.d,                 -scast<float>(2)*p.b*p.d,                 -scast<float>(2)*p.c*p.d,                   scast<float>(1)
        );

#elif 0

    //mat4 t = k_mat4_identity;
    //t.r[0][0] = scast<float>(1) - scast<float>(2)*p.a*p.a;
    //t.r[0][1] = -scast<float>(2)*p.a*p.b;
    //t.r[0][2] = -scast<float>(2)*p.a*p.c;
    //t.r[1][0] = -scast<float>(2)*p.a*p.b;
    //t.r[1][1] = scast<float>(1) - scast<float>(2)*p.b*p.b;
    //t.r[1][2] = -scast<float>(2)*p.b*p.c;
    //t.r[2][0] = -scast<float>(2)*p.c*p.a;
    //t.r[2][1] = -scast<float>(2)*p.c*p.b;
    //t.r[2][2] = scast<float>(1) - scast<float>(2)*p.c*p.c;
    //t.r[3][0] = -scast<float>(2)*p.d*p.a;
    //t.r[3][1] = -scast<float>(2)*p.d*p.b;
    //t.r[3][2] = -scast<float>(2)*p.d*p.c;


    mat4 t(
        scast<float>(1) - scast<float>(2)*p.a*p.a, -scast<float>(2)*p.a*p.b,                -scast<float>(2)*p.a*p.c,                   scast<float>(0),
        -scast<float>(2)*p.a*p.b,                 scast<float>(1) - scast<float>(2)*p.b*p.b, -scast<float>(2)*p.b*p.c,                  scast<float>(0),
        -scast<float>(2)*p.c*p.a,                 -scast<float>(2)*p.c*p.b,                 scast<float>(1) - scast<float>(2)*p.c*p.c,  scast<float>(0),
        -scast<float>(2)*p.d*p.a,                 -scast<float>(2)*p.d*p.b,                 -scast<float>(2)*p.d*p.c,                   scast<float>(1)
        );
#endif

    return t;
}


	
	




//--------------------------
// Find the intersection between a plane and a line.  If the line is parallel to the plane, NULL is returned.
vec3 plane_intersect_line(const plane& p, const vec3& v1, const vec3& v2)
{
    vec3 t = k_vec3_zero;
    vec3 direction = k_vec3_zero;
    vec3 normal = k_vec3_zero;
    float dot, temp;

    normal = p.normal;
    direction = vec3_sub(v2, v1);
    dot = vec3_dot(normal, direction);

    // line is parallel to the plane
    if (!dot) 
    {
        q_debug("Line is parallel to the plane. Line does not intersect the plane.\n");
    }
    else
    {
        //hr.set_ok();
    }

    temp = (p.d + vec3_dot(normal, v1)) / dot;

    forloopi(i, t.size())
    {
        t[i] = v1[i] - temp * direction[i];
    }

    return t;
}

// Construct a plane from a point and a normal
plane vec3_point_normal_to_plane(const vec3& vpoint, const vec3& vnormal)
{
    plane t = k_plane_zero;
    t = vec3_to_plane(vnormal, -vec3_dot(vpoint, vnormal));
    return t;
}

// Construct a plane from 3 points
plane vec3_points_to_plane(const vec3& v1, const vec3& v2, const vec3& v3)
{
    plane t = k_plane_zero;
    vec3 edge1; 
    vec3 edge2; 
    vec3 normal, norm;

    edge1 = vec3_sub(v2, v1);
    edge2 = vec3_sub(v3, v1);
    normal = vec3_cross(edge1, edge2);    
    norm = vec3_normalize(normal);    
    t = vec3_point_normal_to_plane(v1, norm);

    return t;
}

// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
plane plane_transform(const plane& p, const mat4& ma)
{
    plane t = k_plane_zero;

    forloopi(i, t.size())
    {
        t[i] = ma.r[0][i] * p.a + ma.r[1][i] * p.b + ma.r[2][i] * p.c + ma.r[3][i] * p.d;
    }

    return t;
}
    






//--------------------------
// Misc
//--------------------------
//To find the Fresnel term (F):
//If A is angle of incidence and B is the angle of refraction, then
//F = 0.5 * [tan2(A - B) / tan2(A + B) + sin2(A - B) / sin2(A + B)]
//  = 0.5 * sin2(A - B) / sin2(A + B) * [cos2(A + B) / cos2(A - B) + 1]    
//Let r   = sina(A) / sin(B)      (the relative refractive index)
//Let c   = cos(A)
//Let g   = (r2 + c2 - 1)1/2
//Then, expanding using the trig identities and simplifying, you get:
//F = 0.5 * (g + c)2 / (g - c)2 * ([c(g + c) - 1]2 / [c(g - c) + 1]2 + 1)

// Calculate Fresnel term given the cosine of theta (likely obtained by
// taking the dot of two normals), and the refraction index of the material.
float fresnel_term_d3d(float cos_theta, float refraction_index)
{
    float result;

    const float g = mf::sqrt(refraction_index*refraction_index + cos_theta*cos_theta - scast<float>(1));
    const float a = g + cos_theta;
    const float d = g - cos_theta;
    result = (cos_theta * a - scast<float>(1)) * (cos_theta * a - scast<float>(1)) / ((cos_theta * d + scast<float>(1)) * (cos_theta * d + scast<float>(1))) + scast<float>(1);
    result *= scast<float>(0.5) * d * d / (a * a);

    return result;
}



//====================================================================
//--------------------------
// Perspective Projection
//--------------------------

class viewport_gl
{
public:
    float x;
    float y;
    float w;
    float h;  
};


//==================================================================
// GLM
//==================================================================
// For row-major matrices v*m, for column-major matrices m*v
// [x, y, z, w]	*	|m00, m01, m02, m03|
//					|m10, m11, m12, m13|
//					|m20, m21, m22, m23|
//					|m30, m31, m32, m33|

// mul(matrix, vector) = mul(vector, matrix_transposed);
// d3dx: mul(vector, matrix)
vec4 mat4_mul_vec4(const mat4& ma, const vec4& a)
{
	vec4 t = k_vec4_zero;
	forloopi(i, a.size()) 
	{ 
		t.e[i] = a.x*ma.r[0][i] + a.y*ma.r[1][i] + a.z*ma.r[2][i] + a.w*ma.r[3][i];	
	}
	return t;
}

//vec4 mat4_mul_vec4(const vec4& a, const mat4& ma)
//{
//	mat4_mul_vec4(ma, a);
//}

vec4 mat4_mul_vec3(const mat4& ma, const vec3& a)
{
	vec4 temp = vec3_to_vec4(a, scast<float>(1));
	return mat4_mul_vec4(ma, temp);
}

//vec4 mat4_mul_vec3(const vec3& a, const mat4& ma)
//{
//	vec4 temp = vec3_to_vec4(a, scast<float>(1));
//	return mat4_mul_vec4(ma, temp);
//}


mat4 mat4_glm_translate(const mat4& ma, const vec3& a)
{
	return (ma * mat4_translation(a.x, a.y, a.z));
}

mat4 mat4_glm_scale(const mat4& ma, const vec3& a)
{
	return (ma * mat4_scaling(a.x, a.y, a.z));
}


mat4 mat4_glm_rotation_xyz(float angle, const vec3& axis)
{
    float const c = mf::cos(angle);
	float const s = mf::sin(angle);	

    // axis vector
	vec3 a = vec3_normalize(axis);


    //mat4 t = k_mat4_identity;
	//t.m[0][0] = c + (scast<float>(1) - c)*a.x*a.x;
	//t.m[0][1] = (scast<float>(1) - c)*a.x*a.y + s*a.z;
	//t.m[0][2] = (scast<float>(1) - c)*a.x*a.z - s*a.y;
	//t.m[0][3] = scast<float>(0);
	//t.m[1][0] = (scast<float>(1) - c)*a.y*a.x - s*a.z;
	//t.m[1][1] = c + (scast<float>(1) - c)*a.y*a.y;
	//t.m[1][2] = (scast<float>(1) - c)*a.y*a.z + s*a.x;
	//t.m[1][3] = scast<float>(0);
	//t.m[2][0] = (scast<float>(1) - c)*a.z*a.x + s*a.y;
	//t.m[2][1] = (scast<float>(1) - c)*a.z*a.y - s*a.x;
	//t.m[2][2] = c + (scast<float>(1) - c)*a.z*a.z;
	//t.m[2][3] = scast<float>(0);
	//t.m[3][0] = scast<float>(0);
	//t.m[3][1] = scast<float>(0);
	//t.m[3][2] = scast<float>(0);
	//t.m[3][3] = scast<float>(1);	


    mat4 t(
        c + (scast<float>(1) - c)*a.x*a.x,      (scast<float>(1) - c)*a.x*a.y + s*a.z,  (scast<float>(1) - c)*a.x*a.z - s*a.y,  scast<float>(0),
        (scast<float>(1) - c)*a.y*a.x - s*a.z,  c + (scast<float>(1) - c)*a.y*a.y,      (scast<float>(1) - c)*a.y*a.z + s*a.x,  scast<float>(0),
        (scast<float>(1) - c)*a.z*a.x + s*a.y,  (scast<float>(1) - c)*a.z*a.y - s*a.x,  c + (scast<float>(1) - c)*a.z*a.z,      scast<float>(0),
        scast<float>(0),                        scast<float>(0),                        scast<float>(0),                        scast<float>(1)
        );

    return t;
}

mat4 mat4_glm_rotation_xyz(float angle, float x, float y, float z)
{
    vec3 a(x, y, z);
    return mat4_glm_rotation_xyz(angle, a);
}

mat4 mat4_glm_rotate_xyz(const mat4& ma, float angle, const vec3& a)
{
	return (ma * mat4_glm_rotation_xyz(angle, a));
}

mat4 mat4_glm_rotate_x(const mat4& ma, float angle)
{
	return (ma * mat4_rotation_x(angle));
}

mat4 mat4_glm_rotate_y(const mat4& ma, float angle)
{
	return (ma * mat4_rotation_y(angle));
}

mat4 mat4_glm_rotate_z(const mat4& ma, float angle)
{
	return (ma * mat4_rotation_z(angle));
}

//==================================================================
// <OWN ADDED>
//==================================================================

float vec2_distance_sq(const vec2& a, const vec2& b)
{
	return vec2_length_sq(vec2_sub(a, b));
}

float vec2_distance(const vec2& a, const vec2& b)
{	
	return mf::sqrt(vec2_distance_sq(a, b));
}

//------------------------
float vec3_distance_sq(const vec3& a, const vec3& b)
{
	
	//(a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)
	return vec3_length_sq(a-b);

	//float result = scast<float>(0);
	//forloopi(i, a.size())
	//{
	//	//result += (a[i] - b[i]) * (a[i] - b[i]);
	//	result += mf::square(a[i] - b[i]);
	//}
	//return result;
}

//distance between 2 vectors
float vec3_distance(const vec3& a, const vec3& b)
{	
	return mf::sqrt(vec3_distance_sq(a, b));
}

vec3 vec3_fabs(const vec3& a)
{
	vec3 t = k_vec3_zero;
	forloopi(i, a.size())
	{
		t[i] = fabs(a[i]);
	}
	return t;
}

vec3 vec3_deg_to_rad(const vec3& a)
{
	return vec3(mf::deg_to_rad(a.x), mf::deg_to_rad(a.y), mf::deg_to_rad(a.z));
}

//----------------------------------------
mat4 mat4_transposed_inverse(const mat4& m)
{
	return mat4_transpose(mat4_inverse(m));
}

mat4 mat4_shearing(float x, float y)
{
	mat4 t(
		scast<float>(1),	y,					scast<float>(0), scast<float>(0),
		x,					scast<float>(1),	scast<float>(0), scast<float>(0),
		scast<float>(0),	scast<float>(0),	scast<float>(1), scast<float>(0),
		scast<float>(0),	scast<float>(0),	scast<float>(0), scast<float>(1)
		);

	return t;
}

mat4 mat4_shear(const mat4& ma, float x, float y)
{
	return (ma * mat4_shearing(x, y));
}

//----------------------------------------
// Inverse is different for quaterinion (d3dx_math)
// QuatInverse: Conjugate and re-norm
//void QuatInverse(quat q)
void quat_negate(quat& q)
{
	q.axis = -q.axis;	
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------


}



//===================================================================

// variadic template functions cannot export from modules, cannot be inside a namespace
// moved to header base_gmath_wp.h
#if 0
export template <>
struct std::formatter<gm::vec2> : std::formatter<std::string> {
  auto format(gm::vec2 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}", a[0], a[1]), ctx);
  }
};

export template <>
struct std::formatter<gm::vec3> : std::formatter<std::string> {
  auto format(gm::vec3 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2]), ctx);
  }
};

export template <>
struct std::formatter<gm::vec4> : std::formatter<std::string> {
  auto format(gm::vec4 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};


export template <>
struct std::formatter<gm::quat> : std::formatter<std::string> {
  auto format(gm::quat a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

export template <>
struct std::formatter<gm::plane> : std::formatter<std::string> {
  auto format(gm::plane a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

export template <>
struct std::formatter<gm::colorf> : std::formatter<std::string> {
  auto format(gm::colorf a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};


export template <>
struct std::formatter<gm::mat2> : std::formatter<std::string> {
  auto format(gm::mat2 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f}", a[0], a[1], a[2], a[3]), ctx);
  }
};

export template <>
struct std::formatter<gm::mat3> : std::formatter<std::string> {
  auto format(gm::mat3 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f},\n"
		  , a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]), ctx);
  }
};

export template <>
struct std::formatter<gm::mat4> : std::formatter<std::string> {
  auto format(gm::mat4 a, std::format_context& ctx) {
    return std::formatter<std::string>::format(
      std::format("{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n{:.6f}, {:.6f}, {:.6f}, {:.6f},\n"
		  , a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]), ctx);
  }
};
#endif
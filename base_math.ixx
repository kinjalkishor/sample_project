
#include <cmath>
//C++11 mt19937, mt19937_64
#include <random>

#include "base_def.h"
//#include "base_shared.h"

export module base_math;

import base_def;


//----------------------------------------------------------------
// Math Constants
//----------------------------------------------------------------
namespace mathdef
{

// Math defines
// openbsd math.h
constexpr double GM_E			= 2.7182818284590452354;		// e 
constexpr double GM_LOG2E		= 1.4426950408889634074;		// log 2e 
constexpr double GM_LOG10E		= 0.43429448190325182765;		// log 10e 
constexpr double GM_LN2			= 0.69314718055994530942;		// log e2 
constexpr double GM_LN10		= 2.30258509299404568402;		// log e10 
constexpr double GM_PI			= 3.14159265358979323846;		// pi 
constexpr double GM_PI_2		= 1.57079632679489661923;		// pi/2 
constexpr double GM_PI_4		= 0.78539816339744830962;		// pi/4 
constexpr double GM_INV_PI		= 0.31830988618379067154;		// 1/pi 
constexpr double GM_INV2_PI		= 0.63661977236758134308;		// 2/pi 
constexpr double GM_INV2_SQRTPI	= 1.12837916709551257390;		// 2/sqrt(pi) 
constexpr double GM_SQRT2		= 1.41421356237309504880;		// sqrt(2) 
constexpr double GM_INV_SQRT2	= 0.70710678118654752440;		// 1/sqrt(2) 



// other constants
constexpr double GM_INV_SQRTPI		= 0.56418958354775628695;		// 1/sqrt(pi) 
constexpr double GM_TWO_PI		    = 6.28318530717958647692;		// 2*pi; //TAU
constexpr double GM_INV_TWO_PI		= 0.15915494309189533577;		// 1/2*pi
constexpr double GM_SQRT3		    = 1.73205080756887729352;       // sqrt(3) 
constexpr double GM_INV_SQRT3		= 0.57735026918962576450;       // 1/sqrt(3) 


//---
const double GM_INV3_FOUR_PI		= 2.356194490192344928845;		// 3/4*pi

constexpr double GM_DEG_TO_RAD		= 0.01745329251994329577;	    // pi/180;
constexpr double GM_RAD_TO_DEG		= 57.295779513082320876846;     // 180/PI;

constexpr double GM_SEC_TO_MS		= 1000.0;
constexpr double GM_MS_TO_SEC		= 0.001;

const float	GM_FLT_INFINITY			= 1e30f;
const float GM_FLT_EPSILON			= 1.192092896e-07f;

}


//----------------------------------------------------------------
// Math Functions
//----------------------------------------------------------------
export namespace mf
{

constexpr float k_e				= scast<float>(mathdef::GM_E);
constexpr float k_log2e			= scast<float>(mathdef::GM_LOG2E);
constexpr float k_log10e		= scast<float>(mathdef::GM_LOG10E);
constexpr float k_ln2			= scast<float>(mathdef::GM_LN2);
constexpr float k_ln10			= scast<float>(mathdef::GM_LN10);
constexpr float k_pi			= scast<float>(mathdef::GM_PI);
constexpr float k_inv_pi_2		= scast<float>(mathdef::GM_PI_2);
constexpr float k_inv_pi_4		= scast<float>(mathdef::GM_PI_4);
constexpr float k_inv_1_pi		= scast<float>(mathdef::GM_INV_PI);
constexpr float k_inv_2_pi		= scast<float>(mathdef::GM_INV2_PI);
constexpr float k_inv_2_sqrtpi	= scast<float>(mathdef::GM_INV2_SQRTPI);
constexpr float k_sqrt2			= scast<float>(mathdef::GM_SQRT2);
constexpr float k_inv_1_sqrt2	= scast<float>(mathdef::GM_INV_SQRT2);
constexpr float k_inv_1_sqrtpi	= scast<float>(mathdef::GM_INV_SQRTPI);
constexpr float k_x2pi			= scast<float>(mathdef::GM_TWO_PI);
constexpr float k_inv_1_x2pi	= scast<float>(mathdef::GM_INV_TWO_PI);
constexpr float k_sqrt3			= scast<float>(mathdef::GM_SQRT3);
constexpr float k_inv_1_sqrt3	= scast<float>(mathdef::GM_INV_SQRT3);


constexpr float k_epsilon		= std::numeric_limits<float>::epsilon();
constexpr float k_infinity		= std::numeric_limits<float>::infinity();
constexpr float k_round_error	= std::numeric_limits<float>::round_error();
constexpr float k_real_min		= std::numeric_limits<float>::min();
constexpr float k_real_max		= std::numeric_limits<float>::max();

constexpr float k_zero			= scast<float>(0);
constexpr float k_one			= scast<float>(1);


//------------------------------------------------------------------------------------------------------------
// Trigonometric functions
// cos: Compute cosine 
inline float cos(float x)						    { return std::cosf(x); }

// sin: Compute sine 
inline float sin(float x)						    { return std::sinf(x); }

// tan: Compute tangent 
inline float tan(float x)						    { return std::tanf(x); }

// acos: Compute arc cosine 
inline float acos(float x)						    { return std::acosf(x); }

// asin: Compute arc sine 
inline float asin(float x)						    { return std::asinf(x); }

// atan: Compute arc tangent 
inline float atan(float x)						    { return std::atanf(x); }

// atan2: Compute arc tangent with two parameters 
inline float atan2(float y, float x)				{ return std::atan2f(y, x); }



// Hyperbolic functions
// cosh: Compute hyperbolic cosine 
inline float cosh(float x)						    { return std::coshf(x); }

// sinh: Compute hyperbolic sine 
inline float sinh(float x)						    { return std::sinhf(x); }

// tanh: Compute hyperbolic tangent 
inline float tanh(float x)						    { return std::tanhf(x); }

// acosh: Compute area hyperbolic cosine 
inline float acosh(float x)						    { return std::acoshf(x); }

// asinh: Compute area hyperbolic sine 
inline float asinh(float x)						    { return std::asinhf(x); }

// atanh: Compute area hyperbolic tangent 
inline float atanh(float x)						    { return std::atanhf(x); }



// Exponential and logarithmic functions
// exp: Compute exponential function 
inline float exp(float x)						    { return std::expf(x); }

// frexp: Get significand and exponent 
inline float frexp(float x, int* y)				    { return std::frexpf(x, y); }

// ldexp: Generate value from significand and exponent 
inline float ldexp(float x, int y)				    { return std::ldexpf(x, y); }

// log: Compute natural logarithm 
inline float log(float x)						    { return std::logf(x); }

// log10: Compute common logarithm 
inline float log10(float x)						    { return std::log10f(x); }

// modf: Break into fractional and integral parts
inline float modf(float x, float* y)				{ return std::modff(x, y); }

// exp2: Compute binary exponential function 
inline float exp2(float x)						    { return std::exp2f(x); }

// expm1: Compute exponential minus one 
inline float expm1(float x)						    { return std::expm1f(x); }

// ilogb: Integer binary logarithm 
inline int ilogb(float x)						    { return std::ilogbf(x); }

// log1p: Compute logarithm plus one 
inline float log1p(float x)						    { return std::log1pf(x); }

// log2: Compute binary logarithm 
inline float log2(float x)						    { return std::log2f(x); }

// logb: Compute floating-point base logarithm
inline float logb(float x)						    { return std::logbf(x); }

// scalbn: Scale significand using floating-point base exponent
inline float scalbn(float x, int y)				    { return std::scalbnf(x, y); }

// scalbln: Scale significand using floating-point base exponent (long) 
inline float scalbln(float x, long y)			    { return std::scalblnf(x, y); }



// Power functions
// pow: Raise to power 
inline float pow(float x, float y)				    { return std::powf(x, y); }

inline float pow(float x, int y) 
{
    if (y == 2)
    {
        return x * x;
    }

    return std::powf(x, static_cast<float>(y));
}

// sqrt: Compute square root 
inline float sqrt(float x)						    { return std::sqrtf(x); }

// cbrt: Compute cubic root 
inline float cbrt(float x)						    { return std::cbrtf(x); }

// hypot: Compute hypotenuse 
inline float hypot(float x, float y)				{ return std::hypotf(x, y); }



// Error and gamma functions
// erf: Compute error function 
inline float erf(float x)						    { return std::erff(x); }

// erfc: Compute complementary error function 
inline float erfc(float x)						    { return std::erfcf(x); }

// tgamma: Compute gamma function 
inline float tgamma(float x)						{ return std::tgammaf(x); }

// lgamma: Compute log-gamma function 
inline float lgamma(float x)						{ return std::lgammaf(x); }



// Rounding and remainder functions
// ceil: Round up value 
inline float ceil(float x)						    { return std::ceilf(x); }

// floor: Round down value 
inline float floor(float x)						    { return std::floorf(x); }

// fmod: Compute remainder of division 
inline float fmod(float x, float y)				    { return std::fmodf(x, y); }

// trunc: Truncate value 
inline float trunc(float x)						    { return std::truncf(x); }

// round: Round to nearest 
inline float round(float x)						    { return std::roundf(x); }

// lround: Round to nearest and cast to long integer 
inline int roundi(float x)						    { return std::lroundf(x); }

// llround: Round to nearest and cast to long long integer 
inline int64 roundi64(float x)					    { return std::llroundf(x); }

// rint: Round to integral value 
inline float rint(float x)						    { return std::rintf(x); }

// lrint: Round and cast to long integer 
inline int rinti(float x)						    { return std::lrintf(x); }

// llrint: Round and cast to long long integer 
inline int64 rinti64(float x)					    { return std::llrintf(x); }

// nearbyint: Round to nearby integral value 
inline float nearbyint(float x)					    { return std::nearbyintf(x); }

// remainder: Compute remainder (IEC 60559) 
inline float remainder(float x, float y)			{ return std::remainderf(x, y); }

// remquo: Compute remainder and quotient 
inline float remquo(float x, float y, int* z)	    { return std::remquof(x, y, z); }



// Floating-point manipulation functions
// copysign: Copy sign 
inline float copysign(float number, float sign)	    { return std::copysignf(number, sign); }

// nan: Generate quiet NaN 
inline float nan(char const* x)					    { return std::nanf(x); }

// nextafter: Next representable value 
inline float nextafter(float x, float y)			{ return std::nextafterf(x, y); }

// nexttoward: Next representable value toward precise value 
inline float nexttoward(float x, long double y)	    { return std::nexttowardf(x, y); }



// Minimum, maximum, difference functions
// fdim: Positive difference 
inline float fdim(float x, float y)				    { return std::fdimf(x, y); }

// fmax: Maximum value 
inline float fmax(float x, float y)				    { return std::fmaxf(x, y); }

// fmin: Minimum value 
inline float fmin(float x, float y)				    { return std::fminf(x, y); }



// Other functions
// fabs: Compute absolute value 
inline float fabs(float x)						    { return std::fabsf(x); }

// abs: Compute absolute value 
inline int abs(int x)							    { return std::abs(x); }
// llabs: long long abs
inline int64 abs64(int64 x)						    { return std::llabs(scast<llint>(x)); }

// fma: Multiply-add 
inline float fma(float x, float y, float z)		    { return std::fmaf(x, y, z); }



// Macros / Functions
// These are implemented as macros in C and as functions in C++:
// Classification macro / functions
// fpclassify: Classify floating-point value. Categorizes floating point value arg into the 
// following categories: zero, subnormal, normal, infinite, NAN, or implementation-defined category.
inline int fpclassify(float x)					    { return std::fpclassify(x); }

// isfinite: Is finite value
inline bool isfinite(float x)					    { return std::isfinite<float>(x); }

// isinf: Is infinity 
inline bool isinf(float x)						    { return std::isinf<float>(x); }

// isnan: Is Not-A-Number 
inline bool isnan(float x)						    { return std::isnan<float>(x); }

// isnormal: Is normal 
inline bool isnormal(float x)					    { return std::isnormal<float>(x); }

// signbit: Sign bit. Determines if the given floating point number arg is negative. 
inline bool signbit(float x)						{ return std::signbit(x); }



// Comparison macro / functions
// isgreater: Is greater
inline bool isgreater(float x, float y)			    { return std::isgreater<float, float>(x, y); }

// isgreaterequal: Is greater or equal
inline bool isgreaterequal(float x, float y)		{ return std::isgreaterequal<float, float>(x, y); }

// isless: Is less
inline bool isless(float x, float y)				{ return std::isless<float, float>(x, y); }

// islessequal: Is less or equal
inline bool islessequal(float x, float y)		    { return std::islessequal<float, float>(x, y); }

// islessgreater: Is less or greater
inline bool islessgreater(float x, float y)		    { return std::islessgreater<float, float>(x, y); }

// isunordered: Is unordered
inline bool isunordered(float x, float y)		    { return std::isunordered<float, float>(x, y); }



//------------------------------------------------------------------------------------------------------------
inline float deg_to_rad(float a) 
{	
	//return (a * (k_pi / scast<float>(180)));
    return (a * scast<float>(mathdef::GM_DEG_TO_RAD));
}

	
inline float rad_to_deg(float a) 
{	
	//return (a * (scast<float>(180) / k_pi));
	return (a * scast<float>(mathdef::GM_RAD_TO_DEG));
}


inline void sincos(float angle, float& s, float& c)
{
	s = sinf(angle);
	c = cosf(angle);    
}


//---------------------------
// Float Comparison
// Donald Knuth
inline bool approximately_equal(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

inline bool essentially_equal(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

inline bool definitely_greater_than(float a, float b, float epsilon)
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

inline bool definitely_less_than(float a, float b, float epsilon)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}


//---
// returns if a equals b, taking possible rounding errors into account
inline bool equals(float a, float b, const float epsilon = mf::k_epsilon) 
{ 
	//if ((fabs(a - b) > epsilon)) { return false; }	
	//else { return true; } 

	return approximately_equal(a, b, epsilon);
}

inline bool equals_zero(float a) 
{ 
	return equals(a, scast<float>(0));
}


//------------------------------------------------------------------------------------------------------------
inline float square(const float a)
{
	return (a*a);
}

inline float cube(const float a)
{
	return (a*a*a);
}

inline float rsqrt(const float a)
{
	return (scast<float>(1)/mf::sqrt(a));
}

// lerp, mix: a + s*(b-a)
inline float lerp(float a, float b, float s)
{
	// Precision loss when a and b significantly differ in magnitude for (b-a)
	//return (a + s*(b-a));
	return (a*(scast<float>(1)-s) + s*b);
}


// fractional part of x
inline float fract(float x)
{
	return x - mf::floor(x);
}

// unsigned and signed normalized or unorm and snorm
// unit_range to symmetric_unit_range, zo_to_no, 
// [0.0, 1.0] to [-1.0 to 1.0]
inline float range_un_to_sn(float x)
{
	//n = 2.0 * (z - 0.5))
	//n = 2*z - 1
	return ((scast<float>(2)*x) - scast<float>(1));
}

// symmetric_unit_range to unit_range, no_to_zo
// [-1.0 to 1.0] to [0.0, 1.0]
inline float range_sn_to_un(float x)
{
	//z = (n+1)/2 = (n+1)*0.5
	return ((x + scast<float>(1)) * scast<float>(0.5));
}


inline float clamp01(const float& x)
{
    return flib::clamp(x, scast<float>(0), scast<float>(1));
}


inline float clamp1(const float& x)
{
    return flib::clamp(x, scast<float>(-1), scast<float>(1));
}


} //mf


export namespace mf
{

template<class T>
static inline T abs(const T x)
{
	return (x < scast<T>(0)) ? -x : x;
}

template<class T>
static inline T sign(const T x)
{
	//return 0 for 0 (correct)
	return ((x > scast<T>(0)) ? 1 : ((x < scast<T>(0)) ? -1 : 0)); 
}

// Non-zero sign
template<class T>
static inline T sign_nz(const T x)
{
	// return 1 for 0
    return ((x >= scast<T>(0)) ? 1 : -1);
}

}


//----------------------------------------------------------------
// Random Numbers
//----------------------------------------------------------------
export class mrand
{
private:
	static inline constexpr uint k_rand_max = UINT32_MAX;	
	static inline std::mt19937 rng;

public:

	//Random Numbers
	static inline void rand_seed(uint32 seed)
	{
		//rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		rng.seed(seed);
	}

	static inline uint32 rand_u32()
	{
		return rng();
	}


	// frand, unit_random
	// returns a float between 0 and 1.0
	static inline float rand_unit()	
	{
		return (scast<float>(rand_u32())/scast<float>(k_rand_max));		
	}

	// crand, symmetric_random
	// returns a float between -1 and 1.0
	static inline float rand_sunit()	
	{
		return mf::range_un_to_sn(rand_unit());		
	}

	// float in [min, max] range
	static inline float rand_range(float min, float max)
	{
		return min + rand_unit()*(max-min);
	}
};
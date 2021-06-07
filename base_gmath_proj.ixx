#include <limits>
#include "base_def.h"
#include "base_debug.h"

export module base_gmath_proj;


import base_def;
import base_math;
import base_math_arrayfunc;
import base_gmath;


export namespace gm
{

//-----------------------------------------
//eye, at, up
//eye, center, up
//position, target, up (up_vector)
 
//zaxis_dir = normalize(sub(at, eye)
//xaxis_right = normalize(cross(up, zaxis_dir))
//yaxis_upn = cross(zaxis_dir, xaxis_right)
//    
// xaxis_right.x            yaxis_upn.x             zaxis_dir.x            0
// xaxis_right.y            yaxis_upn.y             zaxis_dir.y            0
// xaxis_right.z            yaxis_upn.z             zaxis_dir.z            0
//-dot(xaxis_right, eye)    -dot(yaxis_upn, eye)    -dot(zaxis_dir, eye)   1

// Build a lookat matrix. (left-handed)
mat4 mat4_look_at_lh(const vec3& eye, const vec3& at, const vec3& up)
{
    // xaxis, yaxis, zaxis
    vec3 right, upn, dir; 

#if 1

    //glm //d3dx documentation
    dir = vec3_normalize(vec3_sub(at, eye));
    right = vec3_normalize(vec3_cross(up, dir));
    upn = vec3_cross(dir, right);
#else

    //d3dx
    dir = vec3_sub(at, eye);    
    dir = vec3_normalize(dir);  //dir    

    right = vec3_cross(up, dir);
    upn = vec3_cross(dir, right);  //upn
    right = vec3_normalize(right); //right    
    upn = vec3_normalize(upn);    
#endif


    //mat4 t = k_mat4_identity;
    //t.r[0][0] = right.x;
    //t.r[1][0] = right.y;
    //t.r[2][0] = right.z;
    //t.r[3][0] = -vec3_dot(right, eye);  
    //t.r[0][1] = upn.x;
    //t.r[1][1] = upn.y;
    //t.r[2][1] = upn.z;
    //t.r[3][1] = -vec3_dot(upn, eye);    
    //t.r[0][2] = dir.x;
    //t.r[1][2] = dir.y;
    //t.r[2][2] = dir.z;
    //t.r[3][2] = -vec3_dot(dir, eye);   
    //t.r[0][3] = 0.0f;
    //t.r[1][3] = 0.0f;
    //t.r[2][3] = 0.0f;
    //t.r[3][3] = 1.0f;


    mat4 tm(
        right.x,                upn.x,                  dir.x,                 scast<float>(0),
        right.y,                upn.y,                  dir.y,                 scast<float>(0),
        right.z,                upn.z,                  dir.z,                 scast<float>(0),
        -vec3_dot(right, eye),  -vec3_dot(upn, eye),    -vec3_dot(dir, eye),   scast<float>(1)
        );

    return tm;
}


//zaxis_dir = normalize(sub(eye, at))
//xaxis_right = normalize(cross(up, zaxis_dir))
//yaxis_upn = cross(zaxis_dir, xaxis_right)
//    
// xaxis_right.x           yaxis_upn.x          zaxis_dir.x            0
// xaxis_right.y           yaxis_upn.y          zaxis_dir.y            0
// xaxis_right.z           yaxis_upn.z          zaxis_dir.z            0
// dot(xaxis_right, eye)   dot(yaxis_upn, eye)  dot(zaxis_dir, eye)    1

// LookAt Matrices
// Build a lookat matrix. (right-handed)
mat4 mat4_look_at_rh(const vec3& eye, const vec3& at, const vec3& up)
{
    // xaxis, yaxis, zaxis
    vec3 right, upn, dir;    

#if 1
    //d3d documentation
    dir = vec3_normalize(vec3_sub(eye, at));
    right = vec3_normalize(vec3_cross(up, dir));
    upn = vec3_cross(dir, right);

    mat4 tm(
        right.x,                upn.x,              dir.x,              scast<float>(0),
        right.y,                upn.y,              dir.y,              scast<float>(0),
        right.z,                upn.z,              dir.z,              scast<float>(0),
        vec3_dot(right, eye),   vec3_dot(upn, eye), vec3_dot(dir, eye), scast<float>(1)
        );

#elif 0
    // CHECK: both are correct as vec3_sub(at, eye) -ve sign and vec3_cross() -ve sign cancel each other
    //cross(a, b) = -cross(b, a)

    //glm
    dir = vec3_normalize(vec3_sub(at, eye));    
	right = vec3_normalize(vec3_cross(dir, up));      // reverse order cross    
	upn = vec3_cross(right, dir);                              // reverse order cross

    //mat4 t = k_mat4_identity;
	//t.r[0][0] = right.x;
	//t.r[1][0] = right.y;
	//t.r[2][0] = right.z;                                      // reversed sign
	//t.r[3][0] = -vec3_dot(right, eye);                        // reversed sign
	//t.r[0][1] = upn.x;
	//t.r[1][1] = upn.y;
	//t.r[2][1] = upn.z;                                        // wrong order
	//t.r[3][1] = -vec3_dot(upn, eye);                          // wrong order
	//t.r[0][2] = -dir.x;
	//t.r[1][2] = -dir.y;
	//t.r[2][2] = -dir.z;	
	//t.r[3][2] = vec3_dot(dir, eye);

    mat4 tm(
        right.x,                upn.x,                  -dir.x,                scast<float>(0),
        right.y,                upn.y,                  -dir.y,                scast<float>(0),
        right.z,                upn.z,                  -dir.z,                scast<float>(0),
        -vec3_dot(right, eye),  -vec3_dot(upn, eye),    vec3_dot(dir, eye),    scast<float>(1)
        );

#elif 1

    //formula
    #if 0
        dir = vec3_normalize_from(vec3_sub(eye, at), hr);
        q_hr_failed_print();
	    right = vec3_normalize_from(vec3_cross(up, dir), hr);      
        q_hr_failed_print();
	    upn = vec3_cross(dir, right);                              
    #else
        dir = vec3_sub(eye, at);    
        dir = vec3_normalize(dir);  //dir        
        right = vec3_cross(up, dir);   
        upn = vec3_cross(dir, right);
        right = vec3_normalize(right); //right        
        upn = vec3_normalize(upn);   //upn        
    #endif


    mat4 tm(
        right.x,               upn.x,                   dir.x,                scast<float>(0),
        right.y,               upn.y,                   dir.y,                scast<float>(0),
        right.z,               upn.z,                   dir.z,                scast<float>(0),
        vec3_dot(right, eye),  vec3_dot(upn, eye),      vec3_dot(dir, eye),    scast<float>(1)
        );
#else

    //d3dx
    dir = vec3_sub(at, eye);    
    dir = vec3_normalize(dir);  //dir    
    right = vec3_cross(up, dir);   
    upn = vec3_cross(dir, right);
    right = vec3_normalize(right); //right    
    upn = vec3_normalize(upn);   //upn    


    //mat4 t = k_mat4_identity;
    //t.r[0][0] = -right.x;
    //t.r[1][0] = -right.y;
    //t.r[2][0] = -right.z;
    //t.r[3][0] = vec3_dot(right, eye);   
    //t.r[0][1] = upn.x;
    //t.r[1][1] = upn.y;
    //t.r[2][1] = upn.z;
    //t.r[3][1] = -vec3_dot(upn, eye);     
    //t.r[0][2] = -dir.x;
    //t.r[1][2] = -dir.y;
    //t.r[2][2] = -dir.z;
    //t.r[3][2] = vec3_dot(dir, eye);    
    //t.r[0][3] = 0.0f;
    //t.r[1][3] = 0.0f;
    //t.r[2][3] = 0.0f;
    //t.r[3][3] = 1.0f;


    mat4 tm(
        -right.x,               upn.x,                  -dir.x,                scast<float>(0),
        -right.y,               upn.y,                  -dir.y,                scast<float>(0),
        -right.z,               upn.z,                  -dir.z,                scast<float>(0),
        vec3_dot(right, eye),   -vec3_dot(upn, eye),    vec3_dot(dir, eye),    scast<float>(1)
        );
#endif

    return tm;
}




//-----------------------------------------------------------------------------------------------------------------

#if 0
vec3 projectUR(const vec3& obj, const mat4& model, const mat4& proj, const vec4& viewport)
{
	vec4 temp = vec3_to_vec4(obj, scast<float>(1));

	temp = mat4_mul_vec4(model, temp);
	temp = mat4_mul_vec4(proj, temp);

	temp /= temp.w;
	temp.x = temp.x*scast<float>(0.5) + scast<float>(0.5);
	temp.y = temp.y*scast<float>(0.5) + scast<float>(0.5);

	temp[0] = temp[0] * float(viewport[2]) + float(viewport[0]);
	temp[1] = temp[1] * float(viewport[3]) + float(viewport[1]);

	return vec4_to_vec3(temp);
}
vec3 projectSR(const vec3& obj, const mat4& model, const mat4& proj, const vec4& viewport)
{
	vec4 temp = vec3_to_vec4(obj, scast<float>(1));

	temp = mat4_mul_vec4(model, temp);
	temp = mat4_mul_vec4(proj, temp);

	temp /= temp.w;
	temp = temp * scast<float>(0.5) + scast<float>(0.5);
	temp[0] = temp[0]*float(viewport[2]) + float(viewport[0]);
	temp[1] = temp[1]*float(viewport[3]) + float(viewport[1]);

	return vec4_to_vec3(temp);
}
vec3 unProjectUR(const vec3& win, const mat4& model, const mat4& proj, const vec4& viewport)
{
	mat4 Inverse = mat4_inverse((proj * model));
	q_hr_failed_print();

	vec4 temp = vec3_to_vec4(win, float(1));
	temp.x = (temp.x - float(viewport[0]))/float(viewport[2]);
	temp.y = (temp.y - float(viewport[1]))/float(viewport[3]);
	temp.x = temp.x * scast<float>(2) - scast<float>(1);
	temp.y = temp.y * scast<float>(2) - scast<float>(1);

	vec4 obj = mat4_mul_vec4(Inverse, temp);
	obj /= obj.w;

	return vec4_to_vec3(obj);
}
vec3 unProjectSR(const vec3& win, const mat4& model, const mat4& proj, const vec4& viewport)
{
	mat4 Inverse = mat4_inverse((proj * model));
	q_hr_failed_print();

	vec4 temp = vec3_to_vec4(win, float(1));
	temp.x = (temp.x - float(viewport[0]))/float(viewport[2]);
	temp.y = (temp.y - float(viewport[1]))/float(viewport[3]);
	temp = temp * scast<float>(2) - scast<float>(1);

	vec4 obj = mat4_mul_vec4(Inverse, temp);
	obj /= obj.w;

	return vec4_to_vec3(obj);
}
#endif

// MVP or WVP matrices, model space = world space
vec3 vec3_glm_project_un(const vec3& obj, const viewport_gl& vp, const mat4& proj, const mat4& world)
{
	vec4 t = vec3_to_vec4(obj, scast<float>(1));

	t = mat4_mul_vec4(world, t);
	t = mat4_mul_vec4(proj, t);

	t = t/t.w;
	t.x = vp.x + (scast<float>(1) + t.x)*vp.w*scast<float>(0.5);
	t.y = vp.y + (scast<float>(1) + t.y)*vp.h*scast<float>(0.5);

	return vec4_to_vec3(t);
}



vec3 vec3_glm_project_sn(const vec3& obj, const viewport_gl& vp, const mat4& proj, const mat4& world)
{
	vec4 t = vec3_to_vec4(obj, scast<float>(1));

	t = mat4_mul_vec4(world, t);
	t = mat4_mul_vec4(proj, t);

	t = t/t.w;    
	//t = t * scast<float>(0.5) + scast<float>(0.5);
    t = (scast<float>(1) + t)*scast<float>(0.5);
	t.x = vp.x + t.x*vp.w;
	t.y = vp.y + t.y*vp.h;

	return vec4_to_vec3(t);
}





vec3 vec3_glm_unproject_un(const vec3& win, const viewport_gl& vp, const mat4& proj, const mat4& world)
{	
	mat4 inverse = mat4_inverse(proj * world);	

	vec4 t = vec3_to_vec4(win, scast<float>(1));
	t.x = scast<float>(2)*(t.x - vp.x)/vp.w - scast<float>(1);
	t.y = scast<float>(2)*(t.y - vp.y)/vp.h - scast<float>(1);

	vec4 tv = mat4_mul_vec4(inverse, t);
	tv = tv/tv.w;
    
	return vec4_to_vec3(tv);
}



vec3 vec3_glm_unproject_sn(const vec3& win, const viewport_gl& vp, const mat4& proj, const mat4& world)
{	
	mat4 inverse = mat4_inverse(proj * world);	

	vec4 t = vec3_to_vec4(win, scast<float>(1));
	t.x = (t.x - vp.x)/vp.w;
	t.y = (t.y - vp.y)/vp.h;
	t = t * scast<float>(2) - scast<float>(1);

	vec4 tv = mat4_mul_vec4(inverse, t);
	tv = tv/tv.w;

	return vec4_to_vec3(tv);
}




mat4 vec3_glm_pick_matrix(const vec2& center, const vec2& delta, const viewport_gl& vp)
{
	q_assert(delta.x > scast<float>(0) && delta.y > scast<float>(0));
	mat4 t = k_mat4_identity;

	if(!(delta.x > scast<float>(0) && delta.y > scast<float>(0)))
	{
        q_debug("(delta.x > scast<float>(0) && delta.y > scast<float>(0)), Returning zero matrix. Error will propogate.\n");
		return t; 
	}
    else
    {
        //hr.set_ok();
    }

	vec3 tv = k_vec3_zero;
	tv.x = vp.w - scast<float>(2) * (center.x - vp.x)/delta.x;
	tv.y = vp.h - scast<float>(2) * (center.y - vp.y)/delta.y;
	tv.z = scast<float>(0);

	// Translate and scale the picked region to the entire window
	t = mat4_glm_translate(t, tv);
	return mat4_glm_scale(t, vec3(vp.w/delta.x, vp.h/delta.y, scast<float>(1)));
}



//------------------------------------------
// xWin = x + 0.5 * (xNdc + 1.0) * w;
// yWin = y + 0.5 * (yNdc + 1.0) * h;

// Project vector from object space into screen space
vec3 vec3_project(const vec3& a, const viewport& vp, const mat4& proj, const mat4& view, const mat4& world)
{
    vec3 t = k_vec3_zero;
    mat4 m = k_mat4_identity;

    m = mat4_mul(m, world);
    m = mat4_mul(m, view);
    m = mat4_mul(m, proj);

    t = vec3_transform_coord(a, m);

    //t.x = vp.x + (scast<float>(1) + t.x)*vp.w/scast<float>(2);
    //t.y = vp.y + (scast<float>(1) - t.y)*vp.h/scast<float>(2);
    t.x = vp.x + (scast<float>(1) + t.x)*vp.w*scast<float>(0.5);
    t.y = vp.y + (scast<float>(1) - t.y)*vp.h*scast<float>(0.5);
    t.z = vp.zn + t.z * (vp.zf - vp.zn);

    return t;
}



// Project vector from screen space into object space
vec3 vec3_unproject(const vec3& a, const viewport& vp, const mat4& proj, const mat4& view, const mat4& world)
{
    vec3 t;
    mat4 m = k_mat4_identity;

    m = mat4_mul(m, world);
    m = mat4_mul(m, view);
    m = mat4_mul(m, proj);    
    m = mat4_inverse(m);    

    t = a;

    t.x = scast<float>(2)*(t.x - vp.x)/vp.w - scast<float>(1);
    t.y = scast<float>(1) - scast<float>(2)*(t.y - vp.y)/vp.h;
    t.z = (t.z - vp.zn)/(vp.zf - vp.zn);

    t = vec3_transform_coord(t, m);
    return t;
}


//-----------------------------------------------------------------------------------------------------------------
// Perspective Matrices D3DX
// zo: zero-one, no: negative-one

//mat4 mat4_glm_ortho(float l, float r, float b, float t, float zn, float zf)
//{
//		return orthoLH_un(l, r, b, t, zn, zf);
//		return orthoLH_sn(l, r, b, t, zn, zf);
//		return orthoRH_un(l, r, b, t, zn, zf);
//		return orthoRH_sn(l, r, b, t, zn, zf);
//}
//
//mat4 mat4_glm_frustum(float l, float r, float b, float t, float zn, float zf)
//{
//		return frustumLH_un(l, r, b, t, zn, zf);
//		return frustumLH_sn(l, r, b, t, zn, zf);
//		return frustumRH_un(l, r, b, t, zn, zf);
//		return frustumRH_sn(l, r, b, t, zn, zf);
//}
//
//mat4 mat4_glm_perspective(float fovy, float aspect, float zn, float zf)
//{
//		return perspectiveLH_un(fovy, aspect, zn, zf);
//		return perspectiveLH_sn(fovy, aspect, zn, zf);
//		return perspectiveRH_un(fovy, aspect, zn, zf);
//		return perspectiveRH_sn(fovy, aspect, zn, zf);
//}
//
//mat4 mat4_glm_perspectiveFov(float fov, float w, float h, float zn, float zf)
//{
//		return perspectiveFovLH_un(fov, w, h, zn, zf);
//		return perspectiveFovLH_sn(fov, w, h, zn, zf);
//		return perspectiveFovRH_un(fov, w, h, zn, zf);
//		return perspectiveFovRH_sn(fov, w, h, zn, zf);
//}

//mat4 infinitePerspective(float fovy, float aspect, float zn)
//{
//		return infinitePerspectiveLH(fovy, aspect, zn);
//		return infinitePerspectiveRH(fovy, aspect, zn);
//}
//---


//2*zn/w  0       0              0
//0       2*zn/h  0              0
//0       0       zf/(zf-zn)     1
//0       0       zn*zf/(zn-zf)  0

// Build a perspective projection matrix. (left-handed)
mat4 mat4_perspective_lh(float w, float h, float zn, float zf)
{
    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)*zn/w;
    //t.r[1][1] = scast<float>(2)*zn/h;
    //t.r[2][2] = zf/(zf-zn);
    //t.r[3][2] = (zn*zf)/(zn-zf);
    //t.r[2][3] = scast<float>(1);
    //t.r[3][3] = scast<float>(0);

    mat4 tm(
        scast<float>(2)*zn/w,   scast<float>(0),        scast<float>(0),    scast<float>(0),
        scast<float>(0),        scast<float>(2)*zn/h,   scast<float>(0),    scast<float>(0),
        scast<float>(0),        scast<float>(0),        zf/(zf-zn),         scast<float>(1),
        scast<float>(0),        scast<float>(0),        (zn*zf)/(zn-zf),    scast<float>(0)
        );

    return tm;
}


//2*zn/w  0       0              0
//0       2*zn/h  0              0
//0       0       zf/(zn-zf)    -1
//0       0       zn*zf/(zn-zf)  0

// Build a perspective projection matrix. (right-handed)
mat4 mat4_perspective_rh(float w, float h, float zn, float zf)
{
    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)*zn/w;
    //t.r[1][1] = scast<float>(2)*zn/h;
    //t.r[2][2] = zf/(zn-zf);
    //t.r[3][2] = (zn*zf)/(zn-zf);
    //t.r[2][3] = -scast<float>(1);
    //t.r[3][3] = scast<float>(0);

    mat4 tm(
        scast<float>(2)*zn/w,   scast<float>(0),            scast<float>(0),    scast<float>(0),
        scast<float>(0),        scast<float>(2)*zn/h,       scast<float>(0),    scast<float>(0),
        scast<float>(0),        scast<float>(0),            zf/(zn-zf),         -scast<float>(1),
        scast<float>(0),        scast<float>(0),            (zn*zf)/(zn-zf),    scast<float>(0)
        );

    return tm;
}





//width = tanf(fov * 0.5f);
//height = width/aspect;
//yScale = cot(fovY/2)
//xScale = yScale/aspect_ratio
//
//xScale     0          0               0
//0        yScale       0               0
//0          0       zf/(zf-zn)         1
//0          0       -zn*zf/(zf-zn)     0

// Build a perspective projection matrix. (left-handed)
mat4 mat4_perspective_fov_lh(float fovy, float aspect, float zn, float zf)
{
#if 1
    const float y_scale = scast<float>(1)/mf::tan(fovy*scast<float>(0.5));  //cot(fovy/2);
    const float x_scale = y_scale/aspect;

    mat4 tm(
        x_scale,            scast<float>(0),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    y_scale,            scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    zf/(zf-zn),         scast<float>(1),
        scast<float>(0),    scast<float>(0),    -(zn*zf)/(zf-zn),   scast<float>(0)
        );

#else
    const float thfy = tan(fovy*scast<float>(0.5));
    const float& a = aspect;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(1)/(a * thfy);
    //t.r[1][1] = scast<float>(1)/thfy;
    //t.r[2][2] = zf/(zf-zn);
    //t.r[2][3] = scast<float>(1);
    //t.r[3][2] = (zf*zn)/(zn-zf);
    //t.r[3][3] = scast<float>(0);

    mat4 tm(
        scast<float>(1)/(a*thfy),   scast<float>(0),        scast<float>(0),    scast<float>(0),
        scast<float>(0),            scast<float>(1)/thfy,   scast<float>(0),    scast<float>(0),
        scast<float>(0),            scast<float>(0),        zf/(zf-zn),         scast<float>(1),
        scast<float>(0),            scast<float>(0),        (zf*zn)/(zn-zf),    scast<float>(0)
        );
#endif

    return tm;
}

mat4 mat4_glm_perspective_lh_un(float fovy, float aspect, float zn, float zf)
{
	q_assert(abs(aspect - std::numeric_limits<float>::epsilon()) > scast<float>(0));

	const float thfy = tan(fovy/scast<float>(2));
	const float& a = aspect;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(1)/(a * thfy);
	//t.r[1][1] = scast<float>(1)/(thfy);
	//t.r[2][2] = zf/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        scast<float>(1)/(a * thfy),	scast<float>(0),		scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(1)/(thfy),	scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(0),		zf/(zf-zn),		    scast<float>(1),
        scast<float>(0),			scast<float>(0),		-(zf*zn)/(zf-zn),   scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_perspective_lh_sn(float fovy, float aspect, float zn, float zf)
{
	q_assert(abs(aspect - std::numeric_limits<float>::epsilon()) > scast<float>(0));

	const float thfy = tan(fovy/scast<float>(2));
	const float& a = aspect;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(1)/(a * thfy);
	//t.r[1][1] = scast<float>(1)/(thfy);
	//t.r[2][2] = (zf+zn)/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        scast<float>(1)/(a * thfy),	scast<float>(0),		scast<float>(0),					scast<float>(0),
        scast<float>(0),			scast<float>(1)/(thfy),	scast<float>(0),					scast<float>(0),
        scast<float>(0),			scast<float>(0),		(zf+zn)/(zf-zn),					scast<float>(1),
        scast<float>(0),			scast<float>(0),		-scast<float>(2)*zf*zn/(zf-zn),	    scast<float>(0)
        );

	return tm;
}



//yScale = cot(fovY/2)    
//xScale = yScale/aspect_ratio
//
//xScale     0          0              0
//0        yScale       0              0
//0        0        zf/(zn-zf)        -1
//0        0        zn*zf/(zn-zf)      0

// Build a perspective projection matrix. (right-handed)
mat4 mat4_perspective_fov_rh(float fovy, float aspect, float zn, float zf)
{
#if 1
    const float y_scale = scast<float>(1)/mf::tan(fovy*scast<float>(0.5));  //cot(fovy/2);
    const float x_scale = y_scale/aspect;

    mat4 tm(
        x_scale,            scast<float>(0),    scast<float>(0),    scast<float>(0),
        scast<float>(0),    y_scale,            scast<float>(0),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    zf/(zn-zf),         -scast<float>(1),
        scast<float>(0),    scast<float>(0),    (zn*zf)/(zn-zf),    scast<float>(0)
        );

#else

    // tan_half_fovy
    const float thfy = tan(fovy/scast<float>(2));
    const float& a = aspect;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(1)/(a * thfy);
    //t.r[1][1] = scast<float>(1)/thfy;
    //t.r[2][2] = zf/(zn-zf);           // D3D version
    //t.r[2][3] = -scast<float>(1);
    //t.r[3][2] = (zf*zn)/(zn-zf);      // D3D version
    //t.r[3][3] = scast<float>(0);

    ////t.r[2][2] = (zf+zn/(zn-zf)); 	    // OpenGL version
    ////t.r[3][2] = (2.0f*zn*zf/(zn-zf));   // OpenGL version


    mat4 tm(
        scast<float>(1)/(a*thfy),   scast<float>(0),        scast<float>(0),    scast<float>(0),
        scast<float>(0),            scast<float>(1)/thfy,   scast<float>(0),    scast<float>(0),
        scast<float>(0),            scast<float>(0),        zf/(zn-zf),         -scast<float>(1),
        scast<float>(0),            scast<float>(0),        (zf*zn)/(zn-zf),    scast<float>(0)
        );
#endif

    return tm;
}


mat4 mat4_glm_perspective_rh_un(float fovy, float aspect, float zn, float zf)
{
	q_assert(abs(aspect - std::numeric_limits<float>::epsilon()) > scast<float>(0));

	const float thfy = tan(fovy/scast<float>(2));
	const float& a = aspect;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(1)/(a * thfy);
	//t.r[1][1] = scast<float>(1)/(thfy);
	//t.r[2][2] = zf/(zn-zf);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        scast<float>(1)/(a * thfy),	scast<float>(0),		scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(1)/(thfy),	scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(0),		zf/(zn-zf),		    -scast<float>(1),
        scast<float>(0),			scast<float>(0),		-(zf*zn)/(zf-zn),	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_perspective_rh_sn(float fovy, float aspect, float zn, float zf)
{
	q_assert(abs(aspect - std::numeric_limits<float>::epsilon()) > scast<float>(0));

	const float thfy = tan(fovy/scast<float>(2));
	const float& a = aspect;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(1)/(a * thfy);
	//t.r[1][1] = scast<float>(1)/(thfy);
	//t.r[2][2] = -(zf+zn)/(zf-zn);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        scast<float>(1)/(a * thfy),	scast<float>(0),		scast<float>(0),				scast<float>(0),
        scast<float>(0),			scast<float>(1)/(thfy),	scast<float>(0),				scast<float>(0),
        scast<float>(0),			scast<float>(0),		-(zf+zn)/(zf-zn),				-scast<float>(1),
        scast<float>(0),			scast<float>(0),		-scast<float>(2)*zf*zn/(zf-zn),	scast<float>(0)
        );

	return tm;
}




//---
mat4 mat4_glm_perspective_fov_lh_un(float fov, float w, float h, float zn, float zf)
{
	q_assert(w > scast<float>(0));
	q_assert(h > scast<float>(0));
	q_assert(fov > scast<float>(0));

	const float& rad = fov;
	const float th = mf::cos(scast<float>(0.5) * rad)/mf::sin(scast<float>(0.5) * rad);
    const float tw = th * h/w; ///CHECK: todo max(w , h)/min(w , h)?
	

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = tw;
	//t.r[1][1] = th;
	//t.r[2][2] = zf/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        tw,					scast<float>(0),	scast<float>(0),	scast<float>(0),
        scast<float>(0),	th,					scast<float>(0),	scast<float>(0),
        scast<float>(0),	scast<float>(0),	zf/(zf-zn),		    scast<float>(1),
        scast<float>(0),	scast<float>(0),	-(zf*zn)/(zf-zn),   scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_perspective_fov_lh_sn(float fov, float w, float h, float zn, float zf)
{
	q_assert(w > scast<float>(0));
	q_assert(h > scast<float>(0));
	q_assert(fov > scast<float>(0));

	const float& rad = fov;
	const float th = mf::cos(scast<float>(0.5) * rad)/mf::sin(scast<float>(0.5) * rad);
    const float tw = th * h/w; ///CHECK: todo max(w , h)/min(w , h)?

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = tw;
	//t.r[1][1] = th;
	//t.r[2][2] = (zf+zn)/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        tw,					scast<float>(0),	scast<float>(0),				scast<float>(0),
        scast<float>(0),	th,					scast<float>(0),				scast<float>(0),
        scast<float>(0),	scast<float>(0),	(zf+zn)/(zf-zn),				scast<float>(1),
        scast<float>(0),	scast<float>(0),	-scast<float>(2)*zf*zn/(zf-zn),	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_perspective_fov_rh_un(float fov, float w, float h, float zn, float zf)
{
	q_assert(w > scast<float>(0));
	q_assert(h > scast<float>(0));
	q_assert(fov > scast<float>(0));

	const float& rad = fov;
	const float th = mf::cos(scast<float>(0.5) * rad)/mf::sin(scast<float>(0.5) * rad);
    const float tw = th * h/w; ///CHECK: todo max(w , h)/min(w , h)?

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = tw;
	//t.r[1][1] = th;
	//t.r[2][2] = zf/(zn-zf);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        tw,					scast<float>(0),	scast<float>(0),	scast<float>(0),
        scast<float>(0),	th,					scast<float>(0),	scast<float>(0),
        scast<float>(0),	scast<float>(0),	zf/(zn-zf),		    -scast<float>(1),
        scast<float>(0),	scast<float>(0),	-(zf*zn)/(zf-zn),	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_perspective_fov_rh_sn(float fov, float w, float h, float zn, float zf)
{
	q_assert(w > scast<float>(0));
	q_assert(h > scast<float>(0));
	q_assert(fov > scast<float>(0));

	const float& rad = fov;
	const float th = mf::cos(scast<float>(0.5) * rad)/mf::sin(scast<float>(0.5) * rad);
    const float tw = th * h/w; ///CHECK: todo max(w , h)/min(w , h)?

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = tw;
	//t.r[1][1] = th;
	//t.r[2][2] = -(zf+zn)/(zf-zn);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        tw,					scast<float>(0),	scast<float>(0),				scast<float>(0),
        scast<float>(0),	th,					scast<float>(0),				scast<float>(0),
        scast<float>(0),	scast<float>(0),	-(zf+zn)/(zf-zn),				-scast<float>(1),
        scast<float>(0),	scast<float>(0),	-scast<float>(2)*zf*zn/(zf-zn),	scast<float>(0)
        );

	return tm;
}

//-------------------------------

// CHECK:
//2*zn/(r-l)   0            0                0
//0            2*zn/(t-b)   0                0
//(l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)      -1
//0            0            zn*zf/(zn-zf)    0

// Build a perspective projection matrix. (right-handed)
mat4 mat4_perspective_offcenter_rh(float left, float right, float bottom, float top, float zn, float zf)
{
    const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)*zn/(r-l);
    //t.r[1][1] = -scast<float>(2)*zn/(b-t);
    //t.r[2][0] = scast<float>(1) + scast<float>(2)*l/(r-l);
    //t.r[2][1] = -scast<float>(1) -scast<float>(2)*t/(b-t);
    //t.r[2][2] = zf/(zn-zf);
    //t.r[3][2] = (zn*zf)/(zn-zf);
    //t.r[2][3] = -scast<float>(1);
    //t.r[3][3] = scast<float>(0);


    mat4 tm(
        scast<float>(2)*zn/(r-l),                   scast<float>(0),                            scast<float>(0),    scast<float>(0),
        scast<float>(0),                            -scast<float>(2)*zn/(b-t),                  scast<float>(0),    scast<float>(0),
        scast<float>(1) + scast<float>(2)*l/(r-l),  -scast<float>(1) -scast<float>(2)*t/(b-t),  zf/(zn-zf),         -scast<float>(1),
        scast<float>(0),                            scast<float>(0),                            (zn*zf)/(zn-zf),    scast<float>(0)
        );

    return tm;
}


// CHECK:
//2*zn/(r-l)   0            0              0
//0            2*zn/(t-b)   0              0
//(l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
//0            0            zn*zf/(zn-zf)  0

// Build a perspective projection matrix. (left-handed)
mat4 mat4_perspective_offcenter_lh(float left, float right, float bottom, float top, float zn, float zf)
{
    const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)*zn/(r-l);
    //t.r[1][1] = -scast<float>(2)*zn/(b-t);
    //t.r[2][0] = -scast<float>(1) - scast<float>(2)*l/(r-l);
    //t.r[2][1] = scast<float>(1) + scast<float>(2)*t/(b-t);
    //t.r[2][2] = -zf/(zn-zf);
    //t.r[3][2] = (zn*zf)/(zn-zf);
    //t.r[2][3] = scast<float>(1);
    //t.r[3][3] = scast<float>(0);


    mat4 tm(
        scast<float>(2)*zn/(r-l),                       scast<float>(0),                            scast<float>(0),    scast<float>(0),
        scast<float>(0),                                -scast<float>(2)*zn/(b-t),                  scast<float>(0),    scast<float>(0),
        -scast<float>(1) - scast<float>(2)*l/(r-l),     scast<float>(1) + scast<float>(2)*t/(b-t),  -zf/(zn-zf),        scast<float>(1),
        scast<float>(0),                                scast<float>(0),                            (zn*zf)/(zn-zf),    scast<float>(0)
        );

    return tm;
}


mat4 mat4_glm_ortho(float left, float right, float bottom, float top)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(1));
	//t.r[0][0] = scast<float>(2)/(r-l);
	//t.r[1][1] = scast<float>(2)/(t-b);
	//t.r[2][2] = -scast<float>(1);
	//t.r[3][0] = -(r+l)/(r-l);
	//t.r[3][1] = -(t+b)/(t-b);

	mat4 tm(
        scast<float>(2)/(r-l),	scast<float>(0),		scast<float>(0),	scast<float>(0),
        scast<float>(0),		scast<float>(2)/(t-b),	scast<float>(0),	scast<float>(0),
        scast<float>(0),		scast<float>(0),		-scast<float>(1),	scast<float>(0),
        -(r+l)/(r-l),			-(t+b)/(t-b),			scast<float>(0),	scast<float>(1)
        );

	return tm;
}





//2/w  0    0           0
//0    2/h  0           0
//0    0    1/(zf-zn)   0
//0    0   -zn/(zf-zn)  1

// Build an ortho projection matrix. (left-handed)
mat4 mat4_ortho_lh(float w, float h, float zn, float zf)
{
    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)/w;
    //t.r[1][1] = scast<float>(2)/h;
    //t.r[2][2] = scast<float>(1)/(zf-zn);
    //t.r[3][2] = zn/(zn-zf);

    mat4 tm(
        scast<float>(2)/w,      scast<float>(0),        scast<float>(0),            scast<float>(0),
        scast<float>(0),        scast<float>(2)/h,      scast<float>(0),            scast<float>(0),
        scast<float>(0),        scast<float>(0),        scast<float>(1)/(zf-zn),    scast<float>(0),
        scast<float>(0),        scast<float>(0),        zn/(zn-zf),                 scast<float>(1)
        );

    return tm;
}

mat4 mat4_glm_ortho_lh_un(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(1));
	//t.r[0][0] = scast<float>(2)/(r-l);
	//t.r[1][1] = scast<float>(2)/(t-b);
	//t.r[2][2] = scast<float>(1)/(zf-zn);
	//t.r[3][0] = -(r+l)/(r-l);
	//t.r[3][1] = -(t+b)/(t-b);
	//t.r[3][2] = -zn/(zf-zn);

	mat4 tm(
        scast<float>(2)/(r-l),	scast<float>(0),		scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(2)/(t-b),	scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(0),		scast<float>(1)/(zf-zn),	scast<float>(0),
        -(r+l)/(r-l),			-(t+b)/(t-b),			-zn/(zf-zn),				scast<float>(1)
        );

	return tm;
}


mat4 mat4_glm_ortho_lh_sn(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(1));
	//t.r[0][0] = scast<float>(2)/(r-l);
	//t.r[1][1] = scast<float>(2)/(t-b);
	//t.r[2][2] = scast<float>(2)/(zf-zn);
	//t.r[3][0] = -(r+l)/(r-l);
	//t.r[3][1] = -(t+b)/(t-b);
	//t.r[3][2] = -(zf+zn)/(zf-zn);

	mat4 tm(
        scast<float>(2)/(r-l),	scast<float>(0),		scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(2)/(t-b),	scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(0),		scast<float>(2)/(zf-zn),	scast<float>(0),
        -(r+l)/(r-l),			-(t+b)/(t-b),			-(zf+zn)/(zf-zn),			scast<float>(1)
        );

	return tm;
}


//2/w  0    0           0
//0    2/h  0           0
//0    0    1/(zn-zf)   0
//0    0    zn/(zn-zf)  1

// Build an ortho projection matrix. (right-handed)
mat4 mat4_ortho_rh(float w, float h, float zn, float zf)
{
    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)/w;
    //t.r[1][1] = scast<float>(2)/h;
    //t.r[2][2] = scast<float>(1)/(zn-zf);
    //t.r[3][2] = zn/(zn-zf);

    mat4 tm(
        scast<float>(2)/w,  scast<float>(0),    scast<float>(0),            scast<float>(0),
        scast<float>(0),    scast<float>(2)/h,  scast<float>(0),            scast<float>(0),
        scast<float>(0),    scast<float>(0),    scast<float>(1)/(zn-zf),    scast<float>(0),
        scast<float>(0),    scast<float>(0),    zn/(zn-zf),                 scast<float>(1)
        );

    return tm;
}

mat4 mat4_glm_ortho_rh_un(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(1));
	//t.r[0][0] = scast<float>(2)/(r-l);
	//t.r[1][1] = scast<float>(2)/(t-b);
	//t.r[2][2] = -scast<float>(1)/(zf-zn);
	//t.r[3][0] = -(r+l)/(r-l);
	//t.r[3][1] = -(t+b)/(t-b);
	//t.r[3][2] = -zn/(zf-zn);

	mat4 tm(
        scast<float>(2)/(r-l),	scast<float>(0),		scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(2)/(t-b),	scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(0),		-scast<float>(1)/(zf-zn),   scast<float>(0),
        -(r+l)/(r-l),			-(t+b)/(t-b),			-zn/(zf-zn),				scast<float>(1)
        );

	return tm;
}


mat4 mat4_glm_ortho_rh_sn(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(1));
	//t.r[0][0] = scast<float>(2)/(r-l);
	//t.r[1][1] = scast<float>(2)/(t-b);
	//t.r[2][2] = -scast<float>(2)/(zf-zn);
	//t.r[3][0] = -(r+l)/(r-l);
	//t.r[3][1] = -(t+b)/(t-b);
	//t.r[3][2] = -(zf+zn)/(zf-zn);

	mat4 tm(
        scast<float>(2)/(r-l),	scast<float>(0),		scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(2)/(t-b),	scast<float>(0),			scast<float>(0),
        scast<float>(0),		scast<float>(0),		-scast<float>(2)/(zf-zn),   scast<float>(0),
        -(r+l)/(r-l),			-(t+b)/(t-b),			-(zf+zn)/(zf-zn),			scast<float>(1)
        );

	return tm;
}


//2/(r-l)      0            0           0
//0            2/(t-b)      0           0
//0            0            1/(zn-zf)   0
//(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

// Build an ortho projection matrix. (right-handed)
mat4 mat4_ortho_offcenter_rh(float left, float right, float bottom, float top, float zn, float zf)
{
    const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)/(r-l);
    //t.r[1][1] = scast<float>(2)/(t-b);
    //t.r[2][2] = scast<float>(1)/(zn-zf);
    //t.r[3][0] = -scast<float>(1) - scast<float>(2)*l/(r-l);
    //t.r[3][1] = scast<float>(1) + scast<float>(2)*t/(b-t);
    //t.r[3][2] = zn/(zn-zf);


    mat4 tm(
        scast<float>(2)/(r-l),                          scast<float>(0),                            scast<float>(0),            scast<float>(0),
        scast<float>(0),                                scast<float>(2)/(t-b),                      scast<float>(0),            scast<float>(0),
        scast<float>(0),                                scast<float>(0),                            scast<float>(1)/(zn-zf),    scast<float>(0),
        -scast<float>(1) - scast<float>(2)*l/(r-l),    scast<float>(1) + scast<float>(2)*t/(b-t),   zn/(zn-zf),                 scast<float>(1)
        );

    return tm;
}


//2/(r-l)      0            0           0
//0            2/(t-b)      0           0
//0            0            1/(zf-zn)   0
//(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

// Build an ortho projection matrix. (left-handed)
mat4 mat4_ortho_offcenter_lh(float left, float right, float bottom, float top, float zn, float zf)
{
    const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

    //mat4 tm(scast<float>(1));
    //t.r[0][0] = scast<float>(2)/(r-l);
    //t.r[1][1] = scast<float>(2)/(t-b);
    //t.r[2][2] = scast<float>(1)/(zf-zn);
    //t.r[3][0] = -scast<float>(1) -scast<float>(2)*l/(r-l);
    //t.r[3][1] = scast<float>(1) + scast<float>(2)*t/(b-t);
    //t.r[3][2] = zn/(zn-zf);


    mat4 tm(
        scast<float>(2)/(r-l),                      scast<float>(0),                            scast<float>(0),            scast<float>(0),
        scast<float>(0),                            scast<float>(2)/(t-b),                      scast<float>(0),            scast<float>(0),
        scast<float>(0),                            scast<float>(0),                            scast<float>(1)/(zf-zn),    scast<float>(0),
        -scast<float>(1) - scast<float>(2)*l/(r-l), scast<float>(1) + scast<float>(2)*t/(b-t),   zn/(zn-zf),                scast<float>(1)
        );

    return tm;
}



mat4 mat4_glm_frustum_lh_un(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][0] = (r+l)/(r-l);
	//t.r[2][1] = (t+b)/(t-b);
	//t.r[2][2] = zf/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),	scast<float>(0),
        (r+l)/(r-l),				(t+b)/(t-b),				zf/(zf-zn),		    scast<float>(1),
        scast<float>(0),			scast<float>(0),			-(zf*zn)/(zf-zn),	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_frustum_lh_sn(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][0] = (r+l)/(r-l);
	//t.r[2][1] = (t+b)/(t-b);
	//t.r[2][2] = (zf+zn)/(zf-zn);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),				scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),				scast<float>(0),
        (r+l)/(r-l),				(t+b)/(t-b),				(zf+zn)/(zf-zn),				scast<float>(1),
        scast<float>(0),			scast<float>(0),			-scast<float>(2)*zf*zn/(zf-zn),	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_frustum_rh_un(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][0] = (r+l)/(r-l);
	//t.r[2][1] = (t+b)/(t-b);
	//t.r[2][2] = zf/(zn-zf);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -(zf*zn)/(zf-zn);

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),	scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),	scast<float>(0),
        (r+l)/(r-l),				(t+b)/(t-b),				zf/(zn-zf),		    -scast<float>(1),
        scast<float>(0),			scast<float>(0),			-(zf*zn)/(zf-zn),   scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_frustum_rh_sn(float left, float right, float bottom, float top, float zn, float zf)
{
	const float& l = left;
    const float& r = right;
    const float& b = bottom;
    const float& t = top;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][0] = (r+l)/(r-l);
	//t.r[2][1] = (t+b)/(t-b);
	//t.r[2][2] = -(zf+zn)/(zf-zn);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zf*zn/(zf-zn);

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),				scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),				scast<float>(0),
        (r+l)/(r-l),				(t+b)/(t-b),				-(zf+zn)/(zf-zn),				-scast<float>(1),
        scast<float>(0),			scast<float>(0),			-scast<float>(2)*zf*zn/(zf-zn),	scast<float>(0)
        );

	return tm;
}




mat4 mat4_glm_infinite_perspective_lh(float fovy, float aspect, float zn)
{
	const float range = tan(fovy/scast<float>(2)) * zn;
	const float& l = -range * aspect;
	const float& r = range * aspect;
	const float& b = -range;
	const float& t = range;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][2] = scast<float>(1);
	//t.r[2][3] = scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zn;

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),		scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),		scast<float>(0),
        scast<float>(0),			scast<float>(0),			scast<float>(1),		scast<float>(1),
        scast<float>(0),			scast<float>(0),			-scast<float>(2)*zn,	scast<float>(0)
        );

	return tm;
}

mat4 mat4_glm_infinite_perspective_rh(float fovy, float aspect, float zn)
{
	const float range = tan(fovy/scast<float>(2)) * zn;
	const float& l = -range * aspect;
	const float& r = range * aspect;
	const float& b = -range;
	const float& t = range;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][2] = -scast<float>(1);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = -scast<float>(2)*zn;

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),		scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),		scast<float>(0),
        scast<float>(0),			scast<float>(0),			-scast<float>(1),		-scast<float>(1),
        scast<float>(0),			scast<float>(0),			-scast<float>(2)*zn,	scast<float>(0)
        );

	return tm;
}


// Infinite projection matrix: http//www.terathon.com/gdc07_lengyel.pdf
mat4 mat4_glm_tweaked_infinite_perspective(float fovy, float aspect, float zn, float ep)
{
	const float range = mf::tan(fovy/scast<float>(2)) * zn;
	const float& l = -range * aspect;
	const float& r = range * aspect;
	const float& b = -range;
	const float& t = range;

	//mat4 tm(scast<float>(0));
	//t.r[0][0] = scast<float>(2)*zn/(r-l);
	//t.r[1][1] = scast<float>(2)*zn/(t-b);
	//t.r[2][2] = ep-scast<float>(1);
	//t.r[2][3] = -scast<float>(1);
	//t.r[3][2] = (ep-scast<float>(2))*zn;

	mat4 tm(
        scast<float>(2)*zn/(r-l),	scast<float>(0),			scast<float>(0),			scast<float>(0),
        scast<float>(0),			scast<float>(2)*zn/(t-b),	scast<float>(0),			scast<float>(0),
        scast<float>(0),			scast<float>(0),			ep-scast<float>(1),			-scast<float>(1),
        scast<float>(0),			scast<float>(0),			(ep-scast<float>(2))*zn,	scast<float>(0)
        );

	return tm;
}


mat4 mat4_glm_tweaked_infinite_perspective(float fovy, float aspect, float zn)
{
	return mat4_glm_tweaked_infinite_perspective(fovy, aspect, zn, mf::k_epsilon);
}



//-------------------------------
// GLM


} //gm
#ifndef MMATH_HEADER_FILE
#define MMATH_HEADER_FILE

/* MMath.h -- MMath library file
 *
 * Copyright (C) 2017 Zachary Wells
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <math.h>

#if defined(__cplusplus)
extern "C" {
#endif

	#define MMATH_INLINE static inline
	#define MMATH_CONST static const

	//Types
	#if defined(MMATH_DOUBLE)
	typedef double scalar;
	#else
	typedef float scalar;
	#endif

	typedef struct vec2_s {
		union {
			scalar data[2];
			struct { scalar x, y; };
			//struct { scalar g, a; };
		};
	} vec2;
	typedef struct vec3_s {
		union {
			scalar data[3];
			struct { scalar x, y, z; };
			struct { scalar r, g, b; };
		};
	} vec3;
	typedef struct vec4_s {
		union {
			scalar data[4];
			struct { scalar x, y, z, w; };
			struct { scalar r, g, b, a; };
		};
	} vec4;

	typedef struct quat_s {
		union {
			scalar data[4];
			vec4 vec;
			vec3 axis;
			struct { scalar x, y, z, w; };
		};
	} quat;

	typedef struct mat2_s {
		union {
			scalar data[2 * 2];
			vec2 row[2];
			struct {
				scalar x0, y0;
				scalar x1, y1;
			};
			struct {
				vec2 r0;
				vec2 r1;
			};
		};
	} mat2;
	typedef struct mat3_s {
		union {
			scalar data[3 * 3];
			vec3  row[3];
			struct {
				scalar x0, y0, z0;
				scalar x1, y1, z1;
				scalar x2, y2, z2;
			};
			struct {
				vec3 r0;
				vec3 r1;
				vec3 r2;
			};
		};
	} mat3;
	typedef struct mat4_s {
		union {
			scalar data[4 * 4];
			vec4 row[4];
			struct {
				scalar x0, y0, z0, w0;
				scalar x1, y1, z1, w1;
				scalar x2, y2, z2, w2;
				scalar x3, y3, z3, w3;
			};
			struct {
				vec4 r0;
				vec4 r1;
				vec4 r2;
				vec4 r3;
			};
		};
	} mat4;

	typedef struct transform_t {
		vec3 pos;
		vec3 scale;
		quat rot;
	} transform;
	
	#if defined(MMATH_DOUBLE)
	#define mm_sqrt(var) (sqrt(var))
	#define mm_acos(var) (acos(var))
	#define mm_asin(var) (asin(var))
	#define mm_atan(var) (atan(var))
	#define mm_cos(var)  (cos(var))
	#define mm_sin(var)  (sin(var))
	#define mm_tan(var)  (tan(var))
	#define mm_min(x, y) (fmin(x, y))
	#define mm_max(x, y) (fmax(x, y))
	#define mm_abs(var)  (fabs(var))
	#else
	#define mm_sqrt(var) (sqrtf(var))
	#define mm_acos(var) (acosf(var))
	#define mm_asin(var) (asinf(var))
	#define mm_atan(var) (atanf(var))
	#define mm_cos(var)  (cosf(var))
	#define mm_sin(var)  (sinf(var))
	#define mm_tan(var)  (tanf(var))
	#define mm_min(x, y) (fminf(x, y))
	#define mm_max(x, y) (fmaxf(x, y))
	#define mm_abs(var)  (fabsf(var))
	#endif

	//constants
	#define mm_dpi ((scalar)6.283185307179586) //double pi
	#define mm_pi  ((scalar)3.141592653589793) //pi
	#define mm_hpi ((scalar)1.570796326794896) //half pi

	//Functions
	MMATH_INLINE scalar radians(scalar degrees) {
		return degrees * (scalar)0.0174532925199432; //PI / 180
	}
	MMATH_INLINE scalar degrees(scalar radians) {
		return radians * (scalar)57.295779513082325; //180 / PI
	}

	//Vector Math
	#define VEC_FOR(integer) for (int i = 0; i < integer; i++)
	#define MMATH_GENFUNC_VECNEGATE(integer) \
	MMATH_INLINE vec##integer* vec##integer##Negate(vec##integer *dest, const vec##integer *a) { \
		VEC_FOR(integer) { \
			dest->data[i] = -a->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECABS(integer) \
	MMATH_INLINE vec##integer* vec##integer##Abs(vec##integer *dest, const vec##integer *a) { \
		VEC_FOR(integer) { \
			dest->data[i] = mm_abs(a->data[i]); \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECADDSCALAR(integer) \
	MMATH_INLINE vec##integer* vec##integer##AddScalar(vec##integer *dest, const vec##integer *a, scalar b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] + b; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECSUBSCALAR(integer) \
	MMATH_INLINE vec##integer* vec##integer##SubScalar(vec##integer *dest, const vec##integer *a, scalar b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] - b; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECMULSCALAR(integer) \
	MMATH_INLINE vec##integer* vec##integer##MulScalar(vec##integer *dest, const vec##integer *a, scalar b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] * b; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECDIVSCALAR(integer) \
	MMATH_INLINE vec##integer* vec##integer##DivScalar(vec##integer *dest, const vec##integer *a, scalar b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] / b; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECADD(integer) \
	MMATH_INLINE vec##integer* vec##integer##Add(vec##integer *dest, const vec##integer *a, const vec##integer *b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] + b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECSUB(integer) \
	MMATH_INLINE vec##integer* vec##integer##Sub(vec##integer *dest, const vec##integer *a, const vec##integer *b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] - b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECMUL(integer) \
	MMATH_INLINE vec##integer* vec##integer##Mul(vec##integer *dest, const vec##integer *a, const vec##integer *b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] * b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECDIV(integer) \
	MMATH_INLINE vec##integer* vec##integer##Div(vec##integer *dest, const vec##integer *a, const vec##integer *b) { \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] / b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECDOT(integer) \
	MMATH_INLINE scalar vec##integer##Dot(const vec##integer *a, const vec##integer *b) { \
		scalar ret = 0; \
		VEC_FOR(integer) { \
			ret += a->data[i] * b->data[i]; \
		} \
		return ret; \
	}
	#define MMATH_GENFUNC_VECLEN(integer) \
	MMATH_INLINE scalar vec##integer##Length(const vec##integer *a) { \
		scalar sum = 0; \
		VEC_FOR(integer) { \
			sum += a->data[i] * a->data[i]; \
		} \
		return mm_sqrt(sum); \
	}
	#define MMATH_GENFUNC_VECDIST(integer) \
	MMATH_INLINE scalar vec##integer##Distance(const vec##integer *a, const vec##integer *b) { \
		vec##integer dir; \
		vec##integer##Sub(&dir, b, a); \
		return vec##integer##Length(&dir); \
	}
	#define MMATH_GENFUNC_VECNORM(integer) \
	MMATH_INLINE vec##integer* vec##integer##Normalize(vec##integer *dest, const vec##integer *a) { \
		scalar len = vec##integer##Length(a); \
		if (len == 0) { \
			return dest; \
		} \
		len = 1.f / len; \
		VEC_FOR(integer) { \
			dest->data[i] = a->data[i] * len; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_VECLERP(integer) \
	MMATH_INLINE vec##integer* vec##integer##Lerp(vec##integer *dest, const vec##integer *f, const vec##integer *l, scalar t) { \
		vec##integer temp1; \
		vec##integer##Sub(&temp1, l, f); \
		vec##integer temp2; \
		vec##integer##MulScalar(&temp2, &temp1, t); \
		vec##integer##Add(dest, &temp2, f); \
		return dest; \
	}
	#define MMATH_GENFUNC_VECSTANDARD(integer) \
		MMATH_GENFUNC_VECADDSCALAR(integer) \
		MMATH_GENFUNC_VECSUBSCALAR(integer) \
		MMATH_GENFUNC_VECMULSCALAR(integer) \
		MMATH_GENFUNC_VECDIVSCALAR(integer) \
		MMATH_GENFUNC_VECADD(integer) \
		MMATH_GENFUNC_VECSUB(integer) \
		MMATH_GENFUNC_VECMUL(integer) \
		MMATH_GENFUNC_VECDIV(integer) \
		MMATH_GENFUNC_VECDOT(integer) \
		MMATH_GENFUNC_VECLEN(integer) \
		MMATH_GENFUNC_VECDIST(integer) \
		MMATH_GENFUNC_VECNORM(integer) \
		MMATH_GENFUNC_VECLERP(integer) \
		MMATH_GENFUNC_VECNEGATE(integer) \
		MMATH_GENFUNC_VECABS(integer)
	
	MMATH_GENFUNC_VECSTANDARD(2)
	MMATH_CONST vec2 vec2Zero     = { 0, 0 };
	MMATH_CONST vec2 vec2Identity = { 1, 1 };
	MMATH_INLINE vec3* vec2ToVec3(vec3 *dest, const vec2 *a, scalar z) {
		dest->x = a->x;
		dest->y = a->y;
		dest->z = z;
		return dest;
	}
	MMATH_INLINE vec4* vec2ToVec4(vec4 *dest, const vec2 *a, scalar z, scalar w) {
		dest->x = a->x;
		dest->y = a->y;
		dest->z = z;
		dest->w = w;
		return dest;
	}
	
	MMATH_GENFUNC_VECSTANDARD(3)
	MMATH_CONST vec3 vec3Zero     = { 0, 0, 0 };
	MMATH_CONST vec3 vec3Identity = { 1, 1, 1 };
	MMATH_CONST vec3 vec3XAxis    = { 1, 0, 0 };
	MMATH_CONST vec3 vec3YAxis    = { 0, 1, 0 };
	MMATH_CONST vec3 vec3ZAxis    = { 0, 0, 1 };
	MMATH_INLINE vec2* vec3ToVec2(vec2 *dest, const vec3 *a) {
		dest->x = a->x;
		dest->y = a->y;
		return dest;
	}
	MMATH_INLINE vec4* vec3ToVec4(vec4 *dest, const vec3 *a, scalar w) {
		dest->x = a->x;
		dest->y = a->y;
		dest->z = a->z;
		dest->w = w;
		return dest;
	}
	MMATH_INLINE vec3* vec3Cross(vec3 *dest, const vec3 *a, const vec3 *b) {
		dest->x = a->y * b->z - a->z * b->y;
		dest->y = a->z * b->x - a->x * b->z;
		dest->z = a->x * b->y - a->y * b->x;
		return dest;
	}
	
	MMATH_GENFUNC_VECSTANDARD(4)
	MMATH_CONST vec4 vec4Zero     = { 0, 0, 0, 0 };
	MMATH_CONST vec4 vec4Identity = { 1, 1, 1, 1 };
	MMATH_INLINE vec2* vec4ToVec2(vec2 *dest, const vec4 *a) {
		dest->x = a->x;
		dest->y = a->y;
		return dest;
	}
	MMATH_INLINE vec3* vec4ToVec3(vec3 *dest, const vec4 *a) {
		dest->x = a->x;
		dest->y = a->y;
		dest->z = a->z;
		return dest;
	}
	MMATH_INLINE vec3* vec4DivW(vec3 *dest, const vec4 *a) {
		scalar w = (scalar)1.0 / a->w;
		dest->x = a->x * w;
		dest->y = a->y * w;
		dest->z = a->z * w;
		return dest;
	}
	
	//Quaternion Math
	MMATH_CONST quat quatIndentity = { 0, 0, 0, 1 };
	MMATH_INLINE scalar quatLength(const quat *a) {
		return vec4Length((const vec4*)a);
	}
	MMATH_INLINE quat* quatNormalize(quat *dest, const quat *a) {
		vec4Normalize((vec4*)dest, (const vec4*)a);
		return dest;
	}
	MMATH_INLINE quat* quatAddScalar(quat *dest, const quat *a, scalar b) {
		vec4AddScalar((vec4*)dest, (const vec4*)a, b);
		return dest;
	}
	MMATH_INLINE quat* quatMulScalar(quat *dest, const quat *a, scalar b) {
		vec4MulScalar((vec4*)dest, (const vec4*)a, b);
		return dest;
	}
	MMATH_INLINE quat* quatAdd(quat *dest, const quat *a, const quat *b) {
		vec4Add((vec4*)dest, (const vec4*)a, (const vec4*)b);
		return dest;
	}
	MMATH_INLINE quat* quatMul(quat *dest, const quat *a, const quat *b) {
		dest->w = a->w * b->w - vec3Dot(&a->axis, &b->axis);
		
		vec3 BwAv, AwBv, abv, AxB;
		vec3Add(&abv, vec3MulScalar(&BwAv, &a->axis, b->w),
					  vec3MulScalar(&AwBv, &b->axis, a->w));

		vec3Add(&dest->axis, &abv, vec3Cross(&AxB, &a->axis, &b->axis));
		return dest;
	}
	MMATH_INLINE vec3* quatMulVec3(vec3 *dest, const quat *a, const vec3 *b) {
		vec3 cross1;
		vec3Cross(&cross1, &a->axis, b);
		
		vec3 t;
		vec3MulScalar(&t, &cross1, (scalar)2.0);
		
		vec3 tw;
		vec3MulScalar(&tw, &t, a->w);
		
		vec3 cross2;
		vec3Cross(&cross2, &a->axis, &t);
		
		vec3 tw_cross;
		vec3Add(&tw_cross, &tw, &cross2);
		
		vec3Add(dest, b, &tw_cross);
		return dest;
	}
	MMATH_INLINE quat* quatNegate(quat *dest, const quat *a) {
		dest->x = -a->x;
		dest->y = -a->y;
		dest->z = -a->z;
		dest->w = -a->w;
		return dest;
	}
	MMATH_INLINE quat* quatConjugate(quat *dest, const quat *a) {
		dest->x = -a->x;
		dest->y = -a->y;
		dest->z = -a->z;
		dest->w =  a->w;
		return dest;
	}
	MMATH_INLINE quat* quatInverse(quat *dest, const quat *a) {
		quatConjugate(dest, a);
		scalar length = quatLength(a);
		if (length - ((scalar)1.0) <= 0.00001) {
			scalar l2 = (scalar)1.0 / (length * length);
			dest->x *= l2;
			dest->y *= l2;
			dest->z *= l2;
			dest->w *= l2;
		}
		return dest;
	}
	//pitch X | yaw Y | roll Z
	MMATH_INLINE quat* quatEuler(quat *dest, const vec3 *e) {
		scalar cy = mm_cos(e->y * (scalar)0.5);
		scalar sy = mm_sin(e->y * (scalar)0.5);
		scalar cr = mm_cos(e->z * (scalar)0.5);
		scalar sr = mm_sin(e->z * (scalar)0.5);
		scalar cp = mm_cos(e->x * (scalar)0.5);
		scalar sp = mm_sin(e->x * (scalar)0.5);

		dest->x = cy * sr * cp - sy * cr * sp;
		dest->y = cy * cr * sp + sy * sr * cp;
		dest->z = sy * cr * cp - cy * sr * sp;
		dest->w = cy * cr * cp + sy * sr * sp;
		return dest;
	}
	//MMATH_INLINE void quatToEuler(vec3 *dest, const quat *q) {
		//TODO: make this
	//}
	MMATH_INLINE quat* quatAxisAngle(quat *dest, const vec3 *axis, scalar r) {
		scalar a2 = r * (scalar)0.5;
		vec3MulScalar(&dest->axis, axis, mm_sin(a2));
		dest->w = mm_cos(a2);
		return dest;
	}
	MMATH_INLINE mat3* quatToMat3(mat3 *dest, const quat *a) {
		scalar x2 = a->x * a->x,
			   y2 = a->y * a->y,
			   z2 = a->z * a->z,
			   xy = a->x * a->y,
			   xz = a->x * a->z,
			   yz = a->y * a->z,
			   xw = a->x * a->w,
			   yw = a->y * a->w,
			   zw = a->z * a->w;
		mat3 ret = {
			1-(2*(y2+z2)), 2*(xy+zw),     2*(xz-yw),
			2*(xy-zw),     1-(2*(x2+z2)), 2*(yz+xw),
			2*(xz+yw),     2*(yz-xw),     1-(2*(x2+y2))
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat3ToMat4(mat4 *dest, const mat3 *a);
	MMATH_INLINE mat4* quatToMat4(mat4 *dest, const quat *a) {
		mat3 ret;
		quatToMat3(&ret, a);
		mat3ToMat4(dest, &ret);
		return dest;
	}
	MMATH_INLINE quat* quatSlerp(quat *dest, const quat * f, const quat *l, scalar t) {
		scalar dot = vec4Dot((const vec4*)f, (const vec4*)l);

		if (dot < (scalar)0.0) {
			dot = -dot;
			quatInverse(dest, l);
		} else {
			*dest = *l;
		}

		if (dot < (scalar)0.95) {
			scalar angle = mm_acos(dot);
			quat fp;
			quatMulScalar(&fp, f, mm_sin(angle * (1 - t)));

			quat temp;
			quatMulScalar(&temp, dest, mm_sin(angle * t));
			quatAdd(dest, &fp, &temp);
			quatMulScalar(&temp, dest, (scalar)1.0 / mm_sin(angle));
			*dest = temp;
		} else {
			quat temp;
			vec4Lerp((vec4*)&temp, (const vec4*)f, (const vec4*)dest, t);
			*dest = temp;
		}
		
		return dest;
	}
	
	//Matrix Math
	#define MAT_FOR_FLAT(integer) for (int i = 0; i < integer * integer; i++)
	#define MAT_FOR(integer) for (int x = 0; x < integer; x++) for (int y = 0; y < integer; y++)
	#define MMATH_GENFUNC_MATTRPOSE(integer) \
	MMATH_INLINE mat##integer* mat##integer##Transpose(mat##integer * dest, const mat##integer *a) { \
		MAT_FOR(integer) { \
			dest->row[x].data[y] = a->row[y].data[x]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATDIAG(integer) \
	MMATH_INLINE mat##integer* mat##integer##Diagonal(mat##integer *dest, scalar f) { \
		*dest = (mat##integer) {0}; \
		for (int i = 0; i < integer * integer; i += integer + 1) { \
			dest->data[i] = f; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATADD(integer) \
	MMATH_INLINE mat##integer* mat##integer##Add(mat##integer *dest, const mat##integer *a, const mat##integer *b) { \
		MAT_FOR_FLAT(integer) { \
			dest->data[i] = a->data[i] + b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATSUB(integer) \
	MMATH_INLINE mat##integer* mat##integer##Sub(mat##integer *dest, const mat##integer *a, const mat##integer *b) { \
		MAT_FOR_FLAT(integer) { \
			dest->data[i] = a->data[i] - b->data[i]; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATMUL(integer) \
	MMATH_INLINE mat##integer* mat##integer##Mul(mat##integer *dest, const mat##integer *a, const mat##integer *b) { \
		*dest = (mat##integer){0}; \
		MAT_FOR(integer) { \
			VEC_FOR(integer) { \
				dest->row[x].data[y] += a->row[x].data[i] * b->row[i].data[y]; \
			} \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATMULSCALAR(integer) \
	MMATH_INLINE mat##integer* mat##integer##MulScalar(mat##integer *dest, const mat##integer *a, scalar b) { \
		MAT_FOR_FLAT(integer) { \
			dest->data[i] = a->data[i] * b; \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATMULVEC(integer) \
	MMATH_INLINE vec##integer* mat##integer##MulVec##integer(vec##integer *dest, const mat##integer *a, const vec##integer *b) { \
		*dest = (vec##integer){0}; \
		VEC_FOR(integer) { \
			for (int c = 0; c < integer; c++) { \
				dest->data[i] += a->row[c].data[i] * b->data[c]; \
			} \
		} \
		return dest; \
	}
	#define MMATH_GENFUNC_MATSTANDARD(integer) \
		MMATH_GENFUNC_MATTRPOSE(integer) \
		MMATH_GENFUNC_MATDIAG(integer) \
		MMATH_GENFUNC_MATADD(integer) \
		MMATH_GENFUNC_MATSUB(integer) \
		MMATH_GENFUNC_MATMUL(integer) \
		MMATH_GENFUNC_MATMULSCALAR(integer) \
		MMATH_GENFUNC_MATMULVEC(integer)
	
	MMATH_GENFUNC_MATSTANDARD(2)
	MMATH_CONST mat2 mat2Identity = {
		1, 0,
		0, 1
	};
	MMATH_INLINE mat3* mat2ToMat3(mat3 *dest, const mat2 *a) {
		mat3 ret = {
			a->x0, a->y0, 0,
			a->x1, a->y1, 0,
			0,    0,      1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat2ToMat4(mat4 *dest, const mat2 *a) {
		mat4 ret = {
			a->x0, a->y0, 0, 0,
			a->x1, a->y1, 0, 0,
			0,    0,      1, 0,
			0,    0,      0, 1
		};
		*dest = ret;
		return dest;
	}
	
	MMATH_GENFUNC_MATSTANDARD(3)
	MMATH_CONST mat3 mat3Identity = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	MMATH_INLINE mat2* mat3ToMat2(mat2 *dest, const mat3 *a) {
		mat2 ret = {
			a->x0, a->y0,
			a->x1, a->y1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat3ToMat4(mat4 *dest, const mat3 *a) {
		mat4 ret = {
			a->x0, a->y0, a->z0, 0,
			a->x1, a->y1, a->z1, 0,
			a->x2, a->y2, a->z2, 0,
			0,     0,     0,     1
		};
		*dest = ret;
		return dest;
	}
	//MMATH_INLINE void mat3Inverse(mat3 *dest, const mat3 *a) {
	//	mat3 ret; TODO: also make this
	//}
	MMATH_INLINE mat3* mat3RotateX(mat3 *dest, scalar r) {
		scalar c = mm_cos(r);
		scalar s = mm_sin(r);
		mat3 ret = {
			1, 0, 0,
			0, c, s,
			0,-s, c
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat3* mat3RotateY(mat3 *dest, scalar r) {
		scalar c = mm_cos(r);
		scalar s = mm_sin(r);
		mat3 ret = {
			c, 0,-s,
			0, 1, 0,
		    s, 0, c
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat3* mat3RotateZ(mat3 *dest, scalar r) {
		scalar c = mm_cos(r);
		scalar s = mm_sin(r);
		mat3 ret = {
			c, s, 0,
		   -s, c, 0,
			0, 0, 1
		};
		*dest = ret;
		return dest;
	}

	MMATH_GENFUNC_MATSTANDARD(4)
	MMATH_CONST mat4 mat4Identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	MMATH_INLINE mat4* mat4Scale(mat4 *dest, const vec3 *s) {
		mat4 ret = {
			s->x, 0,    0,    0,
			0,    s->y, 0,    0,
			0,    0,    s->z, 0,
			0,    0,    0,    1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat4Translate(mat4 *dest, const vec3 *t) {
		mat4 ret = {
			1,    0,    0,    0,
			0,    1,    0,    0,
			0,    0,    1,    0,
			t->x, t->y, t->z, 1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat4Perspective(mat4 *dest, scalar aspect, scalar fovY, scalar zNear, scalar zFar) {
		scalar f   = (scalar)1.0 / mm_tan(fovY * (scalar)0.5);
		scalar nf  = (scalar)1.0 / (zNear - zFar);
		mat4 ret = {
			f/aspect, 0,  0,                0,
			0,        f,  0,                0,
			0,        0, (zFar+zNear)*nf,  -1,
			0,        0, (2*zFar*zNear)*nf, 0
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat4Ortho(mat4 *dest, scalar left, scalar right, scalar top, scalar bottom, scalar zNear, scalar zFar) {
		scalar tb = top - bottom;
		scalar rf = right - left;
		scalar fn = zFar - zNear;
		mat4 ret = {
			2/rf,               0,                  0,                      0,
			0,                  2/tb,               0,                      0,
			0,                  0,                  -2/fn,                  0,
			-(right + left)/rf, -(top + bottom)/tb, -(zFar + zNear)/fn,     1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat4* mat4LookAt(mat4 *dest, const vec3 *eye, const vec3 *center, const vec3 *up) {
		vec3 temp;
		vec3Sub(&temp, center, eye);

		vec3 z;
		vec3Normalize(&z, &temp);

		vec3 x;
		vec3Cross(&temp, up, &z);
		vec3Normalize(&x, &temp);

		vec3 y;
		vec3Cross(&temp, &z, &x);
		vec3Normalize(&y, &temp);

		scalar n_dot_x = -vec3Dot(&x, eye);
		scalar n_dot_y = -vec3Dot(&y, eye);
		scalar n_dot_z = -vec3Dot(&z, eye);

		mat4 ret = {
			x.x,   y.x,   z.x,   0,
			x.y,   y.y,   z.y,   0,
			x.z,   y.z,   z.z,   0,
			n_dot_x, n_dot_y, n_dot_z, 1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat2* mat4ToMat2(mat2 *dest, const mat4 *a) {
		mat2 ret = {
			a->x0, a->y0,
			a->x1, a->y1
		};
		*dest = ret;
		return dest;
	}
	MMATH_INLINE mat3* mat4ToMat3(mat3 *dest, const mat4 *a) {
		mat3 ret = {
			a->x0, a->y0, a->z0,
			a->x1, a->y1, a->z1,
			a->x2, a->y2, a->z2
		};
		*dest = ret;
		return dest;
	}

	//Transformations
	MMATH_CONST transform transformIdentity = { {0,0,0}, {1,1,1}, {0,0,0,1} };
	MMATH_INLINE mat4* transformToMat4(mat4 *dest, const transform *t) {
		mat4 ret = {
			t->scale.x, 0, 0, 0,
			0, t->scale.y, 0, 0,
			0, 0, t->scale.z, 0,
			t->pos.x, t->pos.y, t->pos.z, 1
		};
		mat4 rotate;
		quatToMat4(&rotate, &t->rot);
		mat4Mul(dest, &rotate, &ret);
		return dest;
	}
	//TODO: Solve transform inverse (this could mean a lot)
	MMATH_INLINE transform* transformMul(transform *dest, const transform *a, const transform *b) {
		vec3 pos;
		quatMulVec3(&pos, &a->rot, &b->pos);

		vec3 posScale;
		vec3Mul(&posScale, &pos, &a->scale);

		vec3Add(&dest->pos, &posScale, &a->pos);
		vec3Mul(&dest->scale, &a->scale, &b->scale);
		quatMul(&dest->rot, &a->rot, &b->rot);
		return dest;
	}
	MMATH_INLINE transform* transformLerp(transform *dest, const transform *f, const transform *l, scalar t) {
		vec3Lerp(&dest->pos, &f->pos, &l->pos, t);
		vec3Lerp(&dest->scale, &f->scale, &l->scale, t);
		quatSlerp(&dest->rot, &f->rot, &l->rot, t);
		return dest;
	}

#if defined(__cplusplus)
}
#endif

#endif //MMATH_HEADER_FILE

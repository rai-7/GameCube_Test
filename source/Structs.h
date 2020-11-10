#include "gctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/

typedef struct tagcamera {
	guVector pos;
	guVector up;
	guVector view;
} camera;

/*-------------------------------------------------------------------*/

typedef struct f32vec2 /** 2 32-bit float **/
{
	f32 x, y;
} f32vec2;

typedef struct f64vec2 /** 2 64-bit double **/
{
	f64 x, y;
} f64vec2;

typedef struct u8vec2 /** 2 unsigned 8-bit int **/
{
	u8 x, y;
} u8vec2;

typedef struct u8vec3 /** 3 unsigned 8-bit int **/
{
	u8 x, y, z;
} u8vec3;

typedef struct vu8vec2 /** 2 volatile unsigned 8-bit int **/
{
	vu8 x, y;
} vu8vec2;

typedef struct vu8vec3 /** 3 volatile unsigned 8-bit int **/
{
	vu8 x, y, z;
} vu8vec3;

typedef struct u64vec2 /** 2 unsigned 64-bit int **/
{
	u64 x, y;
} u64vec2;

typedef struct u64vec3 /** 3 unsigned 64-bit int **/
{
	u64 x, y, z;
} u64vec3;

typedef struct s8vec2 /** 2 signed 8-bit int **/
{
	s8 x;
	s8 y; 
} s8vec2;

typedef struct s8vec3 /** 3 signed 8-bit int **/
{
	s8 x, y, z;
} s8vec3;

typedef struct bvec2 /** 2 bool **/
{
	BOOL a, b;
} bvec2;

typedef struct ivec2 /** 2 signed 16-bit int **/
{
	int x, y;
} ivec2;

/*-------------------------------------------------------------------*/
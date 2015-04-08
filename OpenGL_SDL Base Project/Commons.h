#pragma once
#define MAX_VERTICES 15000
#define MAX_POLYGONS 15000

struct lighting{
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};


enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVEL3,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum ANIMMODE
{
	ANIM_SPIN = 0,
	ANIM_STRAFE,
	ANIM_BOUNCE,
	ANIM_CUSTOM
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(float initialX, float initialY, float initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}
};

typedef enum CameraType 
{
	CAMERA_PERSPECTIVE,
	CAMERA_ORTHO
};

typedef enum BufferType 
{
	BUFFER_SINGLE,
	BUFFER_DOUBLE
};

//Object stuff

typedef struct
{
	float x, y, z;
} vertex_type;

typedef struct
{
	float x, y, z;
} normal_type;

typedef struct
{
	int a, b, c;
} polygon_type;

typedef struct
{
	float u, v;
} mapcoord_type;

typedef struct
{
	char name[20];

	int vertices_qty;
	int polygons_qty;

	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];

	int id_texture;
} obj_type, *obj_type_ptr;

typedef struct
{
	char name[20];

	int vertices_qty;
	int polygons_qty;

	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];
	normal_type normals[MAX_VERTICES];

	int id_texture;
} obj_type_2, *obj_type_2_ptr;
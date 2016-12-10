#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	//--------------------------------------------//
	//Start
	Cube cube1;
	PhysBody3D* cube1body;
	//--------------------------------------------//
	//Arc
	Cube cube1_1;
	PhysBody3D* cube1_1body;
	Cube cube1_2;
	PhysBody3D* cube1_2body;
	Cube cube1_3;
	PhysBody3D* cube1_3body;
	//--------------------------------------------//
	//Curve
	Cylinder cylinder1;
	PhysBody3D* cylinder1body;
	//--------------------------------------------//
	//First jump
	Cube cube2;
	PhysBody3D* cube2body;
	Cube cube3;
	PhysBody3D* cube3body;
	//--------------------------------------------//
	//Curves
	Cylinder cylinder2;
	PhysBody3D* cylinder2body;
	Cube cube4;
	PhysBody3D* cube4body;
	Cylinder cylinder3;
	PhysBody3D* cylinder3body;
	Cube cube5;
	PhysBody3D* cube5body;
	Cylinder cylinder4;
	PhysBody3D* cylinder4body;
	Cube cube6;
	PhysBody3D* cube6body;
	Cylinder cylinder5;
	PhysBody3D* cylinder5body;
	//--------------------------------------------//
	//Rised curve
	Cube cube7;
	PhysBody3D* cube7body;
	Cube cube8;
	PhysBody3D* cube8body;
	Cube cube9;
	PhysBody3D* cube9body;
	Cube cube10;
	PhysBody3D* cube10body;
	Cylinder cylinder6;
	PhysBody3D* cylinder6body;
	Cube cube11;
	PhysBody3D* cube11body;
	Cube cube12;
	PhysBody3D* cube12body;
	Cube cube13;
	PhysBody3D* cube13body;














	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
};

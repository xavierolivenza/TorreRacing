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

	//Start
	Cube cube1;
	PhysBody3D* cube1body;
	//Arc
	Cube cube1_1;
	PhysBody3D* cube1_1body;
	Cube cube1_2;
	PhysBody3D* cube1_2body;
	Cube cube1_3;
	PhysBody3D* cube1_3body;
	//Curve
	Cylinder cylinder1;
	PhysBody3D* cylinder1body;

	Cube cube2;
	PhysBody3D* cube2body;








	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
};

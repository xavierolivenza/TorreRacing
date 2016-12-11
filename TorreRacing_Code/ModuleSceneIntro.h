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

private:
	//--------------------------------------------//
	//-----------------Car parts------------------//
	//--------------------------------------------//
	//Chasis
	Cube		  p_chassis;
	PhysBody3D*   pb_chassis;
	//--------------------------------------------//
	//Wheels
	Cylinder	  p_wheel;
	PhysBody3D*   pb_wheel;
	Cylinder	  p_wheel2;
	PhysBody3D*   pb_wheel2;
	//--------------------------------------------//
	//Motor
	PhysMotor3D*  left_wheel;
	PhysMotor3D*  right_wheel;
	//--------------------------------------------//

	//--------------------------------------------//
	//---------------Circuit parts----------------//
	//--------------------------------------------//
	//Start
	Cube		 cube1;
	PhysBody3D*  cube1body;
	//--------------------------------------------//
	//Start sensor
	Cube		 start_sensor;
	PhysBody3D*  start_sensorbody;
	//--------------------------------------------//
	//Arc
	Cube		 cube1_1;
	PhysBody3D*  cube1_1body;
	Cube		 cube1_2;
	PhysBody3D*  cube1_2body;
	Cube		 cube1_3;
	PhysBody3D*  cube1_3body;
	//--------------------------------------------//
	//Curve
	Cylinder     cylinder1;
	PhysBody3D*  cylinder1body;
	//--------------------------------------------//
	//First jump
	Cube	     cube2;
	PhysBody3D*  cube2body;
	Cube         cube3;
	PhysBody3D*  cube3body;
	//--------------------------------------------//
	//Curves
	Cylinder     cylinder2;
	PhysBody3D*  cylinder2body;
	Cube         cube4;
	PhysBody3D*  cube4body;
	Cylinder     cylinder3;
	PhysBody3D*  cylinder3body;
	Cube		 cube5;
	PhysBody3D*  cube5body;
	Cylinder	 cylinder4;
	PhysBody3D*  cylinder4body;
	Cube		 cube6;
	PhysBody3D*  cube6body;
	Cylinder	 cylinder5;
	PhysBody3D*  cylinder5body;
	//--------------------------------------------//
	//Rised curve
	Cube		 cube7;
	PhysBody3D*  cube7body;
	Cube		 cube8;
	PhysBody3D*  cube8body;
	Cube		 cube9;
	PhysBody3D*  cube9body;
	Cube		 cube10;
	PhysBody3D*  cube10body;
	Cylinder	 cylinder6;
	PhysBody3D*  cylinder6body;
	Cube		 cube11;
	PhysBody3D*  cube11body;
	Cube		 cube12;
	PhysBody3D*  cube12body;
	Cube		 cube13;
	PhysBody3D*  cube13body;
	//--------------------------------------------//
	//Before consecutive jumps
	Cylinder	 cylinder7;
	PhysBody3D*  cylinder7body;
	Cube		 cube14;
	PhysBody3D*  cube14body;
	Cylinder     cylinder8;
	PhysBody3D*  cylinder8body;
	//--------------------------------------------//
	//Consecutive jumps
	Cube		 cube15;
	PhysBody3D*  cube15body;
	Cube		 cube16;
	PhysBody3D*  cube16body;
	Cube		 cube17;
	PhysBody3D*  cube17body;
	Cube		 cube18;
	PhysBody3D*  cube18body;










	bool sensors_debug = true;

public:

	bool first_time_start_sensor = true;

};

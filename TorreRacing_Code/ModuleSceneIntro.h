#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "Chicken.h"

struct PhysBody3D;
struct PhysMotor3D;
class Chicken;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void RestartChickens();//Function needded to keep chickens_dynamic_array private

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
	Cylinder     cylinder9;
	PhysBody3D*  cylinder9body;
	//--------------------------------------------//
	//After consecutive jumps
	Cube		 cube19;
	PhysBody3D*  cube19body;
	Cylinder     cylinder10;
	PhysBody3D*  cylinder10body;
	Cube		 cube20;
	PhysBody3D*  cube20body;
	Cylinder     cylinder11;
	PhysBody3D*  cylinder11body;
	Cube		 cube21;
	PhysBody3D*  cube21body;
	//--------------------------------------------//
	//Wood
	Cylinder     cylinderWood;
	PhysBody3D*  cylinderWoodbody;
	Cylinder     cylinderWoodHit;
	PhysBody3D*  cylinderWoodHitbody;
	Sphere       sphere1WoodSupport1;
	PhysBody3D*  sphere1WoodSupport1body;
	Cylinder     cylinderWoodSupport1;
	PhysBody3D*  cylinderWoodSupport1body;
	Sphere       sphere2WoodSupport1;
	PhysBody3D*  sphere2WoodSupport1body;
	Sphere       sphere1WoodSupport2;
	PhysBody3D*  sphere1WoodSupport2body;
	Cylinder     cylinderWoodSupport2;
	PhysBody3D*  cylinderWoodSupport2body;
	Sphere       sphere2WoodSupport2;
	PhysBody3D*  sphere2WoodSupport2body;
	//--------------------------------------------//
	Cylinder     cylinder12;
	PhysBody3D*  cylinder12body;
	Cube		 cube22;
	PhysBody3D*  cube22body;
	Cylinder     cylinder13;
	PhysBody3D*  cylinder13body;
	Cube		 cube23;
	PhysBody3D*  cube23body;
	//--------------------------------------------//
	//Final line
	Cylinder     cylinder14;
	PhysBody3D*  cylinder14body;
	Cube		 cube24;
	PhysBody3D*  cube24body;
	//--------------------------------------------//
	Cube		 DeathSensor;
	PhysBody3D*  DeathSensorbody;
	//--------------------------------------------//

	//--------------------------------------------//
	//-----------------Barn parts-----------------//
	//--------------------------------------------//
	Cube		 barn_sensor;
	PhysBody3D*  barn_sensorbody;
	Cube		 barn_ground;
	PhysBody3D*  barn_ground_body;
	Cube		 barn_grass;
	PhysBody3D*  barn_grass_body;
	Cube		 barn_wall_1;
	PhysBody3D*  barn_wall_1_body;
	Cube		 barn_wall_2;
	PhysBody3D*  barn_wall_2_body;
	Cube		 barn_wall_3;
	PhysBody3D*  barn_wall_3_body;
	Cube		 barn_wall_4;
	PhysBody3D*  barn_wall_4_body;
	Cube		 barn_wall_5;
	PhysBody3D*  barn_wall_5_body;
	Cube		 barn_wall_6;
	PhysBody3D*  barn_wall_6_body;
	Cube		 barn_wall_7;
	PhysBody3D*  barn_wall_7_body;
	Cube		 barn_wall_8;
	PhysBody3D*  barn_wall_8_body;
	//--------------------------------------------//
	
	//--------------------------------------------//
	//------------------Chickens------------------//
	//--------------------------------------------//
	p2DynArray<Chicken*> chickens_dynamic_array;
	//--------------------------------------------//
	
public:

	bool first_time_start_sensor = true;
	bool first_time_barn_sensor = true;
	bool sensors_debug = false;

};

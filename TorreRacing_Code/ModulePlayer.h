#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	Timer jump_coolddown;

private:
	btVector3 vehicle_origin_axis;

	Cube cube2;
	PhysBody3D* cube2body;

	Cube cube3;
	PhysBody3D* cube3body;

	Cube cube4;
	PhysBody3D* cube4body;

};
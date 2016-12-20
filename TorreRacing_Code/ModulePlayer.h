#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 10.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void RestartGame();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	uint COW_fx;

	Timer game_timer;

	bool freecam = false;

private:

	mat4x4 original_vehicle_trans;

	btVector3 vehicle_origin_axis;

	Timer jump_coolddown;
	
	Timer break_timer;
};
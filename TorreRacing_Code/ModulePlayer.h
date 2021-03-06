#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 3000.0f
#define TURN_DEGREES 10.0f * DEGTORAD
#define BRAKE_POWER 3000.0f
#define FRONT_IMPULSE 30000.0f
#define LATERAL_IMPULSE 15000.0f
#define JUMP_IMPULSE 15000.0f
#define JUMP_COOLDOWN 3.0f

#define NORMAL_SPEED_LIMIT 150.0f
#define FRONT_DASH_SPEED_LIMIT 250.0f

/*
#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 10.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define FRONT_IMPULSE 10000.0f
#define LATERAL_IMPULSE 5000.0f
#define JUMP_COOLDOWN 3.0f
*/

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

	uint Cow_fx;
	

	Timer game_timer;
	uint chickens_taken = 0;

	Timer death_timer;

	bool freecam = false;
	bool win = false;
	bool fall = false;

private:

	mat4x4 original_vehicle_trans;

	btVector3 vehicle_origin_axis;

	Timer jump_coolddown;
	
	Timer break_timer;

	int lowesttime_all_in_miliseconds = 0;
	int lowesttime_miliseconds = 0;
	int lowesttime_seconds = 0;
	int lowesttime_min = 0;

	bool first_best_time = true;

};
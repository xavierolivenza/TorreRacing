#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

struct PhysVehicle3D;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

private:
	
	vec3			CameraPos;
	vec3			ViewDirection;
	vec3			VehiclePos;
	PhysVehicle3D*  Target;
	mat4x4			ViewMatrix;
	mat4x4			ViewMatrixInverse;

};
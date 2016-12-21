#pragma once

#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleSceneIntro.h"

class ModuleSceneIntro;

class Chicken
{

public:

	Chicken();
	Chicken(const float x, const float y, const float z, ModuleSceneIntro* This);
	~Chicken();

private:

	Sphere chicken_sensor;
	PhysBody3D* chicken_sensor_body;

	Cube Head;
	PhysBody3D* HeadBody;
	mat4x4 Original_Head_Transform;
	Cube Body;
	PhysBody3D* BodyBody;
	mat4x4 Original_Body_Transform;
	Cylinder Leg1;
	PhysBody3D* Leg1Body;
	mat4x4 Original_Leg1_Transform;
	Cylinder Leg2;
	PhysBody3D* Leg2Body;
	mat4x4 Original_Leg2_Transform;

	vec3 OriginalPosition;

public:

	void ActivateChicken();
	void RenderChicken();
	const PhysBody3D* GetSensorBody() const;

	void RestartChicken();

	bool firsttime = true;

private:

	void CreateChicken(const float x, const float y, const float z, ModuleSceneIntro* This);

};
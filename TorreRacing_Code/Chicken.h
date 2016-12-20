#pragma once

#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleSceneIntro.h"

class ModuleSceneIntro;

class Chicken
{

public:

	Chicken();
	Chicken(const float x, const float y, const float z, const float angle, const vec3 RotationAxis, ModuleSceneIntro* This);
	~Chicken();

private:

	Sphere chicken_sensor;
	PhysBody3D* chicken_sensor_body;

	Cube Head;
	PhysBody3D* HeadBody;
	Cube Body;
	PhysBody3D* BodyBody;
	Cylinder Leg1;
	PhysBody3D* Leg1Body;
	Cylinder Leg2;
	PhysBody3D* Leg2Body;

	bool GraphicChickeniscreated = false;
	bool isphysic = false;

public:

	void CreatePhysicChicken();
	void RenderChicken();
	const PhysBody3D* GetSensorBody() const;

private:

	void CreateGraphicChicken(const float x, const float y, const float z, const float angle, const vec3 RotationAxis, ModuleSceneIntro* This);

};
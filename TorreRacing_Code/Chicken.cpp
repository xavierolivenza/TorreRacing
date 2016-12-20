#include "Chicken.h"

#include "Application.h"
#include "ModulePhysics3D.h"

Chicken::Chicken()
{

}

Chicken::Chicken(const float x, const float y, const float z, const float angle, const vec3 RotationAxis, ModuleSceneIntro* This)
{
	CreateGraphicChicken(x, y, z, angle, RotationAxis, This);
}

Chicken::~Chicken()
{

}

void Chicken::CreateGraphicChicken(const float x, const float y, const float z, const float angle, const vec3 RotationAxis, ModuleSceneIntro* This)
{

	// -----------------------------------------------------------

	Body.size.x = 1.5;
	Body.size.y = 1;
	Body.size.z = 1;
	Body.color = White;
	Body.SetPos(x, y, z);
	Body.SetRotation(angle, RotationAxis);

	// -----------------------------------------------------------

	Head.size.x = 0.75;
	Head.size.y = 1;
	Head.size.z = 0.5;
	Head.color = White;
	Head.SetPos(x + 0.75, y + 0.75, z);
	Head.SetRotation(angle, RotationAxis);

	// -----------------------------------------------------------

	Leg1.radius = 0.1;
	Leg1.height = 0.75;
	Leg1.color = Yellow;
	Leg1.SetPos(x, y - 0.75, z - 0.3f);
	Leg1.SetRotation(90, { 0,0,1 });

	// -----------------------------------------------------------

	Leg2.radius = 0.1;
	Leg2.height = 0.75;
	Leg2.color = Yellow;
	Leg2.SetPos(x, y - 0.75, z + 0.3f);
	Leg2.SetRotation(90, { 0,0,1 });

	// -----------------------------------------------------------

	chicken_sensor.radius = 1;
	chicken_sensor.color = Green;
	chicken_sensor.SetPos(x, y, z);

	chicken_sensor_body = App->physics->AddBody(chicken_sensor, 0);
	chicken_sensor_body->SetAsSensor(true);
	chicken_sensor_body->collision_listeners.add(This);
	chicken_sensor_body->SetPos(x, y, z);

	GraphicChickeniscreated = true;

}

void Chicken::CreatePhysicChicken()
{
	if (GraphicChickeniscreated == true)
	{
		// -----------------------------------------------------------

		BodyBody = App->physics->AddBody((Body), 10);

		// -----------------------------------------------------------

		HeadBody = App->physics->AddBody((Head), 10);

		App->physics->AddConstraintP2P(*BodyBody, *HeadBody, { 1.0f,0,0.25f }, { -0.45f,-0.5f,0 });

		// -----------------------------------------------------------

		Leg1Body = App->physics->AddBody(Leg1, 10);

		App->physics->AddConstraintP2P(*BodyBody, *Leg1Body, { -0.35f,-0.5f,-0.35f }, { +0.7f,0,0 });

		// -----------------------------------------------------------

		Leg2Body = App->physics->AddBody(Leg2, 10);

		App->physics->AddConstraintP2P(*BodyBody, *Leg2Body, { +0.35f,-0.5f,-0.35f }, { 0.7f,0,0 });

		// -----------------------------------------------------------
		isphysic = true;
	}
}

void Chicken::RenderChicken()
{
	//uncomment it to temporal sensor visual
	//chicken_sensor.Render();
	if (App->scene_intro->sensors_debug == true)
	{
		chicken_sensor_body->GetTransform(&chicken_sensor.transform);
		chicken_sensor.Render();
	}
	if (isphysic == true)
	{
		HeadBody->GetTransform(&Head.transform);
		BodyBody->GetTransform(&Body.transform);
		Leg1Body->GetTransform(&Leg1.transform);
		Leg2Body->GetTransform(&Leg2.transform);
	}
	Head.Render();
	Body.Render();
	Leg1.Render();
	Leg2.Render();
}

const PhysBody3D* Chicken::GetSensorBody() const
{
	return chicken_sensor_body;
}
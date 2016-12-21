#include "Chicken.h"

#include "Application.h"
#include "ModulePhysics3D.h"

Chicken::Chicken()
{

}

Chicken::Chicken(const float x, const float y, const float z, ModuleSceneIntro* This)
{
	CreateChicken(x, y, z, This);
}

Chicken::~Chicken()
{
}

void Chicken::CreateChicken(const float x, const float y, const float z, ModuleSceneIntro* This/*needed to set hte chicken collider*/)
{

	OriginalPosition.Set(x, y, z);

	// -----------------------------------------------------------

	Body.size.x = 1.5;
	Body.size.y = 1;
	Body.size.z = 1;
	Body.color = White;
	Body.SetPos(x, y, z);
	Body.SetRotation(0, { 0,1,0 });

	BodyBody = App->physics->AddBody((Body), 10);
	BodyBody->Freeze(true);

	// -----------------------------------------------------------

	Head.size.x = 0.75;
	Head.size.y = 1;
	Head.size.z = 0.5;
	Head.color = White;
	Head.SetPos(x + 0.75, y + 0.75, z);
	Head.SetRotation(0, { 0,1,0 });

	HeadBody = App->physics->AddBody((Head), 10);
	HeadBody->Freeze(true);
	
	App->physics->AddConstraintP2P(*BodyBody, *HeadBody, { 1.0f,0,0.25f }, { -0.45f,-0.5f,0 });

	// -----------------------------------------------------------

	Peak.radius = 0.1;
	Peak.height = 0.75;
	Peak.color = Yellow;
	Peak.SetPos(x + 1.3, y + 0.55, z);
	Peak.SetRotation(90, { 1,0,0 });

	PeakBody = App->physics->AddBody(Peak, 1);
	PeakBody->Freeze(true);

	App->physics->AddConstraintP2P(*HeadBody, *PeakBody, { 0.25f,0,0.25f }, { -0.25f,-0.3f,0 });

	// -----------------------------------------------------------

	Eye1.size.x = 0.15;
	Eye1.size.y = 0.15;
	Eye1.size.z = 0.15;
	Eye1.color = Black;
	Eye1.SetPos(x + 1, y + 0.80, z - 0.25);
	Eye1.SetRotation(0, { 0,1,0 });

	Eye1Body = App->physics->AddBody((Eye1), 0.1);
	Eye1Body->Freeze(true);

	App->physics->AddConstraintP2P(*HeadBody, *Eye1Body, { 0.05f,0,0.05f }, { -0.05f,-0.10f,0 });

	// -----------------------------------------------------------

	Eye2.size.x = 0.15;
	Eye2.size.y = 0.15;
	Eye2.size.z = 0.15;
	Eye2.color = Black;
	Eye2.SetPos(x + 1, y + 0.80, z + 0.25);
	Eye2.SetRotation(0, { 0,1,0 });

	Eye2Body = App->physics->AddBody((Eye2), 0.1);
	Eye2Body->Freeze(true);

	App->physics->AddConstraintP2P(*HeadBody, *Eye2Body, { 0.05f,0,0.05f }, { -0.05f,-0.10f,0 });

	// -----------------------------------------------------------

	Leg1.radius = 0.1;
	Leg1.height = 0.75;
	Leg1.color = Yellow;
	Leg1.SetPos(x, y - 0.75, z - 0.3f);
	Leg1.SetRotation(90, { 0,0,1 });

	Leg1Body = App->physics->AddBody(Leg1, 10);
	Leg1Body->Freeze(true);

	App->physics->AddConstraintP2P(*BodyBody, *Leg1Body, { -0.35f,-0.5f,-0.35f }, { +0.7f,0,0 });

	// -----------------------------------------------------------

	Leg2.radius = 0.1;
	Leg2.height = 0.75;
	Leg2.color = Yellow;
	Leg2.SetPos(x, y - 0.75, z + 0.3f);
	Leg2.SetRotation(90, { 0,0,1 });

	Leg2Body = App->physics->AddBody(Leg2, 10);
	Leg2Body->Freeze(true);

	App->physics->AddConstraintP2P(*BodyBody, *Leg2Body, { +0.35f,-0.5f,-0.35f }, { 0.7f,0,0 });

	// -----------------------------------------------------------

	chicken_sensor.radius = 1;
	chicken_sensor.color = Green;
	chicken_sensor.SetPos(x, y, z);

	chicken_sensor_body = App->physics->AddBody(chicken_sensor, 0);
	chicken_sensor_body->SetAsSensor(true);
	chicken_sensor_body->collision_listeners.add(This);
	chicken_sensor_body->SetPos(x, y, z);

	// -----------------------------------------------------------

	HeadBody->GetTransform(&Original_Head_Transform);
	BodyBody->GetTransform(&Original_Body_Transform);
	Leg1Body->GetTransform(&Original_Leg1_Transform);
	Leg2Body->GetTransform(&Original_Leg2_Transform);
	PeakBody->GetTransform(&Original_Peak_Transform);
	Eye1Body->GetTransform(&Original_Eye1_Transform);
	Eye2Body->GetTransform(&Original_Eye2_Transform);
}

void Chicken::ActivateChicken()
{
	BodyBody->Freeze(false);
	HeadBody->Freeze(false);
	Leg1Body->Freeze(false);
	Leg2Body->Freeze(false);
	PeakBody->Freeze(false);
	Eye1Body->Freeze(false);
	Eye2Body->Freeze(false);
}

void Chicken::RenderChicken()
{
	if (App->scene_intro->sensors_debug == true)
	{
		chicken_sensor_body->GetTransform(&chicken_sensor.transform);
		chicken_sensor.Render();
	}
	HeadBody->GetTransform(&Head.transform);
	BodyBody->GetTransform(&Body.transform);
	Leg1Body->GetTransform(&Leg1.transform);
	Leg2Body->GetTransform(&Leg2.transform);
	PeakBody->GetTransform(&Peak.transform);
	Eye1Body->GetTransform(&Eye1.transform);
	Eye2Body->GetTransform(&Eye2.transform);

	Head.Render();
	Body.Render();
	Leg1.Render();
	Leg2.Render();
	Peak.Render();
	Eye1.Render();
	Eye2.Render();
}

const PhysBody3D* Chicken::GetSensorBody() const
{
	return chicken_sensor_body;
}

void Chicken::RestartChicken()
{

	int x = 0;
	int y = 0;
	int z = 0;

	x = OriginalPosition.x;
	y = OriginalPosition.y;
	z = OriginalPosition.z;

	BodyBody->SetPos(x, y, z);
	BodyBody->SetTransform(&Original_Body_Transform);

	// -----------------------------------------------------------

	HeadBody->SetPos(x + 0.75, y + 0.75, z);
	HeadBody->SetTransform(&Original_Head_Transform);

	// -----------------------------------------------------------

	Leg1Body->SetPos(x, y - 0.75, z - 0.3f);
	Leg1Body->SetTransform(&Original_Leg1_Transform);

	// -----------------------------------------------------------

	Leg2Body->SetPos(x, y - 0.75, z + 0.3f);
	Leg2Body->SetTransform(&Original_Leg2_Transform);

	// -----------------------------------------------------------
	
	PeakBody->SetPos(x + 1.3, y + 0.55, z);
	PeakBody->SetTransform(&Original_Peak_Transform);

	// -----------------------------------------------------------
	
	Eye1Body->SetPos(x + 1, y + 0.80, z - 0.25);
	Eye1Body->SetTransform(&Original_Eye1_Transform);

	// -----------------------------------------------------------

	Eye2Body->SetPos(x + 1, y + 0.80, z + 0.25);
	Eye2Body->SetTransform(&Original_Eye2_Transform);

	// -----------------------------------------------------------
	BodyBody->Freeze(true);
	HeadBody->Freeze(true);
	Leg1Body->Freeze(true);
	Leg2Body->Freeze(true);
	PeakBody->Freeze(true);
	Eye1Body->Freeze(true);
	Eye2Body->Freeze(true);

}
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//--------------------------------------------//
	//Start
	cube1.size.x = 10;
	cube1.size.y = 1;
	cube1.size.z = 110;
	cube1body = App->physics->AddBody(cube1, 0);
	cube1body->SetPos(0, 0, 50);
	//Arc
	cube1_1.size.x = 1;
	cube1_1.size.y = 8;
	cube1_1.size.z = 1;
	cube1_1.color = Red;
	cube1_1body = App->physics->AddBody(cube1_1, 0);
	cube1_1body->SetPos(4.5, 4.5, 5.5);
	cube1_2.size.x = 8;
	cube1_2.size.y = 1;
	cube1_2.size.z = 1;
	cube1_2.color = Red;
	cube1_2body = App->physics->AddBody(cube1_2, 0);
	cube1_2body->SetPos(0, 8, 5.5);
	cube1_3.size.x = 1;
	cube1_3.size.y = 8;
	cube1_3.size.z = 1;
	cube1_3.color = Red;
	cube1_3body = App->physics->AddBody(cube1_3, 0);
	cube1_3body->SetPos(-4.5, 4.5, 5.5);
	//--------------------------------------------//
	//Curve
	cylinder1.radius = 10;
	cylinder1.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder1body = App->physics->AddBody(cylinder1, 0);
	cylinder1body->SetPos(-5, 0, 105);
	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//--------------------------------------------//
	/*
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	*/
	//--------------------------------------------//
	//Start
	cube1body->GetTransform(&cube1.transform);
	cube1.Render();
	//Arc
	cube1_1body->GetTransform(&cube1_1.transform);
	cube1_1.Render();
	cube1_2body->GetTransform(&cube1_2.transform);
	cube1_2.Render();
	cube1_3body->GetTransform(&cube1_3.transform);
	cube1_3.Render();
	//--------------------------------------------//
	//Curve
	cylinder1body->GetTransform(&cylinder1.transform);
	cylinder1.Render();
	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
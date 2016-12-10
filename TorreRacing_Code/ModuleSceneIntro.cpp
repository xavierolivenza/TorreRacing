#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define WIDTH 15

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
	cube1.size.x = WIDTH;
	cube1.size.y = 1;
	cube1.size.z = 110;
	cube1body = App->physics->AddBody(cube1, 0);
	cube1body->SetPos(0, 0, 50);
	//Arc
	cube1_1.size.x = 1;
	cube1_1.size.y = 10;
	cube1_1.size.z = 1;
	cube1_1.color = Red;
	cube1_1body = App->physics->AddBody(cube1_1, 0);
	cube1_1body->SetPos(7, 5.5, 5.5);
	cube1_2.size.x = 13;
	cube1_2.size.y = 1;
	cube1_2.size.z = 1;
	cube1_2.color = Red;
	cube1_2body = App->physics->AddBody(cube1_2, 0);
	cube1_2body->SetPos(0, 10, 5.5);
	cube1_3.size.x = 1;
	cube1_3.size.y = 10;
	cube1_3.size.z = 1;
	cube1_3.color = Red;
	cube1_3body = App->physics->AddBody(cube1_3, 0);
	cube1_3body->SetPos(-7, 5.5, 5.5);
	//--------------------------------------------//
	//Curve
	cylinder1.radius = WIDTH;
	cylinder1.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder1body = App->physics->AddBody(cylinder1, 0);
	cylinder1body->SetPos(-7.5, 0, 105);
	//--------------------------------------------//
	//Furst jump
	cube2.size.x = 100;
	cube2.size.y = 1;
	cube2.size.z = WIDTH;
	cube2body = App->physics->AddBody(cube2, 0);
	cube2body->SetPos(-57.5, 0, 112.5);
	cube3.size.x = 200;
	cube3.size.y = 1;
	cube3.size.z = WIDTH;
	cube3body = App->physics->AddBody(cube3, 0);
	cube3body->SetPos(-250, 0, 112.5);
	//--------------------------------------------//
	//Curves
	cylinder2.radius = WIDTH;
	cylinder2.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder2body = App->physics->AddBody(cylinder2, 0);
	cylinder2body->SetPos(-350, 0, 105);
	cube4.size.x = WIDTH;
	cube4.size.y = 1;
	cube4.size.z = 30;
	cube4body = App->physics->AddBody(cube4, 0);
	cube4body->SetPos(-357.5, 0, 90);
	cylinder3.radius = WIDTH;
	cylinder3.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder3body = App->physics->AddBody(cylinder3, 0);
	cylinder3body->SetPos(-365, 0, 75);
	cube5.size.x = 30;
	cube5.size.y = 1;
	cube5.size.z = WIDTH;
	cube5body = App->physics->AddBody(cube5, 0);
	cube5body->SetPos(-380, 0, 67.5);
	cylinder4.radius = WIDTH;
	cylinder4.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder4body = App->physics->AddBody(cylinder4, 0);
	cylinder4body->SetPos(-395, 0, 60);
	cube6.size.x = 50;
	cube6.size.y = 1;
	cube6.size.z = WIDTH;
	cube6body = App->physics->AddBody(cube6, 0);
	cube6body->SetPos(-420, 0, 52.5);
	cylinder5.radius = WIDTH;
	cylinder5.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder5body = App->physics->AddBody(cylinder5, 0);
	cylinder5body->SetPos(-445, 0, 45);
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
	//First jump
	cube2body->GetTransform(&cube2.transform);
	cube2.Render();
	cube3body->GetTransform(&cube3.transform);
	cube3.Render();
	//--------------------------------------------//
	//Curves
	cylinder2body->GetTransform(&cylinder2.transform);
	cylinder2.Render();
	cube4body->GetTransform(&cube4.transform);
	cube4.Render();
	cylinder3body->GetTransform(&cylinder3.transform);
	cylinder3.Render();
	cube5body->GetTransform(&cube5.transform);
	cube5.Render();
	cylinder4body->GetTransform(&cylinder4.transform);
	cylinder4.Render();
	cube6body->GetTransform(&cube6.transform);
	cube6.Render();
	cylinder5body->GetTransform(&cylinder5.transform);
	cylinder5.Render();
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
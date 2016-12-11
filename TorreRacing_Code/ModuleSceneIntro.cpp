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
	//Start sensor
	start_sensor.size.x = WIDTH - 2;
	start_sensor.size.y = 9;
	start_sensor.size.z = 1;
	start_sensor.color = Green;
	start_sensorbody = App->physics->AddBody(start_sensor, 0);
	start_sensorbody->SetAsSensor(true);
	start_sensorbody->collision_listeners.add(this);
	start_sensorbody->SetPos(0, 5, 5.5);
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
	//First jump
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
	//Rised curve
	cube7.size.x = WIDTH;
	cube7.size.y = 1;
	cube7.size.z = 100;
	cube7body = App->physics->AddBody(cube7, 0);
	cube7body->SetPos(-452.5, 0, -5);
	cube8.size.x = WIDTH;
	cube8.size.y = 1;
	cube8.size.z = 100;
	cube8.SetRotation(10, vec3(1, 0, 0));
	cube8body = App->physics->AddBody(cube8, 0);
	cube8body->SetPos(-452.5, 8.69, -104.15);
	cube9.size.x = WIDTH;
	cube9.size.y = 1;
	cube9.size.z = 100;
	cube9.SetRotation(20, vec3(1, 0, 0));
	cube9body = App->physics->AddBody(cube9, 0);
	cube9body->SetPos(-452.5, 34.46, -200.28);
	cube10.size.x = WIDTH;
	cube10.size.y = 1;
	cube10.size.z = 100;
	cube10.SetRotation(30, vec3(1, 0, 0));
	cube10body = App->physics->AddBody(cube10, 0);
	cube10body->SetPos(-452.5, 76.52, -290.48);
	cylinder6.radius = WIDTH * 2;
	cylinder6.SetRotation(96.7177f, vec3(0.3236f, -0.3236f, 0.8891f));
	cylinder6body = App->physics->AddBody(cylinder6, 0);
	cylinder6body->SetPos(-430, 101.57, -333.85);
	cube11.size.x = WIDTH;
	cube11.size.y = 1;
	cube11.size.z = 100;
	cube11.SetRotation(30, vec3(1, 0, 0));
	cube11body = App->physics->AddBody(cube11, 0);
	cube11body->SetPos(-407.5, 76.52, -290.48);
	cube12.size.x = WIDTH;
	cube12.size.y = 1;
	cube12.size.z = 100;
	cube12.SetRotation(20, vec3(1, 0, 0));
	cube12body = App->physics->AddBody(cube12, 0);
	cube12body->SetPos(-407.5, 34.46, -200.28);
	cube13.size.x = WIDTH;
	cube13.size.y = 1;
	cube13.size.z = 100;
	cube13.SetRotation(10, vec3(1, 0, 0));
	cube13body = App->physics->AddBody(cube13, 0);
	cube13body->SetPos(-407.5, 8.69, -104.15);
	//--------------------------------------------//
	//Before consecutive jumps
	cylinder7.radius = WIDTH * 2;
	cylinder7.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder7body = App->physics->AddBody(cylinder7, 0);
	cylinder7body->SetPos(-385, 0, -54.8);
	cube14.size.x = WIDTH;
	cube14.size.y = 1;
	cube14.size.z = 100;
	cube14.SetRotation(-45, vec3(0, 1, 0));
	cube14body = App->physics->AddBody(cube14, 0);
	cube14body->SetPos(-330.69, 0, -77.8);
	cylinder8.radius = WIDTH;
	cylinder8.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder8body = App->physics->AddBody(cylinder8, 0);
	cylinder8body->SetPos(-300.64, 0, -118.46);
	//--------------------------------------------//
	//Consecutive jumps
	cube15.size.x = WIDTH;
	cube15.size.y = 1;
	cube15.size.z = 100;
	cube15body = App->physics->AddBody(cube15, 0);
	cube15body->SetPos(-293.14, 0, -168.46);
	cube16.size.x = WIDTH;
	cube16.size.y = 1;
	cube16.size.z = 100;
	cube16body = App->physics->AddBody(cube16, 0);
	cube16body->SetPos(-293.14, 0, -318.46);
	cube17.size.x = WIDTH;
	cube17.size.y = 1;
	cube17.size.z = 100;
	cube17body = App->physics->AddBody(cube17, 0);
	cube17body->SetPos(-293.14, 0, -468.46);
	cube18.size.x = WIDTH;
	cube18.size.y = 1;
	cube18.size.z = 200;
	cube18body = App->physics->AddBody(cube18, 0);
	cube18body->SetPos(-293.14, 0, -740);
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
	/*
	//code to manually adjust some pieces
	float a = 0;
	float b = 0;
	float c = 0;
	float interval = 0.1;
	float interval_small = 0.01;

	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
	{
		a += interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		a -= interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
	{
		a += interval_small;
	}
	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
	{
		a -= interval_small;
	}
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		b += interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		b -= interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		b += interval_small;
	}
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		b -= interval_small;
	}
	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
	{
		c += interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		c -= interval;
	}
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		c += interval_small;
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		c -= interval_small;
	}

	PhysBody3D* body_to_move = ;
	vec3 pos = body_to_move->GetPos();
	body_to_move->SetPos(pos.x += a, pos.y += b, pos.z += c);
	*/

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
	//Start sensor
	if (sensors_debug == true)
	{
		start_sensorbody->GetTransform(&start_sensor.transform);
		start_sensor.Render();
	}
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
	//Rised curve
	cube7body->GetTransform(&cube7.transform);
	cube7.Render();
	cube8body->GetTransform(&cube8.transform);
	cube8.Render();
	cube9body->GetTransform(&cube9.transform);
	cube9.Render();
	cube10body->GetTransform(&cube10.transform);
	cube10.Render();
	cylinder6body->GetTransform(&cylinder6.transform);
	cylinder6.Render();
	cube11body->GetTransform(&cube11.transform);
	cube11.Render();
	cube12body->GetTransform(&cube12.transform);
	cube12.Render();
	cube13body->GetTransform(&cube13.transform);
	cube13.Render();
	//--------------------------------------------//
	//Before consecutive jumps
	cylinder7body->GetTransform(&cylinder7.transform);
	cylinder7.Render();
	cube14body->GetTransform(&cube14.transform);
	cube14.Render();
	cylinder8body->GetTransform(&cylinder8.transform);
	cylinder8.Render();
	//--------------------------------------------//
	//Consecutive jumps
	cube15body->GetTransform(&cube15.transform);
	cube15.Render();
	cube16body->GetTransform(&cube16.transform);
	cube16.Render();
	cube17body->GetTransform(&cube17.transform);
	cube17.Render();
	cube18body->GetTransform(&cube18.transform);
	cube18.Render();
	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	//--------------------------------------------//

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		sensors_debug = !sensors_debug;
	}
		
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (((body1 == start_sensorbody) || (body2 == start_sensorbody)) && (first_time_start_sensor == true))
	{
		App->player->game_timer.Start();
		first_time_start_sensor = false;
	}
}
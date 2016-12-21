#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define WIDTH 15
#define CHICKEN_Y_FLOOR 1.5f

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

	App->audio->PlayMusic("music/main_theme.ogg");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//--------------------------------------------//
	//Start
	cube1.size.x = WIDTH;
	cube1.size.y = 1;
	cube1.size.z = 110;
	cube1.color = Chocolate;
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
	cylinder1.color = Chocolate;
	cylinder1body = App->physics->AddBody(cylinder1, 0);
	cylinder1body->SetPos(-7.5, 0, 105);
	//--------------------------------------------//
	//First jump
	cube2.size.x = 100;
	cube2.size.y = 1;
	cube2.size.z = WIDTH;
	cube2.color = Chocolate;
	cube2body = App->physics->AddBody(cube2, 0);
	cube2body->SetPos(-57.5, 0, 112.5);
	cube3.size.x = 200;
	cube3.size.y = 1;
	cube3.size.z = WIDTH;
	cube3.color = Chocolate;
	cube3body = App->physics->AddBody(cube3, 0);
	cube3body->SetPos(-250, 0, 112.5);
	//--------------------------------------------//
	//Curves
	cylinder2.radius = WIDTH;
	cylinder2.color = Chocolate;
	cylinder2.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder2body = App->physics->AddBody(cylinder2, 0);
	cylinder2body->SetPos(-350, 0, 105);
	cube4.size.x = WIDTH;
	cube4.size.y = 1;
	cube4.size.z = 30;
	cube4.color = Chocolate;
	cube4body = App->physics->AddBody(cube4, 0);
	cube4body->SetPos(-357.5, 0, 90);
	cylinder3.radius = WIDTH;
	cylinder3.color = Chocolate;
	cylinder3.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder3body = App->physics->AddBody(cylinder3, 0);
	cylinder3body->SetPos(-365, 0, 75);
	cube5.size.x = 30;
	cube5.size.y = 1;
	cube5.size.z = WIDTH;
	cube5.color = Chocolate;
	cube5body = App->physics->AddBody(cube5, 0);
	cube5body->SetPos(-380, 0, 67.5);
	cylinder4.radius = WIDTH;
	cylinder4.color = Chocolate;
	cylinder4.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder4body = App->physics->AddBody(cylinder4, 0);
	cylinder4body->SetPos(-395, 0, 60);
	cube6.size.x = 50;
	cube6.size.y = 1;
	cube6.size.z = WIDTH;
	cube6.color = Chocolate;
	cube6body = App->physics->AddBody(cube6, 0);
	cube6body->SetPos(-420, 0, 52.5);
	cylinder5.radius = WIDTH;
	cylinder5.color = Chocolate;
	cylinder5.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder5body = App->physics->AddBody(cylinder5, 0);
	cylinder5body->SetPos(-445, 0, 45);
	//--------------------------------------------//
	//Rised curve
	cube7.size.x = WIDTH;
	cube7.size.y = 1;
	cube7.size.z = 100;
	cube7.color = Chocolate;
	cube7body = App->physics->AddBody(cube7, 0);
	cube7body->SetPos(-452.5, 0, -5);
	cube8.size.x = WIDTH;
	cube8.size.y = 1;
	cube8.size.z = 100;
	cube8.color = Chocolate;
	cube8.SetRotation(10, vec3(1, 0, 0));
	cube8body = App->physics->AddBody(cube8, 0);
	cube8body->SetPos(-452.5, 8.69, -104.15);
	cube9.size.x = WIDTH;
	cube9.size.y = 1;
	cube9.size.z = 100;
	cube9.color = Chocolate;
	cube9.SetRotation(20, vec3(1, 0, 0));
	cube9body = App->physics->AddBody(cube9, 0);
	cube9body->SetPos(-452.5, 34.46, -200.28);
	cube10.size.x = WIDTH;
	cube10.size.y = 1;
	cube10.size.z = 100;
	cube10.color = Chocolate;
	cube10.SetRotation(30, vec3(1, 0, 0));
	cube10body = App->physics->AddBody(cube10, 0);
	cube10body->SetPos(-452.5, 76.52, -290.48);
	cylinder6.radius = WIDTH * 2;
	cylinder6.color = Chocolate;
	cylinder6.SetRotation(96.7177f, vec3(0.3236f, -0.3236f, 0.8891f));
	cylinder6body = App->physics->AddBody(cylinder6, 0);
	cylinder6body->SetPos(-430, 101.57, -333.85);
	cube11.size.x = WIDTH;
	cube11.size.y = 1;
	cube11.size.z = 100;
	cube11.color = Chocolate;
	cube11.SetRotation(30, vec3(1, 0, 0));
	cube11body = App->physics->AddBody(cube11, 0);
	cube11body->SetPos(-407.5, 76.52, -290.48);
	cube12.size.x = WIDTH;
	cube12.size.y = 1;
	cube12.size.z = 100;
	cube12.color = Chocolate;
	cube12.SetRotation(20, vec3(1, 0, 0));
	cube12body = App->physics->AddBody(cube12, 0);
	cube12body->SetPos(-407.5, 34.46, -200.28);
	cube13.size.x = WIDTH;
	cube13.size.y = 1;
	cube13.size.z = 100;
	cube13.color = Chocolate;
	cube13.SetRotation(10, vec3(1, 0, 0));
	cube13body = App->physics->AddBody(cube13, 0);
	cube13body->SetPos(-407.5, 8.69, -104.15);
	//--------------------------------------------//
	//Before consecutive jumps
	cylinder7.radius = WIDTH * 2;
	cylinder7.color = Chocolate;
	cylinder7.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder7body = App->physics->AddBody(cylinder7, 0);
	cylinder7body->SetPos(-385, 0, -54.8);
	cube14.size.x = WIDTH;
	cube14.size.y = 1;
	cube14.size.z = 100;
	cube14.color = Chocolate;
	cube14.SetRotation(-45, vec3(0, 1, 0));
	cube14body = App->physics->AddBody(cube14, 0);
	cube14body->SetPos(-330.69, 0, -77.8);
	cylinder8.radius = WIDTH;
	cylinder8.color = Chocolate;
	cylinder8.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder8body = App->physics->AddBody(cylinder8, 0);
	cylinder8body->SetPos(-300.64, 0, -118.46);
	//--------------------------------------------//
	//Consecutive jumps
	cube15.size.x = WIDTH;
	cube15.size.y = 1;
	cube15.size.z = 100;
	cube15.color = Chocolate;
	cube15body = App->physics->AddBody(cube15, 0);
	cube15body->SetPos(-293.14, 0, -168.46);
	cube16.size.x = WIDTH;
	cube16.size.y = 1;
	cube16.size.z = 100;
	cube16.color = Chocolate;
	cube16body = App->physics->AddBody(cube16, 0);
	cube16body->SetPos(-293.14, 0, -318.46);
	cube17.size.x = WIDTH;
	cube17.size.y = 1;
	cube17.size.z = 100;
	cube17.color = Chocolate;
	cube17body = App->physics->AddBody(cube17, 0);
	cube17body->SetPos(-293.14, 0, -468.46);
	cube18.size.x = WIDTH;
	cube18.size.y = 1;
	cube18.size.z = 200;
	cube18.color = Chocolate;
	cube18body = App->physics->AddBody(cube18, 0);
	cube18body->SetPos(-293.14, 0, -740);
	cylinder9.radius = WIDTH;
	cylinder9.color = Chocolate;
	cylinder9.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder9body = App->physics->AddBody(cylinder9, 0);
	cylinder9body->SetPos(-300.64, 0, -840);
	//--------------------------------------------//
	//Before consecutive jumps
	cube19.size.x = 50;
	cube19.size.y = 1;
	cube19.size.z = WIDTH;
	cube19.color = Chocolate;
	cube19body = App->physics->AddBody(cube19, 0);
	cube19body->SetPos(-325.64, 0, -847.5);
	cylinder10.radius = WIDTH;
	cylinder10.color = Chocolate;
	cylinder10.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder10body = App->physics->AddBody(cylinder10, 0);
	cylinder10body->SetPos(-350.64, 0, -855);
	cube20.size.x = WIDTH;
	cube20.size.y = 1;
	cube20.size.z = 50;
	cube20.color = Chocolate;
	cube20body = App->physics->AddBody(cube20, 0);
	cube20body->SetPos(-358.14, 0, -880);
	cylinder11.radius = WIDTH;
	cylinder11.color = Chocolate;
	cylinder11.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder11body = App->physics->AddBody(cylinder11, 0);
	cylinder11body->SetPos(-365.64, 0, -905);
	cube21.size.x = 50;
	cube21.size.y = 1;
	cube21.size.z = WIDTH;
	cube21.color = Chocolate;
	cube21body = App->physics->AddBody(cube21, 0);
	cube21body->SetPos(-390.64, 0, -912.5);
	//--------------------------------------------//
	//Wood
	cylinderWood.radius = 0.5;
	cylinderWood.height = 15;
	cylinderWood.SetRotation(90.0f, vec3(0, 1, 0));
	cylinderWood.color = Chocolate;
	cylinderWoodbody = App->physics->AddBody(cylinderWood, 0);
	cylinderWoodbody->SetPos(-390.64, 15, -912.5);
	cylinderWoodHit.radius = 1.5;
	cylinderWoodHit.height = 10;
	cylinderWoodHit.SetRotation(90.0f, vec3(0, 1, 0));
	cylinderWoodHit.color = Brown;
	cylinderWoodHitbody = App->physics->AddBody(cylinderWoodHit, 10);
	cylinderWoodHitbody->SetPos(-390.64, 0, -912.5);
	App->physics->AddConstraintHinge(*cylinderWoodbody, *cylinderWoodHitbody, vec3(0, 0, 0), vec3(0, 12.75, 0), vec3(1, 0, 0), vec3(1, 0, 0));
	sphere1WoodSupport1.radius = 1;
	sphere1WoodSupport1.color = Chocolate;
	sphere1WoodSupport1body = App->physics->AddBody(sphere1WoodSupport1, 0);
	sphere1WoodSupport1body->SetPos(-390.64, 15, -920.5);
	cylinderWoodSupport1.radius = 0.5;
	cylinderWoodSupport1.height = 14;
	cylinderWoodSupport1.SetRotation(90.0f, vec3(0, 0, 1));
	cylinderWoodSupport1.color = Chocolate;
	cylinderWoodSupport1body = App->physics->AddBody(cylinderWoodSupport1, 0);
	cylinderWoodSupport1body->SetPos(-390.64, 7.5, -920.5);
	sphere2WoodSupport1.radius = 1;
	sphere2WoodSupport1.color = Chocolate;
	sphere2WoodSupport1body = App->physics->AddBody(sphere1WoodSupport1, 0);
	sphere2WoodSupport1body->SetPos(-390.64, 0, -920.5);
	sphere1WoodSupport2.radius = 1;
	sphere1WoodSupport2.color = Chocolate;
	sphere1WoodSupport2body = App->physics->AddBody(sphere1WoodSupport2, 0);
	sphere1WoodSupport2body->SetPos(-390.64, 15, -904.5);
	cylinderWoodSupport2.radius = 0.5;
	cylinderWoodSupport2.height = 14;
	cylinderWoodSupport2.SetRotation(90.0f, vec3(0, 0, 1));
	cylinderWoodSupport2.color = Chocolate;
	cylinderWoodSupport2body = App->physics->AddBody(cylinderWoodSupport2, 0);
	cylinderWoodSupport2body->SetPos(-390.64, 7.5, -904.5);
	sphere2WoodSupport2.radius = 1;
	sphere2WoodSupport2.color = Chocolate;
	sphere2WoodSupport2body = App->physics->AddBody(sphere1WoodSupport2, 0);
	sphere2WoodSupport2body->SetPos(-390.64, 0, -904.5);
	//--------------------------------------------//
	cylinder12.radius = WIDTH;
	cylinder12.color = Chocolate;
	cylinder12.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder12body = App->physics->AddBody(cylinder12, 0);
	cylinder12body->SetPos(-415.64, 0, -905);
	cube22.size.x = WIDTH;
	cube22.size.y = 1;
	cube22.size.z = 50;
	cube22.color = Chocolate;
	cube22body = App->physics->AddBody(cube22, 0);
	cube22body->SetPos(-423.14, 0, -880);
	cylinder13.radius = WIDTH;
	cylinder13.color = Chocolate;
	cylinder13.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder13body = App->physics->AddBody(cylinder13, 0);
	cylinder13body->SetPos(-430.64, 0, -855);
	cube23.size.x = 50;
	cube23.size.y = 1;
	cube23.size.z = WIDTH;
	cube23.color = Chocolate;
	cube23body = App->physics->AddBody(cube23, 0);
	cube23body->SetPos(-455.64, 0, -847.5);
	//--------------------------------------------//
	//Final line
	cylinder14.radius = WIDTH;
	cylinder14.color = Chocolate;
	cylinder14.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder14body = App->physics->AddBody(cylinder14, 0);
	cylinder14body->SetPos(-480.64, 0, -840);
	cube24.size.x = WIDTH;
	cube24.size.y = 1;
	cube24.size.z = 500;
	cube24.color = Chocolate;
	cube24body = App->physics->AddBody(cube24, 0);
	cube24body->SetPos(-488.14, 0, -590);
	//--------------------------------------------//
	//Death sensor
	death_sensor1.size.x = 1500;
	death_sensor1.size.y = 1;
	death_sensor1.size.z = 1500;
	death_sensor1.color = Green;
	death_sensor1body = App->physics->AddBody(death_sensor1, 0);
	death_sensor1body->SetAsSensor(true);
	death_sensor1body->collision_listeners.add(this);
	death_sensor1body->SetPos(-450, -100, -350);

	//--------------------------------------------//
	//-----------------Barn parts-----------------//
	//--------------------------------------------//
	barn_sensor.size.x = WIDTH;
	barn_sensor.size.y = 11;
	barn_sensor.size.z = 1;
	barn_sensor.color = Green;
	barn_sensorbody = App->physics->AddBody(barn_sensor, 0);
	barn_sensorbody->SetAsSensor(true);
	barn_sensorbody->collision_listeners.add(this);
	barn_sensorbody->SetPos(-488.14, 6, -340.5);
	barn_ground.size.x = 45;
	barn_ground.size.y = 1;
	barn_ground.size.z = 60;
	barn_ground.color = Sienna;
	barn_ground_body = App->physics->AddBody(barn_ground, 0);
	barn_ground_body->SetPos(-488.14, 0, -310); 
	barn_grass.size.x = 55;
	barn_grass.size.y = 1;
	barn_grass.size.z = 70;
	barn_grass.color = Green;
	barn_grass_body = App->physics->AddBody(barn_grass, 0);
	barn_grass_body->SetPos(-488.14, -0.25, -310);
	barn_wall_1.size.x = 1;
	barn_wall_1.size.y = 20;
	barn_wall_1.size.z = 60;
	barn_wall_1.color = DarkRed;
	barn_wall_1_body = App->physics->AddBody(barn_wall_1, 0);
	barn_wall_1_body->SetPos(-465.14, 9.5, -310);
	barn_wall_2.size.x = 1;
	barn_wall_2.size.y = 20;
	barn_wall_2.size.z = 60;
	barn_wall_2.color = DarkRed;
	barn_wall_2_body = App->physics->AddBody(barn_wall_2, 0);
	barn_wall_2_body->SetPos(-511.14, 9.5, -310);
	barn_wall_3.size.x = 47;
	barn_wall_3.size.y = 20;
	barn_wall_3.size.z = 1;
	barn_wall_3.color = DarkRed;
	barn_wall_3_body = App->physics->AddBody(barn_wall_3, 0);
	barn_wall_3_body->SetPos(-488.14, 9.5, -279.5);
	barn_wall_4.size.x = 16;
	barn_wall_4.size.y = 20;
	barn_wall_4.size.z = 1;
	barn_wall_4.color = DarkRed;
	barn_wall_4_body = App->physics->AddBody(barn_wall_4, 0);
	barn_wall_4_body->SetPos(-472.64, 9.5, -340.5);
	barn_wall_5.size.x = 16;
	barn_wall_5.size.y = 20;
	barn_wall_5.size.z = 1;
	barn_wall_5.color = DarkRed;
	barn_wall_5_body = App->physics->AddBody(barn_wall_5, 0);
	barn_wall_5_body->SetPos(-503.64, 9.5, -340.5);
	barn_wall_6.size.x = 15;
	barn_wall_6.size.y = 8;
	barn_wall_6.size.z = 1;
	barn_wall_6.color = DarkRed;
	barn_wall_6_body = App->physics->AddBody(barn_wall_6, 0);
	barn_wall_6_body->SetPos(-488.14, 15.5, -340.5);
	barn_wall_7.size.x = 1;
	barn_wall_7.size.y = 11;
	barn_wall_7.size.z = 8;
	barn_wall_7.color = DarkRed;
	barn_wall_7_body = App->physics->AddBody(barn_wall_7, 0);
	barn_wall_7_body->SetPos(-495.14, 6, -340.5 - 4.5);
	barn_wall_8.size.x = 1;
	barn_wall_8.size.y = 11;
	barn_wall_8.size.z = 8;
	barn_wall_8.color = DarkRed;
	barn_wall_8_body = App->physics->AddBody(barn_wall_8, 0);
	barn_wall_8_body->SetPos(-481.14, 6, -340.5 - 4.5);

	//--------------------------------------------//
	//------------------Chickens------------------//
	//--------------------------------------------//
	chickens_dynamic_array.PushBack(new Chicken( 0, CHICKEN_Y_FLOOR, 10, this));
	chickens_dynamic_array.PushBack(new Chicken( 2, CHICKEN_Y_FLOOR, 20, this));
	chickens_dynamic_array.PushBack(new Chicken(-2, CHICKEN_Y_FLOOR, 30, this));
	//--------------------------------------------//

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	uint chickens_dynamic_array_count = chickens_dynamic_array.Count();
	for (int i = 0; i < chickens_dynamic_array_count; i++)
	{
		delete chickens_dynamic_array[i];
	}
	chickens_dynamic_array.Clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/*
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
	cylinder9body->GetTransform(&cylinder9.transform);
	cylinder9.Render();
	//--------------------------------------------//
	//After consecutive jumps
	cube19body->GetTransform(&cube19.transform);
	cube19.Render();
	cylinder10body->GetTransform(&cylinder10.transform);
	cylinder10.Render();
	cube20body->GetTransform(&cube20.transform);
	cube20.Render();
	cylinder11body->GetTransform(&cylinder11.transform);
	cylinder11.Render();
	cube21body->GetTransform(&cube21.transform);
	cube21.Render();
	//--------------------------------------------//
	//Wood
	cylinderWoodbody->GetTransform(&cylinderWood.transform);
	cylinderWood.Render();
	cylinderWoodHitbody->GetTransform(&cylinderWoodHit.transform);
	cylinderWoodHit.Render();
	sphere1WoodSupport1body->GetTransform(&sphere1WoodSupport1.transform);
	sphere1WoodSupport1.Render();
	cylinderWoodSupport1body->GetTransform(&cylinderWoodSupport1.transform);
	cylinderWoodSupport1.Render();
	sphere2WoodSupport1body->GetTransform(&sphere2WoodSupport1.transform);
	sphere2WoodSupport1.Render();
	sphere1WoodSupport2body->GetTransform(&sphere1WoodSupport2.transform);
	sphere1WoodSupport2.Render();
	cylinderWoodSupport2body->GetTransform(&cylinderWoodSupport2.transform);
	cylinderWoodSupport2.Render();
	sphere2WoodSupport2body->GetTransform(&sphere2WoodSupport2.transform);
	sphere2WoodSupport2.Render();
	//--------------------------------------------//
	cylinder12body->GetTransform(&cylinder12.transform);
	cylinder12.Render();
	cube22body->GetTransform(&cube22.transform);
	cube22.Render();
	cylinder13body->GetTransform(&cylinder13.transform);
	cylinder13.Render();
	cube23body->GetTransform(&cube23.transform);
	cube23.Render();
	//--------------------------------------------//
	//Final line
	cylinder14body->GetTransform(&cylinder14.transform);
	cylinder14.Render();
	cube24body->GetTransform(&cube24.transform);
	cube24.Render();
	//--------------------------------------------//
	//Death sensor
	if (sensors_debug == true)
	{
		death_sensor1body->GetTransform(&death_sensor1.transform);
		death_sensor1.Render();
	}

	//--------------------------------------------//
	//-----------------Barn parts-----------------//
	//--------------------------------------------//
	if (sensors_debug == true)
	{
		barn_sensorbody->GetTransform(&barn_sensor.transform);
		barn_sensor.Render();
	}
	barn_ground_body->GetTransform(&barn_ground.transform);
	barn_ground.Render();
	barn_grass_body->GetTransform(&barn_grass.transform);
	barn_grass.Render();
	barn_wall_1_body->GetTransform(&barn_wall_1.transform);
	barn_wall_1.Render();
	barn_wall_2_body->GetTransform(&barn_wall_2.transform);
	barn_wall_2.Render();
	barn_wall_3_body->GetTransform(&barn_wall_3.transform);
	barn_wall_3.Render();
	barn_wall_4_body->GetTransform(&barn_wall_4.transform);
	barn_wall_4.Render();
	barn_wall_5_body->GetTransform(&barn_wall_5.transform);
	barn_wall_5.Render();
	barn_wall_6_body->GetTransform(&barn_wall_6.transform);
	barn_wall_6.Render();
	barn_wall_7_body->GetTransform(&barn_wall_7.transform);
	barn_wall_7.Render();
	barn_wall_8_body->GetTransform(&barn_wall_8.transform);
	barn_wall_8.Render();

	//render Chickens
	uint chickens_dynamic_array_count = chickens_dynamic_array.Count();
	for (int i = 0; i < chickens_dynamic_array_count; i++)
	{
		chickens_dynamic_array[i]->RenderChicken();
	}

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
	if (((body1 == barn_sensorbody) || (body2 == barn_sensorbody)) && (first_time_barn_sensor == true))
	{
		App->player->game_timer.Stop();
		first_time_barn_sensor = false;
	}
	if ((body1 == death_sensor1body) || (body2 == death_sensor1body))
	{
		App->player->RestartGame();
	}

	//Chickens sensors
	const PhysBody3D* chicken_sensor;
	uint chickens_dynamic_array_count = chickens_dynamic_array.Count();
	for (int i = 0; i < chickens_dynamic_array_count; i++)
	{
		chicken_sensor = chickens_dynamic_array[i]->GetSensorBody();
		if ((body1 == chicken_sensor) || (body2 == chicken_sensor))
		{
			if (chickens_dynamic_array[i]->firsttime == true)
			{
				chickens_dynamic_array[i]->ActivateChicken();
				chickens_dynamic_array[i]->firsttime = false;
			}
		}
	}
}
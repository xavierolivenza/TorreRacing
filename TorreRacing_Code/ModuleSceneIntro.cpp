#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

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

	Win_fx = App->audio->LoadFx("sounds/Win_fx.wav");
	Chicken_fx = App->audio->LoadFx("sounds/Chicken_fx.wav");
	Lose_fx = App->audio->LoadFx("sounds/Lose_fx.wav");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//--------------------------------------------//
	//Start
	cube1.size.x = WIDTH;
	cube1.size.y = 1;
	cube1.size.z = 110;
	cube1.color = Chocolate;
	cube1.SetPos(0, 0, 50);
	cube1body = App->physics->AddBody(cube1, 0);
	//Start sensor
	start_sensor.size.x = WIDTH - 2;
	start_sensor.size.y = 9;
	start_sensor.size.z = 1;
	start_sensor.color = Green;
	start_sensor.SetPos(0, 5, 5.5);
	start_sensorbody = App->physics->AddBody(start_sensor, 0);
	start_sensorbody->SetAsSensor(true);
	start_sensorbody->collision_listeners.add(this);
	//Arc
	cube1_1.size.x = 1;
	cube1_1.size.y = 10;
	cube1_1.size.z = 1;
	cube1_1.color = Red;
	cube1_1.SetPos(7, 5.5, 5.5);
	cube1_1body = App->physics->AddBody(cube1_1, 0);
	cube1_2.size.x = 13;
	cube1_2.size.y = 1;
	cube1_2.size.z = 1;
	cube1_2.color = Red;
	cube1_2.SetPos(0, 10, 5.5);
	cube1_2body = App->physics->AddBody(cube1_2, 0);
	cube1_3.size.x = 1;
	cube1_3.size.y = 10;
	cube1_3.size.z = 1;
	cube1_3.color = Red;
	cube1_3.SetPos(-7, 5.5, 5.5);
	cube1_3body = App->physics->AddBody(cube1_3, 0);
	//--------------------------------------------//
	//Curve
	cylinder1.radius = WIDTH;
	cylinder1.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder1.color = Chocolate;
	cylinder1.SetPos(-7.5, 0, 105);
	cylinder1body = App->physics->AddBody(cylinder1, 0);
	//--------------------------------------------//
	//First jump
	cube2.size.x = 100;
	cube2.size.y = 1;
	cube2.size.z = WIDTH;
	cube2.color = Chocolate;
	cube2.SetPos(-57.5, 0, 112.5);
	cube2body = App->physics->AddBody(cube2, 0);
	cube3.size.x = 200;
	cube3.size.y = 1;
	cube3.size.z = WIDTH;
	cube3.color = Chocolate;
	cube3.SetPos(-250, 0, 112.5);
	cube3body = App->physics->AddBody(cube3, 0);
	//--------------------------------------------//
	//Curves
	cylinder2.radius = WIDTH;
	cylinder2.color = Chocolate;
	cylinder2.SetPos(-350, 0, 105);
	cylinder2.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder2body = App->physics->AddBody(cylinder2, 0);
	cube4.size.x = WIDTH;
	cube4.size.y = 1;
	cube4.size.z = 30;
	cube4.color = Chocolate;
	cube4.SetPos(-357.5, 0, 90);
	cube4body = App->physics->AddBody(cube4, 0);
	cylinder3.radius = WIDTH;
	cylinder3.color = Chocolate;
	cylinder3.SetPos(-365, 0, 75);
	cylinder3.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder3body = App->physics->AddBody(cylinder3, 0);
	cube5.size.x = 30;
	cube5.size.y = 1;
	cube5.size.z = WIDTH;
	cube5.color = Chocolate;
	cube5.SetPos(-380, 0, 67.5);
	cube5body = App->physics->AddBody(cube5, 0);
	cylinder4.radius = WIDTH;
	cylinder4.color = Chocolate;
	cylinder4.SetPos(-395, 0, 60);
	cylinder4.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder4body = App->physics->AddBody(cylinder4, 0);
	cube6.size.x = 50;
	cube6.size.y = 1;
	cube6.size.z = WIDTH;
	cube6.color = Chocolate;
	cube6.SetPos(-420, 0, 52.5);
	cube6body = App->physics->AddBody(cube6, 0);
	cylinder5.radius = WIDTH;
	cylinder5.color = Chocolate;
	cylinder5.SetPos(-445, 0, 45);
	cylinder5.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder5body = App->physics->AddBody(cylinder5, 0);
	//--------------------------------------------//
	//Rised curve
	cube7.size.x = WIDTH;
	cube7.size.y = 1;
	cube7.size.z = 100;
	cube7.color = Chocolate;
	cube7.SetPos(-452.5, 0, -5);
	cube7body = App->physics->AddBody(cube7, 0);
	cube8.size.x = WIDTH;
	cube8.size.y = 1;
	cube8.size.z = 100;
	cube8.color = Chocolate;
	cube8.SetPos(-452.5, 8.69, -104.15);
	cube8.SetRotation(10, vec3(1, 0, 0));
	cube8body = App->physics->AddBody(cube8, 0);
	cube9.size.x = WIDTH;
	cube9.size.y = 1;
	cube9.size.z = 100;
	cube9.color = Chocolate;
	cube9.SetPos(-452.5, 34.46, -200.28);
	cube9.SetRotation(20, vec3(1, 0, 0));
	cube9body = App->physics->AddBody(cube9, 0);
	cube10.size.x = WIDTH;
	cube10.size.y = 1;
	cube10.size.z = 100;
	cube10.color = Chocolate;
	cube10.SetPos(-452.5, 76.52, -290.48);
	cube10.SetRotation(30, vec3(1, 0, 0));
	cube10body = App->physics->AddBody(cube10, 0);
	cylinder6.radius = WIDTH * 2;
	cylinder6.color = Chocolate;
	cylinder6.SetPos(-430, 101.57, -333.85);
	cylinder6.SetRotation(96.7177f, vec3(0.3236f, -0.3236f, 0.8891f));
	cylinder6body = App->physics->AddBody(cylinder6, 0);
	cube11.size.x = WIDTH;
	cube11.size.y = 1;
	cube11.size.z = 100;
	cube11.color = Chocolate;
	cube11.SetPos(-407.5, 76.52, -290.48);
	cube11.SetRotation(30, vec3(1, 0, 0));
	cube11body = App->physics->AddBody(cube11, 0);
	cube12.size.x = WIDTH;
	cube12.size.y = 1;
	cube12.size.z = 100;
	cube12.color = Chocolate;
	cube12.SetPos(-407.5, 34.46, -200.28);
	cube12.SetRotation(20, vec3(1, 0, 0));
	cube12body = App->physics->AddBody(cube12, 0);
	cube13.size.x = WIDTH;
	cube13.size.y = 1;
	cube13.size.z = 100;
	cube13.color = Chocolate;
	cube13.SetPos(-407.5, 8.69, -104.15);
	cube13.SetRotation(10, vec3(1, 0, 0));
	cube13body = App->physics->AddBody(cube13, 0);
	//--------------------------------------------//
	//Before consecutive jumps
	cylinder7.radius = WIDTH * 2;
	cylinder7.color = Chocolate;
	cylinder7.SetPos(-385, 0, -54.8);
	cylinder7.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder7body = App->physics->AddBody(cylinder7, 0);
	cube14.size.x = WIDTH;
	cube14.size.y = 1;
	cube14.size.z = 100;
	cube14.color = Chocolate;
	cube14.SetPos(-330.69, 0, -77.8);
	cube14.SetRotation(-45, vec3(0, 1, 0));
	cube14body = App->physics->AddBody(cube14, 0);
	cylinder8.radius = WIDTH;
	cylinder8.color = Chocolate;
	cylinder8.SetPos(-300.64, 0, -118.46);
	cylinder8.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder8body = App->physics->AddBody(cylinder8, 0);
	//--------------------------------------------//
	//Consecutive jumps
	cube15.size.x = WIDTH;
	cube15.size.y = 1;
	cube15.size.z = 100;
	cube15.color = Chocolate;
	cube15.SetPos(-293.14, 0, -168.46);
	cube15body = App->physics->AddBody(cube15, 0);
	cube16.size.x = WIDTH;
	cube16.size.y = 1;
	cube16.size.z = 100;
	cube16.color = Chocolate;
	cube16.SetPos(-293.14, 0, -318.46);
	cube16body = App->physics->AddBody(cube16, 0);
	cube17.size.x = WIDTH;
	cube17.size.y = 1;
	cube17.size.z = 100;
	cube17.color = Chocolate;
	cube17.SetPos(-293.14, 0, -468.46);
	cube17body = App->physics->AddBody(cube17, 0);
	cube18.size.x = WIDTH;
	cube18.size.y = 1;
	cube18.size.z = 200;
	cube18.color = Chocolate;
	cube18.SetPos(-293.14, 0, -740);
	cube18body = App->physics->AddBody(cube18, 0);
	cylinder9.radius = WIDTH;
	cylinder9.color = Chocolate;
	cylinder9.SetPos(-300.64, 0, -840);
	cylinder9.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder9body = App->physics->AddBody(cylinder9, 0);
	//--------------------------------------------//
	//Before consecutive jumps
	cube19.size.x = 50;
	cube19.size.y = 1;
	cube19.size.z = WIDTH;
	cube19.color = Chocolate;
	cube19.SetPos(-325.64, 0, -847.5);
	cube19body = App->physics->AddBody(cube19, 0);
	cylinder10.radius = WIDTH;
	cylinder10.color = Chocolate;
	cylinder10.SetPos(-350.64, 0, -855);
	cylinder10.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder10body = App->physics->AddBody(cylinder10, 0);
	cube20.size.x = WIDTH;
	cube20.size.y = 1;
	cube20.size.z = 50;
	cube20.color = Chocolate;
	cube20.SetPos(-358.14, 0, -880);
	cube20body = App->physics->AddBody(cube20, 0);
	cylinder11.radius = WIDTH;
	cylinder11.color = Chocolate;
	cylinder11.SetPos(-365.64, 0, -905);
	cylinder11.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder11body = App->physics->AddBody(cylinder11, 0);
	cube21.size.x = 50;
	cube21.size.y = 1;
	cube21.size.z = WIDTH;
	cube21.color = Chocolate;
	cube21.SetPos(-390.64, 0, -912.5);
	cube21body = App->physics->AddBody(cube21, 0);
	//--------------------------------------------//
	//Wood
	cylinderWood.radius = 0.5;
	cylinderWood.height = 15;
	cylinderWood.SetRotation(90.0f, vec3(0, 1, 0));
	cylinderWood.color = Chocolate;
	cylinderWood.SetPos(-390.64, 15, -912.5);
	cylinderWoodbody = App->physics->AddBody(cylinderWood, 0);
	cylinderWoodHit.radius = 1.25;
	cylinderWoodHit.height = 10;
	cylinderWoodHit.SetRotation(90.0f, vec3(0, 1, 0));
	cylinderWoodHit.color = Brown;
	cylinderWoodHitbody = App->physics->AddBody(cylinderWoodHit, 10);
	cylinderWoodHitbody->SetPos(-390.64, 0, -912.5);
	App->physics->AddConstraintHinge(*cylinderWoodbody, *cylinderWoodHitbody, vec3(0, 0, 0), vec3(0, 12.75, 0), vec3(1, 0, 0), vec3(1, 0, 0));
	sphere1WoodSupport1.radius = 1;
	sphere1WoodSupport1.color = Chocolate;
	sphere1WoodSupport1.SetPos(-390.64, 15, -920.5);
	sphere1WoodSupport1body = App->physics->AddBody(sphere1WoodSupport1, 0);
	cylinderWoodSupport1.radius = 0.5;
	cylinderWoodSupport1.height = 14;
	cylinderWoodSupport1.SetRotation(90.0f, vec3(0, 0, 1));
	cylinderWoodSupport1.color = Chocolate;
	cylinderWoodSupport1.SetPos(-390.64, 7.5, -920.5);
	cylinderWoodSupport1body = App->physics->AddBody(cylinderWoodSupport1, 0);
	sphere2WoodSupport1.radius = 1;
	sphere2WoodSupport1.color = Chocolate;
	sphere2WoodSupport1.SetPos(-390.64, 0, -920.5);
	sphere2WoodSupport1body = App->physics->AddBody(sphere1WoodSupport1, 0);
	sphere1WoodSupport2.radius = 1;
	sphere1WoodSupport2.color = Chocolate;
	sphere1WoodSupport2.SetPos(-390.64, 15, -904.5);
	sphere1WoodSupport2body = App->physics->AddBody(sphere1WoodSupport2, 0);
	cylinderWoodSupport2.radius = 0.5;
	cylinderWoodSupport2.height = 14;
	cylinderWoodSupport2.SetRotation(90.0f, vec3(0, 0, 1));
	cylinderWoodSupport2.color = Chocolate;
	cylinderWoodSupport2.SetPos(-390.64, 7.5, -904.5);
	cylinderWoodSupport2body = App->physics->AddBody(cylinderWoodSupport2, 0);
	sphere2WoodSupport2.radius = 1;
	sphere2WoodSupport2.color = Chocolate;
	sphere2WoodSupport2.SetPos(-390.64, 0, -904.5);
	sphere2WoodSupport2body = App->physics->AddBody(sphere1WoodSupport2, 0);
	//--------------------------------------------//
	cylinder12.radius = WIDTH;
	cylinder12.color = Chocolate;
	cylinder12.SetPos(-415.64, 0, -905);
	cylinder12.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder12body = App->physics->AddBody(cylinder12, 0);
	cube22.size.x = WIDTH;
	cube22.size.y = 1;
	cube22.size.z = 50;
	cube22.color = Chocolate;
	cube22.SetPos(-423.14, 0, -880);
	cube22body = App->physics->AddBody(cube22, 0);
	cylinder13.radius = WIDTH;
	cylinder13.color = Chocolate;
	cylinder13.SetPos(-430.64, 0, -855);
	cylinder13.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder13body = App->physics->AddBody(cylinder13, 0);
	cube23.size.x = 50;
	cube23.size.y = 1;
	cube23.size.z = WIDTH;
	cube23.color = Chocolate;
	cube23.SetPos(-455.64, 0, -847.5);
	cube23body = App->physics->AddBody(cube23, 0);
	//--------------------------------------------//
	//Final line
	cylinder14.radius = WIDTH;
	cylinder14.color = Chocolate;
	cylinder14.SetPos(-480.64, 0, -840);
	cylinder14.SetRotation(90.0f, vec3(0, 0, 1));
	cylinder14body = App->physics->AddBody(cylinder14, 0);
	cube24.size.x = WIDTH;
	cube24.size.y = 1;
	cube24.size.z = 100;
	cube24.color = Chocolate;
	cube24.SetPos(-488.14, 0, -790);
	cube24body = App->physics->AddBody(cube24, 0);
	cube25.size.x = WIDTH;
	cube25.size.y = 1;
	cube25.size.z = 100;
	cube25.color = Chocolate;
	cube25.SetPos(-488.14, 0, -690);
	cube25body = App->physics->AddBody(cube25, 0);
	cube26.size.x = WIDTH;
	cube26.size.y = 1;
	cube26.size.z = 100;
	cube26.color = Chocolate;
	cube26.SetPos(-488.14, 0, -590);
	cube26body = App->physics->AddBody(cube26, 0);
	cube27.size.x = WIDTH;
	cube27.size.y = 1;
	cube27.size.z = 100;
	cube27.color = Chocolate;
	cube27.SetPos(-488.14, 0, -490);
	cube27body = App->physics->AddBody(cube27, 0);
	cube28.size.x = WIDTH;
	cube28.size.y = 1;
	cube28.size.z = 100;
	cube28.color = Chocolate;
	cube28.SetPos(-488.14, 0, -390);
	cube28body = App->physics->AddBody(cube28, 0);
	//--------------------------------------------//
	//Death
	DeathSensor.size.x = 100;
	DeathSensor.size.y = 1;
	DeathSensor.size.z = 100;
	DeathSensor.color = Green;
	DeathSensor.SetPos(-488.14, 30, -310);
	DeathSensorbody = App->physics->AddBody(DeathSensor, 0);
	DeathSensorbody->SetAsSensor(true);
	DeathSensorbody->collision_listeners.add(this);
	//--------------------------------------------//

	//--------------------------------------------//
	//-----------------Barn parts-----------------//
	//--------------------------------------------//
	barn_sensor.size.x = WIDTH;
	barn_sensor.size.y = 11;
	barn_sensor.size.z = 1;
	barn_sensor.color = Green;
	barn_sensor.SetPos(-488.14, 6, -340.5);
	barn_sensorbody = App->physics->AddBody(barn_sensor, 0);
	barn_sensorbody->SetAsSensor(true);
	barn_sensorbody->collision_listeners.add(this);
	barn_ground.size.x = 45;
	barn_ground.size.y = 1;
	barn_ground.size.z = 60;
	barn_ground.color = Sienna;
	barn_ground.SetPos(-488.14, 0, -310);
	barn_ground_body = App->physics->AddBody(barn_ground, 0);
	barn_grass.size.x = 55;
	barn_grass.size.y = 1;
	barn_grass.size.z = 70;
	barn_grass.color = Green;
	barn_grass.SetPos(-488.14, -0.25, -310);
	barn_grass_body = App->physics->AddBody(barn_grass, 0);
	barn_wall_1.size.x = 1;
	barn_wall_1.size.y = 20;
	barn_wall_1.size.z = 60;
	barn_wall_1.color = DarkRed;
	barn_wall_1.SetPos(-465.14, 9.5, -310);
	barn_wall_1_body = App->physics->AddBody(barn_wall_1, 0);
	barn_wall_2.size.x = 1;
	barn_wall_2.size.y = 20;
	barn_wall_2.size.z = 60;
	barn_wall_2.color = DarkRed;
	barn_wall_2.SetPos(-511.14, 9.5, -310);
	barn_wall_2_body = App->physics->AddBody(barn_wall_2, 0);
	barn_wall_3.size.x = 47;
	barn_wall_3.size.y = 20;
	barn_wall_3.size.z = 1;
	barn_wall_3.color = DarkRed;
	barn_wall_3.SetPos(-488.14, 9.5, -279.5);
	barn_wall_3_body = App->physics->AddBody(barn_wall_3, 0);
	barn_wall_4.size.x = 16;
	barn_wall_4.size.y = 20;
	barn_wall_4.size.z = 1;
	barn_wall_4.color = DarkRed;
	barn_wall_4.SetPos(-472.64, 9.5, -340.5);
	barn_wall_4_body = App->physics->AddBody(barn_wall_4, 0);
	barn_wall_5.size.x = 16;
	barn_wall_5.size.y = 20;
	barn_wall_5.size.z = 1;
	barn_wall_5.color = DarkRed;
	barn_wall_5.SetPos(-503.64, 9.5, -340.5);
	barn_wall_5_body = App->physics->AddBody(barn_wall_5, 0);
	barn_wall_6.size.x = 15;
	barn_wall_6.size.y = 8;
	barn_wall_6.size.z = 1;
	barn_wall_6.color = DarkRed;
	barn_wall_6.SetPos(-488.14, 15.5, -340.5);
	barn_wall_6_body = App->physics->AddBody(barn_wall_6, 0);
	barn_wall_7.size.x = 1;
	barn_wall_7.size.y = 11;
	barn_wall_7.size.z = 8;
	barn_wall_7.color = DarkRed;
	barn_wall_7.SetPos(-495.14, 6, -340.5 - 4.5);
	barn_wall_7_body = App->physics->AddBody(barn_wall_7, 0);
	barn_wall_8.size.x = 1;
	barn_wall_8.size.y = 11;
	barn_wall_8.size.z = 8;
	barn_wall_8.color = DarkRed;
	barn_wall_8.SetPos(-481.14, 6, -340.5 - 4.5);
	barn_wall_8_body = App->physics->AddBody(barn_wall_8, 0);

	//--------------------------------------------//
	//------------------Chickens------------------//
	//--------------------------------------------//
	chickens_dynamic_array.PushBack(new Chicken( -7.5, CHICKEN_Y_FLOOR, 115, this));
	chickens_dynamic_array.PushBack(new Chicken( -365, CHICKEN_Y_FLOOR, 85, this));
	chickens_dynamic_array.PushBack(new Chicken( -395, CHICKEN_Y_FLOOR, 70, this));
	chickens_dynamic_array.PushBack(new Chicken( -445, CHICKEN_Y_FLOOR, 35, this));
	chickens_dynamic_array.PushBack(new Chicken( -430, 103.57, -333.85, this));
	chickens_dynamic_array.PushBack(new Chicken( -410, 108.57, -338.85, this));
	chickens_dynamic_array.PushBack(new Chicken( -385, CHICKEN_Y_FLOOR, -54.8, this));
	chickens_dynamic_array.PushBack(new Chicken( -300.64, CHICKEN_Y_FLOOR, -126.46, this));
	chickens_dynamic_array.PushBack(new Chicken( -310.64, CHICKEN_Y_FLOOR, -840, this));
	chickens_dynamic_array.PushBack(new Chicken( -405.64, CHICKEN_Y_FLOOR, -910.5, this));
	chickens_dynamic_array.PushBack(new Chicken( -465.64, CHICKEN_Y_FLOOR, -840.5, this));
	chickens_dynamic_array.PushBack(new Chicken( -488.14, CHICKEN_Y_FLOOR, -650, this));
	chickens_dynamic_array.PushBack(new Chicken( -488.14, CHICKEN_Y_FLOOR, -400.5, this));
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
	//--------------------------------------------//
	//Start
	cube1.Render();
	//Start sensor
	if (sensors_debug == true)
	{
		start_sensor.Render();
	}
	//Arc
	cube1_1.Render();
	cube1_2.Render();
	cube1_3.Render();
	//--------------------------------------------//
	//Curve
	cylinder1.Render();
	//--------------------------------------------//
	//First jump
	cube2.Render();
	cube3.Render();
	//--------------------------------------------//
	//Curves
	cylinder2.Render();
	cube4.Render();
	cylinder3.Render();
	cube5.Render();
	cylinder4.Render();
	cube6.Render();
	cylinder5.Render();
	//--------------------------------------------//
	//Rised curve
	cube7.Render();
	cube8.Render();
	cube9.Render();
	cube10.Render();
	cylinder6.Render();
	cube11.Render();
	cube12.Render();
	cube13.Render();
	//--------------------------------------------//
	//Before consecutive jumps
	cylinder7.Render();
	cube14.Render();
	cylinder8.Render();
	//--------------------------------------------//
	//Consecutive jumps
	cube15.Render();
	cube16.Render();
	cube17.Render();
	cube18.Render();
	cylinder9.Render();
	//--------------------------------------------//
	//After consecutive jumps
	cube19.Render();
	cylinder10.Render();
	cube20.Render();
	cylinder11.Render();
	cube21.Render();
	//--------------------------------------------//
	//Wood
	cylinderWood.Render();
	cylinderWoodHitbody->GetTransform(&cylinderWoodHit.transform);
	cylinderWoodHit.Render();
	sphere1WoodSupport1.Render();
	cylinderWoodSupport1.Render();
	sphere2WoodSupport1.Render();
	sphere1WoodSupport2.Render();
	cylinderWoodSupport2.Render();
	sphere2WoodSupport2.Render();
	//--------------------------------------------//
	cylinder12.Render();
	cube22.Render();
	cylinder13.Render();
	cube23.Render();
	//--------------------------------------------//
	//Final line
	cylinder14.Render();
	cube24.Render();
	cube25.Render();
	cube26.Render();
	cube27.Render();
	cube28.Render();
	//--------------------------------------------//
	//Death
	if (sensors_debug == true)
	{
		DeathSensor.Render();
	}
	//--------------------------------------------//

	//--------------------------------------------//
	//-----------------Barn parts-----------------//
	//--------------------------------------------//
	if (sensors_debug == true)
	{
		barn_sensor.Render();
	}
	barn_ground.Render();
	barn_grass.Render();
	barn_wall_1.Render();
	barn_wall_2.Render();
	barn_wall_3.Render();
	barn_wall_4.Render();
	barn_wall_5.Render();
	barn_wall_6.Render();
	barn_wall_7.Render();
	barn_wall_8.Render();

	//render Chickens
	uint chickens_dynamic_array_count = chickens_dynamic_array.Count();
	for (int i = 0; i < chickens_dynamic_array_count; i++)
	{
		chickens_dynamic_array[i]->RenderChicken();
	}

	vec3 VehiclePos = App->player->vehicle->GetPos();
	if (VehiclePos.y <= -2)
	{
		App->audio->PlayFx(Lose_fx);
	}

	if (VehiclePos.y <= - 100)
	{
		App->player->RestartGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		sensors_debug = !sensors_debug;
	}
		
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == App->player->vehicle) || (body2 == App->player->vehicle))
	{
		if (((body1 == start_sensorbody) || (body2 == start_sensorbody)) && (first_time_start_sensor == true))
		{
			App->player->game_timer.Start();
			first_time_start_sensor = false;
		}
		if (((body1 == barn_sensorbody) || (body2 == barn_sensorbody)) && (first_time_barn_sensor == true))
		{

			App->audio->PlayFx(Win_fx);
			App->player->game_timer.Stop();
			App->player->win = true;
			first_time_barn_sensor = false;

		}
		//Barn death sensor
		if ((body1 == DeathSensorbody) || (body2 == DeathSensorbody))
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
					App->audio->PlayFx(Chicken_fx);
					App->player->chickens_taken++;
					chickens_dynamic_array[i]->firsttime = false;
				}
			}
		}
	}
}

void ModuleSceneIntro::RestartChickens()
{
	uint chickens_dynamic_array_count = App->scene_intro->chickens_dynamic_array.Count();
	for (int i = 0; i < chickens_dynamic_array_count; i++)
	{
		App->scene_intro->chickens_dynamic_array[i]->firsttime = true;
		App->scene_intro->chickens_dynamic_array[i]->RestartChicken();
	}
}
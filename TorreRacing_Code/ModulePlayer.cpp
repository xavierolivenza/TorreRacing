#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"
#include "p2SString.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	jump_coolddown.Start();
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	Cow_fx = App->audio->LoadFx("sounds/Cow_fx.wav");

	VehicleInfo car;

	// Car properties ----------------------------------------
	//car.chassis_size.Set(2, 0.1, 4);
	//car.chassis_offset.Set(0, 0.8, 0);

	car.num_chassis = 15;
	car.chassis_size = new vec3[car.num_chassis];
	car.chassis_size[0].Set(2.5, 0.1, 5);		//SKATE
	car.chassis_size[1].Set(0.5, 0.7, 0.5);		//LEG1
	car.chassis_size[2].Set(0.5, 0.7, 0.5);		//LEG2
	car.chassis_size[3].Set(0.5, 0.7, 0.5);		//LEG3
	car.chassis_size[4].Set(0.5, 0.7, 0.5);		//LEG4
	car.chassis_size[5].Set(1.55, 1.5, 2.8);	//BODY
	car.chassis_size[6].Set(1, 1, 1);			//HEAD
	car.chassis_size[7].Set(0.15, 0.15, 0.15);	//EYE1
	car.chassis_size[8].Set(0.15, 0.15, 0.15);	//EYE2
	car.chassis_size[9].Set(1.75, 0.1, 1.5);	//SKATEF
	car.chassis_size[10].Set(1.75, 0.1, 1.5);	//SKATEB
	car.chassis_size[11].Set(0.3, 0.2, 0.2);	//HORN1
	car.chassis_size[12].Set(0.125, 0.3, 0.125);//HORN11
	car.chassis_size[13].Set(0.3, 0.2, 0.2);	//HORN2
	car.chassis_size[14].Set(0.125, 0.3, 0.125);//HORN22

	car.color_parts.PushBack(Blue);				//SKATE
	car.color_parts.PushBack(SaddleBrown);		//LEG1
	car.color_parts.PushBack(SaddleBrown);		//LEG2
	car.color_parts.PushBack(SaddleBrown);		//LEG3
	car.color_parts.PushBack(SaddleBrown);		//LEG4
	car.color_parts.PushBack(SaddleBrown);		//BODY
	car.color_parts.PushBack(SaddleBrown);		//HEAD
	car.color_parts.PushBack(Black);			//EYE1
	car.color_parts.PushBack(Black);			//EYE2
	car.color_parts.PushBack(Blue);				//SKATEF
	car.color_parts.PushBack(Blue);				//SKATEB
	car.color_parts.PushBack(LightYellow);		//HORN1
	car.color_parts.PushBack(LightYellow);		//HORN11
	car.color_parts.PushBack(LightYellow);		//HORN2
	car.color_parts.PushBack(LightYellow);		//HORN22

	car.chassis_offset = new vec3[car.num_chassis];
	car.chassis_offset[0].Set(0, 0.8, 0);		//SKATE
	car.chassis_offset[1].Set(-0.5, 1.10, 1);	//LEG1
	car.chassis_offset[2].Set(0.5, 1.10, 1);	//LEG2
	car.chassis_offset[3].Set(-0.5, 1.10, -1);	//LEG3
	car.chassis_offset[4].Set(0.5, 1.10, -1);	//LEG4
	car.chassis_offset[5].Set(0, 2.1, 0);		//BODY
	car.chassis_offset[6].Set(0, 3.2, 1.6);		//HEAD
	car.chassis_offset[7].Set(-0.2, 3.5, 2.1);	//EYE1
	car.chassis_offset[8].Set(0.2, 3.5, 2.1);	//EYE2
	car.chassis_offset[9].Set(0, 0.8, 2.5);		//SKATEF
	car.chassis_offset[10].Set(0, 0.8, -2.5);	//SKATEB
	car.chassis_offset[11].Set(0.6, 3.4, 1.7);	//HORN1
	car.chassis_offset[12].Set(0.75, 3.5, 1.7);	//HORN11
	car.chassis_offset[13].Set(-0.6, 3.4, 1.7);	//HORN2
	car.chassis_offset[14].Set(-0.75, 3.5, 1.7);//HORN22

	car.mass = 1500.0f;
	car.suspensionStiffness = 3.0f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.90f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = 3*0.5f;
	float half_length = 5*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0 * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0 * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0 * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0 * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 12, 0);
	vehicle->GetTransform(&original_vehicle_trans);

	//Rised curve tp
	//vehicle->SetPos(-452.5, 12, -5);

	//Before Consecutive jumps tp
	//vehicle->SetPos(-300.64, 12, -118.46);

	//After Consecutive jumps tp
	//vehicle->SetPos(-300.64, 12, -840);

	//Wood tp
	//vehicle->SetPos(-365.64, 12, -905);

	//Final line tp
	//vehicle->SetPos(-488.14, 12, -590);
	
	//End Barn tp
	//vehicle->SetPos(-488.14, 0, -310);

	game_timer.Start();
	game_timer.Stop();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	//Reload Game, restart
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		RestartGame();
	}

	/*
	//old camera
	//camera look to origin of car
	btTransform* vehicle_transform = vehicle->GetBTTransform();
	btVector3 vehicle_origin = vehicle_transform->getOrigin();
	vec3 vehicle_origin_vec3(vehicle_origin.getX(), vehicle_origin.getY(), vehicle_origin.getZ());
	App->camera->LookAt(vehicle_origin_vec3);
	//camera pos behind car
	App->camera->Position.x = vehicle_origin.getX();
	App->camera->Position.y = vehicle_origin.getY();
	App->camera->Position.z = vehicle_origin.getZ() - 15;

	//ajustar que la camera va arrosegada pel terra
	int dx = -(vehicle_origin_axis.getX() - vehicle_origin.getX());
	int dy = -(vehicle_origin_axis.getY() - vehicle_origin.getY());

	float Sensitivity = 0.25f;

	App->camera->Position -= App->camera->Reference;

	if (dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		App->camera->X = rotate(App->camera->X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		App->camera->Y = rotate(App->camera->Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		App->camera->Z = rotate(App->camera->Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		App->camera->Y = rotate(App->camera->Y, DeltaY, App->camera->X);
		App->camera->Z = rotate(App->camera->Z, DeltaY, App->camera->X);

		if (App->camera->Y.y < 0.0f)
		{
			App->camera->Z = vec3(0.0f, App->camera->Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			App->camera->Y = cross(App->camera->Z, App->camera->X);
		}
	}
	App->camera->Position = App->camera->Reference + App->camera->Z * length(App->camera->Position);
	// Recalculate matrix -------------
	App->camera->CalculateViewMatrix();

	vehicle_origin_axis = vehicle_transform->getOrigin();
	*/

	//Teleportation
	//Start
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		vehicle->SetPos(0, 12, 0);
	}
	//Rised curve
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		vehicle->SetPos(-452.5, 12, -5);
	}
	//Before Consecutive jumps
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		vehicle->SetPos(-300.64, 12, -118.46);
	}
	//After Consecutive jumps
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		vehicle->SetPos(-300.64, 12, -840);
	}
	//Wood
	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		vehicle->SetPos(-365.64, 12, -905);
	}
	//Final line
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		vehicle->SetPos(-488.14, 12, -590);
	}
	//End
	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	{
		vehicle->SetPos(-488.14, 0, -310);
	}

	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		freecam = !freecam;
	}

	float Vehicle_Velocity = 0;
	Vehicle_Velocity = App->player->vehicle->GetKmh();

	if (isnan(Vehicle_Velocity) >= 1)
	{
		Vehicle_Velocity = 0;
	}

	if (freecam == false)
	{
		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (Vehicle_Velocity <= NORMAL_SPEED_LIMIT))
		{
			acceleration = MAX_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			break_timer.Start();
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (Vehicle_Velocity >= -NORMAL_SPEED_LIMIT))
		{
			if (break_timer.Read() * 0.001 <= 3.0f)
			{
				acceleration = -MAX_ACCELERATION * 2;
			}
			else
			{
				acceleration = -MAX_ACCELERATION;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			brake = BRAKE_POWER;
		}

		//Left dash
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
			mat4x4 vehicle_trans;
			vehicle->GetTransform(&vehicle_trans);

			//Vehicle Axis
			vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
			//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
			vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

			//Vehicle pos and camera look to it
			vec3 VehiclePos = vehicle_trans.translation();
			vec3 Position = (VehiclePos)+X * LATERAL_IMPULSE;
			vec3 Reference = ViewDirection + VehiclePos;

			//Z = normalize(Position + Reference);
			X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
			//Y = cross(Z, X);

			Position += Z * 0.05f;

			vehicle->Push((Position.x - VehiclePos.x), (Position.y - VehiclePos.y), (Position.z - VehiclePos.z));
		}

		//Right dash
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
			mat4x4 vehicle_trans;
			vehicle->GetTransform(&vehicle_trans);

			//Vehicle Axis
			vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
			//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
			vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

			//Vehicle pos and camera look to it
			vec3 VehiclePos = vehicle_trans.translation();
			vec3 Position = (VehiclePos)-X * LATERAL_IMPULSE;
			vec3 Reference = ViewDirection + VehiclePos;

			//Z = normalize(Position + Reference);
			X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
			//Y = cross(Z, X);

			Position += Z * 0.05f;

			vehicle->Push((Position.x - VehiclePos.x), (Position.y - VehiclePos.y), (Position.z - VehiclePos.z));
		}

		//Front dash
		if ((App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && (Vehicle_Velocity <= FRONT_DASH_SPEED_LIMIT))
		{
			vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
			mat4x4 vehicle_trans;
			vehicle->GetTransform(&vehicle_trans);

			//Vehicle Axis
			//vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
			//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
			vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

			//Vehicle pos and camera look to it
			vec3 VehiclePos = vehicle_trans.translation();
			vec3 Position = (VehiclePos)+Z * FRONT_IMPULSE;
			vec3 Reference = ViewDirection + VehiclePos;

			Z = normalize(Position + Reference);
			//X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
			//Y = cross(Z, X);

			Position += Z * 0.05f;

			vehicle->Push((Position.x - VehiclePos.x), (Position.y - VehiclePos.y), (Position.z - VehiclePos.z));
		}

		//Jump
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

			if ((jump_coolddown.Read() * 0.001) >= JUMP_COOLDOWN)
			{
				vehicle->Push(0.0f, JUMP_IMPULSE, 0.0f);
				jump_coolddown.Start();
				App->audio->PlayFx(Cow_fx);
			}
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	float jump_cooldown_calc = 0.0f;
	jump_cooldown_calc = JUMP_COOLDOWN - jump_coolddown.Read() * 0.001f;
	if (jump_cooldown_calc < 0)
		jump_cooldown_calc = 0;

	int tiemer_milisec_read = 0;
	tiemer_milisec_read = game_timer.Read() - chickens_taken * 2000;

	if (tiemer_milisec_read <= 0)
	{
		tiemer_milisec_read = 0;
	}

	float minutes_f = 0.0f;
	int minutes_i = 0;
	float decimal_minutes = 0.0f;
	float seconds_f = 0.0f;
	int seconds_i = 0;
	float decimal_seconds = 0.0f;
	int miliseconds_i = 0;
	minutes_f = tiemer_milisec_read * 0.001f * 0.0167f;
	minutes_i = minutes_f;
	decimal_minutes = minutes_f - minutes_i;
	seconds_f = decimal_minutes * 60;
	seconds_i = seconds_f;
	decimal_seconds = seconds_f - seconds_i;
	miliseconds_i = decimal_seconds * 1000;

	p2SString title;
	if (win == false)
	{
		title.create("TorreRacing, Time: %i:%i:%i Velocity %.2f JumpCooldown: %.2f Run down chickens: %i Lowest Time: %i:%i:%i",
			minutes_i, seconds_i, miliseconds_i,
			Vehicle_Velocity,
			jump_cooldown_calc,
			chickens_taken,
			lowesttime_min, lowesttime_seconds,lowesttime_miliseconds);
	}
	else
	{
		title.create("TorreRacing, You won with a time of %i:%i:%i. Run down chickens: %i. Lowest Time: %i:%i:%i. Press R to restart", 
			minutes_i, seconds_i, miliseconds_i,
			chickens_taken,
			lowesttime_min, lowesttime_seconds, lowesttime_miliseconds);

		if ((tiemer_milisec_read < lowesttime_all_in_miliseconds) || (first_best_time == true))
		{
			lowesttime_all_in_miliseconds = tiemer_milisec_read;
			lowesttime_miliseconds = miliseconds_i;
			lowesttime_seconds = seconds_i;
			lowesttime_min = minutes_i;
			first_best_time = false;
		}
	}
	App->window->SetTitle(title.GetString());

	/*
	char title[100];
	if (win == false)
	{
		vec3 VehiclePos = vehicle->GetPos();
		sprintf_s(title, "TorreRacing, Time: %i:%i:%i Velocity %.2f JumpCooldown: %.2f Pos x:%.2f y:%.2f z:%.2f", minutes_i, seconds_i, miliseconds_i, Vehicle_Velocity, jump_cooldown_calc, VehiclePos.x, VehiclePos.y, VehiclePos.z);
	}
	else
	{
		sprintf_s(title, "TorreRacing, You won with a time of %i:%2.i:%4.i. Press R to restart", minutes_i, seconds_i, miliseconds_i);
	}
	App->window->SetTitle(title);
	*/

	return UPDATE_CONTINUE;
}

void ModulePlayer::RestartGame()
{
	vehicle->SetPos(0, 12, 0);
	vehicle->SetTransform(&original_vehicle_trans);
	vehicle->SetAngularVelocity(0, 0, 0);
	vehicle->SetLinearVelocity(0, 0, 0);
	game_timer.Start();
	game_timer.Stop();
	App->scene_intro->first_time_start_sensor = true;
	App->scene_intro->first_time_barn_sensor = true;
	App->scene_intro->RestartChickens();
	chickens_taken = 0;
	win = false;
	fall = false;
	death_timer.Start();
	death_timer.Stop();
}
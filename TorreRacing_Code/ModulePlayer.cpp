#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

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

	//cubes to test rotations
	/**/
	cube2.size.x = 1;
	cube2.size.y = 1;
	cube2.size.z = 1;
	cube2body = App->physics->AddBody(cube2, 500);
	cube2body->SetPos(0, 0, 0);

	cube3.size.x = 1;
	cube3.size.y = 1;
	cube3.size.z = 1;
	cube3body = App->physics->AddBody(cube3, 500);
	cube3body->SetPos(0, 0, 0);

	cube4.size.x = 1;
	cube4.size.y = 1;
	cube4.size.z = 1;
	cube4body = App->physics->AddBody(cube4, 500);
	cube4body->SetPos(0, 0, 0);
	/**/

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 0.1, 4);
	car.chassis_offset.Set(0, 0.8, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0.55 * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[1].connection.Set(-half_width - 0.55 * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[2].connection.Set(half_width + 0.55 * wheel_width, connection_height, -half_length + wheel_radius);
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
	car.wheels[3].connection.Set(-half_width - 0.55 * wheel_width, connection_height, -half_length + wheel_radius);
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
	vehicle->SetPos(0, 12, 10);
	
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
	/*
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

	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
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

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	//Left dash
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{

	}

	//Right dash
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{

	}
	


	//------------------------------------------------Front dash code for rotation--------------------------------------------
	vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
	mat4x4 vehicle_trans;
	vehicle->GetTransform(&vehicle_trans);

	//Vehicle Axis
	//vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
	//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
	vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

	//Vehicle pos and camera look to it
	vec3 VehiclePos = vehicle_trans.translation();
	vec3 Position = (VehiclePos)+Z * 10;
	vec3 Reference = ViewDirection + VehiclePos;

	Z = normalize(Position + Reference);
	//X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	//Y = cross(Z, X);

	Position += Z * 0.05f;

	//cube2body->SetPos(Position.x, Position.y, Position.z);
	cube2body->GetTransform(&cube2.transform);
	cube2.SetPos(Position.x, Position.y, Position.z);
	cube2.Render();

	/*
	//------------------------------------------------Left dash code for rotation--------------------------------------------
	vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
	mat4x4 vehicle_trans;
	vehicle->GetTransform(&vehicle_trans);

	//Vehicle Axis
	//vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
	//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
	vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

	//Vehicle pos and camera look to it
	vec3 VehiclePos = vehicle_trans.translation();
	vec3 Position = (VehiclePos)+Z * 10;
	vec3 Reference = ViewDirection + VehiclePos;

	Z = normalize(Position + Reference);
	//X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	//Y = cross(Z, X);

	Position += Z * 0.05f;

	//cube2body->SetPos(Position.x, Position.y, Position.z);
	cube2body->GetTransform(&cube2.transform);
	cube2.SetPos(Position.x, Position.y, Position.z);
	cube2.Render();

	//------------------------------------------------Right dash code for rotation--------------------------------------------
	vec3 ViewDirection = vec3(0.0f, 5.0f, 0.0f);
	mat4x4 vehicle_trans;
	vehicle->GetTransform(&vehicle_trans);

	//Vehicle Axis
	//vec3 X = vec3(vehicle_trans[0], vehicle_trans[1], vehicle_trans[2]);
	//vec3 Y = vec3(vehicle_trans[4], vehicle_trans[5], vehicle_trans[6]);
	vec3 Z = vec3(vehicle_trans[8], vehicle_trans[9], vehicle_trans[10]);

	//Vehicle pos and camera look to it
	vec3 VehiclePos = vehicle_trans.translation();
	vec3 Position = (VehiclePos)+Z * 10;
	vec3 Reference = ViewDirection + VehiclePos;

	Z = normalize(Position + Reference);
	//X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	//Y = cross(Z, X);

	Position += Z * 0.05f;

	//cube2body->SetPos(Position.x, Position.y, Position.z);
	cube2body->GetTransform(&cube2.transform);
	cube2.SetPos(Position.x, Position.y, Position.z);
	cube2.Render();
	*/


	//Front dash
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
	{
		float impulse = 1000.0f;
		btQuaternion impulse_quaternion(impulse, 0.0f, 0.0f, 0.0f);
		
		btTransform* vehicle_bt_transform = vehicle->GetBTTransform();
		btQuaternion vehicle_rotation_quaternion = vehicle_bt_transform->getRotation();
		btQuaternion vehicle_quaternion_conj(-vehicle_rotation_quaternion.getX(), -vehicle_rotation_quaternion.getY(), -vehicle_rotation_quaternion.getZ(), vehicle_rotation_quaternion.getW());
		
 		vehicle_rotation_quaternion *= impulse_quaternion;
		vehicle_rotation_quaternion *= vehicle_quaternion_conj;

		vehicle->Push(vehicle_rotation_quaternion.getZ(), vehicle_rotation_quaternion.getY(), vehicle_rotation_quaternion.getX());
	}

	//Jump
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if ((jump_coolddown.Read() * 0.001) >= 2.0f)
		{
			vehicle->Push(0.0f, 5000.0f, 0.0f);
			jump_coolddown.Start();
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	float jump_cooldown_calc = 2.0f - jump_coolddown.Read() * 0.001;
	if (jump_cooldown_calc < 0)
		jump_cooldown_calc = 0;

	char title[80];
	sprintf_s(title, "TorreRacing, Vehicle velocity: %.1f Km/h, JumpCooldown: %.2f", vehicle->GetKmh(), jump_cooldown_calc);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}
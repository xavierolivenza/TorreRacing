#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
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
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
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
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
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
	
	//Front dash
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
	{
		float impulse = 100.0f;
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
		vehicle->Push(0.0f, 10000.0f, 0.0f);
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}
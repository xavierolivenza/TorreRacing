#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{
	body->setUserPointer(this);
}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);

	vehicle_position.x = x;
	vehicle_position.y = y;
	vehicle_position.z = z;
}

const vec3 PhysBody3D::GetPos() const
{
	vec3 VehiclePos;

	mat4x4 vehicle_trans;
	GetTransform(&vehicle_trans);

	VehiclePos = vehicle_trans.translation();

	return VehiclePos;
}

// ---------------------------------------------------------
void PhysBody3D::SetAsSensor(bool is_sensor)
{
	if (this->is_sensor != is_sensor)
	{
		this->is_sensor = is_sensor;
		if (is_sensor == true)
			body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		else
			body->setCollisionFlags(body->getCollisionFlags() &~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

// ---------------------------------------------------------
bool PhysBody3D::IsSensor() const
{
	return is_sensor;
}

void PhysBody3D::SetAngularVelocity(float x, float y, float z)
{
	this->body->setAngularVelocity(btVector3(x, y, z));
}

void PhysBody3D::SetLinearVelocity(float x, float y, float z)
{
	this->body->setLinearVelocity(btVector3(x, y, z));
}

void PhysBody3D::Freeze(bool freezed)
{
	if (freezed == true)
	{
		this->body->forceActivationState(DISABLE_SIMULATION);
	}
	else
	{
		this->body->forceActivationState(ACTIVE_TAG);
	}
}
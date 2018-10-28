#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

struct flipper;

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody*CreateStaticCircle(int x, int y, int radius, int resti);
	PhysBody* CreateRectangle(int x, int y, int width, int height,float rest);
	PhysBody* CreateStaticRectangle(int x, int y, int width, int height,int resti);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateStaticChain(int x, int y, int* points, int size, int resti = 0);

	

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	//flippers
	b2Body* CreateAttacherBody(int x, int y, int diameter);
	PhysBody* CreateFlipperPbody(int x, int y, int* points, int size);
	b2RevoluteJoint* CreateFlipperJoint(const flipper &f, int lowerAngle, int upperAngle);
	flipper CreateFlipper(int posX, int posY, int att_diameter, int flipper_chain[], int chain_size, SDL_Rect flipper_rect, int lowerAngle, int upperAngle, int adjx, int adjy);

	//Flipper movement
	void FlipperSetMaxMotorTorque(flipper &f, float32 MaxTorque);
	void FlipperSetMotorSpeed(flipper &f, float32 MotorSpeed);

	//create primatic joint
	b2PrismaticJoint* CreatePrismaticJoint(PhysBody * anchor, PhysBody * body, int max_move, int min_move, int motor_speed, int max_force);

private:

	bool debug;
	b2World* world;


	b2Body* ground;
	
	// Mouse joint

	b2MouseJoint* mouse_joint;
	b2Body* body_clicked;
};
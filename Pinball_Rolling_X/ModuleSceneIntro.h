#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"



class PhysBody;
struct b2Body;
struct b2RevoluteJoint;
struct b2PrismaticJoint;

struct flipper
{
	//flipper b2 body and physbody
	b2Body* Attacher;
	PhysBody* Pbody;

	//flipper joint
	b2RevoluteJoint* Joint;

	//Rect for blitting purposes
	SDL_Rect Rect;
};

struct kicker {
	PhysBody* anchor;
	PhysBody* body;
	b2PrismaticJoint* joint;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	bool PrintStaticElements = true;

public:

	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	SDL_Texture* Ball;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* StaticScene;
	SDL_Texture* ScoreBoard;
	SDL_Texture* BouncerTR;
	SDL_Texture* BouncerCIR;
	SDL_Texture* BlueBouncerLight;
	SDL_Texture* spriteSheet;
	SDL_Texture* launchertext;

	//flippers

	flipper rightFlipper;
	SDL_Rect rightFlipperRect;

	flipper leftFlipper;
	SDL_Rect leftFlipperRect;

	flipper rightUpFlipper;
	SDL_Rect rightUpFlipperRect;

	flipper leftUpFlipper;
	SDL_Rect leftUpFlipperRect;
	
	//kicker
	kicker launcher;
	SDL_Rect launcherRect;

	uint HitBall;
	uint BouncerSound;

	bool BlitBouncer=false;
	bool BlitBouncerL =false;
	bool BlitBouncerCircle = false;
	bool BlitBouncerLCircle = false;
	bool BlitBlueBouncer = false;

	int start_time;
	

};

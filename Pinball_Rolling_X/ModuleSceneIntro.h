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

	
	


	SDL_Texture* Ball;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture*StaticScene;
	SDL_Texture*ScoreBoard;
	SDL_Texture*BouncerTR;
	SDL_Texture*BouncerCIR;
	SDL_Texture*BlueBouncerLight;
	SDL_Texture* spriteSheet;
	
	//lights
	SDL_Texture*BigBlueLight;
	SDL_Texture*BigBlueTriLightH;


	//flippers

	flipper rightFlipper;
	SDL_Rect rightFlipperRect;

	flipper leftFlipper;
	SDL_Rect leftFlipperRect;

	flipper rightUpFlipper;
	SDL_Rect rightUpFlipperRect;

	flipper leftUpFlipper;
	SDL_Rect leftUpFlipperRect;

	//music

	uint HitBall;
	uint BouncerSound;
	uint BlueUpperSenser1;
	uint SmallLightOn;
	uint BallInPitFX;

	//Collisions bools
	bool BlitBouncer=false;
	bool BlitBouncerL =false;
	bool BlitBouncerCircle = false;
	bool BlitBouncerLCircle = false;
	bool BlitBlueBouncer = false;

	//Sensors bools
	//Light Sensors Bools
	bool sensor_BlueUpperSenser1=false;
	bool sensor_BlueUpperSenser2 = false;
	bool sensor_BlueUpperSenser3 = false;
	bool sensor_BlueUpperSenser4 = false;
	bool sensor_UpperSmallSenser1 = false;
	//Essntial Sensors
	bool PitSensorForBall = false;

	//numOfBalls
	int BallsNum = 4;

	//startingPoint
	iPoint StartingPoint;
};

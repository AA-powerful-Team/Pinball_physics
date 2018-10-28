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
	p2List<PhysBody*> world_parts;


	//Colliders
	PhysBody* Bouncer = nullptr;
	PhysBody*BouncerL = nullptr;
	PhysBody* BouncerCircle = nullptr;
	PhysBody*BouncerLCircle = nullptr;
	PhysBody*BlueBouncer = nullptr;


	//Sensors
		//Upper part
	PhysBody*UpperSenser1;
	PhysBody*UpperSenser2;
	PhysBody*UpperSenser3;
	PhysBody*UpperSenser4;
	PhysBody*UpperSmallSenser1;
	PhysBody*UpperSmallSenser2;
	PhysBody*UpperSmallSenser3;

		//Lower part
	PhysBody*LowerBigSensor1;

	//EssentialSensors
	PhysBody*pitSensor;
	

	


	SDL_Texture* Ball;
	SDL_Texture* StaticScene;
	SDL_Texture* ScoreBoard;
	SDL_Texture* BouncerTR;
	SDL_Texture* BouncerCIR;
	SDL_Texture* BlueBouncerLight;
	SDL_Texture* spriteSheet;
	SDL_Texture* launchertext;
	
	//lights
	SDL_Texture*BigBlueLight;
	SDL_Texture*BigBlueTriLightH;
	SDL_Texture*LittleBlueLight;


	
	SDL_Texture*PostScoreTex;

	//flippers

	flipper rightFlipper;
	SDL_Rect rightFlipperRect;

	flipper leftFlipper;
	SDL_Rect leftFlipperRect;

	flipper rightUpFlipper;
	SDL_Rect rightUpFlipperRect;

	flipper leftUpFlipper;
	SDL_Rect leftUpFlipperRect;

	flipper InvisibleFlipper;
	SDL_Rect invisibleFlipperRect;


	//kicker
	kicker launcher;
	SDL_Rect launcherRect;

	//FX
	uint HitBall;
	uint BouncerSound;
	uint BlueUpperSenser1;
	uint SmallLightOn;
	uint BallInPitFX;
	uint FlipperUp;
	uint FlipperDown;
	uint KickerFX;

	//Collisions bools
	bool BlitBouncer=false;
	bool BlitBouncerL =false;
	bool BlitBouncerCircle = false;
	bool BlitBouncerLCircle = false;
	bool BlitBlueBouncer = false;

	//Sensors bools
		//Upper Light Sensors Bools
	bool sensor_BlueUpperSenser1=false;
	bool sensor_BlueUpperSenser2 = false;
	bool sensor_BlueUpperSenser3 = false;
	bool sensor_BlueUpperSenser4 = false;
	bool sensor_UpperSmallSenser1 = false;
	bool sensor_UpperSmallSenser2 = false;
	bool sensor_UpperSmallSenser3 = false;

		//Lower Light Sensors Bools
	bool sensor_LowerBigSensor1 = false;





	//Essntial Sensors bool
	bool PitSensorForBall = false;
	bool EndMatch = false;

	//numOfBalls
	int BallsNum = 4;

	//startingPoint
	iPoint StartingPoint;
	bool up = false;
};

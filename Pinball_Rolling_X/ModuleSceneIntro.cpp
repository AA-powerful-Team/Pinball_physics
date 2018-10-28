#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	Ball = StaticScene = ScoreBoard = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	
	Ball= App->textures->Load("Assets/Sprites/BallResized.png");
	StaticScene = App->textures->Load("Assets/Sprites/staticPritesWindowSize.png");
	ScoreBoard= App->textures->Load("Assets/Sprites/ScoreBoardResized.png");
	BouncerTR = App->textures->Load("Assets/Sprites/RedTriangle.png");
	BouncerCIR = App->textures->Load("Assets/Sprites/RedLightHit.png");
	BlueBouncerLight= App->textures->Load("Assets/Sprites/BlueRect.png");
	BigBlueLight = App->textures->Load("Assets/Sprites/BigLightCIrcle.png");
	BigBlueTriLightH = App->textures->Load("Assets/Sprites/BigLightTriangleH.png");

	HitBall = App->audio->LoadFx("Assets/FX/BallhittingSound.wav");		//Clean UP music REMEMBER
	BouncerSound= App->audio->LoadFx("Assets/FX/BallHitBouncers.wav");
	BlueUpperSenser1 = App->audio->LoadFx("Assets/FX/TopBigBlueLighOn.wav");
	SmallLightOn= App->audio->LoadFx("Assets/FX/SmallLightOn.wav");
	BallInPitFX = App->audio->LoadFx("Assets/FX/OhhNoo.wav");



	spriteSheet = App->textures->Load("Assets/Sprites/spriteSheet.png");

	int fliper_down_right[16] = {
		271, 739,
		225, 772,
		225, 781,
		230, 781,
		285, 757,
		289, 749,
		288, 740,
		280, 735
	};

	// Pivot 1, 0
	int fliper_down_left[16] = {
		128, 736,
		175, 772,
		174, 780,
		169, 781,
		114, 757,
		110, 749,
		111, 742,
		119, 736,
	};

	int fliper_up_left[14] = {
		298, 370,
		255, 348,
		243, 348,
		242, 359,
		246, 364,
		294, 377,
		300, 375
	};

	// Pivot 1, 0
	int fliper_up_right[14] = {
		370, 317,
		348, 365,
		350, 371,
		354, 369,
		384, 330,
		384, 321,
		378, 315
	};
	
	leftFlipperRect = { 0,78,63,43 };
	leftFlipper = App->physics->CreateFlipper(120, 748,
		9, fliper_down_left, 16, leftFlipperRect, -45, 0, -120, -747);

	rightFlipperRect = { 71,78,63,43 };
	rightFlipper = App->physics->CreateFlipper(280, 748,
		9, fliper_down_right, 16, rightFlipperRect, 15 - 15, 60 - 15, -280, -747);

	leftUpFlipperRect = { 0,0,60,32 };
	leftUpFlipper = App->physics->CreateFlipper(254, 356,
		9, fliper_up_left, 14, leftUpFlipperRect, -45, 0, -254, -356);

	rightUpFlipperRect = { 101, 0, 38, 57 };
	rightUpFlipper = App->physics->CreateFlipper(374, 327,
		9, fliper_up_right, 14, rightUpFlipperRect, 15 - 15, 60 - 15, -374, -327);



	 StartingPoint.x=453;
	 StartingPoint.y = 730;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	
	App->textures->Unload(Ball);
	App->textures->Unload(StaticScene);
	App->textures->Unload(ScoreBoard);
	App->textures->Unload(BouncerTR);
	App->textures->Unload(BouncerCIR);
	App->textures->Unload(BlueBouncerLight);
	App->textures->Unload(BigBlueLight);
	App->textures->Unload(BigBlueTriLightH);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	//printingTheElement that are not going to move


	App->renderer->Blit(StaticScene, 0, 0);
	App->renderer->Blit(ScoreBoard, 477, 0);


//Check Collisions
	if (BlitBouncer) {
		App->renderer->Blit(BouncerTR, 283, 577);	
		BlitBouncer = false;
	}

	if (BlitBouncerL) {
		App->renderer->Blit(BouncerTR, 65, 577,NULL,SDL_FLIP_HORIZONTAL);
		BlitBouncerL = false;
	}

	if (BlitBouncerLCircle) {

		App->renderer->Blit(BouncerCIR, 185, 120);
		BlitBouncerLCircle = false;
	}
	
	if (BlitBouncerCircle) {

		App->renderer->Blit(BouncerCIR, 253, 116);
		BlitBouncerCircle = false;
	}
	if (BlitBlueBouncer) {

		App->renderer->Blit(BlueBouncerLight, 94, 266);
		BlitBlueBouncer = false;
	}

	//CheckSensors
	
	if (sensor_BlueUpperSenser1) {
		
		
		App->renderer->Blit(BigBlueTriLightH, 278,8);
		App->renderer->Blit(BigBlueLight, 281, 45);
		//sensor_BlueUpperSenser1 = false;
	}
	if (sensor_BlueUpperSenser2) {

		App->renderer->Blit(BigBlueTriLightH, 242, 8);
		App->renderer->Blit(BigBlueLight, 247, 44);
		//sensor_BlueUpperSenser2 = false;
	
	}

	if (sensor_BlueUpperSenser3) {

		App->renderer->Blit(BigBlueTriLightH, 207, 8);
		App->renderer->Blit(BigBlueLight, 211, 47);
		//sensor_BlueUpperSenser3 = false;
	}

	if (sensor_BlueUpperSenser4) {

		App->renderer->Blit(BigBlueLight, 339, 23);
		//sensor_BlueUpperSenser3 = false;
	}

	//Check Essential Sensors
	//Ball in Pit
	
	if (PitSensorForBall || App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && BallsNum>0) {

		circles.add(App->physics->CreateCircle(StartingPoint.x,StartingPoint.y,10));
		circles.getLast()->data->listener = this;

		PitSensorForBall = false;
		
	}



	// fliper controls

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, 25.0f);
		App->physics->FlipperSetMotorSpeed(leftFlipper, -25.0f);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, 25.0f);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, -25.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == (KEY_UP))
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(leftFlipper, 25.0f);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, 25.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == (KEY_IDLE) && leftFlipper.Joint->GetJointAngle() * RADTODEG >= -45)
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(leftFlipper, 0.0f);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, 0.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, 25.0f);
		App->physics->FlipperSetMotorSpeed(rightFlipper, 25.0f);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, 25.0f);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, 25.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == (KEY_UP))
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(rightFlipper, -25.0f);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, -25.0f);

	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == (KEY_IDLE) && rightFlipper.Joint->GetJointAngle() * RADTODEG <= 135)
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(rightFlipper, 0.0f);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, 0.0f);
	}

	
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(Ball, x, y, NULL,SDL_FLIP_NONE,1.0f, c->data->GetRotation());
		c = c->next;
	}
	
	//draw flipers
	iPoint coords(112, 692);

	App->renderer->Blit(spriteSheet, coords.x, coords.y + leftFlipper.Rect.h, &leftFlipper.Rect,SDL_FLIP_NONE, 1.0f, leftFlipper.Pbody->GetRotation(), 10, leftFlipper.Rect.h / 2 - 15);

	coords.x = 290;
	coords.y = 750;

	App->renderer->Blit(spriteSheet, coords.x - 63, coords.y - 15, &rightFlipper.Rect, SDL_FLIP_NONE, 1.0f, rightFlipper.Pbody->GetRotation(), 55, rightFlipper.Rect.h / 2 - 7);

	coords.x = 240;
	coords.y = 315;

	App->renderer->Blit(spriteSheet, coords.x, coords.y + leftUpFlipper.Rect.h, &leftUpFlipper.Rect, SDL_FLIP_NONE, 1.0f, leftUpFlipper.Pbody->GetRotation(), 10, leftUpFlipper.Rect.h / 2 - 15);

	coords.x = 410;
	coords.y = 330;

	App->renderer->Blit(spriteSheet, coords.x - 63, coords.y - 15, &rightUpFlipper.Rect, SDL_FLIP_NONE, 1.0f, rightUpFlipper.Pbody->GetRotation(), 30, rightUpFlipper.Rect.h / 2 - 13);




	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (bodyA == App->physics->Bouncer || bodyB == App->physics->Bouncer) {
		BlitBouncer = true;
		App->audio->PlayFx(BouncerSound);

	}
	else if (bodyA == App->physics->BouncerL || bodyB == App->physics->BouncerL) {
		BlitBouncerL = true;
		App->audio->PlayFx(BouncerSound);
	}
	else if (bodyA == App->physics->BouncerLCircle || bodyB == App->physics->BouncerLCircle) {
		BlitBouncerLCircle = true;
		App->audio->PlayFx(BouncerSound);
	}
	else if (bodyA == App->physics->BouncerCircle || bodyB == App->physics->BouncerCircle) {
		BlitBouncerCircle = true;
		App->audio->PlayFx(BouncerSound);
	}
	else if (bodyA == App->physics->BlueBouncer || bodyB == App->physics->BlueBouncer) {
		BlitBlueBouncer = true;
		App->audio->PlayFx(BouncerSound);
	}


	if (bodyA==App->physics->UpperSenser1 && bodyB==circles.getLast()->data ||
		bodyB == App->physics->UpperSenser1 && bodyA == circles.getLast()->data) {
		
		if (sensor_BlueUpperSenser1 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser1 = true;
		}

	}

	if (bodyA == App->physics->UpperSenser2 && bodyB == circles.getLast()->data || 
		bodyB == App->physics->UpperSenser2 && bodyA == circles.getLast()->data) {
		
		if (sensor_BlueUpperSenser2 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser2 = true;
		}
	}

	if (bodyA == App->physics->UpperSenser3 && bodyB == circles.getLast()->data || 
		bodyB == App->physics->UpperSenser3 && bodyA == circles.getLast()->data) {

		if (sensor_BlueUpperSenser3 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser3 = true;
		}
	}

	if (bodyA == App->physics->UpperSenser4 && bodyB == circles.getLast()->data || 
		bodyB == App->physics->UpperSenser4 && bodyA == circles.getLast()->data) {

		if (sensor_BlueUpperSenser4 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser4 = true;
		}
	}
	if (bodyA == App->physics->UpperSmallSenser1 && bodyB == circles.getLast()->data ||
		bodyB == App->physics->UpperSmallSenser1 && bodyA == circles.getLast()->data) {

		if (sensor_UpperSmallSenser1 != true) {
			App->audio->PlayFx(SmallLightOn);
			sensor_UpperSmallSenser1 = true;
		}
	}
	
	if (bodyA == App->physics->pitSensor && bodyB == circles.getLast()->data ||
		bodyB == App->physics->pitSensor && bodyA == circles.getLast()->data) {

		if (PitSensorForBall != true) {
			App->audio->PlayFx(BallInPitFX);
			PitSensorForBall = true;
		}

		BallsNum--;
	}

	

	App->audio->PlayFx(HitBall);
}

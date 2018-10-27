#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainPoints.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	Ball = box = rick = StaticScene = ScoreBoard = NULL;
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
	box = App->textures->Load("pinball/crate.png");
	bonus_fx = App->audio->LoadFx("Assets/FX/BallhittingSound.wav");
	StaticScene = App->textures->Load("Assets/Sprites/staticPritesWindowSize.png");
	
	ScoreBoard= App->textures->Load("Assets/Sprites/ScoreBoardResized.png");

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
		9, fliper_down_left, 16, leftFlipperRect, -45, 0, -120,-747);

	rightFlipperRect = { 71,78,63,43 };
	rightFlipper = App->physics->CreateFlipper(280, 748,
		9, fliper_down_right, 16, rightFlipperRect, 15-15, 60-15, -280 , -747);

	leftUpFlipperRect = { 0,0,60,32 };
	leftUpFlipper = App->physics->CreateFlipper(254, 356,
		9, fliper_up_left, 14, leftUpFlipperRect, -45, 0, -254, -356);

	rightUpFlipperRect = { 101, 0, 38, 57 };
	rightUpFlipper = App->physics->CreateFlipper(374, 327,
		9, fliper_up_right, 14, rightUpFlipperRect, 15 - 15, 60 - 15, -374, -327);



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	//printingTheElement that are not going to move


	App->renderer->Blit(StaticScene, 0, 0);
	App->renderer->Blit(ScoreBoard, 477, 0);


	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
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
		// Prepare for raycast ------------------------------------------------------

		iPoint mouse;
		mouse.x = App->input->GetMouseX();
		mouse.y = App->input->GetMouseY();

		// All draw functions ------------------------------------------------------
		p2List_item<PhysBody*>* c = circles.getFirst();

		while (c != NULL)
		{
			int x, y;
			c->data->GetPosition(x, y);
			App->renderer->Blit(Ball, x, y, NULL, 1.0f, c->data->GetRotation());
			c = c->next;
		}


		
	
	
	//draw flipers
	iPoint coords(112, 692);
	/*leftFlipper.Pbody->GetPosition(coords.x, coords.y);*/

	App->renderer->Blit(spriteSheet, coords.x, coords.y + leftFlipper.Rect.h, &leftFlipper.Rect, 1.0f, leftFlipper.Pbody->GetRotation(), 10, leftFlipper.Rect.h / 2 -15);

	coords.x= 290;
	coords.y= 750;

	App->renderer->Blit(spriteSheet, coords.x-63, coords.y -15, &rightFlipper.Rect, 1.0f, rightFlipper.Pbody->GetRotation(), 55, rightFlipper.Rect.h/2 - 7 );
	
	coords.x = 240;
	coords.y = 315; 

	App->renderer->Blit(spriteSheet, coords.x, coords.y + leftUpFlipper.Rect.h, &leftUpFlipper.Rect, 1.0f, leftUpFlipper.Pbody->GetRotation(), 10, leftUpFlipper.Rect.h / 2 - 15);

	coords.x = 410;
	coords.y = 330; 

	App->renderer->Blit(spriteSheet, coords.x - 63, coords.y - 15, &rightUpFlipper.Rect, 1.0f, rightUpFlipper.Pbody->GetRotation(), 30, rightUpFlipper.Rect.h / 2 - 13);


	
	//draw map

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	App->audio->PlayFx(bonus_fx);
}

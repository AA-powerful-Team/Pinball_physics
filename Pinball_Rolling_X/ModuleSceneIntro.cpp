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
	StaticScene = App->textures->Load("Assets/Sprites/staticPritesWindowSize.png");
	ScoreBoard= App->textures->Load("Assets/Sprites/ScoreBoardResized.png");
	BouncerTR = App->textures->Load("Assets/Sprites/RedTriangle.png");

	HitBall = App->audio->LoadFx("Assets/FX/BallhittingSound.wav");		//Clean UP music REMEMBER
	BouncerSound= App->audio->LoadFx("Assets/FX/BallHitBouncers.wav");

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
	


	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	//printingTheElement that are not going to move


	App->renderer->Blit(StaticScene, 0, 0);
	App->renderer->Blit(ScoreBoard, 477, 0);



	if (BlitBouncer) {
		App->renderer->Blit(BouncerTR, 283, 577);	
		BlitBouncer = false;
	}

	if (BlitBouncerL) {
		App->renderer->Blit(BouncerTR, 144, 577);
		BlitBouncerL = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));
		circles.getLast()->data->listener = this;
	}


	


	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(Ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (bodyA == App->physics->Bouncer || bodyB == App->physics->Bouncer) {
		BlitBouncer = true;
		App->audio->PlayFx(BouncerSound);

	}
	if (bodyA == App->physics->BouncerL || bodyB == App->physics->BouncerL) {
		BlitBouncerL = true;
		App->audio->PlayFx(BouncerSound);
	}

	App->audio->PlayFx(HitBall);
}

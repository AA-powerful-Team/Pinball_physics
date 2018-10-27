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
	BouncerCIR = App->textures->Load("Assets/Sprites/RedLightHit.png");
	BlueBouncerLight= App->textures->Load("Assets/Sprites/BlueRect.png");

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
	App->textures->Unload(BouncerCIR);
	App->textures->Unload(BlueBouncerLight);

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
		App->renderer->Blit(Ball, x, y, NULL,SDL_FLIP_NONE,1.0f, c->data->GetRotation());
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

	App->audio->PlayFx(HitBall);
}

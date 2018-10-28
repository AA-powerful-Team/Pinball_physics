#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainPoints.h"
#include "ModuleFonts.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	Ball = StaticScene = ScoreBoard = BouncerTR= BlueBouncerLight= spriteSheet= launchertext= BigBlueLight= 
	BigBlueTriLightH= LittleBlueLight= PostScoreTex= nullptr;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//score define
	score = 0;
	high_score = 0;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	
	Ball= App->textures->Load("Assets/Sprites/BallResized.png");
	StaticScene = App->textures->Load("Assets/Sprites/staticPritesWindowSize.png");
	ScoreBoard= App->textures->Load("Assets/Sprites/ScoreBoardResized.png");
	BouncerTR = App->textures->Load("Assets/Sprites/RedTriangle.png");
	BouncerCIR = App->textures->Load("Assets/Sprites/RedLightHit.png");
	BlueBouncerLight= App->textures->Load("Assets/Sprites/BlueRect.png");
	BigBlueLight = App->textures->Load("Assets/Sprites/BigLightCIrcle.png");
	BigBlueTriLightH = App->textures->Load("Assets/Sprites/BigLightTriangleH.png");
	 launchertext = App->textures->Load("Assets/Sprites/Kicker_small.png"); 
	spriteSheet = App->textures->Load("Assets/Sprites/spriteSheet.png"); 
	PostScoreTex = App->textures->Load("Assets/Sprites/PostScore.png");
	LittleBlueLight= App->textures->Load("Assets/Sprites/LityleCircleLight.png");


	HitBall = App->audio->LoadFx("Assets/FX/BallhittingSound.wav");		//Clean UP music REMEMBER
	BouncerSound= App->audio->LoadFx("Assets/FX/BallHitBouncers.wav");
	BlueUpperSenser1 = App->audio->LoadFx("Assets/FX/TopBigBlueLighOn.wav");
	SmallLightOn= App->audio->LoadFx("Assets/FX/SmallLightOn.wav");
	BallInPitFX = App->audio->LoadFx("Assets/FX/OhhNoo.wav");
	FlipperUp= App->audio->LoadFx("Assets/FX/FlipperUp.wav");;
	FlipperDown=App->audio->LoadFx("Assets/FX/FlipperDown.wav");
	KickerFX= App->audio->LoadFx("Assets/FX/Kicker.wav");

	launcherRect = {0,0,38,68};
	YellowScoreRect = {0,0,31,32};
	OrangeScoreRect = {0,0,31,32};
	YellowScoreText = App->textures->Load("Assets/Sprites/OrangeNums.png");
	OrangeScoreText = App->textures->Load("Assets/Sprites/YellowNums.png");

	/*OrangeFont = App->fonts->Load("Assets/Sprites/OrangeNums.png", "0123456789", 1);
	YellowFont = App->fonts->Load("Assets/Sprites/YellowNums.png", "0123456789", 1);
*/
	//int fliper_down_right[16] = {
	//	271, 739,
	//	225, 772,
	//	225, 781,
	//	230, 781,
	//	285, 757,
	//	289, 749,
	//	288, 740,
	//	280, 735
	//};

	//// Pivot 1, 0
	//int fliper_down_left[16] = {
	//	128, 736,
	//	175, 772,
	//	174, 780,
	//	169, 781,
	//	114, 757,
	//	110, 749,
	//	111, 742,
	//	119, 736,
	//};

	//int fliper_up_left[14] = {
	//	298, 370,
	//	255, 348,
	//	243, 348,
	//	242, 359,
	//	246, 364,
	//	294, 377,
	//	300, 375
	//};

	//// Pivot 1, 0
	//int fliper_up_right[14] = {
	//	370, 317,
	//	348, 365,
	//	350, 371,
	//	354, 369,
	//	384, 330,
	//	384, 321,
	//	378, 315
	//};

	//int up_left_corner[122] = {
	//	27, 486,
	//	60, 400,
	//	21, 279,
	//	5, 202,
	//	0, 42,
	//	12, 23,
	//	28, 20,
	//	49, 22,
	//	65, 38,
	//	67, 86,
	//	70, 143,
	//	76, 180,
	//	87, 220,
	//	92, 220,
	//	91, 213,
	//	81, 179,
	//	76, 143,
	//	72, 98,
	//	70, 71,
	//	69, 42,
	//	69, 17,
	//	80, 4,
	//	97, 4,
	//	107, 14,
	//	108, 36,
	//	111, 69,
	//	113, 102,
	//	118, 120,
	//	121, 133,
	//	136, 169,
	//	144, 171,
	//	129, 143,
	//	121, 116,
	//	116, 86,
	//	117, 57,
	//	124, 42,
	//	137, 20,
	//	161, 1,
	//	178, 1,
	//	202, 0,
	//	227, -1,
	//	255, 0,
	//	282, 0,
	//	303, 0,
	//	335, 5,
	//	370, 19,
	//	388, 30,
	//	409, 48,
	//	422, 62,
	//	438, 83,
	//	455, 114,
	//	465, 140,
	//	469, 171,
	//	469, 818,
	//	476, 821,
	//	475, -1,
	//	-2, -1,
	//	-1, 570,
	//	8, 556,
	//	24, 540,
	//	24, 497
	//};

	//// Pivot -1, -1
	//int invFlipper[8] = {
	//	465, 300,
	//	456, 317,
	//	433, 356,
	//	468, 301
	//};




	//// Pivot 0, 0
	//int bonus_entrance[44] = {
	//	119, 385,
	//	103, 377,
	//	62, 264,
	//	35, 176,
	//	31, 58,
	//	36, 60,
	//	40, 174,
	//	65, 258,
	//	238, 346,
	//	241, 370,
	//	296, 385,
	//	279, 453,
	//	270, 469,
	//	288, 409,
	//	271, 391,
	//	245, 391,
	//	233, 433,
	//	167, 401,
	//	160, 353,
	//	136, 338,
	//	112, 340,
	//	115, 372,


	//};

	//// Pivot 0, 0
	//int top_triangle_right[28] = {
	//	306, 78,
	//	309, 43,
	//	323, 45,
	//	335, 53,
	//	351, 61,
	//	366, 73,
	//	377, 84,
	//	385, 92,
	//	392, 104,
	//	399, 111,
	//	408, 130,
	//	415, 144,
	//	413, 154,
	//	316, 86
	//};

	//// Pivot -1, -1
	//int middle_pice_with_right_fliper_up[28] = {
	//	345, 373,
	//	355, 374,
	//	389, 332,
	//	391, 321,
	//	377, 308,
	//	415, 231,
	//	413, 281,
	//	398, 338,
	//	376, 378,
	//	341, 438,
	//	311, 486,
	//	329, 433,
	//	337, 403,
	//	344, 381
	//};

	//// Pivot -1, -1
	//int right_down_base[16] = {
	//	432, 858,
	//	256, 860,
	//	257, 823,
	//	402, 735,
	//	400, 569,
	//	361, 517,
	//	431, 365,
	//	432, 839
	//};

	//// Pivot -1, -1
	//int left_down_path_to_flipper[16] = {
	//	31, 597,
	//	33, 602,
	//	34, 682,
	//	106, 725,
	//	109, 732,
	//	100, 729,
	//	27, 685,
	//	27, 602,

	//};

	//// Pivot -1, -1
	//int middle_thing[14] = {
	//	189, 817,
	//	193, 810,
	//	203, 810,
	//	207, 815,
	//	206, 829,
	//	189, 830,
	//	188, 822
	//};

	//// Pivot -1, -1
	//int right_down_path_to_flipper[16] = {
	//	370, 598,
	//	367, 602,
	//	366, 682,
	//	293, 726,
	//	288, 734,
	//	302, 727,
	//	371, 684,
	//	372, 603
	//};

	//// Pivot 1, 0
	//int triangle_bottom_left[6] = {
	//	0, 734,
	//	139, 821,
	//	-1, 821
	//};

	//// Pivot 1, 0
	//int top1_path[12] = {
	//	206, 81,
	//	206, 48,
	//	203, 43,
	//	201, 46,
	//	201, 80,
	//	204, 85,
	//};

	//// Pivot 1, 0
	//int top2_path[12] = {
	//	236, 76,
	//	235, 40,
	//	239, 37,
	//	242, 40,
	//	242, 74,
	//	241, 79
	//};

	//// Pivot 1, 0
	//int top3_path[12] = {
	//	270, 74,
	//	270, 40,
	//	274, 34,
	//	277, 40,
	//	277, 74,
	//	274, 80
	//};

	//// Pivot 1, 0
	//int triangle_boucer[12] = {
	//	115, 678,
	//	75, 583,
	//	66, 581,
	//	67, 664,
	//	112, 688,
	//	116, 683
	//};

	//// Pivot 1, 0
	//int triangle_boucer_right[14] = {
	//	284, 680,
	//	326, 581,
	//	330, 580,
	//	335, 584,
	//	334, 662,
	//	291, 686,
	//	284, 686
	//};


	//int BlueBouncer_Coord[16] = {
	//	92, 270,
	//	95, 266,
	//	100, 265,
	//	149, 290,
	//	152, 294,
	//	152, 298,
	//	149, 298,
	//	94, 272
	//};

	//int blue_triangle[10] = {
	//	86, 270,
	//	94, 268,
	//	100, 268,
	//	98, 273,
	//	90, 270
	//};

	//int invWall[8] = {
	//	0, 569,
	//	1, 735,
	//	-15, 732,
	//	-16, 568
	//};
	//// Pivot -1, -1
	//int triangleRightWall[10] = {
	//	334, 585,
	//	333, 658,
	//	288, 686,
	//	293, 680,
	//	330, 657
	//};
	//// Pivot -1, -1
	//int triangleLeftWall[10] = {
	//	63, 582,
	//	64, 660,
	//	105, 684,
	//	108, 682,
	//	67, 658
	//};

	//Bouncers
	world_parts.add(Bouncer = App->physics->CreateStaticChain(0, 0, triangle_boucer_right, 12, BOUNCER_RESTI));
	world_parts.add(BouncerL = App->physics->CreateStaticChain(0, 0, triangle_boucer, 12, BOUNCER_RESTI));
	world_parts.add(BouncerCircle = App->physics->CreateStaticCircle(275, 136, 20, BOUNCER_RESTI));
	world_parts.add(BouncerLCircle = App->physics->CreateStaticCircle(207, 140, 20, BOUNCER_RESTI));
	world_parts.add(BlueBouncer = App->physics->CreateStaticChain(1, 0, BlueBouncer_Coord, 12, BOUNCER_RESTI));
	//no restitution
	world_parts.add(App->physics->CreateStaticChain(0, 0, blue_triangle, 10, 0));
	world_parts.add(App->physics->CreateStaticChain(0, 0, top3_path, 12, 0));
	world_parts.add(App->physics->CreateStaticChain(0, 0, top2_path, 12, 0));
	world_parts.add(App->physics->CreateStaticChain(0, 0, top1_path, 12, 0));
	world_parts.add(App->physics->CreateStaticChain(0, 0, triangleRightWall, 10, 0));
	world_parts.add(App->physics->CreateStaticChain(0, 0, triangleLeftWall, 10, 0));
	//with restitution
	world_parts.add(App->physics->CreateStaticChain(0, 0, invWall, 8, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(0, 0, triangle_bottom_left, 6, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(0, 1, right_down_path_to_flipper, 16, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(0, 2, middle_thing, 14, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(2, 1, left_down_path_to_flipper, 16, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(2, 0, right_down_base, 16, WALL_RESTITUTION));

	world_parts.add(App->physics->CreateStaticChain(0, 0, middle_pice_with_right_fliper_up, 28, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(0, 0, bonus_entrance, 44, WALL_RESTITUTION));

	world_parts.add(App->physics->CreateStaticChain(0, 0, top_triangle_right, 28, WALL_RESTITUTION));
	world_parts.add(App->physics->CreateStaticChain(0, 0, up_left_corner, 122, WALL_RESTITUTION));

	//sensors
		//Upper Part
	
	sensorsList.add(UpperSenser1 = App->physics->CreateRectangleSensor(293, 57, 10, 10));
	sensorsList.add(UpperSenser2 = App->physics->CreateRectangleSensor(258, 56, 10, 10));
	sensorsList.add(UpperSenser3 = App->physics->CreateRectangleSensor(222, 60, 10, 10));
	sensorsList.add(UpperSenser4 = App->physics->CreateRectangleSensor(350, 35, 10, 10));
	sensorsList.add(UpperSmallSenser1 = App->physics->CreateRectangleSensor(392, 147, 7, 7));
	sensorsList.add(UpperSmallSenser2 = App->physics->CreateRectangleSensor(370, 135, 7, 7));
	sensorsList.add(UpperSmallSenser3 = App->physics->CreateRectangleSensor(345, 117, 7, 7));
		
		//Lower Part
	sensorsList.add(LowerBigSensor1= App->physics->CreateRectangleSensor(390, 705, 10,10));


	//EssentialSensors
	sensorsList.add(pitSensor = App->physics->CreateRectangleSensor(200, 835, 400, 10));
	sensorsList.add(KickerPathSensor= App->physics->CreateRectangleSensor(450, 230, 50, 5));

	//Flipper Collision this shold go with th eother colliders from the module physics
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
		9, fliper_up_right, 14, rightUpFlipperRect, 0, 45, -374, -327);

	//invisible flipper
	invisibleFlipperRect = { 0,0,10,10 };
	InvisibleFlipper = App->physics->CreateFlipper(460, 300,
		1, invFlipper, 8, invisibleFlipperRect, -30, 0, -463, -301);
	
	//startingPoint
	 StartingPoint.x=453;
	 StartingPoint.y = 730;

	 //Kicker
	launcher.anchor = App->physics->CreateStaticRectangle(460, 820, 5, 5,0);
	launcher.body = App->physics->CreateRectangle(450, 820, 30, 10,0.5);
	launcher.joint = App->physics->CreatePrismaticJoint(launcher.anchor, launcher.body, 1, -60, -10, 15);

	//Spawn Ball
	circles.add(App->physics->CreateCircle(StartingPoint.x, StartingPoint.y, 10));
	circles.getLast()->data->listener = this;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	//remove music & FX
	App->audio->CleanUp();

	//text clean up
	App->textures->Unload(Ball);
	App->textures->Unload(StaticScene);
	App->textures->Unload(ScoreBoard);
	App->textures->Unload(BouncerTR);
	App->textures->Unload(BouncerCIR);
	App->textures->Unload(BlueBouncerLight);
	App->textures->Unload(BigBlueLight);
	App->textures->Unload(BigBlueTriLightH);
	App->textures->Unload(PostScoreTex);
	App->textures->Unload(launchertext);
	App->textures->Unload(spriteSheet);
	App->textures->Unload(LittleBlueLight);
	App->textures->Unload(YellowScoreText);
	App->textures->Unload(OrangeScoreText);

	LOG("Unloading map");

	// Remove circles

	p2List_item<PhysBody*>* item;
	item = circles.getFirst();

	int counter = 1;
	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;

	}

	circles.clear();
	LOG("Unloading circles");

	//remove world parts
	p2List_item<PhysBody*>* item2;
	item2 = world_parts.getFirst();


	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;

	}

	world_parts.clear();
	LOG("Unloading world parts");

	//remove sensors
	p2List_item<PhysBody*>* item3;
	item3 = sensorsList.getFirst();


	while (item3 != NULL)
	{
		RELEASE(item3->data);
		item3 = item3->next;

	}

	sensorsList.clear();
	LOG("Unloading sensors");

	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	InvisibleFlipper.Pbody->body->SetGravityScale(0);
	//printingTheElement that are not going to move
	App->renderer->Blit(StaticScene, 0, 0);
	App->renderer->Blit(ScoreBoard, 477, 0);

	//lose Condition
	if (BallsNum <= 0) {
		App->renderer->Blit(PostScoreTex,200,300);
		EndMatch = true;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) {
		
			//RESET SCORE
			BallsNum = 4;
			EndMatch = false;

		}

	}


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

	//Lights-----------------------------------------------
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

	if (sensor_UpperSmallSenser1) {


		App->renderer->Blit(LittleBlueLight,385,140);
		//sensor_UpperSmallSenser1=false

	}

	if (sensor_UpperSmallSenser2) {


		App->renderer->Blit(LittleBlueLight, 360, 124);
		//sensor_UpperSmallSenser2=false

	}

	if (sensor_UpperSmallSenser3) {


		App->renderer->Blit(LittleBlueLight, 336, 110);
		//sensor_UpperSmallSenser3=false

	}

	if (sensor_LowerBigSensor1) {


		App->renderer->Blit(BigBlueLight, 378,695);
		//sensor_UpperSmallSenser3=false

	}

	//---------------------------------------------------

	//Check Essential Sensors
	//Ball in Pit
	
if (!EndMatch) {

	
	if (PitSensorForBall || App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && BallsNum>0) {

		circles.add(App->physics->CreateCircle(StartingPoint.x,StartingPoint.y,10));
		circles.getLast()->data->listener = this;

		PitSensorForBall = false;
		FlipperKickerup = false;
		
	}

	//------------------------UI Score-------------------
	if (score > high_score) {
		high_score = score;
	}

	if (sensor_BlueUpperSenser1 && sensor_BlueUpperSenser2 && sensor_BlueUpperSenser3&&sensor_BlueUpperSenser4)
	{
		AddScore(ScoreMultiply, 25);
		sensor_BlueUpperSenser1 = sensor_BlueUpperSenser2 = sensor_BlueUpperSenser3 = sensor_BlueUpperSenser4 = false;
	}
	
	if (sensor_BlueUpperSenser1 && sensor_BlueUpperSenser2 && sensor_BlueUpperSenser3)
	{
		AddScore(ScoreMultiply, 15);
		sensor_BlueUpperSenser1 = sensor_BlueUpperSenser2 = sensor_BlueUpperSenser3 = false;
	}


	if (sensor_UpperSmallSenser1 && sensor_UpperSmallSenser2 && sensor_UpperSmallSenser3)
	{
		AddScore(ScoreMultiply, 30);
		sensor_UpperSmallSenser1 = sensor_UpperSmallSenser2 = sensor_UpperSmallSenser3 = false;
	}
	//-------------------------------------

	// fliper controls
	if (FlipperKickerup)
	{
		App->physics->FlipperSetMaxMotorTorque(InvisibleFlipper, -30.0f);
		App->physics->FlipperSetMotorSpeed(InvisibleFlipper, flipperMaxTorque);

	}
	else if (FlipperKickerup ==false){
		App->physics->FlipperSetMaxMotorTorque(InvisibleFlipper, flipperMaxTorque);
		App->physics->FlipperSetMotorSpeed(InvisibleFlipper, -flipperMaxTorque);

	}


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, flipperMaxTorque);
		App->physics->FlipperSetMotorSpeed(leftFlipper, -flipperMaxTorque);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, flipperMaxTorque);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, -flipperMaxTorque);

	
		App->audio->PlayFx(FlipperUp);

	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == (KEY_UP))
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(leftFlipper, flipperMaxTorque);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, flipperMaxTorque);

		
		App->audio->PlayFx(FlipperDown);

	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == (KEY_IDLE) && leftFlipper.Joint->GetJointAngle() * RADTODEG >= -45)
	{
		App->physics->FlipperSetMaxMotorTorque(leftFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(leftFlipper, 0.0f);
		App->physics->FlipperSetMaxMotorTorque(leftUpFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(leftUpFlipper, 0.0f);

	}

	//flipper 2
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, flipperMaxTorque);
		App->physics->FlipperSetMotorSpeed(rightFlipper, flipperMaxTorque);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, flipperMaxTorque);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, flipperMaxTorque);

		App->audio->PlayFx(FlipperUp);

		
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == (KEY_UP))
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(rightFlipper, -flipperMaxTorque);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, 10.0f);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, -flipperMaxTorque);

		App->audio->PlayFx(FlipperDown);

	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == (KEY_IDLE) && rightFlipper.Joint->GetJointAngle() * RADTODEG <= 135)
	{
		App->physics->FlipperSetMaxMotorTorque(rightFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(rightFlipper, 0.0f);
		App->physics->FlipperSetMaxMotorTorque(rightUpFlipper, 0.0f);
		App->physics->FlipperSetMotorSpeed(rightUpFlipper, 0.0f);
	}
	
	//kicker controls
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {

		launcher.joint->SetMotorSpeed(2);
		launcher.joint->SetMaxMotorForce(3);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

		launcher.joint->SetMotorSpeed(2);
		launcher.joint->SetMaxMotorForce(3);
		
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) {
		launcher.joint->SetMotorSpeed(-15);
		launcher.joint->SetMaxMotorForce(20);
		
		App->audio->PlayFx(KickerFX);
	}
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

	//draw kicker
	iPoint launch_pos;
	launcher.body->GetPosition(launch_pos.x, launch_pos.y);
	launch_pos.x -= launcher.body->width ;
	launch_pos.y -= launcher.body->height;
	App->renderer->Blit(launchertext, launch_pos.x+13 , launch_pos.y+6, &launcherRect);


	return UPDATE_CONTINUE;
}

//Collisions
void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//BouncerLiCollisions--------------------------
	if (bodyA == Bouncer || bodyB ==Bouncer) {
		BlitBouncer = true;
		App->audio->PlayFx(BouncerSound);
		AddScore(ScoreMultiply,5);

	}
	else if (bodyA == BouncerL || bodyB ==BouncerL) {
		BlitBouncerL = true;
		App->audio->PlayFx(BouncerSound);
		AddScore(ScoreMultiply, 5);
	}
	else if (bodyA == BouncerLCircle || bodyB == BouncerLCircle) {
		BlitBouncerLCircle = true;
		App->audio->PlayFx(BouncerSound);
		AddScore(ScoreMultiply, 25);
	}
	else if (bodyA == BouncerCircle || bodyB == BouncerCircle) {
		BlitBouncerCircle = true;
		App->audio->PlayFx(BouncerSound);
		AddScore(ScoreMultiply, 25);
	}
	else if (bodyA == BlueBouncer || bodyB ==BlueBouncer) {
		BlitBlueBouncer = true;
		App->audio->PlayFx(BouncerSound);
		AddScore(ScoreMultiply, 10);
	}
	//---------------------------------------------------

	//sensorsDetection------------------------------------
	if (bodyA==UpperSenser1 && bodyB==circles.getLast()->data ||
		bodyB == UpperSenser1 && bodyA == circles.getLast()->data) {
		
		if (sensor_BlueUpperSenser1 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser1 = true;
		}

	}

	if (bodyA == UpperSenser2 && bodyB == circles.getLast()->data || 
		bodyB == UpperSenser2 && bodyA == circles.getLast()->data) {
		
		if (sensor_BlueUpperSenser2 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser2 = true;
		}
	}

	if (bodyA ==UpperSenser3 && bodyB == circles.getLast()->data || 
		bodyB == UpperSenser3 && bodyA == circles.getLast()->data) {

		if (sensor_BlueUpperSenser3 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser3 = true;
		}
	}

	if (bodyA == UpperSenser4 && bodyB == circles.getLast()->data || 
		bodyB == UpperSenser4 && bodyA == circles.getLast()->data) {

		if (sensor_BlueUpperSenser4 != true) {
			App->audio->PlayFx(BlueUpperSenser1);
			sensor_BlueUpperSenser4 = true;
		}
	}
	if (bodyA == UpperSmallSenser1 && bodyB == circles.getLast()->data ||
		bodyB == UpperSmallSenser1 && bodyA == circles.getLast()->data) {

		if (sensor_UpperSmallSenser1 != true) {
			App->audio->PlayFx(SmallLightOn);
			sensor_UpperSmallSenser1 = true;
		}
	}

	if (bodyA == UpperSmallSenser2 && bodyB == circles.getLast()->data ||
		bodyB == UpperSmallSenser2 && bodyA == circles.getLast()->data) {

		if (sensor_UpperSmallSenser2 != true) {
			App->audio->PlayFx(SmallLightOn);
			sensor_UpperSmallSenser2 = true;
		}
	}

	if (bodyA == UpperSmallSenser3 && bodyB == circles.getLast()->data ||
		bodyB == UpperSmallSenser3 && bodyA == circles.getLast()->data) {

		if (sensor_UpperSmallSenser3 != true) {
			App->audio->PlayFx(SmallLightOn);
			sensor_UpperSmallSenser3 = true;
		}
	}
	//---------------------------------------------

	if (bodyA == UpperSmallSenser3 && bodyB == circles.getLast()->data ||
		bodyB == LowerBigSensor1 && bodyA == circles.getLast()->data) {

		if (sensor_LowerBigSensor1 != true) {
			App->audio->PlayFx(SmallLightOn);
			sensor_LowerBigSensor1 = true;
		}
	}


	//Essential Sensero Detection------------------
	
	if (bodyA == pitSensor && bodyB == circles.getLast()->data ||
		bodyB == pitSensor && bodyA == circles.getLast()->data) {

		if (PitSensorForBall != true) {
			App->audio->PlayFx(BallInPitFX);
			PitSensorForBall = true;
		}
		
		FlipperKickerup = false;
		
		BallsNum--;
	}

	if (bodyA == KickerPathSensor && bodyB == circles.getLast()->data ||
		bodyB == KickerPathSensor && bodyA == circles.getLast()->data) {

		if (FlipperKickerup != true) {
			FlipperKickerup = true;
		}

	}

	//----------------------------------------------

	App->audio->PlayFx(HitBall);
}


//ui funtions
void ModuleSceneIntro::AddScore(int multiply, int Addpoints)
{
	score += ScoreMultiply * Addpoints;
}

void ModuleSceneIntro::AddBonusScore(int multiply, int bonus)
{
	score += bonus * multiply;
}


//void ModuleSceneIntro::DrawScore() 
//{
//	App->renderer->Blit(YellowScoreText, 25, 460, &YellowScoreRect);
//	App->renderer->Blit(OrangeScoreText, 487, 460, &OrangeScoreRect);
//
//	char char_score[10];
//	sprintf_s(char_score, "%.5d", score);
//	App->fonts->Blit(27, 475, OrangeFont, char_score);
//
//	char char_hscore[10];
//	sprintf_s(char_hscore, "%.5d", high_score);
//	App->fonts->Blit(489, 475, YellowFont, char_hscore);
//
//	/*App->renderer->Blit(balls_left.image, 310, 455, &balls_left.rect);*/
//
//	/*for (int i = 0; i < losed_balls; i++) {
//		App->render->Blit(lose_ball.image, 313 + i * 10, 470, &lose_ball.rect);
//	}*/
//}
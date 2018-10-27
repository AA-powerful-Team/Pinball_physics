#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	//// big static circle as "ground" in the middle of the screen
	//int x = SCREEN_WIDTH / 2;
	//int y = SCREEN_HEIGHT / 1.5f;
	//int diameter = SCREEN_WIDTH / 2;

	//b2BodyDef body;
	//body.type = b2_staticBody;
	//body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	//b2Body* big_ball = world->CreateBody(&body);

	//b2CircleShape shape;
	//shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	//b2FixtureDef fixture;
	//fixture.shape = &shape;
	//big_ball->CreateFixture(&fixture);

	/*must add 2 circeles of 21 radius
		center 1
		208, 139,
		center 2
		277, 135*/
	// Pivot 0, 0
	int up_left_corner[120] = {
		26, 537,
		27, 486,
		60, 400,
		21, 279,
		5, 202,
		0, 42,
		12, 23,
		28, 15,
		52, 17,
		65, 38,
		67, 86,
		70, 143,
		77, 179,
		88, 217,
		93, 219,
		93, 211,
		82, 177,
		76, 143,
		72, 98,
		70, 71,
		71, 40,
		69, 17,
		80, 4,
		97, 4,
		109, 13,
		111, 36,
		112, 70,
		113, 102,
		118, 120,
		121, 133,
		132, 158,
		139, 170,
		143, 161,
		121, 116,
		116, 86,
		117, 57,
		124, 42,
		137, 20,
		161, 1,
		178, 1,
		202, 0,
		226, 2,
		255, 0,
		282, 0,
		301, 3,
		327, 6,
		370, 19,
		388, 30,
		409, 48,
		422, 62,
		438, 83,
		455, 114,
		465, 140,
		469, 171,
		469, 818,
		476, 821,
		475, -1,
		-2, -1,
		-1, 570,
		19, 544
	};

	// Pivot 0, 0
	int bonus_entrance[44] = {
		119, 385,
		103, 377,
		60, 263,
		35, 172,
		30, 58,
		36, 60,
		40, 171,
		65, 258,
		239, 342,
		239, 366,
		296, 384,
		273, 468,
		268, 459,
		285, 410,
		267, 387,
		244, 391,
		234, 430,
		169, 397,
		158, 356,
		140, 339,
		114, 334,
		115, 372
	};

	// Pivot 0, 0
	int top_triangle_right[28] = {
		306, 78,
		309, 43,
		323, 45,
		335, 53,
		351, 61,
		366, 73,
		377, 84,
		385, 92,
		392, 104,
		399, 111,
		408, 130,
		415, 144,
		413, 154,
		316, 86
	};

	// Pivot -1, -1
	int middle_pice_with_right_fliper_up[28] = {
		345, 373,
		354, 369,
		388, 329,
		387, 317,
		376, 304,
		415, 231,
		409, 305,
		398, 338,
		376, 378,
		341, 438,
		310, 484,
		329, 433,
		337, 403,
		344, 381
	};
	
	// Pivot -1, -1
	int right_down_base[14] = {
		433, 366,
		432, 818,
		260, 820,
		402, 733,
		400, 569,
		361, 517,
		427, 370
	};

	// Pivot -1, -1
	int left_down_path_to_flipper[16] = {
		31, 597,
		33, 602,
		35, 679,
		109, 726,
		111, 732,
		102, 732,
		27, 685,
		27, 602
		};

	// Pivot -1, -1
	int middle_thing[12] = {
		188, 821,
		188, 814,
		192, 808,
		204, 808,
		208, 814,
		208, 822
	};

	// Pivot -1, -1
	int right_down_path_to_flipper[16] = {
		367, 602,
		366, 679,
		289, 726,
		289, 731,
		296, 731,
		370, 684,
		372, 601,
		367, 595
	};

	// Pivot 1, 0
	int triangle_bottom_left[6] = {
		0, 734,
		139, 821,
		-1, 821
	};

	// Pivot 1, 0
	int top1_path[12] = {
		208, 81,
		208, 46,
		204, 41,
		200, 46,
		200, 80,
		204, 85
	};

	// Pivot 1, 0
	int top2_path[12] = {
		235, 76,
		235, 39,
		239, 37,
		244, 40,
		244, 76,
		241, 82
	};

	// Pivot 1, 0
	int top3_path[12] = {
		270, 74,
		270, 40,
		274, 34,
		277, 40,
		277, 74,
		274, 80
	};

	// Pivot 1, 0
	int triangle_boucer[6] = {
		123, 694,
		65, 556,
		65, 662
	};

	// Pivot 1, 0
	int triangle_boucer_right[6] = {
		276, 696,
		336, 552,
		336, 660
	};

	// Pivot 1, 0
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

	// Pivot 1, 0
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
		119, 736
	};

	int BlueBouncer_Coord[12] = {
	91, 274,
	97, 267,
	105, 270,
	132, 283,
	153, 294,
	151, 303
	};



	world_parts.add(Bouncer = CreateStaticChain(1, 0, triangle_boucer_right, 6));
	world_parts.add(BouncerL = CreateStaticChain(1, 0, triangle_boucer, 6));
	world_parts.add(BouncerCircle = CreateStaticCircle(275, 136, 20));
	world_parts.add(BouncerLCircle = CreateStaticCircle(207, 140, 20));
	world_parts.add(BlueBouncer = CreateStaticChain(1,0, BlueBouncer_Coord, 12));

	world_parts.add(CreateStaticChain(1, 0, top3_path, 12));
	world_parts.add(CreateStaticChain(1, 0, top2_path, 12));
	world_parts.add(CreateStaticChain(1, 0, top1_path, 12));
	world_parts.add(CreateStaticChain(1, 0, triangle_bottom_left, 6));
	world_parts.add(CreateStaticChain(-1, 1, right_down_path_to_flipper, 16));
	world_parts.add(CreateStaticChain(-1, 1, middle_thing, 12));
	world_parts.add(CreateStaticChain(-1, 1, left_down_path_to_flipper, 16));
	world_parts.add(CreateStaticChain(-1, 1, right_down_base, 14));
	world_parts.add(CreateStaticChain(-1, 1, middle_pice_with_right_fliper_up, 28));
	world_parts.add(CreateStaticChain(0, 0, top_triangle_right, 28));
	world_parts.add(CreateStaticChain(0, 0, bonus_entrance, 44));
	world_parts.add(CreateStaticChain(0, 0, up_left_corner, 120));
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateStaticCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

PhysBody* ModulePhysics::CreateStaticChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	// Implement a simple mouse joint when a body is clicked for debug purposes
	bool mouse_down = (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN);
	bool mouse_repeat = (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT);
	bool mouse_up = (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP);

	b2Vec2 mouse_position(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));


	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			// test if the current body contains mouse position
			if (mouse_down == true && body_clicked == NULL)
			{
				if (f->GetShape()->TestPoint(b->GetTransform(), mouse_position) == true)
					body_clicked = b;
			}
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (body_clicked != NULL && mouse_joint == NULL)
	{
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_clicked;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * body_clicked->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (mouse_repeat == true && mouse_joint != NULL)
	{
		mouse_joint->SetTarget(mouse_position);
		App->renderer->DrawLine(
			METERS_TO_PIXELS(mouse_joint->GetAnchorA().x), METERS_TO_PIXELS(mouse_joint->GetAnchorA().y),
			METERS_TO_PIXELS(mouse_joint->GetAnchorB().x), METERS_TO_PIXELS(mouse_joint->GetAnchorB().y),
			255, 0, 0);

	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (mouse_up == true && mouse_joint != NULL)
	{
		world->DestroyJoint(mouse_joint);
		mouse_joint = NULL;
		body_clicked = NULL;
	}


	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}
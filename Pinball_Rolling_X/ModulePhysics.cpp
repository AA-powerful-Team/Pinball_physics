#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"
//#include "ChainPoints.h"
#include "ModuleSceneIntro.h"


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
	int up_left_corner[122] = {
		27, 486,
		60, 400,
		21, 279,
		5, 202,
		0, 42,
		12, 23,
		28, 20,
		49, 22,
		65, 38,
		67, 86,
		70, 143,
		76, 180,
		87, 220,
		92, 220,
		91, 213,
		81, 179,
		76, 143,
		72, 98,
		70, 71,
		69, 42,
		69, 17,
		80, 4,
		97, 4,
		107, 14,
		108, 36,
		111, 69,
		113, 102,
		118, 120,
		121, 133,
		136, 169,
		144, 171,
		129, 143,
		121, 116,
		116, 86,
		117, 57,
		124, 42,
		137, 20,
		161, 1,
		178, 1,
		202, 0,
		227, -1,
		255, 0,
		282, 0,
		303, 0,
		335, 5,
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
		8, 556,
		24, 540,
		24, 497
	};

	// Pivot 0, 0
	int bonus_entrance[58] = {
		119, 385,
		103, 377,
		62, 264,
		35, 176,
		31, 58,
		36, 60,
		40, 174,
		65, 258,
		238, 346,
		241, 370,
		296, 385,
		279, 453,
		270, 469,
		288, 409,
		271, 391,
		245, 391,
		233, 433,
		167, 401,
		160, 353,
		136, 338,
		112, 340,
		115, 372,
		115, 372,
		115, 372,
		115, 372,
		115, 372,
		115, 372,
		115, 372,
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
	int middle_pice_with_right_fliper_up[38] = {
		345, 373,
		355, 374,
		389, 332,
		391, 321,
		377, 308,
		415, 231,
		413, 281,
		398, 338,
		376, 378,
		341, 438,
		311, 486,
		329, 433,
		337, 403,
		344, 381,
		344, 381,
		344, 381,
		344, 381,
		344, 381,
		344, 381
	};
	
	// Pivot -1, -1
	int right_down_base[16] = {
		432, 858,
		256, 860,
		257, 823,
		402, 735,
		400, 569,
		361, 517,
		431, 365,
		432, 839
	};

	// Pivot -1, -1
	int left_down_path_to_flipper[16] = {
		31, 597,
		33, 602,
		34, 682,
		106, 725,
		109, 732,
		100, 729,
		27, 685,
		27, 602,
		
		};

	// Pivot -1, -1
	int middle_thing[14] = {
		189, 817,
		193, 810,
		203, 810,
		207, 815,
		206, 829,
		189, 830,
		188, 822
	};

	// Pivot -1, -1
	int right_down_path_to_flipper[16] = {
		370, 598,
		367, 602,
		366, 682,
		293, 726,
		288, 734,
		302, 727,
		371, 684,
		372, 603
	};

	// Pivot 1, 0
	int triangle_bottom_left[6] = {
		0, 734,
		139, 821,
		-1, 821
	};

	// Pivot 1, 0
	int top1_path[12] = {
		206, 81,
		206, 48,
		203, 43,
		201, 46,
		201, 80,
		204, 85,
	};

	// Pivot 1, 0
	int top2_path[12] = {
		236, 76,
		235, 40,
		239, 37,
		242, 40,
		242, 74,
		241, 79
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
	int triangle_boucer[12] = {
		115, 678,
		75, 583,
		66, 581,
		67, 664,
		112, 688,
		116, 683
	};

	// Pivot 1, 0
	int triangle_boucer_right[14] = {
		284, 680,
		326, 581,
		330, 580,
		335, 584,
		334, 662,
		291, 686,
		284, 686
	};


	

	int BlueBouncer_Coord[16] = {
		92, 270,
		95, 266,
		100, 265,
		149, 290,
		152, 294,
		152, 298,
		149, 298,
		94, 272
	};



	world_parts.add(Bouncer = CreateStaticChain(0, 0, triangle_boucer_right, 14,2));
	world_parts.add(BouncerL = CreateStaticChain(0, 0, triangle_boucer, 12,2));
	world_parts.add(BouncerCircle = CreateStaticCircle(275, 136, 20,2));
	world_parts.add(BouncerLCircle = CreateStaticCircle(207, 140, 20,2));
	world_parts.add(BlueBouncer = CreateStaticChain(1,0, BlueBouncer_Coord, 16,2));

	world_parts.add(CreateStaticChain(0, 0, top3_path, 12));
	world_parts.add(CreateStaticChain(0, 0, top2_path, 12));
	world_parts.add(CreateStaticChain(0, 0, top1_path, 12));
	world_parts.add(CreateStaticChain(0, 0, triangle_bottom_left, 6));
	world_parts.add(CreateStaticChain(0, 1, right_down_path_to_flipper, 16));
	world_parts.add(CreateStaticChain(0, 2, middle_thing, 14));
	world_parts.add(CreateStaticChain(2, 1, left_down_path_to_flipper, 16));
	world_parts.add(CreateStaticChain(2, 0, right_down_base, 16));
	world_parts.add(CreateStaticChain(0, 0, middle_pice_with_right_fliper_up, 38));
	world_parts.add(CreateStaticChain(0, 0, top_triangle_right, 28));
	world_parts.add(CreateStaticChain(0, 0, bonus_entrance, 58));
	world_parts.add(CreateStaticChain(0, 0, up_left_corner, 122));
	
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

PhysBody* ModulePhysics::CreateStaticCircle(int x, int y, int radius,int resti)
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
	fixture.restitution = resti;
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

PhysBody* ModulePhysics::CreateStaticChain(int x, int y, int* points, int size,int resti)
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
	fixture.restitution = resti;
	fixture.density = 1.0f;
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

b2Body* ModulePhysics::CreateAttacherBody(int x, int y, int diameter)
{
	b2Body* flipper_attacher; //body to Ret

	b2BodyDef flipper_attacher_body;
	flipper_attacher_body.type = b2_staticBody;
	flipper_attacher_body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	flipper_attacher = world->CreateBody(&flipper_attacher_body);

	b2CircleShape flipper_attacher_shape;
	flipper_attacher_shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef flipper_attacher_fixture;
	flipper_attacher_fixture.shape = &flipper_attacher_shape;
	flipper_attacher->CreateFixture(&flipper_attacher_fixture);

	return flipper_attacher;
}

PhysBody* ModulePhysics::CreateFlipperPbody(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;

	//creating the shape
	b2Vec2* chain = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		chain[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		chain[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	box.Set(chain, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	delete chain;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

b2RevoluteJoint* ModulePhysics::CreateFlipperJoint(const flipper &flipper, int lowerAngle, int upperAngle)
{
	//Initialize the joint
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(flipper.Attacher, flipper.Pbody->body, flipper.Attacher->GetWorldCenter());

	jointDef.collideConnected = false;
	//SET the limits for the joint 
	jointDef.enableLimit = true;
	jointDef.lowerAngle = lowerAngle * DEGTORAD;
	jointDef.upperAngle = upperAngle * DEGTORAD;

	//Activate the motor 
	jointDef.enableMotor = true;

	//Create the joint
	return (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}


flipper ModulePhysics::CreateFlipper(int posX, int posY, int att_diameter, int flipper_chain[], int chain_size,
	SDL_Rect flipper_rect, int lowerAngle, int upperAngle, int adjx, int adjy)
{
	flipper flip;



	flip.Attacher = CreateAttacherBody(posX, posY, att_diameter);
	flip.Pbody = CreateFlipperPbody(posX + adjx, posY + adjy, flipper_chain, chain_size);
	flip.Rect = flipper_rect;
	flip.Joint = CreateFlipperJoint(flip, lowerAngle, upperAngle);

	return flip;
}

void ModulePhysics::FlipperSetMaxMotorTorque(flipper &flipper, float32 MaxTorque)
{
	flipper.Joint->SetMaxMotorTorque(MaxTorque);
}

void ModulePhysics::FlipperSetMotorSpeed(flipper &flipper, float32 MotorSpeed)
{
	flipper.Joint->SetMotorSpeed(MotorSpeed);
}


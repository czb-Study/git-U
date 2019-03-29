#include "MyContactListener.h"


MyContactListener::MyContactListener(void)
{
}


MyContactListener::~MyContactListener(void)
{
}


void MyContactListener::BeginContact(b2Contact* contact)
{ 
	CCSprite *sprite =  (CCSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	if (sprite != NULL)
	{
		sprite->setColor(ccc3(255,0,0));
	}
	sprite =  (CCSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
	if (sprite != NULL)
	{
		sprite->setColor(ccc3(255,0,0));
	}
}
void MyContactListener::EndContact(b2Contact* contact)
{
	CCSprite *sprite =  (CCSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	if (sprite != NULL)
	{
		sprite->setColor(ccc3(255,255,255));
	}
	sprite =  (CCSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
	if (sprite != NULL)
	{
		sprite->setColor(ccc3(255,255,255));
	}
}
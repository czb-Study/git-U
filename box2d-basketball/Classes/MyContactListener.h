#pragma once

#include "cocos2d.h"
#include <Box2D/Box2D.h>
USING_NS_CC;

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{ /* handle pre-solve event */ }
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{ /* handle post-solve event */ }
};


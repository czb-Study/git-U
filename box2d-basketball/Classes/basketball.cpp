#include "basketball.h"

#define PTM_RATIO 32
#define MASS                0.4//����
#define Height              500
#define Width               640
CCScene* basketball::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    basketball *layer = basketball::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool basketball::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	left = (visibleSize.width - Width) / 2;
	bottom = (visibleSize.height - Height) / 2;
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	texture = CCTextureCache::sharedTextureCache()->addImage("tex.png");



	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	world = new b2World(gravity);

	myContactListener = new MyContactListener();
	world->SetContactListener(myContactListener);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom
	groundBox.Set(b2Vec2(left / PTM_RATIO,bottom /PTM_RATIO), b2Vec2((left+Width)/ PTM_RATIO,bottom /PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top
	groundBox.Set(b2Vec2(left/PTM_RATIO,(bottom+Height)/PTM_RATIO), b2Vec2((left+Width)/PTM_RATIO,(bottom+Height)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(left/PTM_RATIO,(bottom+Height)/PTM_RATIO), b2Vec2(left /PTM_RATIO,bottom/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2((left+Width)/PTM_RATIO,bottom/PTM_RATIO), b2Vec2((left+Width)/PTM_RATIO,(bottom+Height)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

	//Ҳ������������һ������
	/*b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f/PTM_RATIO, 0);*/
	groundBody->CreateFixture(&groundBox, 0.0f);
	this->setTouchEnabled(true);
	this->scheduleUpdate();

	createSence();

    return true;
}

basketball::~basketball()
{
	delete world;
	delete myContactListener;
	world = NULL;
}
void basketball::createSence()
{
	//������������Ⱦ��ʽ�ľ���ڵ�
	CCSpriteBatchNode *mgr = CCSpriteBatchNode::createWithTexture(texture);
	//��ӵ�����
	this->addChild(mgr);
	//����
	background = CCSprite::createWithTexture(texture, CCRectMake(0, 0, 640, 500));
	background->setAnchorPoint(ccp(0, 0));
	background->setPosition(ccp(left, bottom));
	mgr->addChild(background);
	//��ʼ����
	startArea = CCSprite::createWithTexture(texture, CCRectMake(647, 124, 100, 100));
	startArea->setPosition(ccp(left + 80, bottom + 150));
	mgr->addChild(startArea);
	//��ͷ
	arrow = CCSprite::createWithTexture(texture, CCRectMake(0, 500, 690, 120));
	arrow->setPosition(startArea->getPosition());
	arrow->setScale(0.1);
	mgr->addChild(arrow);
	//����
	ball = CCSprite::createWithTexture(texture, CCRectMake(654, 0, 72, 72));
	ball->setPosition(startArea->getPosition());
	mgr->addChild(ball);
	//����
	basketry = CCSprite::createWithTexture(texture, CCRectMake(656, 86, 114, 24));
	basketry->setPosition(ccp(left + 550, bottom + 300));
	mgr->addChild(basketry);
	//
	target = CCSprite::createWithTexture(texture, CCRectMake(648, 272, 16, 160));
	target->setPosition(ccp(left + 600, bottom + 350));
	mgr->addChild(target);
	//���Ǽ�
	trangle = CCSprite::createWithTexture(texture, CCRectMake(760, 0, 90, 90));
	trangle->setPosition(ccp(left + Width - 45, bottom + 45));
	mgr->addChild(trangle);
	//���Ǽ�box
	b2BodyDef trangleBodyDef;
	trangleBodyDef.position.Set(0.0f, 0.0f);
	b2Body* trangleBody = world->CreateBody(&trangleBodyDef);
	// Define the ground box shape.
    b2EdgeShape trangleBox;
	 // bottom
	trangleBox.Set(b2Vec2((left+Width-90-10)/ PTM_RATIO,bottom /PTM_RATIO), b2Vec2((left+Width)/ PTM_RATIO,(bottom+90+10) /PTM_RATIO));
    trangleBody->CreateFixture(&trangleBox,0);
	//�������
	b2BodyDef basketryBodyDef;
	basketryBodyDef.position.Set(0.0f, 0.0f);
	b2Body* basketryBody = world->CreateBody(&basketryBodyDef);
	// Define the ground box shape.
    b2EdgeShape basketryBox;
	 // bottom
	basketryBox.Set(b2Vec2((basketry->getPosition().x-57)/PTM_RATIO,basketry->getPosition().y/PTM_RATIO), b2Vec2((basketry->getPosition().x-47)/PTM_RATIO,basketry->getPosition().y/PTM_RATIO));
    basketryBody->CreateFixture(&basketryBox,0);
	//�ұ�����
	b2BodyDef basketryBodyDef1;
	basketryBodyDef1.position.Set(0.0f, 0.0f);
	b2Body* basketryBody1 = world->CreateBody(&basketryBodyDef1);
	// Define the ground box shape.
    b2EdgeShape basketryBox1;
	 // bottom
	basketryBox1.Set(b2Vec2((basketry->getPosition().x+45)/PTM_RATIO,basketry->getPosition().y/PTM_RATIO), b2Vec2((basketry->getPosition().x+50)/PTM_RATIO,basketry->getPosition().y/PTM_RATIO));
    basketryBody1->CreateFixture(&basketryBox1,0);
	//����
	b2BodyDef bodyDef;
	bodyDef.type=b2_staticBody;
	bodyDef.position.Set(ball->getPosition().x/PTM_RATIO,ball->getPosition().y/PTM_RATIO);
	bodyDef.userData = ball;
	body = world->CreateBody(&bodyDef);
	b2CircleShape dynamicBox;
	dynamicBox.m_radius=42.0f/PTM_RATIO;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = MASS;		//�ܶ�
	fixtureDef.friction = 0.3f;		//Ħ��ϵ��
	fixtureDef.restitution = 0.8f;      //�ָ�ϵ��
	body->CreateFixture(&fixtureDef);	

}

void basketball::registerWithTouchDispatcher()
{
	 CCDirector* pDirector = CCDirector::sharedDirector();
	 pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void basketball::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = touch->getLocation();
	touchLocation = convertToNodeSpace(touchLocation);
	//�õ���ǰ���λ���뿪ʼλ�õ�����������������
	force = startArea->getPosition() - touchLocation;
	//�������ȵĳ�����ʾ���صĶ���
	arrow->setScaleX(force.getLength() / 500);
	//�ı�Ƕ���ʾ���صĶ���
	arrow->setRotation(-force.getAngle()*180/3.14);
	//������괥���ƶ�����ͷ�Ĵ�С������������Ӧ�仯
	//������ƶ�����������¼Ϊ��force������TouchEndʱ��ΪͶ��ʱ��������

}
void basketball::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	 
	CCPoint touchLocation = touch->getLocation();
	touchLocation = convertToNodeSpace(touchLocation);
	body->SetType(b2_dynamicBody);
	body->ApplyForceToCenter(b2Vec2(force.x*10,force.y*10));
	body->ApplyTorque(360.0f);
	//�Ƿ��ͷ�����
	isShoot = true;
}
bool basketball::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = touch->getLocation();
	touchLocation = convertToNodeSpace(touchLocation);

	ball->setPosition(startArea->getPosition());
	body->SetTransform(b2Vec2(startArea->getPosition().x/PTM_RATIO,startArea->getPosition().y/PTM_RATIO),0.0f);
	body->SetType(b2_staticBody);
	startPos = touchLocation;
	isShoot = false;

	return true;
}
void basketball::update(float dt)
{
	int velocityIterations = 8;
    int positionIterations = 2;

// Instruct the world to perform a single step of simulation. It is
// generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) 
		{
			CCSprite *sprite = (CCSprite*)b->GetUserData();
			sprite->setPosition(ccp(
			 						b->GetPosition().x * PTM_RATIO, 
									b->GetPosition().y * PTM_RATIO)
								);
			sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}	
}

void basketball::parseContact()
{
    b2Vec2 contactPoint;
    contactPoint.SetZero();
    for(b2Contact * contact = world->GetContactList();contact;contact=contact->GetNext()){
       /*if (contact->GetFixtureA()->GetBody() == contactObj ||
            contact->GetFixtureB()->GetBody() == contactObj){*/
		{
            b2Manifold *manifold = contact->GetManifold();
            switch (manifold->type) {
                case b2Manifold::e_circles:
                    contactPoint = contact->GetFixtureA()->GetBody()->GetWorldPoint(manifold->localPoint);
                    break;
				case b2Manifold::e_faceA:
                    contactPoint = contact->GetFixtureA()->GetBody()->GetWorldPoint(manifold->localPoint);
                    break;
                case b2Manifold::e_faceB:
                    contactPoint = contact->GetFixtureB()->GetBody()->GetWorldPoint(manifold->localPoint);
                    break;
                default:
                    break;
            }
        }
    }
}





#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));
		
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		CCMenuItemFont *item1   =CCMenuItemFont::create("start",this,menu_selector(HelloWorld::move));
		CCMenu *menu    =CCMenu::create(item1,NULL);
		addChild(menu);
		menu->setPosition(ccp(420,50));

		CCSprite *sprite  =CCSprite::create("CloseNormal.png");
		addChild(sprite);
		sprite->setTag(10);

		//CCSize size    =CCDirector::sharedDirector()->getWinSize();

		CCSprite *ansprite  =CCSprite::create("grossini_dance_01.png");

		addChild(ansprite);
		ansprite->setPosition(ccp(size.width/2,size.height/2));

		CCAnimation* animation   =CCAnimation::create();
		for (int i=1;i<15;i++)
		{
			CCString* fileName   =CCString::createWithFormat("grossini_dance_%02d.png",i);
			/*	CCSize spritesize     =ansprite->getContentSize();
			CCRect rect                =CCRect(0,0,spritesize.width,spritesize.height);
			CCSpriteFrame *frame    =CCSpriteFrame::create(fileName->getCString(),rect);
			animation->addSpriteFrame(frame);*/

			animation->addSpriteFrameWithFileName(fileName->getCString());
		}
		
		animation->setDelayPerUnit(0.1f);
		animation->setLoops(-1);
		CCAnimate* animate     =CCAnimate::create(animation);

		ansprite->runAction(animate);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::show(){
	CCLabelTTF *label=CCLabelTTF::create("stop","Arial",30);
	this->addChild(label);
	label->setPosition(ccp(240,160));
}

void HelloWorld::move(CCObject *sender){

	CCMoveBy *moveBy =CCMoveBy::create(2.0f,ccp(240,100));
	CCRotateBy *rotateBy   =CCRotateBy::create(2.0f,720);
	CCFlipX *flipx   =CCFlipX::create(true);

	CCFiniteTimeAction *spaw  =CCSpawn::create(moveBy,rotateBy,flipx,NULL);

	CCCallFunc *call =CCCallFunc::create(this,callfunc_selector(HelloWorld::show));


	CCFiniteTimeAction *seq  =CCSequence::create(moveBy,rotateBy,call,flipx,spaw,NULL);
	CCNode *node    =this->getChildByTag(10);
	node->runAction(seq);

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


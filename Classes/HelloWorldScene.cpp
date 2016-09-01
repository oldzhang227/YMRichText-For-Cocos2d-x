#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "YMRichText/YMRichText.h"
#include "json/rapidjson.h"
#include "json//document.h"
#include "YMRichText/YMBubbleText.h"
#include "YMRichText/YMMessage.h"

enum LINKTYPE
{
	LINKTYPE_url = 1,
	LinkTYPE_dialog = 2,
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	// 添加搜索路径
	FileUtils::getInstance()->addSearchPath("/emoj");
	FileUtils::getInstance()->addSearchPath("/image");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 背景图
	ImageView* backImage = ImageView::create("chat_bg.jpg");
	backImage->ignoreContentAdaptWithSize(false);
	backImage->setAnchorPoint(Point::ZERO);
	backImage->setContentSize(visibleSize);
	backImage->setPosition(origin);
	this->addChild(backImage);

	std::string ymString = FileUtils::getInstance()->getStringFromFile("text.txt");
	// 计算高度
	YMBubbleText* bubbbleText = YMBubbleText::create(ymString);
	bubbbleText->setMaxLineWidth(visibleSize.width - HEAD_SIZE * 2 - 30);
	bubbbleText->setStretchableImage("chatfrom_bg_normal.png", Rect(40, 60, 1, 1));
	bubbbleText->setOffset(Rect(20,10,10,10));
	bubbbleText->adjustFrame();
	float h = bubbbleText->getContentSize().height;
	// 构造数据
	for (int i = 0; i < 10; i++)
	{
		YMMessage* message = YMMessage::create(ymString);
		if (message)
		{
			if (i % 2 == 0)
			{
				message->setIsLeft(false);
			}
			message->setHeight(h);
			_ymMessages.pushBack(message);
		}
	}
	// 显示列表
	TableView* tableView = TableView::create(this, visibleSize);
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setAnchorPoint(Point::ZERO);
	tableView->setPosition(origin);
	tableView->reloadData();
	this->addChild(tableView);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::clickYMLinkTextCallBack(const std::string& linkData)
{
	rapidjson::Document jsonDict;
	jsonDict.Parse<0>(linkData.c_str());
	if (jsonDict.HasParseError())
	{
		CCLOG("GetParseError %d\n", jsonDict.GetParseError());
		return;
	}

	if (jsonDict.HasMember("type"))
	{
		int type = jsonDict["type"].GetInt();
			switch (type) {
			case LINKTYPE_url:
			{
				std::string url = jsonDict["url"].GetString();
				Application::getInstance()->openURL(url);
			}
			break;
			case LinkTYPE_dialog:
			{
				std::string text = jsonDict["text"].GetString();
				showMessage(text);
			}
			break;
			default:
				break;
			}
	}
	
}

Size HelloWorld::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	float h = _ymMessages.at(idx)->getHeight();
	float w = table->getContentSize().width;
	return Size(w, h);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx)
{
	TableViewCell* ceil = table->dequeueCell();
	if (!ceil)
	{
		ceil = TableViewCell::create();
	}
	else
	{
		ceil->removeAllChildren();
	}

	float tableWidth = table->getContentSize().width;
	float bubbleWidth = tableWidth - HEAD_SIZE * 2 - 30;

	YMMessage* message = _ymMessages.at(idx);
	// 气泡文本
	YMBubbleText* bubbleText = YMBubbleText::create(message->getYMString());
	bubbleText->setMaxLineWidth(bubbleWidth);
	bubbleText->addYMLinkTextClickListener(CC_CALLBACK_1(HelloWorld::clickYMLinkTextCallBack, this));
	// 头像
	ImageView* head = nullptr;
	if (message->isLeft())
	{
		bubbleText->setOffset(Rect(20, 10, 10, 10));
		bubbleText->setStretchableImage("chatfrom_bg_focused.png", Rect(40, 60, 1, 1));
		bubbleText->setPositionX(HEAD_SIZE);
		bubbleText->adjustFrame();
		bubbleText->setAnchorPoint(Point::ZERO);
		float h = bubbleText->getContentSize().height;
		head = ImageView::create("head1.jpg");
		head->ignoreContentAdaptWithSize(false);
		head->setAnchorPoint(Point::ZERO);
		head->setPosition(Point(0.0f, h - HEAD_SIZE));
		head->setContentSize(Size(HEAD_SIZE, HEAD_SIZE));

	}
	else
	{
		bubbleText->setOffset(Rect(10, 10, 20, 10));
		bubbleText->setStretchableImage("chatto_bg_focused.png", Rect(40, 60, 1, 1));
		bubbleText->setPositionX(HEAD_SIZE);
		bubbleText->adjustFrame();
		bubbleText->setAnchorPoint(Point::ZERO);
		float h = bubbleText->getContentSize().height;
		head = ImageView::create("head2.jpg");
		head->ignoreContentAdaptWithSize(false);
		head->setContentSize(Size(HEAD_SIZE, HEAD_SIZE));
		head->setAnchorPoint(Point::ZERO);
		head->setPosition(Point(tableWidth - HEAD_SIZE, h - HEAD_SIZE));
	}
	ceil->addChild(bubbleText);
	ceil->addChild(head);
	return ceil;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table)
{
	return _ymMessages.size();
}

void HelloWorld::showMessage(std::string message)
{
	YMBubbleText* bubbbleText = YMBubbleText::create(message);
	bubbbleText->setMaxLineWidth(300);
	bubbbleText->setStretchableImage("tip.png", Rect(48, 33, 1, 1));
	bubbbleText->setOffset(Rect(10, 10, 10, 10));
	bubbbleText->adjustFrame();

	FadeIn* fadeIn = FadeIn::create(0.5f);
	DelayTime* delayTime = DelayTime::create(0.5f);
	FadeOut* fadeOut = FadeOut::create(0.5f);
	auto call = CallFuncN::create([](Node* node) {
		node->removeFromParent();
	});
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bubbbleText->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Sequence* action = Sequence::create(fadeIn, delayTime, fadeOut, call, nullptr);
	bubbbleText->runAction(action);

	this->addChild(bubbbleText);
}

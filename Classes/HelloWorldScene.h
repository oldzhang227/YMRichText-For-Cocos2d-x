#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "YMRichText/YMMessage.h"
USING_NS_CC;
USING_NS_CC_EXT;


#define HEAD_SIZE	80

class HelloWorld : public cocos2d::Layer,public TableViewDataSource
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	// 点击事件
	void clickYMLinkTextCallBack(const std::string& linkData);

	// TabelView
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);

	virtual ssize_t numberOfCellsInTableView(TableView *table);

	// 显示消息提示
	void showMessage(std::string message);
private:

	Vector<YMMessage*> _ymMessages;
};

#endif // __HELLOWORLD_SCENE_H__

//
//  YMLickText.h
//  YMLickText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//

#ifndef YMLINKTEXT_H
#define YMLINKTEXT_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;


// 点击回调
typedef std::function<void(const std::string& linkData)> ymlinkTextClickCallBack;


class YMLinkText:public Text
{
public:
	YMLinkText();
	~YMLinkText();

	// 创建
	static YMLinkText* create(const std::string& textContent,
		const std::string& fontName,
		float fontSize);

	virtual bool init(const std::string& textContent,
		const std::string& fontName,
		float fontSize)override;

	// 回调
	void addClickCallBack(const ymlinkTextClickCallBack& callBack);
	// 点击
	void onClick(Ref* pSender);
	// 数据
	void setLinkData(const std::string& linkData);
	// 设置文字颜色
	void setTextColor(const Color4B color);
protected:
	virtual void adaptRenderers() override;
	virtual void onSizeChanged() override;

private:
	// 是否需要刷新线
	bool _lineDirty;
	// 划线
	DrawNode* _drawNode;
	// 数据
	std::string _linkData;
	// 回调
	ymlinkTextClickCallBack _ymCallBack;
};















#endif

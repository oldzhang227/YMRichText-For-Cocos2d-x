//
//  YMLickText.cpp
//  YMLickText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//

#include "YMLinkText.h"



YMLinkText::YMLinkText():Text(),
_drawNode(nullptr),
_lineDirty(true)
{

}

YMLinkText::~YMLinkText()
{

}


YMLinkText* YMLinkText::create(const std::string &textContent, const std::string &fontName, float fontSize)
{
	YMLinkText *text = new (std::nothrow) YMLinkText;
	if (text && text->init(textContent, fontName, fontSize))
	{
		text->autorelease();
		return text;
	}
	CC_SAFE_DELETE(text);
	return nullptr;
}


bool YMLinkText::init(const std::string &textContent, const std::string &fontName, float fontSize)
{
	bool ret = true;
	do
	{
		_drawNode = DrawNode::create();
		addChild(_drawNode);
		if (!Text::init(textContent, fontName, fontSize))
		{
			ret = false;
			break;
		}
		setTouchEnabled(true);
		addClickEventListener(CC_CALLBACK_1(YMLinkText::onClick, this));
	} while (0);
	return ret;
}


void YMLinkText::addClickCallBack(const ymlinkTextClickCallBack& callBack)
{
	_ymCallBack = callBack;
}

void YMLinkText::onClick(Ref* pSender)
{
	if (_ymCallBack)
	{
		_ymCallBack(_linkData);
	}
}

void YMLinkText::setLinkData(const std::string& linkData)
{
	_linkData = linkData;
}

void YMLinkText::setTextColor(const Color4B color)
{
	Text::setTextColor(color);
	_lineDirty = true;
}

void YMLinkText::adaptRenderers()
{
	Text::adaptRenderers();

	if (_drawNode && _lineDirty)
	{
		Point orginPoint = Point::ZERO;
		Point desPoint = Point(_contentSize.width, 0.0f);
		Color4F color = Color4F(getTextColor());
		_drawNode->drawLine(orginPoint, desPoint, color);
		_lineDirty = false;
	}
}

void YMLinkText::onSizeChanged()
{
	Text::onSizeChanged();
	_lineDirty = true;
}



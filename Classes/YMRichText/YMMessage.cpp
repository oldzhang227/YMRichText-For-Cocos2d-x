//
//  YMMessage.cpp
//  YMMessage
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#include "YMMessage.h"

YMMessage::YMMessage():
_isLeft(true),
_height(0.0f),
_ymString("")
{

}

YMMessage::~YMMessage()
{

}

YMMessage* YMMessage::create(const std::string & ymString)
{
	YMMessage *ymMessage = new (std::nothrow) YMMessage;
	if (ymMessage)
	{
		ymMessage->setYMString(ymString);
		ymMessage->autorelease();
		return ymMessage;
	}
	CC_SAFE_DELETE(ymMessage);
	return nullptr;
}


void YMMessage::setYMString(const std::string & ymString)
{
	_ymString = ymString;
}

void YMMessage::setHeight(float h)
{
	_height = h;
}

void YMMessage::setIsLeft(bool isLeft)
{
	_isLeft = isLeft;
}

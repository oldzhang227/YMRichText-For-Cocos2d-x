//
//  YMMessage.h
//  YMMessage
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#ifndef YMMESSAGE_H
#define YMMESSAGE_H
#include "cocos2d.h"

USING_NS_CC;


class YMMessage:public Ref
{
public:
	YMMessage();
	~YMMessage();

	// 创建
	static YMMessage* create(const std::string& ymString);
	// 设置文本
	void setYMString(const std::string& ymString);
	std::string getYMString() { return _ymString; };
	// 设置高度
	void setHeight(float h);
	float getHeight() { return _height; };
	// 设置朝向
	void setIsLeft(bool isLeft);
	bool isLeft() { return _isLeft; };
private:

	bool          _isLeft;
	float         _height;
	std::string	  _ymString;

};
#endif
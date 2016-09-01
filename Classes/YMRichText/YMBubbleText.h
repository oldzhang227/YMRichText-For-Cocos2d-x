//
//  YMBubbleText.h
//  YMBubbleText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#ifndef YMBUBBLETEXT_H
#define YMBUBBLETEXT_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "YMRichText.h"

USING_NS_CC;
using namespace ui;

class YMBubbleText:public Widget
{
public:
	YMBubbleText();
	~YMBubbleText();

	static YMBubbleText* create(const std::string& ymString);
	bool init(const std::string& ymString);
	// 设置宽度
	void setMaxLineWidth(float width);
	// 文字相对背景图偏移
	void setOffset(const Rect& rect);
	// 设置文本
	void setText(const std::string& text);
	// 设置背景图
	void setStretchableImage(const std::string& image, const Rect &capInsets);
	// 调整
	void adjustFrame();
	//点击事件
	void addYMLinkTextClickListener(const ymlinkTextClickCallBack& callBack);
protected:
	virtual void adaptRenderers() override;
private:

	bool          _dirty;
	Rect          _offset;
	ImageView*    _imageView;
	YMRichText*   _richText;

};

#endif
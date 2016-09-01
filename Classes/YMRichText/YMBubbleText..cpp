//
//  YMBubbleText.cpp
//  YMBubbleText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#include "YMBubbleText.h"


YMBubbleText::YMBubbleText():Widget(),
_dirty(true),
_offset(Rect::ZERO),
_imageView(nullptr),
_richText(nullptr)
{

}

YMBubbleText::~YMBubbleText()
{

}


YMBubbleText* YMBubbleText::create(const std::string& ymString)
{
	YMBubbleText *ymBubbleText = new (std::nothrow) YMBubbleText;
	if (ymBubbleText && ymBubbleText->init(ymString))
	{
		ymBubbleText->autorelease();
		return ymBubbleText;
	}
	CC_SAFE_DELETE(ymBubbleText);
	return nullptr;
}


bool YMBubbleText::init(const std::string& ymString)
{
	bool ret = true;
	do
	{
		if (!Widget::init())
		{
			ret = false;
			return ret;
		}
		_imageView = ImageView::create();
		addChild(_imageView);
		_richText = YMRichText::create(ymString);
		addChild(_richText);
	} while (0);
	return ret;
}

void YMBubbleText::setMaxLineWidth(float width)
{
	if (_richText)
	{
		_richText->setMaxLineWidth(width);
		_dirty = true;
	}
}

void YMBubbleText::setOffset(const Rect& rect)
{
	_offset = rect;
	_dirty = true;
}

void YMBubbleText::setText(const std::string& text)
{
	if (_richText)
	{
		_richText->setText(text);
		_dirty = true;
	}
}

void YMBubbleText::setStretchableImage(const std::string& image, const Rect &capInsets)
{
	if (_imageView)
	{
		_imageView->setAnchorPoint(Point::ZERO);
		_imageView->setPosition(Point::ZERO);
		_imageView->ignoreContentAdaptWithSize(false);
		_imageView->setScale9Enabled(true);
		_imageView->loadTexture(image);
		_imageView->setCapInsets(capInsets);
		_dirty = true;
	}
}

void YMBubbleText::adjustFrame()
{
	if (_dirty)
	{
		// 调整位置，大小
		_richText->setPosition(_offset.origin);
		_richText->formateText();
		Size textSize = _richText->getContentSize();
		float w = textSize.width + _offset.origin.x + _offset.size.width;
		float h = textSize.height + _offset.origin.y + _offset.size.height;
		Size imageSize = Size(w, h);
		_imageView->setContentSize(imageSize);
		setContentSize(imageSize);

		_dirty = false;
	}
}

void YMBubbleText::addYMLinkTextClickListener(const ymlinkTextClickCallBack& callBack)
{
	if (_richText)
	{
		_richText->addYMLinkTextClickListener(callBack);
	}
}

void YMBubbleText::adaptRenderers()
{
	Widget::adaptRenderers();
	adjustFrame();
}

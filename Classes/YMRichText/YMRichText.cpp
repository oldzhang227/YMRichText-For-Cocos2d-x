//
//  YMRichText.cpp
//  YMRichText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#include "YMRichText.h"
#include <float.h>
#include "YMLinkText.h"
#include "Gif/InstantGif.h"
#include "Gif/GifBase.h"


YMRichText::YMRichText():
	_dirty(true),
	_verticalSpace(0.0f),
	_leftSpace(FLT_MAX),
	_maxWidth(FLT_MAX),
	_ymString(""),
	_defFontSize(22),
	_defFontName("fonts/dsf.ttf"),
	_defColor(Color4B::WHITE),
	_linkClickCallBack(nullptr)
{
	
}

YMRichText::~YMRichText()
{


}

YMRichText* YMRichText::create(const std::string& ymString)
{
	YMRichText* ymRichText = new YMRichText();
	if (ymRichText)
	{
		ymRichText->init(ymString);
		ymRichText->autorelease();
	}

	return ymRichText;
}

bool YMRichText::init(const std::string& ymString)
{
	setText(ymString);
	ignoreContentAdaptWithSize(false);

	return true;
}

void YMRichText::setText(const std::string& ymString)
{
	_ymString = ymString;
	_dirty = true;
}

void YMRichText::addYMLinkTextClickListener(const ymlinkTextClickCallBack& callBack)
{
	_linkClickCallBack = callBack;
}

void YMRichText::setMaxLineWidth(float width)
{
	_maxWidth = width;
	_dirty = true;
}

void YMRichText::formateText()
{
	if (_dirty == false) {
		return;
	}
	removeAllChildren();
	_container.clear();
	if (_ymString == "") {
		return;
	}
	// 解析文本
	YMStringParser ymStringParser = YMStringParser();
	auto result = ymStringParser.parser(_ymString);
	if (result.empty() == false)
	{
		addNewLine();
		for(YMStringElement* element: result)
		{
			CCLOG("%s",element->toString().c_str());
			switch (element->type()) {
			case YMStringType::YMString_text:
				handerLabelElement(element);
				break;
			case YMStringType::YMString_emoj:
				handerEmojElement(element);
				break;
			case YMStringType::YMString_image:
				handerImageElement(element);
				break;
			case YMStringType::YMString_link:
				handerLinkElement(element);
				break;
			case YMStringType::YMString_break:
				addNewLine();
				break;
			case YMStringType::YMString_defset:
				handerDefSetElement(element);
				break;
			default:
				break;
			}
		}
	}
	formatetRender();
	_dirty = false;
}



void YMRichText::adaptRenderers()
{
	formateText();
}


void YMRichText::formatetRender()
{
   // 总的高度
	float totalHeight = 0.0f;
	// 计算每行行高
	std::vector<float> heightArray;
    for (Vector<Node*> row : _container) {
        float maxHeight = 0.0f;
        for (auto node : row) {
			float h = node->getContentSize().height;
            if (h > maxHeight) {
                maxHeight = h;
            }
        }
		heightArray.push_back(maxHeight);
		totalHeight += maxHeight;
    }
	// 加上间距 
	totalHeight += (heightArray.size() - 1) * _verticalSpace;
    // 设置子节点位置
    float maxX = 0.0f;
	float y = totalHeight;
    for (int i = 0; i < _container.size(); ++i) {
		float maxHeight = heightArray[i];
        float x = 0.0f;
		y -= maxHeight;
        for (Node* node: _container[i]) {
			Size size = node->getContentSize();
			size.height = maxHeight;
			node->setAnchorPoint(Point::ZERO);
			node->setContentSize(size);
			node->setPosition(Point(x,y));
			this->addChild(node);
            x += size.width;
        }
		y -= _verticalSpace;
        if (x > maxX) {
            maxX = x;
        }
    }
    
	setContentSize(Size(maxX, totalHeight));
}

void YMRichText::addNewLine()
{
    _leftSpace = _maxWidth;
	_container.push_back(Vector<Node*>());
}

void YMRichText::pushInContainer(Node* node)
{
	 _container[_container.size() - 1].pushBack(node);
}

Color4B YMRichText::parserColor(std::string colorStr)
{
    // #ARGB
	colorStr = colorStr.substr(1);
    
    uint32_t num = strtoul(colorStr.c_str(), nullptr, 16);
	GLubyte a = num >> 24;
	GLubyte r = num >> 16;
	GLubyte g = num >> 8 ;
	GLubyte b = num;

	return Color4B(r, g, b, a);
}


void YMRichText::setVerticalSpace(float verticalSpace)
{
	_verticalSpace = verticalSpace;
	_dirty = true;
}

void YMRichText::handerLabelElement(YMStringElement* element)
{
    std::string attr = "";
    int fontSize = _defFontSize;
    if ((attr = element->getAttrValue(ATTR_SIZE)) != "") {
        fontSize = atoi(attr.c_str());
    }
    Color4B color = _defColor;
	if ((attr = element->getAttrValue(ATTR_CORLOR)) != "") {
		color = parserColor(attr);
	}
	std::string contentStr = element->getContentStr();
	Label* label = Label::createWithTTF(contentStr, _defFontName, fontSize);
	label->setVerticalAlignment(TextVAlignment::BOTTOM);
	label->setTextColor(color);
    Size size = label->getContentSize();
    if (size.width < _leftSpace) {
		pushInContainer(label);
        _leftSpace -= size.width;
    }
    else
    {
		// 转来转去的，效率有点堪忧
		std::string utf8String = "";
		std::u16string utf16String;
		if (!StringUtils::UTF8ToUTF16(contentStr, utf16String))
		{
			return;
		}
		// 拆分换行
        for (int i = 0;  i < utf16String.size(); ++i) {
            // 转换前必须治空
            utf8String = "";
			if (StringUtils::UTF16ToUTF8(utf16String.substr(i, 1), utf8String))
			{
				label->setString(utf8String);
				Size size = label->getContentSize();
				_leftSpace -= size.width;
				if (_leftSpace < 0) {
                    utf8String = "";
					if (StringUtils::UTF16ToUTF8(utf16String.substr(0, i), utf8String))
					{
						label->setString(utf8String);
						pushInContainer(label);
						addNewLine();
						element->setContentStr(contentStr.substr(utf8String.size()));
						handerLabelElement(element);
					}
					break;
				}
			}
        }
    }
}

void YMRichText::handerImageElement(YMStringElement* element)
{
    std::string attr = "";
    int width = 0, height = 0;
    if ((attr = element->getAttrValue(ATTR_WIDTH)) != "") {
		width = atoi(attr.c_str());
    }
    if ((attr = element->getAttrValue(ATTR_HEIGHT)) != "") {
        height = atoi(attr.c_str());
    }
    std::string fileName = "";
    if ((attr = element->getAttrValue(ATTR_IMAGE)) != "") {
        fileName = attr;
    }
	Sprite* sprite = Sprite::create(fileName);
	if (sprite)
	{
		if (width != 0 && height != 0) {
			sprite->setContentSize(Size(width, height));
		}
		float w = sprite->getContentSize().width;
		_leftSpace -= w;
		if (_leftSpace < 0) {
			addNewLine();
			_leftSpace -= w;
		}
		pushInContainer(sprite);
	}
}

void YMRichText::handerEmojElement(YMStringElement *element)
{
    std::string attr = "";
    int width = 0, height = 0;
    if ((attr = element->getAttrValue(ATTR_WIDTH)) != "") {
        width = atoi(attr.c_str());
    }
    if ((attr = element->getAttrValue(ATTR_HEIGHT)) != "") {
		height = atoi(attr.c_str());
    }
	std::string name = element->getAttrValue(ATTR_EMOJ) + ".gif";
	name = CCFileUtils::sharedFileUtils()->fullPathForFilename(name.c_str());
	GifBase *gif = InstantGif::create(name.c_str());
	if (gif)
	{
		gif->setAnchorPoint(Point::ZERO);
		gif->setPosition(Point::ZERO);
		if (width != 0 && height != 0)
		{
			gif->setContentSize(Size(width, height));
		}

		_leftSpace -= gif->getContentSize().width;
		if (_leftSpace < 0) {
			addNewLine();
			_leftSpace -= gif->getContentSize().width;
		}
		pushInContainer(gif);
	}
}

void YMRichText::handerLinkElement(YMStringElement* element)
{
	std::string attr = "";
	int fontSize = _defFontSize;
	if ((attr = element->getAttrValue(ATTR_SIZE)) != "") {
		fontSize = atoi(attr.c_str());
	}
	Color4B color = _defColor;
	if ((attr = element->getAttrValue(ATTR_CORLOR)) != "") {
		color = parserColor(attr);
	}
	std::string linkData = element->getAttrValue(ATTR_LINK);
	std::string contentStr = element->getContentStr();
	YMLinkText* label = YMLinkText::create(contentStr, _defFontName, fontSize);
	label->setTextVerticalAlignment(TextVAlignment::BOTTOM);
	label->setTextColor(color);
	label->setLinkData(linkData);
	label->addClickCallBack(_linkClickCallBack);
	Size size = label->getContentSize();
	if (size.width < _leftSpace) {
		pushInContainer(label);
		_leftSpace -= size.width;
	}
	else
	{
		// 转来转去的，效率有点堪忧
		std::string utf8String;
		std::u16string utf16String;
		if (!StringUtils::UTF8ToUTF16(contentStr, utf16String))
		{
			return;
		}
		// 拆分换行
		for (int i = 0; i < utf16String.size(); ++i) {
            utf8String = "";
			if (StringUtils::UTF16ToUTF8(utf16String.substr(i, 1), utf8String))
			{
				label->setString(utf8String);
				Size size = label->getContentSize();
				_leftSpace -= size.width;
				if (_leftSpace < 0) {
                    utf8String = "";
					if (StringUtils::UTF16ToUTF8(utf16String.substr(0, i), utf8String))
					{
						label->setString(utf8String);
						pushInContainer(label);
						addNewLine();
						element->setContentStr(contentStr.substr(utf8String.size()));
						handerLinkElement(element);
					}
					break;
				}
			}
		}
	}

}

void YMRichText::handerDefSetElement(YMStringElement*element)
{
	std::string attr = "";
	if ((attr = element->getAttrValue(ATTR_DEFS)) != "") {
		_defFontSize = atoi(attr.c_str());
	}
	if ((attr = element->getAttrValue(ATTR_DEFC)) != "") {
		_defColor = parserColor(attr.c_str());
	}
}



//
//  YMStringElement.cpp
//  YMStringElement
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//


#include "YMStringElement.h"

YMStringElement::YMStringElement():
_type(YMStringType::YMString_nil),
_content("")
{


}

YMStringElement::~YMStringElement()
{

}

void YMStringElement::addAttrValue(std::string key, std::string value)
{
	_attrs[key] = value;
}

std::string YMStringElement::getAttrValue(const std::string & key)
{
	auto iter = _attrs.find(key);
	if (iter != _attrs.end())
	{
		return iter->second;
	}

	return "";
}

void YMStringElement::formatType()
{
	// 通过是否包含关键字来判断
	if (getAttrValue(ATTR_IMAGE) != "")
	{
		_type = YMStringType::YMString_image;
	}
	if (getAttrValue(ATTR_LINK) != "")
	{
		_type = YMStringType::YMString_link;
	}
	if (getAttrValue(ATTR_EMOJ) != "")
	{
		_type = YMStringType::YMString_emoj;
	}
	if (getAttrValue(ATTR_DEFC) != "" || getAttrValue(ATTR_DEFS) != "")
	{
		_type = YMStringType::YMString_defset;
	}
	if (_type == YMStringType::YMString_nil && !_content.empty())
	{
		_type = YMStringType::YMString_text;
	}
}

void YMStringElement::setType(YMStringType type)
{
	_type = type;
}

std::string YMStringElement::toString()
{
	if (_type == YMStringType::YMString_break)
	{
		return "\n";
	}
	if (_attrs.empty())
	{
		return _content;
	} 
	else
	{
		std::string s = "[" + _content + "/";
		auto iter = _attrs.begin();
		while (iter != _attrs.end())
		{
			s += iter->first + "=" + iter->second;
			iter++;
			if (iter != _attrs.end())
			{
				s += "&";
			}
		}
		s += "]";
		return s;
	}
}

bool YMStringElement::isNormalString()
{
	if (_type == YMStringType::YMString_text && _attrs.empty())
	{
		return true;
	}
	return false;
}


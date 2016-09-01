//
//  YMStringParser.cpp
//  YMStringParser
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#include "YMStringParser.h"


YMStringParser::YMStringParser()
{

}

YMStringParser::~YMStringParser()
{
	for (auto element:_elements)
	{
		delete element;
	}
	_elements.clear();
}

std::vector<YMStringElement*> YMStringParser::parser(const std::string & str)
{
	const char* p = &str[0];
	while (*p != '\0')
	{
		switch (*p)
		{
		case '[':
			{
				bool isFormatter = false;
				int len = checkAttrsString(p + 1);
				if (len > 0)
				{
					const char* s = geneAttrsString(p);
					if (s != p)
					{
						p = s;
						isFormatter = true;
					}
				} 
				if (!isFormatter)
				{
					p = geneNormalString(p);
				}
			}
			break;
		case  '\n':
			{
				p = genBreakString(p);
			}
			break;
		default:
			{
				p = geneNormalString(p);
			}
			break;
		}

	}
	return _elements;
}

std::string YMStringParser::encode(std::string str)
{
	replaceString(str, "[", "$lt;");
	replaceString(str, "]", "$rt;");
	replaceString(str, "/", "$gt;");
	replaceString(str, "&", "$at;");
	return str;
}

std::string YMStringParser::decode(std::string str)
{
	replaceString(str,"$lt;", "[");
	replaceString(str,"$rt;", "]");
	replaceString(str,"$gt;", "/");
	replaceString(str,"$at;", "&");
	return str;
}

void YMStringParser::replaceString(std::string& content, const std::string& src, const std::string& dst)
{
	std::string::size_type pos = 0;
	while ((pos = content.find(src,pos)) != std::string::npos)
	{
		content.replace(pos, src.size(), dst);
		pos += dst.size();
	}
}

int YMStringParser::checkNormalString(const char * p)
{
	if (*p == '\0')
	{
		return 0;

	} 
	else
	{
		int len = 0;
		do 
		{
			p++;
			len++;
			if (*p == '[' || *p == '\n')
			{
				break;
			}
		} while (*p != '\0');
		return len;
	}
}

int YMStringParser::checkAttrsString(const char * p)
{
	int len = 0;
	while (*p != '\0')
	{
		switch (*p)
		{
		case '[':
		case '\n':
		{
			return 0;
		}
		break;
		case  ']':
		{
			return len + 1;
		}
		break;
		default:
		{
			p++;
			len++;
		}
			break;
		}
	}
	return 0;
}

const char* YMStringParser::geneNormalString(const char* p)
{
	int len = checkNormalString(p);
	std::string content = std::string(p, len);
	YMStringElement* element = new YMStringElement();
	element->setContentStr(content);
	pushYMStringElement(element);
	p += len;
	return p;
}

const char* YMStringParser::geneAttrsString(const char* p)
{
	const char* s = p;
	s++;
	const char* t = s;
	YMStringElement* element = new YMStringElement();
	std::string key = "", value = "";

	while (*s != '\0')
	{
		switch (*s)
		{
		case '/':
		{
			if (element->getContentStr() == "")
			{
				std::string content = std::string(t, s);
				element->setContentStr(content);
				t = s + 1;
			}
		}
		break;
		case '=':
		{
			if (key == "")
			{
				key = std::string(t, s);
				t = s + 1;
			}
		}
		break;
		case '&':
		{
			value = std::string(t, s);
			t = s + 1;
			if (key != "" && value != "")
			{
				element->addAttrValue(key, value);
				key = "";
				value = "";
			}
			else
			{
				delete element;
				return p;
			}
		}
		break;
		case ']':
		{
			value = std::string(t, s);
			t = s + 1;
			if (key != "" && value != "")
			{
				element->addAttrValue(key, value);
				key = "";
				value = "";
			}
			else
			{
				delete element;
				return p;
			}
		}
		break;
		}
		if (*s == ']')
		{
			break;
		}
		s++;
	}
	pushYMStringElement(element);

	return ++s;
}

const char* YMStringParser::genBreakString(const char* p)
{
	YMStringElement* element = new YMStringElement();
	element->setType(YMStringType::YMString_break);
	pushYMStringElement(element);

	return ++p;
}

void YMStringParser::pushYMStringElement(YMStringElement* element)
{
	if(element == nullptr) return;
	element->formatType();
	if (element->isNormalString())
	{
		int len = _elements.size();
		if (len > 0)
		{
			auto lastElement = _elements[len - 1];
			if (lastElement->isNormalString())
			{
				std::string newContent = lastElement->getContentStr() + element->getContentStr();
				lastElement->setContentStr(newContent);
			}
			else
			{
				_elements.push_back(element);
			}
		}
		else
		{
			_elements.push_back(element);
		}
	}
	else
	{
		_elements.push_back(element);
	}
}

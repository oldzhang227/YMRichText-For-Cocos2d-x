//
//  YMStringElement.h
//  YMStringElement
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//

#ifndef RICHMESSAGE_H
#define RICHMESSAGE_H
#include <string>
#include <map>

// 关键字
#define ATTR_CORLOR "c"     //文字颜色
#define ATTR_SIZE   "s"     //文字大小
#define ATTR_WIDTH  "w"     //宽度
#define ATTR_HEIGHT "h"     //高度
#define ATTR_IMAGE  "image" //图片路径
#define ATTR_EMOJ   "emoj"  //表情名
#define ATTR_LINK   "link"  //链接内容
#define ATTR_DEFC   "defc"  //默认字体颜色
#define ATTR_DEFS   "defs"  //默认字体大小

// 富文本类型
enum class YMStringType
{
	YMString_nil		= 0,// 默认
	YMString_text		= 1,// [文字/c=#ARGB&s=20]
	YMString_image		= 2,// [/image=图片.png&w=100&h=100]
	YMString_emoj		= 3,// [/emoj=xxxx]
	YMString_link		= 4,// [文字/link={json}]
	YMString_break		= 5,// \n
	YMString_defset		= 6,// 默认字体
};

class YMStringElement
{
public:
	YMStringElement();
	~YMStringElement();

	void setContentStr(std::string content) { _content = content; };
	std::string getContentStr() { return _content; };

	void addAttrValue(std::string key, std::string value);
	std::string getAttrValue(const std::string& key);

	void formatType();
	void setType(YMStringType type);

	std::string toString();
	bool isNormalString();
	YMStringType type() { return _type; };

private:
	// 类型
	YMStringType _type;
	// 文本内容
	std::string _content;
	// 额外属性
	std::map<std::string, std::string> _attrs;
};







#endif

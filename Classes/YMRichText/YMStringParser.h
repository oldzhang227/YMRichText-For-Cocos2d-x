//
//  YMStringParser.h
//  YMStringParser
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//


/*
	解析字符串生成拆分后的富文本数组

	规则：
	[]:对括号内的内容解析
	/:正常文本与属性内容的分隔
	=:属性名=属性值
	&:多个属性连接

	示例:
	[文本/c=red&s=20]
	[/image=图片.png]
	[/emoj=表情名]
	[文本/blink={json}]
*/

#ifndef YMString_PARSER_H
#define YMString_PARSER_H
#include <string>
#include <vector>
#include "YMStringElement.h"


class YMStringParser
{
public:
	YMStringParser();
	~YMStringParser();

	// 返回拆分解析后数组
	std::vector<YMStringElement*> parser(const std::string& str);

	// 特殊字符转义
	std::string encode(std::string str);
	std::string decode(std::string str);
	void replaceString(std::string& content, const std::string& src, const std::string& dst);
private:
	// 截止到特殊字符
	int checkNormalString(const char* p);
	// 截取[]内容
	int checkAttrsString(const char* p);
	// 生成纯字符文本
	const char* geneNormalString(const char* p);
	// 生成带属性文本
	const char* geneAttrsString(const char* p);
	// 换行
	const char* genBreakString(const char* p);
	// 合并连续的纯字符文本
	void pushYMStringElement(YMStringElement* element);
	// 结果
	std::vector<YMStringElement*> _elements;
};







#endif
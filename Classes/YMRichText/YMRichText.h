//
//  YMRichText.h
//  YMRichText
//
//  Created by zhangxinwei on 16/8/23.
//  Copyright © 2016年 zhangxinwei. All rights reserved.
//
#ifndef YMRICHTEXT_H
#define YMRICHTEXT_H

#include "YMStringParser.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "YMLinkText.h"
USING_NS_CC;
using namespace ui;



class YMRichText:public Widget
{
public:
	YMRichText();
	~YMRichText();

	// 创建
	static YMRichText* create(const std::string& ymString);
	// 初始化
	bool init(const std::string& ymString);
	// 设置文本
	void setText(const std::string& ymString);
	//点击事件
	void addYMLinkTextClickListener(const ymlinkTextClickCallBack& callBack);
	// 设置行宽
	void setMaxLineWidth(float width);
	// 根据行宽拆分行
	void formateText();
	// 设置位置,大小
	void formatetRender();
	// 文本
	void handerLabelElement(YMStringElement* element);
	// 图片
	void handerImageElement(YMStringElement*element);
	// GIF
	void handerEmojElement(YMStringElement*element);
	// 链接
	void handerLinkElement(YMStringElement*element);
	// 默认
	void handerDefSetElement(YMStringElement*element);
	// 换行
	void addNewLine();
	// 添加到当前行 
	void pushInContainer(Node* node);
	// 解析颜色
	Color4B parserColor(std::string colorStr);
	// 设置行间距
	void setVerticalSpace(float verticalSpace);
protected:
	virtual void adaptRenderers() override;
private:
	// 行距
	float _verticalSpace;
	// 默认字体
	std::string _defFontName;
	// 默认字体大小
	int _defFontSize;
	// 默认颜色
	Color4B _defColor;
	// 是否需要刷新 
	bool _dirty;
	// 剩余宽度
	float _leftSpace;
	// 最大行宽（自动高度）
	float _maxWidth;
	// 富文本字符串
	std::string _ymString;
	// 二维数组存储
	std::vector<Vector<Node*>> _container;
	// 链接点击事件
	ymlinkTextClickCallBack _linkClickCallBack;
};


#endif // !YMRICHTEXT_H
# YMRichText-For-Cocos2d-x

cocos2d-x 富文本:支持图片，文字，GIF表情

Thanks For:[gif-for-cocos2dx-3.x](https://github.com/opentalking/gif-for-cocos2dx-3.x)

###字符串解析格式:
    []: 对括号内的内容解析
  	/:  正常文本与属性内容的分隔
  	=:  属性名=属性值
  	&:  多个属性连接
  	
###预定义属性字段:
    整段文字默认设置(字体颜色,大小):[defc=#ARGB&defs=20]
    文字(字体颜色,大小):           [文字/c=#ARGB&s=20]
    图片(宽度,高度):               [/image=图片名&w=100&h=100]
    表情:                         [/emoj=表情名]
    链接:                         [文字/link={json}]
    换行:                         \n
    
###示例文本:
[/defs=30&defc=#FF000000][还魂门:/c=#FFFF00FF]<br>
[/image=002@2x.png]打开 地狱的大门,不请自来 贪欲念<br>
[/emoj=020][无常路上 买命钱,是生是畜 黄泉见/c=#FFFF0000]<br>
[/image=006@2x.png][还魂门前 许个愿,不要相约 来世见/c=#FF00FF00]<br>
[/image=004@2x.png]盗不到的 叫永远,解不开的 是心门<br>
[/emoj=038][最美的是 遗言,最丑的是 誓言/c=#FF0000FF]<br>
[/emoj=006]那些无法 的改变,就在放下 举起间<br>
[/image=007@2x.png]最假的是 眼泪,最真的看 不见<br>
[/image=010@2x.png][/emoj=010][/image=bd.png][百度一下，你就知道/link={"type":1,"url":"http:www.baidu.com"}]<br>
[/emoj=011][/image=011@2x.png][点击一下，弹出对话框悟空传/c=#FFFF0000&link={"type":2,"text":"我要这天，再遮不住我眼。我要这地，再埋不了我心。要这众生，都明白我意。要那诸佛，全都烟消云散。"}]
  
###效果图:
![](https://github.com/YMSIR/YMRichText-For-Cocos2d-x/blob/master/Resources/show.gif) 

HTML 学习笔记
=============
基于w3school 的 HTML 学习笔记

<!-- GFM-TOC -->
* [HTML 基础](#HTML-基础)
  1. 标题 \<h1\>
  2. 段落 \<p\>
  3. 链接 \<a\>
  4. 图像 \<img\>
  5. HTML \<html\>
  6. 主题 \<body\>

<!-- GFM-TOC -->


# HTML 基础

#### 什么是 HTML？
* HTML 是用来描述网页的一种语言。
* HTML 指的是超文本标记语言 (Hyper Text Markup Language)
* HTML **不是一种编程语言，而是一种标记语言**(markup language)
* 标记语言是一套标记标签 (markup tag)
* HTML 使用**标记标签**来描述网页

#### HTML 标签
* HTML 标记标签通常被称为 HTML 标签 (HTML tag)。
* HTML 标签是由尖括号包围的关键词，比如 ```<html>```
* HTML 标签通常是成对出现的，比如 ```<b>``` 和 ```<b\>```
* 标签对中的第一个标签是开始标签，第二个标签是结束标签
* 开始和结束标签也被称为开放标签和闭合标签

#### HTML 文档 = 网页

* HTML 文档描述网页
* HTML 文档包含 HTML 标签和纯文本
* HTML 文档也被称为网页
* Web 浏览器的作用是读取 HTML 文档，并以网页的形式显示出它们。**浏览器不会显示 HTML 标签，而是使用标签来解释页面的内容**：

```html
<html>
<body>

<h1>我的第一个标题</h1>

<p>我的第一个段落。</p>

</body>
</html>

```
##### 例子解释
```<html>``` 与 ```</html>``` 之间的文本描述网页
```<body>``` 与 ```</body>``` 之间的文本是可见的页面内容
```<h1>``` 与 ```</h1>``` 之间的文本被显示为标题
```<p>``` 与 ```</p>``` 之间的文本被显示为段落

### HTML 标题
HTML 标题（Heading）是通过 ```<h1>``` - ```<h6>``` 等标签进行定义的。
```html
<h1>This is a heading</h1>
<h2>This is a heading</h2>
<h3>This is a heading</h3>
```

### HTML 段落
HTML 段落是通过 ```<p>``` 标签进行定义的。
```html
<p>This is a paragraph.</p>
<p>This is another paragraph.</p>
```

### HTML 链接
HTML 链接是通过 ```<a>``` 标签进行定义的。
```html
<a href="http://houjie.com">My Blog</a>
```
*注释：在 href 属性中指定链接的地址。*

### HTML 图像
HTML 图像是通过 ```<img>``` 标签进行定义的。
```html
<img src="w3school.jpg" width="104" height="142" />
```
*注释：图像的名称和尺寸是以属性的形式提供的。*


### HTML 元素
HTML 文档是由 HTML 元素定义的
HTML 元素指的是从开始标签（start tag）到结束标签（end tag）的所有代码。
|开始标签	|元素内容	|结束标签|
|:--------|:---------|:--------|
|```<p>```	|This is a paragraph|	```</p>```|
|```<a href="default.htm" >```|	This is a link|	```</a>```|
|```<br />```|||		
*注释：开始标签常被称为开放标签（opening tag），结束标签常称为闭合标签（closing tag）。*


### HTML 元素语法
* HTML 元素以开始标签起始
* HTML 元素以结束标签终止
* 元素的内容是开始标签与结束标签之间的内容
* 某些 HTML 元素具有空内容（empty content）
* 空元素在开始标签中进行关闭（以开始标签的结束而结束）
* 大多数 HTML 元素可拥有属性
*提示：您将在本教程的下一章中学习更多有关属性的内容。*

### 嵌套的 HTML 元素
* 大多数 HTML 元素可以嵌套（可以包含其他 HTML 元素）。
* HTML 文档由嵌套的 HTML 元素构成。

### HTML 文档实例
```html
<html>

<body>
<p>This is my first paragraph.</p>
</body>

</html>
```
上面的例子包含三个 HTML 元素。

#### HTML 实例解释
* ```<p>``` 元素：
```<p>```This is my first paragraph.```</p>```
这个 ```<p>``` 元素定义了 HTML 文档中的一个段落。
这个元素拥有一个开始标签 ```<p>```，以及一个结束标签 ```</p>```。
元素内容是：This is my first paragraph。

* ```<body>``` 元素：
```html
<body>
<p>This is my first paragraph.</p>
</body>
```
```<body>``` 元素定义了 HTML 文档的主体。
这个元素拥有一个开始标签 ```<body>```，以及一个结束标签 ```</body>```。
元素内容是另一个 HTML 元素（p 元素）。

* ```<html>``` 元素：
```html
<html>

<body>
<p>This is my first paragraph.</p>
</body>

</html>
```
```<html>``` 元素定义了整个 HTML 文档。
这个元素拥有一个开始标签 ```<html>```，以及一个结束标签 ```</html>```。
元素内容是另一个 HTML 元素（body 元素）。

### 不要忘记结束标签
即使您忘记了使用结束标签，大多数浏览器也会正确地显示 HTML：
```html
<p>This is a paragraph
<p>This is a paragraph
```
上面的例子在大多数浏览器中都没问题，但不要依赖这种做法。**忘记使用结束标签会产生不可预料的结果或错误。**
注释：未来的 HTML 版本不允许省略结束标签。

### 空的 HTML 元素
没有内容的 HTML 元素被称为**空元素**。**空元素是在开始标签中关闭的。**
```<br>``` 就是没有关闭标签的空元素*（```<br>``` 标签定义换行）*。
在 XHTML、XML 以及未来版本的 HTML 中，所有元素都必须被关闭。
在开始标签中添加斜杠，比如 ```<br />```，是**关闭空元素的正确方法**，HTML、XHTML 和 XML 都接受这种方式。
即使 ```<br>``` 在所有浏览器中都是有效的，但使用 ```<br />``` 其实是更长远的保障。



### HTML 提示：使用小写标签
HTML 标签对大小写不敏感：```<P>``` 等同于 ```<p>```。许多网站都使用大写的 HTML 标签。
W3School 使用的是小写标签，因为**万维网联盟（W3C）在 HTML 4 中推荐使用小写，而在未来 (X)HTML 版本中强制使用小写。**

### HTML 属性
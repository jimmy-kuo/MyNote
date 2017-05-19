package Demo5;

/**
 * Created by z.g.13@163.com on 2016/7/25.

    图书信息(Book)，图书的属性包括
        书名(name)、
        作者(author)、
        出版社(press)、
        刊号(ISBN)、
        出版日期(pubDate)、
        页数(pages)等。
 */
public class Book_info
{
    private String name;
    private String author;
    private String press;
    private String ISBN;
    private String pubDate;
    private String pages;

    Book_info(String str1, String str2, String str3, String str4, String str5, String str6)
    {
        /** 构造函数 */
        name = str1;
        author = str2;
        press = str3;
        ISBN = str4;
        pubDate = str5;
        pages = str6;
    }

}

package Demo2_3;

import java.util.Scanner;

/**
 * Created by hj on 16-7-14.
 * 图书信息类
 * 书名、作者、出版社、刊号、出版日期、页数和摘要
 */
class Book_Info {
    String bookname;
    String author;
    String press;
    String ISBN;
    String publishData;
    String pageNum;
    String bookAbstrac;

    Book_Info(String arg1,String arg2,String arg3,String arg4,String arg5,String arg6,String arg7)
    {
        /**
         * /。， 0
        * 构造函数-1
        */
        bookname = arg1;
        author = arg2;
        press = arg3;
        ISBN = arg4;
        publishData = arg5;
        pageNum = arg6;
        bookAbstrac = arg7;
    }

    Book_Info()
    {
        /**
         * 构造函数-2
         */
        System.out.println("请按屏幕提示信息，输入书籍对应的信息");
        System.out.print("请输入书籍的书名：");
        Scanner in = new Scanner(System.in);
        bookname = in.nextLine();
        //System.out.println(bookname);
        System.out.print("请输入书籍的作者：");
        author = in.nextLine();
        System.out.print("请输入书籍的出版社：");
        press = in.nextLine();
        System.out.print("请输入书籍的刊号：");
        ISBN = in.nextLine();
        System.out.print("请输入书籍的出版日期：");
        publishData = in.nextLine();
        System.out.print("请输入书籍的页数：");
        pageNum = in.nextLine();
        System.out.print("请输入书籍的摘要：");
        bookAbstrac = in.nextLine();
    }

    void displayInfo()
    {
        System.out.println("---图书信息---");
        System.out.println("书名\t："+this.bookname);
        System.out.println("作者\t："+this.author);
        System.out.println("出版社\t："+this.press);
        System.out.println("刊号\t："+this.ISBN);
        System.out.println("出版日期\t："+this.publishData);
        System.out.println("页数\t："+this.pageNum);
        System.out.println("摘要\t："+this.bookAbstrac);
        System.out.println();
    }
}

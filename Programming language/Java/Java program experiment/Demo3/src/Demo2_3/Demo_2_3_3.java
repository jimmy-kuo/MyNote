package Demo2_3;

import java.util.Scanner;
import java.util.Vector;

/**
 * Created by hj on 16-7-14.
 * 使用向量保存图书信息，包括书名、作者、出版社、刊号、出版日期、页数和摘要，
 * 并能够实现图书的插入、删除、查找功能。插入、删除时要显示操作是否正确与否的提示信息；
 * 查找时按关键字值进行查找，并显示查找结果。
 */
class Demo_2_3_3 {
    private Book_Info tmp;
    private Vector<Book_Info> BookVector;
    private Scanner in = new Scanner(System.in);

    Demo_2_3_3()
    {
        /**
         * 构造函数
         */
        BookVector = new Vector<>(20, 1);
        System.out.println("请输入初始化时图书信息数目");
        int booknum = in.nextInt();
        int i;
        for(i=0;i<booknum;i++)
            this.insert();
    }

    private void insert()
    {
        /**
         * 插入
         */
        tmp = new Book_Info();
        BookVector.addElement(tmp);
    }

    private void selete()
    {
        /**
         * 查询
         */
        System.out.println("请输入要查询的书目信息(模糊搜索)：");
        String search_info = in.next();
        int VectorSize = BookVector.size();
        int i;
        for(i=0;i<VectorSize;i++)
        {
            //从Vector中取出的是Object类型变量，需要转换成所需类型
            tmp = BookVector.elementAt(i);
            if (this.infoContain(tmp,search_info))
                tmp.displayInfo();
        }
    }

    private boolean infoContain(Book_Info book, String search) {
        return book.bookname.contains(search) ||
                book.author.contains(search) ||
                book.press.contains(search) ||
                book.ISBN.contains(search) ||
                book.publishData.contains(search) ||
                book.pageNum.contains(search) ||
                book.bookAbstrac.contains(search);
    }

    void delete()
    {
        /**
         * 删除
         */
        System.out.println("请输入要删除书籍的ISBN号（刊号）。");
        String ISBN = in.next();
        boolean opreationFlag = true;

        //=============可以重构的部分===============
        int VectorSize = BookVector.size();
        int i;
        for(i=0;i<VectorSize;i++)
        {
            //从Vector中取出的是Object类型变量，需要转换成所需类型
            tmp = BookVector.elementAt(i);
            if(tmp.ISBN.contains(ISBN))
            {
                opreationFlag = false;
                System.out.println("您要删除的书籍信息为：");
                tmp.displayInfo();

                System.out.println("确认删除吗：？（Y/N）");
                String answer = in.next();
                switch (answer) {
                    case "Y":
                    case "y":
                        BookVector.remove(i);
                        break;
                    case "N":
                    case "n":
                        System.out.println("取消删除");
                        break;
                    default:
                        System.out.println("输入了错误的信息，请重新操作。");
                        break;
                }
            }
        }
        if(opreationFlag)
            System.out.println("未查询到对应的书籍信息");

    }


}

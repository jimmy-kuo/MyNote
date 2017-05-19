package Demo5;

/**
 * Created by z.g.13@163.com on 2016/7/25.
    借书记录(BorrowRecord)包括：
        用户(user)、
        借书日期(borrowDate)、
        图书(book)。

    还书记录(ReturnRecord)包括：
        用户(user)、
        还书日期(returnDate)、
        图书(book)。
 */
public class Book_record
{
    private String user;
    private String recordDate;
    private String book;
    private String type;

    Book_record(String str1, String str2, String str3, String str4)
    {
        /** 构造函数 */
        user = str1;
        recordDate = str2;
        book = str3;
        type = str4;
    }

}

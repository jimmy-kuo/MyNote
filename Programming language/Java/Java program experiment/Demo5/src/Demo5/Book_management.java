package Demo5;

import javax.swing.*;
import java.awt.*;
import java.util.Vector;

/**
 * Created by z.g.13@163.com on 2016/7/25.
 编写一个图书管理程序，该程序具有如下功能：
    1)	录入图书信息(Book)，
            图书的属性包括书名(name)、作者(author)、
            出版社(press)、刊号(ISBN)、出版日期(pubDate)、页数(pages)等。
    2)	录入用户信息(User)，
            用户属性包括用户名(account)，密码(password)、用户类型(type)，
            用户分为管理员和普通用户。
    3)	记录每个用户的借书记录，借书记录(BorrowRecord)包括：
            用户(user)、借书日期(borrowDate)、图书(book)。
    4)	记录每个用户的还书记录，还书记录(ReturnRecord)包括：
            用户(user)、还书日期(returnDate)、图书(book)。
 */
public class Book_management extends JFrame
{
    // 数据容器
    private Vector<Book_info> V_BookInfo = new Vector<>(10,5);
    private Vector<User_info> V_UserInfo = new Vector<>(2,1);
    private Vector<Book_record> V_BookRecord = new Vector<>(10,5);

    // 登录界面GUI
    private JButton b_login = new JButton("Login");
    private JLabel l_passwd = new JLabel("PASSWORD",JLabel.CENTER);
    private JPasswordField t_passwd = new JPasswordField(8);
    private JLabel l_userid = new JLabel("USER",JLabel.CENTER);
    private JTextField t_user = new JTextField(8);
    private JPanel panel_login_1 = new JPanel(new GridLayout(1,2,10,15));
    private JPanel panel_login_2 = new JPanel(new GridLayout(1,2,10,15));

    // 管理界面GUI
    // 录入图书信息
    private JLabel title = new JLabel("                                                                                 Book management - `13                                                               ",JLabel.CENTER);
    private JLabel book_title1 = new JLabel("                               录入书籍信息：                                                    ");
    private JLabel book_title2 = new JLabel("-------------------------------------------------------------------------------------------------------------------------------------------------------------                                                                                           ");
    private JLabel l_name = new JLabel("name",JLabel.CENTER);
    private JTextField t_name = new JTextField(8);
    private JLabel l_author = new JLabel("author",JLabel.CENTER);
    private JTextField t_author = new JTextField(8);
    private JLabel l_press = new JLabel("press",JLabel.CENTER);
    private JTextField t_press = new JTextField(8);
    private JLabel l_ISBN = new JLabel("ISBN",JLabel.CENTER);
    private JTextField t_ISBN = new JTextField(8);
    private JLabel l_pubDate = new JLabel("pubDate",JLabel.CENTER);
    private JTextField t_pubDate = new JTextField(8);
    private JLabel l_pages = new JLabel("pages",JLabel.CENTER);
    private JTextField t_pages = new JTextField(8);
    private JPanel panel_1 = new JPanel(new GridLayout(2,6,10,15));
    private JButton b_reg_book = new JButton(" 登录书籍信息");

    // 录入用户信息
    private JLabel user_title1 = new JLabel("                               录入用户信息：                                                    ");
    private JLabel user_title2 = new JLabel("-------------------------------------------------------------------------------------------------------------------------------------------------------------                                                                                           ");
    private JPanel panel_2 = new JPanel(new GridLayout(1,6,10,15));
    private JLabel l_new_userid = new JLabel("user_id",JLabel.CENTER);
    private JTextField t_new_userid = new JTextField(8);
    private JLabel l_new_passwd = new JLabel("passwd",JLabel.CENTER);
    private JTextField t_new_passwd = new JTextField(8);
    private JLabel l_type = new JLabel("user_type",JLabel.CENTER);
    String s[] = {"admin", "user"};
    private JList<String> list = new JList<>(s);
    private JButton b_reg_user = new JButton("注册用户");

    // 借/还书信息
    private JLabel record_title1 = new JLabel("                               录入书籍借还信息：                                                    ");
    private JLabel record_title2 = new JLabel("-------------------------------------------------------------------------------------------------------------------------------------------------------------                                                                                           ");
    private JPanel panel_3 = new JPanel(new GridLayout(1,6,10,15));
    private JLabel l_record_user = new JLabel("user",JLabel.CENTER);
    private JTextField t_record_user = new JTextField(8);
    private JLabel l_record_book = new JLabel("book",JLabel.CENTER);
    private JTextField t_record_book = new JTextField(8);
    private JLabel l_record_date = new JLabel("date",JLabel.CENTER);
    private JTextField t_record_date = new JTextField(8);
    private JLabel l_r_type = new JLabel("user_type",JLabel.CENTER);
    String r[] = {"borrow", "return"};
    private JList<String> r_list = new JList<>(r);
    private JButton b_reg_record = new JButton("记录注册");


    Book_management()
    {
        data_init();
        GUI_init_login();
        login_listen();
    }
    private void data_init()
    {
        /** 数据初始化 */
        // 初始化图书信息
        Book_info b1 = new Book_info("1","2","3","4","5","6");
        V_BookInfo.add(b1);
        Book_info b2 = new Book_info("01","02","03","04","05","06");
        V_BookInfo.add(b2);
        Book_info b3 = new Book_info("-1","-2","-3","-4","-5","-6");
        V_BookInfo.add(b3);
        Book_info b4 = new Book_info("/1","/2","/3","/4","/5","/6");
        V_BookInfo.add(b4);
        // 初始化用户信息
        User_info u1 = new User_info("13","13","admin");
        V_UserInfo.add(u1);
        User_info u2 = new User_info("hj","hj","user");
        V_UserInfo.add(u2);
    }

    private void GUI_init_login()
    {
        /**
         *   GUI登录界面初始化
         */
        setTitle("Login");    //  标题
        setLayout(new FlowLayout(FlowLayout.LEADING));    //  设置为流窗格-竖排
        setSize(270, 150);    //  大小
        setResizable(false);    //  不能缩放
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    //  关闭操作
        setLocationRelativeTo(null);    //  设置显示在屏幕中央

        t_passwd.setEditable(true);    //  修改文本条
        t_user.setEditable(true);    //  修改文本条
        // 设计GUI界面
        panel_login_2.add(l_passwd);
        panel_login_2.add(t_passwd);
        panel_login_1.add(l_userid);
        panel_login_1.add(t_user);
        add(panel_login_1);
        add(panel_login_2);
        add(b_login);

        setVisible(true);    // 设为可见
    }

    private void login_listen()
    {
        /** 登录按钮监听器 */
        b_login.addActionListener(e ->
                {

                    int V_UserInfo_length = V_UserInfo.size();
                    int i;
                    for (i = 0; i < V_UserInfo_length; i++)
                    {
                        User_info tmp = V_UserInfo.elementAt(i);
                        if (tmp.user_check(t_user.getText(), t_passwd.getText())) {
                            String dialog_str = "登陆成功-用户类型：" + tmp.getType();
                            JOptionPane.showMessageDialog(null, dialog_str);
                            change_gui();
                            return;
                        }
                    }
                    String dialog_str = "登陆失败-请重试";
                    JOptionPane.showMessageDialog(null, dialog_str);
                }
        );
    }

    private void change_gui()
    {
        /**
         *   GUI管理界面初始化
         */
        setTitle("Book Management - `13");    //  标题
        setLayout(new FlowLayout(FlowLayout.LEADING));    //  设置为流窗格-竖排
        setSize(800, 600);    //  大小
        setResizable(true);    //  可以缩放
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    //  关闭操作
        setLocationRelativeTo(null);    //  设置显示在屏幕中央
        //  去除登录界面GUI的元素
        remove(panel_login_1);
        remove(panel_login_2);
        remove(b_login);

        // 重写生成GUI界面
        // 图书信息录入界面
        add(title);
        add(book_title1);
        add(book_title2);
        panel_1.add(l_name);
        panel_1.add(t_name);
        panel_1.add(l_author);
        panel_1.add(t_author);
        panel_1.add(l_press);
        panel_1.add(t_press);
        panel_1.add(l_ISBN);
        panel_1.add(t_ISBN);
        panel_1.add(l_pubDate);
        panel_1.add(t_pubDate);
        panel_1.add(l_pages);
        panel_1.add(t_pages);
        add(panel_1);
        add(b_reg_book);

        // 用户录入界面
        list.setVisibleRowCount(2);
        list.setBorder(BorderFactory.createTitledBorder("用户类型"));
        add(user_title1);
        add(record_title2);
        panel_2.add(l_new_userid);
        panel_2.add(t_new_userid);
        panel_2.add(l_new_passwd);
        panel_2.add(t_new_passwd);
        panel_2.add(l_type);
        panel_2.add(list);
        add(panel_2);
        add(b_reg_user);

        // 记录登入界面
        r_list.setVisibleRowCount(2);
        r_list.setBorder(BorderFactory.createTitledBorder("记录类型"));
        add(record_title1);
        add(user_title2);
        panel_3.add(l_record_user);
        panel_3.add(t_record_user);
        panel_3.add(l_record_book);
        panel_3.add(t_record_book);
        panel_3.add(l_record_date);
        panel_3.add(t_record_date);
        panel_3.add(l_r_type);
        panel_3.add(r_list);
        add(panel_3);
        add(b_reg_record);
        setVisible(true);    // 设为可见
        listener();
    }

    private void listener()
    {
        /** 按钮的监听类 */
        b_reg_book.addActionListener(e ->
                {
                    Book_info tmp = new Book_info(t_name.getText(),t_author.getText(),t_press.getText(),t_ISBN.getText(),t_pubDate.getText(),t_pages.getText());
                    V_BookInfo.add(tmp);
                    t_name.setText("");
                    t_author.setText("");
                    t_press.setText("");
                    t_ISBN.setText("");
                    t_pubDate.setText("");
                    t_pages.setText("");
                }
        );

        b_reg_user.addActionListener(e ->
                {
                    User_info tmp = new User_info(t_new_userid.getText(),t_new_passwd.getText(),list.getSelectedValue());
                    V_UserInfo.add(tmp);
                    t_new_userid.setText("");
                    t_new_passwd.setText("");
                }
        );

        b_reg_record.addActionListener(e ->
                {
                    Book_record tmp = new Book_record(t_record_user.getText(),t_record_book.getText(),t_record_date.getText(),r_list.getSelectedValue());
                    V_BookRecord.add(tmp);
                    t_record_user.setText("");
                    t_record_book.setText("");
                    t_record_date.setText("");
                }
        );
    }
}


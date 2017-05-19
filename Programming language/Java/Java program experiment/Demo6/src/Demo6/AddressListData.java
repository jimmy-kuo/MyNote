package Demo6;

/**
 * Created by z.g.13@163.com on 2016/7/26.
 	定义一个通信录类，
    包括  姓名、
         地址、
        邮政编码、
        电话、
        手机、
        Email
        等成员变量；
 */
public class AddressListData {
    protected String name;
    protected String adress;
    protected String post_code;
    protected String phone;
    protected String tel;
    protected String email;

    AddressListData(String N,String AD,String Pc,String p, String t, String e)
    {
        /** 构造函数 */
        name = N;
        adress = AD;
        post_code = Pc;
        phone = p;
        tel = t;
        email = e;
    }

    protected boolean search_by_keyword(String input)
    {
        return (name.equals(input)||adress.equals(input)||post_code.equals(input)||phone.equals(input)||tel.equals(input)||email.equals(input));
    }

}

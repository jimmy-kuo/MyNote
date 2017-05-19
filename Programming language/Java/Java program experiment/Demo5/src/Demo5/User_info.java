package Demo5;

/**
 * Created by z.g.13@163.com on 2016/7/25.
 用户信息(User)，用户属性包括
    用户名(account)，
    密码(password)，
    用户类型(type)，

    用户分为管理员和普通用户。
 */
public class User_info
{
    private String account;
    private String password;
    private String type;

    User_info(String str1, String str2, String str3)
    {
        /** 构造函数 */
        account = str1;
        password = str2;
        type = str3;
    }

    protected boolean user_check(String user,String pswd)
    {
        /** 检查输入的用户名和密码 */
        return(account.equals(user)&& password.equals(pswd));
    }

    protected String getType()
    {
        /** 获取账户属性 */
        return type;
    }
}

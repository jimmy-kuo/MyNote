package Demo6;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.Vector;

/**
 * Created by z.g.13@163.com on 2016/7/26.
 编写一个个人通信录程序，具有如下功能：
 	定义一个通信录类，包括姓名、地址、邮政编码、电话、手机、Email等成员变量；

 	将通信录类的对象存储在文件中。

 	设计一个用户界面，在该界面中可以实现
        通信录增加、
        修改、
        删除和
        查询的功能。

 */
public class AddressListGUI extends Frame
{
    // 数据容器
    private Vector<AddressListData> V_ALD = new Vector<>(10,5);

    // GUI元素
    private JLabel title_1 = new JLabel("-------------------------信息界面---------------------------------------------------------------------------------------------------------------",JLabel.CENTER);
    private JLabel l_name = new JLabel("name",JLabel.CENTER);
    private JTextField t_name = new JTextField(8);
    private JLabel l_address = new JLabel("address",JLabel.CENTER);
    private JTextField t_address = new JTextField(8);
    private JLabel l_postcode = new JLabel("postcode",JLabel.CENTER);
    private JTextField t_postcode = new JTextField(8);
    private JLabel l_phone = new JLabel("phone",JLabel.CENTER);
    private JTextField t_phone = new JTextField(8);
    private JLabel l_tel = new JLabel("tel",JLabel.CENTER);
    private JTextField t_tel = new JTextField(8);
    private JLabel l_email = new JLabel("email",JLabel.CENTER);
    private JTextField t_email = new JTextField(8);
    private JPanel panel_1 = new JPanel(new GridLayout(2,6,10,15));

    private JLabel title_2 = new JLabel("--------------------------按序号查询-----------------------------------------------------------按关键词查询-----------------------------------",JLabel.CENTER);
    private JLabel l_index = new JLabel("search_index",JLabel.CENTER);
    private JTextField t_index = new JTextField(8);
    private JButton b_index = new JButton("search");
    private JPanel panel_2 = new JPanel(new GridLayout(1,3,10,15));

    private JLabel l_keyword = new JLabel("search_keyword",JLabel.CENTER);
    private JTextField t_keyword = new JTextField(8);
    private JButton b_keyword = new JButton("search");
    private JPanel panel_3 = new JPanel(new GridLayout(1,3,10,15));

    private JLabel title_3 = new JLabel("--------------------------功能按钮---------------------------------------------------------------------------------------------------------",JLabel.CENTER);
    private JButton b_change = new JButton("change");
    private JButton b_delete = new JButton("delete");
    private JButton b_add = new JButton("add");
    private JButton b_save = new JButton("save_to_file");
    private JPanel panel_4 = new JPanel(new GridLayout(1,4,10,15));

    AddressListGUI()
    {
        /** 构造函数 */
        DATA_init();
        GUI_init();
        Listen();
    }

    private void DATA_init()
    {
        /** 数据初始化 */
        readTxtFile("DATA.txt");
        //writeTxtFile("DATA.txt");

    }

    private void readTxtFile(String filePath)
    {
        /** 读取文件的数据到数组中 */
        try {
            String encoding="GBK";
            File file=new File(filePath);
            if(file.isFile() && file.exists())
            { //判断文件是否存在
                InputStreamReader read = new InputStreamReader(
                        new FileInputStream(file),encoding);//考虑到编码格式
                BufferedReader bufferedReader = new BufferedReader(read);
                String lineTxt = null;
                while((lineTxt = bufferedReader.readLine()) != null)
                {

                    AddressListData tmp = new AddressListData(lineTxt.split("-")[0], lineTxt.split("-")[1], lineTxt.split("-")[2],
                            lineTxt.split("-")[3], lineTxt.split("-")[4], lineTxt.split("-")[5]);
                    V_ALD.add(tmp);
                }
                read.close();
            }
            else
            {
                System.out.println("找不到指定的文件");
            }
        }
        catch (Exception e)
        {
            System.out.println("读取文件内容出错");
            e.printStackTrace();
        }
    }

    private void writeTxtFile(String filePath)
    {
        /** 把当前的数据写入到文件中 */
        try
        {
            // 缓存写入文件
            File file = new File(filePath);
            if (!file.exists())
                file.createNewFile();
            FileWriter fw = new FileWriter(file.getAbsoluteFile());
            BufferedWriter bw = new BufferedWriter(fw);

            //把当前数据数组写入文件
            int Vl = V_ALD.size();
            int i;
            for(i=0;i<Vl;i++)
            {
                AddressListData tmp;
                tmp = V_ALD.elementAt(i);
                String str = "";
                str = tmp.name + "-" + tmp.adress + "-" + tmp.post_code + "-" + tmp.phone + "-" + tmp.tel + "-" + tmp.email;
                //System.out.println(str);
                bw.write(str);
                bw.newLine();
            }
            bw.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    private void GUI_init()
    {
        /**
         *   GUI登录界面初始化
         */
        setTitle("Login");    //  标题
        setLayout(new FlowLayout(FlowLayout.LEADING));    //  设置为流窗格-竖排
        setSize(630, 275);    //  大小
        setResizable(false);    //  不能缩放
        setLocationRelativeTo(null);    //  设置显示在屏幕中央
        setVisible(true);    // 设为可见
        // GUI设计-1
        add(title_1);
        panel_1.add(l_name);
        panel_1.add(t_name);
        panel_1.add(l_address);
        panel_1.add(t_address);
        panel_1.add(l_postcode);
        panel_1.add(t_postcode);
        panel_1.add(l_phone);
        panel_1.add(t_phone);
        panel_1.add(l_tel);
        panel_1.add(t_tel);
        panel_1.add(l_email);
        panel_1.add(t_email);
        add(panel_1);
        // GUI设计-2
        add(title_2);
        panel_2.add(l_index);
        t_index.setText("0");
        panel_2.add(t_index);
        panel_2.add(b_index);
        add(panel_2);
        panel_3.add(l_keyword);
        panel_3.add(t_keyword);
        panel_3.add(b_keyword);
        add(panel_3);
        // GUI设计-3
        add(title_3);
        panel_4.add(b_change);
        panel_4.add(b_delete);
        panel_4.add(b_add);
        panel_4.add(b_save);
        add(panel_4);
    }

    private void Listen()
    {
        /** 按钮的事件监听类 */
        b_index.addActionListener(e ->
                {
                    // 按照索引查找
                    int Vsize = V_ALD.size();
                    int index = Integer.valueOf(t_index.getText()).intValue();
                    AddressListData tmp;
                    if (index<Vsize&&index>0)
                    {
                        tmp = V_ALD.elementAt(index - 1);
                        t_name.setText(tmp.name);
                        t_address.setText(tmp.adress);
                        t_postcode.setText(tmp.post_code);
                        t_phone.setText(tmp.phone);
                        t_tel.setText(tmp.tel);
                        t_email.setText(tmp.email);
                    }
                }
        );

        b_keyword.addActionListener(e ->
                 {
                     // 按照关键词查找
                     int Vsize = V_ALD.size();
                     int i;
                     AddressListData tmp;
                     for(i=0;i<Vsize;i++)
                     {
                         tmp = V_ALD.elementAt(i);
                         if(tmp.search_by_keyword(t_keyword.getText()))
                         {
                             t_name.setText(tmp.name);
                             t_address.setText(tmp.adress);
                             t_postcode.setText(tmp.post_code);
                             t_phone.setText(tmp.phone);
                             t_tel.setText(tmp.tel);
                             t_email.setText(tmp.email);
                             t_index.setText(String.valueOf(i+1));
                         }
                     }
                 }
        );

        b_change.addActionListener(e ->
        {
            // 修改
            AddressListData tmp;
            int index = Integer.valueOf(t_index.getText()).intValue();
            int Vsize = V_ALD.size();
            if (index<Vsize&&index>0)
            {
                V_ALD.remove(index-1);
                tmp= new AddressListData(t_name.getText(),t_address.getText(),t_postcode.getText(),t_phone.getText(),t_tel.getText(),t_email.getText());
                V_ALD.add(index - 1, tmp);
            }
        }
        );

        b_add.addActionListener(e ->
        {
            // 增加
            AddressListData tmp;
            tmp = new AddressListData(t_name.getText(),t_address.getText(),t_postcode.getText(),t_phone.getText(),t_tel.getText(),t_email.getText());
            V_ALD.add(tmp);
        });

        b_delete.addActionListener(e ->
        {
            // 删除
            int index = Integer.valueOf(t_index.getText()).intValue();
            int Vsize = V_ALD.size();
            if (index<Vsize&&index>0)
                V_ALD.remove(index-1);
        });

        b_save.addActionListener(e ->
        {
            // 储存到文件
            writeTxtFile("DATA2.txt");
        }
        );
    }

}

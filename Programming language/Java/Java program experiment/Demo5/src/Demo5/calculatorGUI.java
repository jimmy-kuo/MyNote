package Demo5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JPanel;

/**
 * Created by z.g.13@163.com on 2016/7/25.
    利用Frame设计一个简单计算器，

        该计算器可以实现三种常用的三角函数(sin、cos、tan) 和
                         5种常用运算(+,-,*,/,sqr)的功能。

        计算器窗口内的内容大多是按键，将这些按键全部定义为按钮，
        另外，还需要一个显示区，用来表示输入的值及最后结果。
 */
public class calculatorGUI extends JFrame
{
    // 数字按钮
    private JButton button_num_1 = new JButton("1");
    private JButton button_num_2 = new JButton("2");
    private JButton button_num_3 = new JButton("3");
    private JButton button_num_4 = new JButton("4");
    private JButton button_num_5 = new JButton("5");
    private JButton button_num_6 = new JButton("6");
    private JButton button_num_7 = new JButton("7");
    private JButton button_num_8 = new JButton("8");
    private JButton button_num_9 = new JButton("9");
    private JButton button_num_0 = new JButton("0");

    //功能按钮
    private JButton button_func_point  = new JButton(".");
    private JButton button_func_add  = new JButton("+");
    private JButton button_func_subtract  = new JButton("-");
    private JButton button_func_multiply  = new JButton("x");
    private JButton button_func_divide  = new JButton("÷");
    private JButton button_func_root  = new JButton("√");
    private JButton button_func_equal  = new JButton("=");
    private JButton button_func_tan  = new JButton("tan");
    private JButton button_func_sin  = new JButton("sin");
    private JButton button_func_cos  = new JButton("cos");
    private JButton button_func_clear  = new JButton("C");
    private JButton button_func_back = new JButton("←");

    private JPanel panel2 = new JPanel(new GridLayout(1,2,10,15));    // 功能按钮面板容器
    private JPanel panel = new JPanel(new GridLayout(5,4,10,15));    // 按钮面板容器
    private JTextArea input = new JTextArea(2,23);    // 输入文本条
    private JTextArea result = new JTextArea(2,13);    // 输出文本条
    private double input_num = 0;
    private double result_num = 0;
    private int opreation_falg = -1;
    // 操作表示 -1 = 默认无操作。0-等 1-加,2-减,3-乘,4-除。

    calculatorGUI()
    {
        GUI_init();
        Listener();
    }

    private void GUI_init()
    {
        /**
        *   GUI界面初始化
        */
        setTitle("Calculator - `13");    //标题
        setLayout(new FlowLayout(FlowLayout.LEADING));    //设置为流窗格
        setSize(270, 310);    //大小
        setResizable(false);    //不能缩放
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    //关闭操作
        setLocationRelativeTo(null);    //设置显示在屏幕中央

        input.setEditable(false);    //无法修改文本条
        result.setEditable(false);    //无法修改文本条

        add(input);    //增加输入文本条
        add(result);    //增加输入文本条
        //第一行
        //panel2.add(result);  //增加结果文本条
        panel2.add(button_func_clear);
        panel2.add(button_func_back);
        add(panel2);    //功能及结果面板

        // 第一行
        panel.add(button_func_sin);
        panel.add(button_func_cos);
        panel.add(button_func_tan);
        panel.add(button_func_root);
        // 第二行
        panel.add(button_num_7);
        panel.add(button_num_8);
        panel.add(button_num_9);
        panel.add(button_func_divide);
        // 第三行
        panel.add(button_num_4);
        panel.add(button_num_5);
        panel.add(button_num_6);
        panel.add(button_func_multiply);
        // 第四行
        panel.add(button_num_1);
        panel.add(button_num_2);
        panel.add(button_num_3);
        panel.add(button_func_subtract);
        // 第五行
        panel.add(button_num_0);
        panel.add(button_func_point);
        panel.add(button_func_equal);
        panel.add(button_func_add);
        add(panel);// 增加面板


        setVisible(true);    // 设为可见
        input.setText("0");    // 输入框设为 0
        result.setText("0");    // 输出框设为 0
    }

    private void Listener()
    {
        /**
         * 注册按钮的事件监听器
         */

        //给数字按钮添加事件监听器
        button_num_0.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                if (input_num == 0 && input.getText().length() == 1)
                    input.setText("0");
                else
                    input.setText(input.getText()+"0");
            }
        }
        );
        button_num_1.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("1");
                        else
                            input.setText(input.getText()+"1");
                    }
                }
        );
        button_num_2.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("2");
                        else
                            input.setText(input.getText()+"2");
                    }
                }
        );
        button_num_3.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("3");
                        else
                            input.setText(input.getText()+"3");
                    }
                }
        );
        button_num_4.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("4");
                        else
                            input.setText(input.getText()+"4");
                    }
                }
        );
        button_num_5.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("5");
                        else
                            input.setText(input.getText()+"5");
                    }
                }
        );
        button_num_6.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("6");
                        else
                            input.setText(input.getText()+"6");
                    }
                }
        );
        button_num_7.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("7");
                        else
                            input.setText(input.getText()+"7");
                    }
                }
        );
        button_num_8.addActionListener(new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("8");
                        else
                            input.setText(input.getText()+"8");
                    }
                }
        );
        button_num_9.addActionListener(
                new ActionListener()
                {
                    @Override
                    public void actionPerformed(ActionEvent e)
                    {
                        input_num = Double.parseDouble(input.getText());
                        if (input_num == 0 && input.getText().length() == 1)
                            input.setText("9");
                        else
                            input.setText(input.getText()+"9");
                    }
                }
        );

        // 给小数点添加事件监听器
        button_func_point.addActionListener(new ActionListener()
        {@Override public void actionPerformed(ActionEvent e) {input.setText(input.getText()+".");}});

        // 给Clear添加事件监听器
        button_func_clear.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                opreation_falg = -1;
                input.setText("0");
                result.setText("0");
            }
        });

        // 给Back添加事件监听器
        button_func_back.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if (input.getText().length() != 1)
                    input.setText(input.getText().substring(0,input.getText().length()-1));
                else
                    input.setText("0");
            }
        });

        // 给三角函数添加事件监听器
        button_func_sin.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Math.sin(input_num);
                result.setText(Double.toString(result_num));
            }
        });
        button_func_cos.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Math.cos(input_num);
                result.setText(Double.toString(result_num));
            }
        });
        button_func_tan.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Math.tan(input_num);
                result.setText(Double.toString(result_num));
            }
        });

        // 给开方添加事件监听器
        button_func_root.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Math.sqrt(input_num);
                result.setText(Double.toString(result_num));
            }
        });


        // 给基本操作添加事件监听器
        button_func_add.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Double.parseDouble(result.getText());

                if (opreation_falg == -1)
                {
                    input.setText("0");
                    result.setText(Double.toString(input_num));
                }
                else
                {
                    equal();

                }
                opreation_falg = 1;
            }
        });
        button_func_divide.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Double.parseDouble(result.getText());

                if (opreation_falg == -1)
                {
                    input.setText("0");
                    result.setText(Double.toString(input_num));
                }
                else
                {
                    equal();

                }
                opreation_falg = 4;
            }
        });
        button_func_subtract.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Double.parseDouble(result.getText());

                if (opreation_falg == -1)
                {
                    input.setText("0");
                    result.setText(Double.toString(input_num));
                }
                else
                {
                    equal();

                }
                opreation_falg = 2;
            }
        });
        button_func_multiply.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                input_num = Double.parseDouble(input.getText());
                result_num = Double.parseDouble(result.getText());

                if (opreation_falg == -1)
                {
                    input.setText("0");
                    result.setText(Double.toString(input_num));
                }
                else
                {
                    equal();

                }
                opreation_falg = 3;
            }
        });

        //添加等号监听器
        button_func_equal.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                equal();
                opreation_falg = 0;
            }
        });


    }

    // 等号的监听器单独写成方法,供其它监听器调用
    private void equal()
    {
        input_num = Double.parseDouble(input.getText());
        result_num = Double.parseDouble(result.getText());

        switch (opreation_falg)
        {
            case -1:
                result_num = input_num;
                break;
            case 0:
                break;
            case 1:
                result_num = result_num + input_num;
                break;
            case 2:
                result_num = result_num - input_num;
                break;
            case 3:
                result_num = result_num * input_num;
                break;
            case 4:
                if (input_num != 0)
                    result_num = result_num / input_num;
                else
                    result_num = 88888888;
                break;
        }
        input.setText("0");
        result.setText(Double.toString(result_num));

    }
}


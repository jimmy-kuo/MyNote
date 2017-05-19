package com.company;

/**
 * Created by ·13 on 7/9/2016.
 */

// 主程序调用这个类 实现输出
public class Demo_1_1 {
    protected  String name = "侯捷";

    //返回规定格式的字符串
    protected  String Print (){
                        //调用自身类的属性，名称
        return "Hello," + this.name;
    }
}

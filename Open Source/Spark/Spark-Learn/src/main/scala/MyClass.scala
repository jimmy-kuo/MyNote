package Spark_learn

import org.apache.spark.rdd.RDD

/**
  * RDD 调用函数方法测试
  * */


// ref - https://blog.csdn.net/zixiao217/article/details/77203704
// ref - https://blog.csdn.net/qq_36330643/article/details/73849000

// scala 包导入方法

// Scala 中导入包有以下几种方式:
//  import 导入一个类
//  一个 import 导入多个类
//  使用下划线 _ 导入指定包下所有事物
//  导入包时 => 指定别名

class MyClass {
  // 这里，如果我们创建一个 MyClass 的实例，并调用 doStuff，
  // 在 map 内有 MyClass 实例的 func1 方法的引用，所以整个对象需要被发送到集群的。它类似于 rdd.map(x => this.func1(x))
  // 类似的方式，访问外部对象的字段将引用整个对象:
  val feild = "hello "

  def func1(s: String): Boolean = {
    s.contains("s")
  }

  def doStuff(rdd: RDD[String]): RDD[String] = {
    rdd.filter(func1)
  }

  // 相当于写 rdd.map(x => this.field + x), 它引用 this 所有的东西.
  // 为了避免这个问题, 最简单的方式是复制 field 到一个本地变量，而不是外部访问它:

  def doStuff1(rdd: RDD[String]): RDD[String] = {
    val _filed = this.feild
    rdd.map(line => _filed + line)
  }


}

package Spark_learn

import org.apache.spark.rdd.RDD

/**
  * RDD 调用函数方法测试
  * */

object MyFunctions {
  def strHasChar(s: String): Boolean = {
    return s.contains("a")
  }
}


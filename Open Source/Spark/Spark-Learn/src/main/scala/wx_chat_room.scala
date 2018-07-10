package Spark_learn

import org.apache.spark._
import org.apache.spark.graphx._
// To make some of the examples work we will also need RDD
import org.apache.spark.rdd.RDD

import org.graphstream.graph.{Graph => GraphStream}
import org.graphstream.graph.implementations._


object wx_chat_room {
  def main(args: Array[String]): Unit = {
    // init
    val conf = new SparkConf().setAppName("MyFirstSparkApp").setMaster("local")
    val sc = new SparkContext(conf)

    // file
    val file = sc.textFile("./DATA/wxg_chatroom_graph.txt")
    val vertexStr: RDD[String] = file.flatMap(line => line.split("\t").filter(_.contains(":")))
    val vertexHexSize: RDD[(String, String)] = vertexStr.map(s => (s.substring(0, s.indexOf(":")),
      s.substring(s.indexOf(":") + 1, s.length()))) // 32bit id
    //val vertexIdMap : RDD[(String,Long)] = vertexHexSize.map()

//    // todo 先不考虑直接在RDD里操作 拉下来再parallelize
//    for ((i, j) <- vertexHex) {
//      println(i + "|  -  |" + j)
//    }


    sc.stop()
  }
}

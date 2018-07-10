package Spark_learn

/**
  * GraphX 学习
  *
  * jerryhou(侯捷)
  * 2018-07-03
  **/

import org.apache.spark._
import org.apache.spark.graphx._
// To make some of the examples work we will also need RDD
import org.apache.spark.rdd.RDD

import org.graphstream.graph.{Graph => GraphStream}
import org.graphstream.graph.implementations._

// GraphX 是 Spark 中用于图形和图形并行计算的新组件。
// 在高层次上， GraphX 通过引入一个新的图形抽象来扩展 Spark RDD ：一种具有附加到每个顶点和边缘的属性的定向多重图形。


// todo
// 1. graphX基本知识
// 2. graph 如何自定义构建图
// 3. graphx 基本函数
// 4. 完成一个简单的demo
// 5. 从文件中构建一个graph rdd
object MyGraphX {
  def main(args: Array[String]): Unit = {
    // init
    val conf = new SparkConf().setAppName("MyFirstSparkApp").setMaster("local")
    val sc = new SparkContext(conf)

    // file
    val file = sc.textFile("E:\\DATA\\wxg_chatroom_graph.txt")

    // doc
    // Create an RDD for the vertices
    val users: RDD[(VertexId, (String, String))] =
    sc.parallelize(Array((3L, ("rxin", "student")),
      (7L, ("jgonzal", "postdoc")),
      (5L, ("franklin", "prof")),
      (2L, ("istoica", "prof"))))
    // Create an RDD for edges
    val relationships: RDD[Edge[String]] =
      sc.parallelize(Array(Edge(3L, 7L, "collab"),
        Edge(5L, 3L, "advisor"),
        Edge(2L, 5L, "colleague"),
        Edge(5L, 7L, "pi")))
    // Define a default user in case there are relationship with missing user
    val defaultUser = ("John Doe", "Missing")
    // Build the initial Graph
    val graph = Graph(users, relationships, defaultUser)

    // 找出所有pos是postdoc的定点
    graph.vertices.filter { case (_, (_, pos)) => pos == "postdoc" }.foreach(println)
    // 找出所有起点id大于终点id边的个数
    println(graph.edges.filter(e => e.srcId > e.dstId).count())
    graph.triplets.foreach(println)


    //创建原始可视化对象
    val graphStream: SingleGraph = new SingleGraph("GraphStream")

    // 设置graphStream全局属性. Set up the visual attributes for graph visualization
    graphStream.addAttribute("ui.stylesheet.css", "url(./DATA/style/stylesheet.css)")
    graphStream.addAttribute("ui.quality")
    graphStream.addAttribute("ui.antialias")

//    edge.tollway { size: 2px; stroke-color: red; stroke-width: 1px; stroke-mode: plain; }
//    edge.tunnel { stroke-color: blue; stroke-width: 1px; stroke-mode: plain; }
//    edge.bridge { stroke-color: yellow; stroke-width: 1px; stroke-mode: plain; }
    // 加载顶点到可视化图对象中
    for ((id, attr) <- graph.vertices.collect()) {
      val node = graphStream.addNode(id.toString).asInstanceOf[SingleNode]
      node.addAttribute("ui.label", id + attr._1 + ":" + attr._2 + "\n")
      val speedMax = 97.6 / 130.0
      node.setAttribute("ui.size", "0.7")
    }
    //加载边到可视化图对象中
    for (Edge(s, d, arrt) <- graph.edges.collect()) {
      val edge = graphStream.addEdge(s.toString ++ d.toString,
        s.toString, d.toString,
        true).
        asInstanceOf[AbstractEdge]
      //edge.addAttribute("ui.color", 0.750)

    }
    //显示
    graphStream.display()
    sc.stop()
  }
}

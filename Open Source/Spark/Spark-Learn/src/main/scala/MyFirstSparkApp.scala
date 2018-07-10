package Spark_learn

/**
  * 我的第一个Spark程序
  *
  * jerryhou(侯捷)
  * 2018-07-03
  **/

import org.apache.spark.SparkContext
import org.apache.spark.SparkConf
import org.apache.spark.rdd.RDD

import Spark_learn.MyFunctions.strHasChar

//import MyClass

object MyFirstSparkApp {
  def main(args: Array[String]): Unit = {

    // Spark 程序必须做的第一件事情是创建一个 SparkContext 对象，
    // 它会告诉 Spark 如何访问集群。要创建一个 SparkContext，首先需要构建一个包含应用程序的信息的 SparkConf 对象。
    // 每一个 JVM 可能只能激活一个 SparkContext 对象。在创新一个新的对象之前，必须调用 stop() 该方法停止活跃的 SparkContext。

    val conf = new SparkConf().setAppName("MyFirstSparkApp").setMaster("local")
    val sc = new SparkContext(conf)

    // 并行集合中一个很重要参数是 partitions（分区）的数量，它可用来切割 dataset（数据集）。
    // Spark 将在集群中的每一个分区上运行一个任务。通常您希望群集中的每一个 CPU 计算 2-4 个分区。
    // 一般情况下，Spark 会尝试根据您的群集情况来自动的设置的分区的数量。当然，您也可以将分区数作为第二个参数传递到
    val data = Array(1, 2, 3, 4, 5)
    val distData = sc.parallelize(data)
    val distData1 = sc.parallelize(data, 4)
    // 求和
    println("data sum : " + distData.reduce((x, y) => x + y))

    // 使用 Spark 读取文件时需要注意:
    //如果使用本地文件系统的路径，所工作节点的相同访问路径下该文件必须可以访问。
    // 复制文件到所有工作节点上，或着使用共享的网络挂载文件系统。
    //
    //所有 Spark 基于文件的 input 方法, 包括 textFile, 支持在目录上运行, 压缩文件, 和通配符. 例如,
    // 您可以使用 textFile("/my/directory"), textFile("/my/directory/*.txt"), and textFile("/my/directory/*.gz").
    //
    //textFile 方法也可以通过第二个可选的参数来控制该文件的分区数量.
    // 默认情况下, Spark 为文件的每一个 block（块）创建的一 个 partition 分区（HDFS 中块大小默认是 128MB），
    // 当然你也可以通过传递一个较大的值来要求一个较高的分区数量。请注意，分区的数量不能够小于块的数量。
    //
    //除了文本文件之外，Spark 的 Scala API 也支持一些其它的数据格式:
    //SparkContext.wholeTextFiles 可以读取包含多个小文本文件的目录,
    // 并且将它们作为一个 (filename, content) pairs 来返回. 这与 textFile 相比,
    // 它的每一个文件中的每一行将返回一个记录. 分区由数据量来确定, 某些情况下, 可能导致分区太少.
    // 针对这些情况, wholeTextFiles 在第二个位置提供了一个可选的参数用户控制分区的最小数量.
    //
    //针对 SequenceFiles, 使用 SparkContext 的 sequenceFile[K, V] 方法
    // ，其中 K 和 V 指的是文件中 key 和 values 的类型. 这些应该是 Hadoop 的 Writable 接口的子类,
    // 像 IntWritable and Text. 此外, Spark 可以让您为一些常见的 Writables 指定原生类型; 例如, sequenceFile[Int, String]
    // 会自动读取 IntWritables 和 Texts.
    //
    //针对其它的 Hadoop InputFormats, 您可以使用 SparkContext.hadoopRDD 方法,
    // 它接受一个任意的 JobConf 和 input format class, key class 和 value class.
    // 通过相同的方法你可以设置你的 input source（输入源）.
    // 你还可以针对 InputFormats 使用基于 “new” MapReduce API (org.apache.hadoop.mapreduce) 的 SparkContext.newAPIHadoopRDD.
    //
    //RDD.saveAsObjectFile 和 SparkContext.objectFile 支持使用简单的序列化的 Java objects 来保存 RDD.
    // 虽然这不像 Avro 这种专用的格式一样高效，但其提供了一种更简单的方式来保存任何的 RDD。.

    val lines = sc.textFile("E:\\README.md")
    val lineLengths = lines.map(s => s.length)
    val totalLine = lineLengths.count()
    val totalLength = lineLengths.reduce((a, b) => a + b)
    val longestLength = lineLengths.reduce((a, b) => if (a > b) a else b)
    println("文件总长度 : " + totalLength + " 行数 : " + totalLine + " 最大行长度 : " + longestLength)

    // 第一行从外部文件中定义了一个基本的 RDD，但这个数据集并未加载到内存中或即将被行动:
    // line 仅仅是一个类似指针的东西，指向该文件. 第二行定义了 lineLengths 作为 map transformation 的结果。
    // 请注意，由于 laziness（延迟加载）lineLengths 不会被立即计算. 最后，我们运行 reduce，这是一个 action。
    // 此时，Spark 分发计算任务到不同的机器上运行，每台机器都运行在 map 的一部分并本地运行 reduce，仅仅返回它聚合后的结果给驱动程序.
    //
    // 如果我们也希望以后再次使用 lineLengths，我们还可以添加:
    lineLengths.persist()
    // 在 reduce 之前，这将导致 lineLengths 在第一次计算之后就被保存在 memory 中。

    // ref - https://blog.csdn.net/houmou/article/details/52491419
    // spark中cache()和persist()的区别

    // 1. cache() 内部调用了persist()
    // 2. cache()只有一个默认的存储级别 persist()有多种持久化方式 内存/硬盘/堆外存/反序列化/备份数

    // 传递 Functions（函数）给 Spark
    // 两种方式
    // 1.object 函数
    // 2.class 函数 注意
    val linesContainsS = lines.filter(Spark_learn.MyFunctions.strHasChar)
    println(linesContainsS.count())

    var cc = new MyClass()
    val lineStartWithHello = cc.doStuff1(lines)
    for (l <- lineStartWithHello) {
      // println(l.substring(0,5))
    }
    println(lineStartWithHello.map(str => str.contains("hel")).count())

    // 理解闭包
    // 在集群中执行代码时，一个关于 Spark 更难的事情是理解变量和方法的范围和生命周期.
    // 修改其范围之外的变量 RDD 操作可以混淆的常见原因。在下面的例子中，我们将看一下使用的 foreach() 代码递增累加计数器，
    // 但类似的问题，也可能会出现其他操作上.


    //  Accumulator 累加器。当一个执行的任务分配到集群中的各个 worker 结点时，Spark 的累加器是专门提供安全更新变量的机制


    // ref - https://blog.csdn.net/u013063153/article/details/53304087
    // Spark之中map与flatMap的区别
    // 1. map()是将函数用于RDD中的每个元素，将返回值构成新的RDD。
    // 2. flatmap()是将函数应用于RDD中的每个元素，将返回的迭代器的所有内容构成新的RDD,
    // 这样就得到了一个由各列表中的元素组成的RDD,而不是一个列表组成的RDD。


    // RDD - kv
    var words = lines.flatMap(line => line.split(" "))
    var wordsCount = words.map(word => (word, 1)).reduceByKey((a, b) => a + b)
    var localv = wordsCount.collect() // 将RDD加载到本地
//    for ((w, c) <- wordsCount)
//      println(w + " has came " + c + " times ")

    // 另一种常见的语法用于打印 RDD 的所有元素使用 rdd.foreach(println) 或 rdd.map(println)。
    // 在一台机器上，这将产生预期的输出和打印 RDD 的所有元素。然而，在集群 cluster 模式下，
    // stdout 输出正在被执行写操作 executors 的 stdout 代替，而不是在一个驱动程序上，
    // 因此 stdout 的 driver 程序不会显示这些！要打印 driver 程序的所有元素，
    // 可以使用的 collect() 方法首先把 RDD 放到 driver 程序节点上: rdd.collect().foreach(println)。
    // 这可能会导致 driver 程序耗尽内存，虽说，因为 collect() 获取整个 RDD 到一台机器;
    // 如果你只需要打印 RDD 的几个元素，一个更安全的方法是使用 take(): rdd.take(100).foreach(println)。


    // 共享变量
    //通常情况下，一个传递给 Spark 操作（例如 map 或 reduce）的函数 func 是在远程的集群节点上执行的。
    // 该函数 func 在多个节点执行过程中使用的变量，是同一个变量的多个副本。这些变量的以副本的方式拷贝到每个机器上，
    // 并且各个远程机器上变量的更新并不会传播回 driver program（驱动程序）。通用且支持 read-write（读-写） 的共享变量在任务间是不能胜任的。
    // 所以，Spark 提供了两种特定类型的共享变量 : broadcast variables（广播变量）和 accumulators（累加器）。

    // 广播变量
    //Broadcast variables（广播变量）允许程序员将一个 read-only（只读的）变量缓存到每台机器上，而不是给任务传递一个副本。
    val broadcastVar = sc.broadcast(Array(1, 2, 3))
    for (i <- broadcastVar.value) // 需要调用value才行(相当是做了一层封装,有点类似与python的进程级变量)
      println(i)
    // 在创建广播变量之后，在集群上执行的所有的函数中，应该使用该广播变量代替原来的 v 值，所以节点上的 v 最多分发一次。
    // 另外，对象 v 在广播后不应该再被修改，以保证分发到所有的节点上的广播变量具有同样的值（例如，如果以后该变量会被运到一个新的节点）。


    // Accumulators（累加器）是一个仅可以执行 “added”（添加）的变量来通过一个关联和交换操作，因此可以高效地执行支持并行。
    // 累加器可以用于实现 counter（ 计数，类似在 MapReduce 中那样）或者 sums（求和）。

    val accum = sc.longAccumulator("My Accumulator")
    sc.parallelize(Array(1, 2, 3, 4)).foreach(x => accum.add(x))
    println(accum.value)


    sc.stop()


  }
}


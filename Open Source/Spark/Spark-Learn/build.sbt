name := "hello,world"

version := "0.1"

scalaVersion := "2.12.6"

// Spark
libraryDependencies += "org.apache.spark" % "spark-sql_2.11" % "2.3.1"
libraryDependencies += "org.apache.spark" % "spark-core_2.11" % "2.3.1"
libraryDependencies += "org.apache.spark" % "spark-graphx_2.11" % "2.3.1"
libraryDependencies += "org.apache.spark" % "spark-mllib_2.11" % "2.3.1"

// Graph Visualization
libraryDependencies += "org.graphstream" % "gs-core" % "1.3"
libraryDependencies += "org.graphstream" % "gs-ui" % "1.3"
libraryDependencies += "org.graphstream" % "gs-algo" % "1.3"

libraryDependencies += "org.scalanlp" % "breeze_2.11" % "0.12"
libraryDependencies += "org.scalanlp" % "breeze-viz_2.11" % "0.12"

libraryDependencies += "org.jfree" % "jcommon" % "1.0.24"
libraryDependencies += "org.jfree" % "jfreechart" % "1.0.19"

// TEST
libraryDependencies += "org.scalatest" %% "scalatest" % "3.0.5" % "test"
package Demo8;

import com.sun.management.OperatingSystemMXBean;
import com.sun.org.apache.xml.internal.serializer.OutputPropertiesFactory;
import java.io.File;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.lang.management.ManagementFactory;
import java.net.Socket;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.lang.management.ManagementFactory;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;
import com.sun.management.OperatingSystemMXBean;

/**
 * Created by z.g.13@163.com on 2016/7/26.
 * 客户端
 */
public class Client
{
    private static int port = 6013;//Port
    private static String host = "127.0.0.1"; //IP

    Client() throws Exception //异常都直接往外抛
    {
        // 建立连接
        Socket client = new Socket(host, port);
        // 发送数据
        Writer writer = new OutputStreamWriter(client.getOutputStream());

        writer.write("Hello Server.");
        writer.flush(); // flush


        int num_D = getDiskInfo().split("<br>").length;
        int i;
        for(i=0;i<num_D;i++)
        {
            writer.write(getDiskInfo().split("<br>")[i]);
            writer.write("\n");
            writer.flush();
            //System.out.println(getDiskInfo().split("<br>")[i]);
        }
        int num_M = getEMS().split("<br>").length;
        int j;
        for(j=0;j<num_M;j++)
        {
            writer.write(getEMS().split("<br>")[j]);
            writer.write("\n");
            writer.flush();
            //System.out.println(getEMS().split("<br>")[j]);
        }
        writer.close();
        client.close();
    }

    public static String getDiskInfo()
    {
        /**
         *  获取本地磁盘信息
         *  @return 返回每隔硬盘的信息的字符串
         */
        StringBuffer sb=new StringBuffer();
        File[] roots = File.listRoots();// 获取磁盘分区列表
        for (File file : roots)
        {
            long totalSpace=file.getTotalSpace();
            long freeSpace=file.getFreeSpace();
            long usableSpace=file.getUsableSpace();
            if(totalSpace>0){
                sb.append(file.getPath() + "(总计：");
                sb.append(Math.round(((double)totalSpace/ (1024*1024*1024))*100/100.0) + "GB  ");
                if(Math.round((((double)usableSpace/ (1024*1024*1024))*100)/100.0)<=1){
                    sb.append("剩余：" + Math.round((((double)usableSpace/ (1024*1024))*100)/100.0) + "MB)<br>");
                }else{
                    sb.append("剩余：" + Math.round((((double)usableSpace/ (1024*1024*1024))*100)/100.0) + "GB)<br>");
                }
                // sb.append("已使用" + Math.round((((double)(totalSpace-usableSpace)/(1024*1024*1024))*100)/100.0) + "G<br>");
            }
        }
        return sb.toString();
    }

    public static String getEMS()
    {
        /**
         * 获取内存情况
         * @return  还有内存目前情况的字符串
         */
        StringBuffer sb=new StringBuffer();
        OperatingSystemMXBean osmb = (OperatingSystemMXBean) ManagementFactory
                .getOperatingSystemMXBean();
        sb.append("系统物理内存总计：" + osmb.getTotalPhysicalMemorySize()
                / 1024 / 1024 + "MB<br>");
        sb.append("系统物理可用内存总计：" + osmb.getFreePhysicalMemorySize()
                / 1024 / 1024 + "MB");
        return sb.toString();
    }
}

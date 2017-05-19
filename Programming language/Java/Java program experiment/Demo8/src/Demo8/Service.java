package Demo8;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by z.g.13@163.com on 2016/7/26.
    //服务器端
 */
public class Service
{
    private static int port = 6013;
    private ServerSocket server ;//服务器socket

    Service() throws IOException //异常信息都往外抛
    {
        server = new ServerSocket(port);
        Socket socket = server.accept(); //阻塞式appect 直到有客户端连接
        Reader reader = new InputStreamReader(socket.getInputStream());
        char chars[] = new char[64];
        int len;
        StringBuilder sb = new StringBuilder();
        while ((len=reader.read(chars)) != -1)
        {
            sb.append(new String(chars, 0, len));
        }
        System.out.println("from client: " + sb);

        // 客户端退出后断开连接
        reader.close();
        socket.close();
        server.close();
    }
}

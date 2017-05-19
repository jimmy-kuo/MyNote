package Demo7;

public class Main {
    /**
     * 编写一个多线程的控制程序，称为赛马程序。
     *          创建分别代表两匹马的两个线程，
     *          并将它们设置为高低不同的优先级，并以进度条的形式显示赛马过程。
     * */
    public static void main(String[] args) {
	// write your code here
        house h = new house("马1,",1);
        house h2 = new house("马2,",1);
        h.start();
        h2.start();
    }
}

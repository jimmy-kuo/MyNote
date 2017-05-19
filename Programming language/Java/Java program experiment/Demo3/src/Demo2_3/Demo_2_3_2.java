package Demo2_3;

import org.jetbrains.annotations.Nullable;

import java.util.Scanner;

/**
 * Created by hj on 16-7-14.
 * 设计一个矩阵乘法程序，输入两个矩阵可以计算出它们的乘积。
 */
public class Demo_2_3_2 {
    private int matrix1[][];
    private int matrix2[][];
    private int result_matrix[][];

    public Demo_2_3_2() {
        /**
         * 构造函数
         */
        int i, j, tmp;
        int ColumnNum, RowNum;
        Scanner in = new Scanner(System.in);

        System.out.println("请输入第一个矩阵的行数:");
        RowNum = in.nextInt();
        System.out.println("请输入第一个矩阵的列数:");
        ColumnNum = in.nextInt();
        matrix1 = new int[RowNum][ColumnNum];
        for (i = 1; i <= RowNum; i++)
            for (j = 1; j <= ColumnNum; j++) {
                System.out.println("请输入矩阵第" + i + "行第" + j + "列的数字");
                tmp = in.nextInt();
                matrix1[i - 1][j - 1] = tmp;
            }

        System.out.println("请输入第二个矩阵的行数:");
        RowNum = in.nextInt();
        System.out.println("请输入第二个矩阵的列数:");
        ColumnNum = in.nextInt();
        matrix2 = new int[RowNum][ColumnNum];
        for (i = 1; i <= RowNum; i++)
            for (j = 1; j <= ColumnNum; j++) {
                System.out.println("请输入矩阵第" + i + "行第" + j + "列的数字");
                tmp = in.nextInt();
                matrix2[i - 1][j - 1] = tmp;
            }
        //this.printTest(matrix1);
        //this.printTest(matrix2);

        result_matrix = this.matrixMultiplication(matrix1, matrix2);
        this.printTest(result_matrix);
    }

    private void printTest(int arry[][]) {
        /**
         * 测试输出一个矩阵
         */
        System.out.println("--------result--------");
        int i, j;
        int row, col;
        row = arry.length;
        col = arry[0].length;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++)
                System.out.print(arry[i][j] + " ");
            System.out.println();
        }
        System.out.println();
    }

    @Nullable
    private int[][] matrixMultiplication(int arry1[][], int arry2[][]) {
        /**
         * 矩阵乘法
         * @parm1：矩阵1
         * @parm2：矩阵2
         * @return：矩阵1和2相乘的结果，若无法相乘返回null
         */
        int row1, col1, row2, col2;
        row1 = arry1.length;
        col1 = arry1[0].length;
        row2 = arry2.length;
        col2 = arry2[0].length;

        if (col1 != row2) {
            System.out.println("Error：输入的两个矩阵无法相乘");
            return null;
        }

        result_matrix = new int[row1][col2];
        int tmp;
        int i, j, l;
        for (i = 0; i < row1; i++)
            for (j = 0; j < col2; j++)
            {
                tmp = 0;
                for (l = 0; l < col1; l++)
                        //System.out.println(matrix1[i][l] + "*" + matrix2[l][j]);
                        tmp += matrix1[i][l] * matrix2[l][j];
                result_matrix[i][j] = tmp;
            }
        return result_matrix;
    }
}



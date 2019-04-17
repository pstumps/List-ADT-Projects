import java.util.Scanner;
import java.io.*;

public class Sparse {
	public static void main(String[] args) throws IOException{

        if(args.length != 2) throw new RuntimeException
            ("Usage: Sparse.java input output");

        Scanner sc = new Scanner(new File(args[0]));
        PrintWriter output = new PrintWriter(new FileWriter(args[1]));

        int n = sc.nextInt();

        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);

        int MatrixA_nnz = sc.nextInt();
        int MatrixB_nnz = sc.nextInt();

        int row;
        int col;
        double val;

        sc.nextLine();

        for(int i=1; i<= MatrixA_nnz; i++) {


            //System.out.println("Collecting row" +x);

            row = sc.nextInt();

            //System.out.println("Collecting column");

            col = sc.nextInt();

            //System.out.println("Collecting value");

            val = sc.nextDouble();

            A.changeEntry(row, col, val);

            if(!sc.hasNext()){
                break;
            }

        }

        sc.nextLine();

        for(int i=1; i<= MatrixB_nnz; i++){

            //System.out.println("Collecting row");
            row = sc.nextInt();
            //System.out.println("Collecting column");
            col = sc.nextInt();
            //System.out.println("Collecting value");
            val = sc.nextDouble();

            B.changeEntry(row, col, val);

            if(!sc.hasNext()){
                break;
            }

        }

        output.println("A has " + MatrixA_nnz + " non-zero entries:");
        output.println(A);

        output.println("B has " + MatrixB_nnz + " non-zero entries:");
        output.println(B);

        output.println("(1.5)*A =");
        output.println(A.scalarMult(1.5));

        output.println("A+B =");
        output.println(A.add(B));

        output.println("A+A =");
        output.println(A.add(A));

        output.println("B-A =");
        output.println(B.sub(A));

        output.println("A-A =");
        output.println(A.sub(A));

        output.println("Transpose(A) =");
        output.println(A.transpose());

        output.println("A*B =");
        output.println(A.mult(B));

        output.println("B*B =");
        output.println(B.mult(B));

        sc.close();
        output.close();
	}
}
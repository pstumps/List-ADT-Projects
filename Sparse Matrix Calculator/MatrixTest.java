//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101
//PA3 - MatrixClient.java
//Test file for Matrix.java

public class MatrixTest{
   public static void main(String[] args){
      int i, j, n=100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);
      
      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,3,9); B.changeEntry(3,3,1);
      
      
      
      System.out.println("Printing A");
      System.out.println(A.getNNZ());
      System.out.println(A);
      
      System.out.println("Printing B");
      System.out.println(B.getNNZ());
      System.out.println(B);
      
      System.out.println("Printing C, A * 1.5 -- Scalar mult");
      Matrix C = A.scalarMult(1.5);
      System.out.println(C.getNNZ());
      System.out.println(C);
      
      System.out.println("Printing D, A + A");
      Matrix D = A.add(A);
      System.out.println(D.getNNZ());
      System.out.println(D);
      
      System.out.println("Printing E, A + B");
      Matrix E = A.add(B);
      System.out.println(E.getNNZ());
      System.out.println(E);
      
      System.out.println("Printing F, B + A");
      Matrix F = B.add(A);
      System.out.println(F.getNNZ());
      System.out.println(F);
      
      System.out.println("Printing G, A - A");
      Matrix G = A.sub(A);
      System.out.println(G.getNNZ());
      System.out.println(G);
      
      System.out.println("Printing G1, A - B");
      Matrix G1 = A.sub(B);
      System.out.println(G1.getNNZ());
      System.out.println(G1);
      
      System.out.println("Printing G2, B - A");
      Matrix G2 = B.sub(A);
      System.out.println(G2.getNNZ());
      System.out.println(G2);
      
      System.out.println("Printing H, transpose of B");
      Matrix H = B.transpose();
      System.out.println(H.getNNZ());
      System.out.println(H);
      
      System.out.println("Printing I, A x A");
      Matrix I = A.mult(A);
      System.out.println(I.getNNZ());
      System.out.println(I);

      System.out.println("Printing K, B x B");
      Matrix K = B.mult(B);
      System.out.println(K.getNNZ());
      System.out.println(K);

      System.out.println("Printing K2, A x B");
      Matrix K2 = A.mult(B);
      System.out.println(K2.getNNZ());
      System.out.println(K2);

      Matrix J = A.copy();
      System.out.println("Printing A after copy");
      System.out.println(A.getNNZ());
      System.out.println(A);
      
      System.out.println("Printing J after copy");
      System.out.println(J.getNNZ());
      System.out.println(J);
      
      System.out.println("Determining if A = J (Should be true)");
      System.out.println(A.equals(J));
      System.out.println("Determining if A = B (Should be false)");
      System.out.println(A.equals(B));
      System.out.println("Determining if A = A (Should be true)");
      System.out.println(A.equals(A));
    
      System.out.println("Using makeZero on A then printing");
      A.makeZero();
      System.out.println(A.getNNZ());
      System.out.println(A);

      System.out.println("Adding entry to matrix after MakeZero");
      A.changeEntry(5, 5, 5.0);
      System.out.println(A.getNNZ());
      System.out.println(A);
   }
}
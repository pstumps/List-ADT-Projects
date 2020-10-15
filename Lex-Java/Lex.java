//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 
//PA 1
//Sorts items from an array in alphabetical order
import java.util.Scanner;
import java.io.*;

public class Lex {
	public static void main(String[] args) throws IOException{
		
		if (args.length > 2 || args.length < 2) {
			System.err.println("Usage: Lex input filename output filename");
			System.exit(0);
        }
        
        int inputLines=0;
        String line = null;
        String input[]= null;
        List sorted = new List();
        sorted.append(0);
		
        Scanner sc = new Scanner(new File(args[0]));
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		
		while (sc.hasNextLine()) {
            inputLines++;
            sc.nextLine();
        }

        input = new String[inputLines];

        for (int i=0; i<inputLines; i++){
            input[i]= in.nextLine();
        }

        //debugging
        //sorted.moveFront();
        //System.out.println(sorted.get());
        for (int i = 0; i < inputLines-1; i++) {
            sorted.moveFront();
            for (int j = -i ; j < 1; j++) {
                if (input[sorted.get()].compareTo(input[i+1])>0) {  
                    sorted.insertBefore(i+1);
                    j = 1;
                    //System.out.println("Comparing " +input[sorted.get()]+ " to " +input[i+1]);
                    //System.out.println(sorted);
                }
                else if (sorted.index() == sorted.length()-1) {
                    //System.out.println("Appending " +input[i+1]);
                    sorted.append(i+1);
                    j = 1;
                }		 
                else {
                    sorted.moveNext(); 		  
                }
            }  
        }
        //System.out.print(sorted);
        sorted.moveFront();
        //System.out.println();
        //System.out.println(sorted.get());
        while(sorted.index() != -1){
            out.println(input[sorted.get()]);
            sorted.moveNext();
        }

        sc.close();
        out.close();
		
    }
}

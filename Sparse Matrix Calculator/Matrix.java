//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101
//PA 3
//Matrix ADT

public class Matrix{

    public class Entry{
        
        int column;
        double value;

        public Entry(int column, double value){
           this.column = column;
           this.value = value;
        }
        

		public boolean equals(Object x){
            Entry e;
            boolean tf = false;
            if(x instanceof Entry){
                e = (Entry)x;
                if(this.value == e.value && this.column == e.column){
                    tf =  true;
                }
            }
            return tf;
        }

        public String toString(){
            return("(" +this.column+ ", " +this.value+ ")");
        }
    }

    //Constructor

    private int n;
    private int NNZ;
    private List rowList[];

    public Matrix (int n){
        if(n<1) throw new RuntimeException
            ("Cannot initialize Matrix of size n < 1");
        
        this.n = n;
        this.NNZ = 0;
        this.rowList = new List[n+1];

        for(int i=1; i<=n; i++){
            rowList[i] = new List();
        }
    }

    //Access Functions

    //Returns n, number of rows and columns of matrix
    int getSize(){
        return n;
    }

    //Returns number of non-zero entries 
    int getNNZ(){
    	int nnz = 0;
        for(int i=1; i <= getSize(); i++) {
        		nnz +=  rowList[i].length();
        }
        return nnz;
    }

    //Overrides Object's equals() method
    public boolean equals(Object x){
        Matrix C;
        boolean tf = false;
        if(x instanceof Matrix){
            C = (Matrix)x;
            if(this.NNZ != C.NNZ){
                return tf;
            }
            if(this.getSize() != C.getSize()) {
            	return tf;
            }
            for(int i=1; i <= C.getSize() ; i++){
            	List A = this.rowList[i];
            	List B = C.rowList[i];
            	tf = A.equals(B);
            	if(tf == false) {
					return tf;
				}
            }
        }
        return tf;
    }

    //Manipulation procedures

    //Sets Matrix to zero state
    void makeZero(){
        for(int i=1; i <= n; i++){
            this.rowList[i] = new List();
        }
    }

    //Returns new Matrix with same entries 
    Matrix copy() {
        Matrix C = new Matrix(this.n);
        for(int i=1; i<=this.getSize(); i++) {
        		List L = this.rowList[i];
        		for(L.moveFront(); L.index() >= 0; L.moveNext()) {
        			Entry t = (Entry)L.get();
        			C.changeEntry(i, t.column, t.value);
        		}
        }
        return C;
    }

    //Changes ith row, jth column of this matrix to x
    //pre: 1<=i<=getSize(), 1<=j<=getSize
    void changeEntry(int i, int j, double x){
    	
        if(i < 1) throw new RuntimeException
            ("Cannot changeEntry of a row less than 1.");
        //if(i > this.n) throw new RuntimeException
        //    ("Cannot changeEntry of a row greater than matrix size.");
        if(j < 1) throw new RuntimeException
            ("Cannot changeEntry of a column less than 1.");
        //if(j > this.n) throw new RuntimeException
        //    ("Cannot changeEntry of a column greater than matrix size.");

        Entry e = new Entry(j, x);
        rowList[i].moveFront();
        while(rowList[i].index() != -1) {
        		if(((Entry)rowList[i].get()).column == j) {
        			if(x != 0) {
        				((Entry)rowList[i].get()).value = x;
        				break;
        			}
        			else if(x == 0){
        				rowList[i].delete();
        				break;
        			}
        		}
        		if(((Entry)rowList[i].get()).column > j){
					rowList[i].insertBefore(e);
        			break;
        		}
        		rowList[i].moveNext();
        }
        if(rowList[i].index() == -1 && x != 0) {
        		rowList[i].append(e);
        }
        else if (rowList[i].length() > 0 && x !=0 && ((Entry)rowList[i].get()).column < j) {
        		//if(((Entry)rowList[i].get()).column != j) {
        			rowList[i].insertAfter(e);
        		//}
        }
    }
    
   Matrix scalarMult(double x) {
    		Matrix S = new Matrix(this.n);
    		for(int i =1; i<= this.getSize(); i++) {
    			List L = this.rowList[i];
    			L.moveFront();
    			while(L.index() != -1) {
    				Entry scale = (Entry)L.get();
    				S.changeEntry(i, scale.column, scale.value*x);
    				L.moveNext();
    			}
    		}
    		return S;
   }
   
   Matrix add(Matrix M) {
	   Matrix D = new Matrix(this.n);
	   if(M == this) {
		   return M.scalarMult(2);
	   }
	   else {
		   for(int row=1; row<=M.getSize(); row++) {
			   List A = rowList[row];
			   List B = M.rowList[row];
			   A.moveFront();
			   B.moveFront();
			   D.rowList[row] = addVector(A, B);
			   /*while(A.index() != -1 && B.index() != -1) {
				   Entry x = (Entry)A.get();
				   Entry y = (Entry)B.get();
				   double added = x.value + y.value;
				   Entry z = new Entry(x.column, added);
				   D.changeEntry(i, z.column, z.value);
				   A.moveNext();
				   B.moveNext();
			   }*/
			   
		   }
	   }
	   
	   if(M.getSize() != this.getSize()) throw new RuntimeException
	   		("Cannot add two matrices of different sizes.");
	   
	   return D;
   }

   Matrix sub(Matrix M) {
	  
	   Matrix Su = M.scalarMult(-1);
	   Matrix T = new Matrix(this.n);
	   
	   if(M == this) {
		   T.makeZero();
	   }
	   else if (M != this) {
	   		for(int row=1; row<=M.getSize(); row++) {
	   			List A = rowList[row];
	   			List B = Su.rowList[row];
	   			A.moveFront();
	   			B.moveFront();
	   			T.rowList[row] = addVector(A, B);
	   		}
	   }
	   
	   if (M.getSize() != this.getSize()) throw new RuntimeException
			   ("Cannot subtract two matrices of different sizes.");
	   
	   return T;
   }
   
   Matrix transpose() {
	   Matrix T = new Matrix(this.n);
	   for(int row=1; row<= this.getSize(); row++) {
		   List R = this.rowList[row];
		   R.moveFront();
		   while(R.index() != -1) {
			   Entry x = (Entry)R.get();
			   T.changeEntry(x.column, row, x.value);
			   R.moveNext();
		   }
	   }
	   return T;
   }
   
    Matrix mult(Matrix M) {
	    Matrix Mu = new Matrix(this.n);
	    Matrix Tr = M.transpose();
	   
	    if(this.getSize() != M.getSize()) throw new RuntimeException
	   		("Cannot call mult on matrices of different sizes.");
        
	    for(int row=1; row<=this.getSize(); row++) {
		    List U = this.rowList[row];
		    if(U.length() > 0) {
			    for(int col=1; col<=this.getSize(); col++) {
				    List T = Tr.rowList[col];
				    if(T.length() > 0) {
					    double product = dot(U, T);
					    Mu.changeEntry(row, col, product);
				    }
			    }
			   
		    }
	    }
	    return Mu;
    }
   
   //Other Functions
    
    public String toString() {
    		String M = "";
    		for(int i=1; i<= this.getSize(); i++) {
    			if(rowList[i].length() != 0) {
    				M += i+": " +rowList[i].toString()+ "\n";
    			}
    		}
    		return M;
    }
    
    
    private List addVector(List A, List B) {
    		List C = new List();
    		A.moveFront();
    		B.moveFront();
    		while(A.index() != -1 && B.index() != -1) {
    			Entry x = (Entry)A.get();
    			Entry y = (Entry)B.get();
    			//If both lists have an entry for this column and they do not equal zero, this will add those entry values
    			if(x.column == y.column) {
    				if(x.value + y.value == 0) {
    					A.moveNext();
    					B.moveNext();
    				}
    				else if (x.value == 0 && y.value == 0) {
    					A.moveNext();
    					B.moveNext();
    				}
    				else if(x.value + y.value != 0) {
    					Entry z = new Entry(x.column, x.value + y.value);
    					C.append(z);
    					A.moveNext();
    					B.moveNext();
    				}
    			}
    			//If there is an entry in List A that is not in List B, this will append that entry from B to C and continue moving through B
    			if(x.column > y.column) {
    				Entry z = new Entry(y.column, y.value);
    				C.append(z);
    				//A.moveNext();
    				B.moveNext();
    			}
    			//Similarly, if there is an entry in List B that is not in List A, this will append that entry from A to C and continue moving through A
    			if(y.column > x.column) {
    				Entry z = new Entry(x.column, x.value);
    				C.append(z);
    				A.moveNext();
    				//B.moveNext();
    			}
    		}
    		//This appends entries in a matrix list where the list is not the 1st or nth vector
    		while(A.index() != -1 || B.index() != -1) {
    			if(B.index() != -1) {
    				Entry z = (Entry)B.get();
    				C.append(z);
    				B.moveNext();
    				//B.moveNext();
    			}
    			else if (A.index() != -1) {
    				Entry z = (Entry)A.get();
    				C.append(z);
    				//A.moveNext();
    				A.moveNext();
    			}
    		}
    		return C;
    }
    
    private static double dot(List A, List B) {
    		double p = 0;
    		A.moveFront();
    		B.moveFront();
    		while(A.index() != -1 && B.index() != -1) {
    			Entry x = (Entry)A.get();
    			Entry y = (Entry)B.get();
    			if(x.column == y.column && (x.value !=0 || y.value != 0)) {
    				p += (x.value*y.value);
    				A.moveNext();
    				B.moveNext();
    			}
    			else if(x.column > y.column) {
    				B.moveNext();
    			}
    			else if(y.column > x.column) {
    				A.moveNext();
    			}
    		}
    		if(A.index() == -1 && B.index() == -1) {
    			return p;
    		}
    		return p;
    }
    
    
}

//Old changeentry - Was not correctly replacing entries
/*    void changeEntry(int i, int j, double x){
Entry e = new Entry(j, x);
rowList[i].moveFront();

if(x != 0) {

		if(rowList[i].length() == 0) {
			rowList[i].append(e);
		}
		else if(rowList[i].length() > 0){
			while(rowList[i].index() != -1) {
				if(((Entry)rowList[i].get()).column == j && ((Entry)rowList[i].get()).value != x) {
					((Entry)rowList[i].get()).value = x;
					rowList[i].delete();
					
				}
				else {
					rowList[i].moveNext();
				}
			}
			//rowList[i].moveFront();
			boolean longerthan1 = false;
			while(rowList[i].index() != -1) {
				if(j < ((Entry)rowList[i].get()).column ) {
					rowList[i].insertBefore(e);
					longerthan1 = true;
					
				}
				else {
					rowList[i].moveNext();
				}
			}
			if(longerthan1 == false) {
				rowList[i].append(e);
			}
		}
}

if(x == 0) {
		if(rowList[i].length() > 0) {
			while(rowList[i].index() != -1) {
				if(((Entry)rowList[i].get()).value != 0 && ((Entry)rowList[i].get()).column == j) {
					rowList[i].delete();
					break;
				}
				rowList[i].moveNext();
			}
		}
}
}*/
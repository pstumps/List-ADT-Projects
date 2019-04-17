//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101
//PA 3
//List ADT modified for Matrix.java

public class List {
	
	public class Node {
		Object Entry;
		Node next;
		Node prev;
		int index;
		
		public Node(Object Entry){
			this.Entry = Entry;
			next = null;
			prev = null;
		}
		
		public boolean equals(Object x) {
			boolean tf = false;
			Node t;
			if(x instanceof Node) {
				t = (Node) x;
				tf = (this.Entry == t.Entry);
			}
			return tf;
		}
		
		public String toString() {
			return String.valueOf(Entry);
		}
	}
	
	private Node head;
	private Node tail;
	private Node curr;
	private int length;
	private int index;
	
	//Constructor
	
	public List() {
		head = null;
		tail = null;
		curr = null;
		length = 0;
		index = -1;	
	}
	
	//Access Functions
	
	int length() {
		return length;
	}
	
	//returns front element
	Object front() {
		if (length() == 0) throw new RuntimeException
			("Front does not exist.");
		return head.Entry;
	}
	
	//return back element
	Object back() {
		if (length() == 0) throw new RuntimeException
			("Tail does not exist.");
		return tail.Entry;
	}
	
	//returns cursor element
	Object get() {
		//if(this.index() < 0) throw new RuntimeException
		//	("Cannot call get() on null cursor");
		if(this.length() == 0) throw new RuntimeException
			("Cannot call get() on empty List");
		return curr.Entry;
	}
	
	//returns cursor of index element
	public int index() {
		if (curr == null) {
			return -1;
		}
		return index;
	}
	
	public boolean equals (Object L) {
		boolean tf = false;
		List eq;
		Node T;
		Node F;
		if(L instanceof List) {
			eq = (List) L;
			T = this.head;
			F = eq.head;
			tf = (eq.length == this.length);
			while(tf && T != null) {
				tf = T.equals(F);
				T = T.next;
				F = F.next;
			}
			
		}
		return tf;
	}
	
	// Manipulation procedures
	
	void clear() {
		head = null;
		length = 0;
		index = -1;
	}
	//places cursor under front element
	void moveFront() {
		if(length() > 0){
			curr = head;
			index = 0;
		}
	}
	//places cursor under back element
	void moveBack() {
		if(length() > 0){
			curr = tail;
			index = length -1;
		}
	}
	//moves cursor one step toward front of list
	void movePrev() {
		if(curr == null) {
			curr = null;
			index = -1;
		}
		else if(curr == head && curr != null) {
			curr = null;
			index = -1;
		}
		else if (curr != head && curr != null) {
			curr = curr.prev;
			index --;
		}
	}
	//moves cursor one step toward back
	void moveNext() {
		if(curr == null) {
			curr = null;
			index = -1;
		}
		else if(curr == tail && curr != null) {
			curr = null;
			index = -1;
		}
		else if(curr != tail && curr != null) {
			curr = curr.next;
			index++;
		}
		
	}
	//insert new element into front of list
	void prepend(Object Entry) {
		Node N;
		if (length() == 0) {
			head = new Node(Entry);
			tail = head;
			curr = head;
		}
		else {
			N = head;
			N.prev = new Node(Entry);
			head = N.prev;
			head.next = N;
			index++;
		}
		//for (Node curr = tail.prev; curr != null; curr=curr.prev) {
		//	++curr.index;
		//}
		length++;
	}
	//insert new element after back of list
	void append(Object Entry) {
		Node N;
		if (length() == 0) {
			tail = new Node(Entry);
			head = tail;
			curr = tail;
			length++;
		}
		else {
			N = tail;
			N.next = new Node(Entry);
			tail = N.next;
			tail.prev = N;
			length++;
		}
		//for (Node curr = head.next;curr != null; curr = curr.next) {
		//	++curr.index;
		//}
	}
	//insert element before cursor
	void insertBefore(Object Entry) {
		Node N = new Node(Entry);
		if(length() == 0) throw new RuntimeException
			("Node does not exist.");
		if (index() == 0 || curr == head) {
			prepend(Entry);
			return;
		}
		Node cprev = curr.prev;
		N.prev = cprev;
		N.next = curr;
		cprev.next = N;
		curr.prev = N;
		length++;
		index++;
	}
	//insert element after cursor
	void insertAfter(Object Entry) {
		Node N = new Node(Entry);
		if (length() == 0) throw new RuntimeException
			("Node does not exist");
		if(index() == length()-1 || curr == tail){
			append(Entry);
			return;
		}
		N.prev = curr;
		N.next = curr.next;
		curr.next = N;
		length++;
	}
	
	void deleteFront() {
		if (length() == 0) throw new RuntimeException
			("Head node does not exist.");
		if(length() < 0) throw new RuntimeException
			("Cannot call deleteFront on negative length list.");
		
		if(length() == 1) {
			head = null;
			tail = null;
			index = -1;
		}
		if(curr == head){
			curr = curr.next;
		}
		if(length() > 0){
			head = head.next;
			head.prev = null;
			length--;
			index--;
		}
	}
	
	void deleteBack() {
		if (length() == 0) throw new RuntimeException
			("Tail node does not exist.");
		if (length() < 0) throw new RuntimeException
			("Cannot call deleteBack on negative length list.");
		if(length() == 1) {
			head = null;
			curr = null;
			tail = null;
			index = -1;
			length--;
		}
		if(curr == tail){
			curr = null;
			index= -1;
		}
		if(length() > 0){
			tail = tail.prev;
			tail.next = null;
			length--;
			//index--;
		}
	}
	
	void delete() {
		if (length() == 0) throw new RuntimeException
			("Node does not exist.");
		if(length() < 0)  throw new RuntimeException
			("Cannot call delete on negative length list.");
		if(curr == head || index == 0){
			head = null;
			curr = null;
			index = -1;
		}
		if(curr == tail || index() == length()-1){
			tail = null;
			curr = null;
			index = -1;
		}
		curr = null;
		length--;
		index = -1;
	}
	
	// Other Methods
	
	public String toString() {
		String l = "";
		for (Node curr = head; curr != null; curr = curr.next) {
			l = l += curr.toString() + " ";
		}
		return l;
	}
	
/*	List copy() {
		List l = new List();
		for (Node curr = head; curr != null; curr = curr.next) {
			l.append(curr.data);
		}
		return l;
	}
	Removed for PA3 */
}

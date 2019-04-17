//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101
//PA 1
//List ADT
public class List {
	
	public class Node {
		int data;
		int index;
		Node next;
		Node prev;
		
		Node(int d){
			data = d;
			next = null;
			prev = null;
		}
		
		public String toString() {
			return String.valueOf(data);
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
	}
	
	//Access Functions
	
	int length() {
		return length;
	}
	
	//returns front element
	int front() {
		if (length == 0) throw new RuntimeException
			("Front does not exist.");
		return head.data;
	}
	
	//return back element
	int back() {
		if (length == 0) throw new RuntimeException
			("Tail does not exist.");
		return tail.data;
	}
	
	//returns cursor element
	int get() {
		if(length() > 0 && index() >= 0){
			return curr.data;
		}
		return -1;
	}
	
	//returns cursor of index element
	int index() {
		if (curr == null) {
			return -1;
		}
		Node t = head;
		int index = 0;
		while( t!= null){
			if(t.data == curr.data){
				return index;
			}
			index++;
			t=t.next;
		}
		return -1;
	}
	
	boolean equals (List L) {
		Node cmp = L.head;
		Node th = head;
		while(cmp.next != null) {
			if(cmp.data != th.data) {
				return false;
			}
			cmp = cmp.next;
			th = th.next;
			
		}
		return true;
	}
	
	// Manipulation procedures
	
	void clear() {
		head = null;
		length = 0;
		index = -1;
	}
	//places cursor under front element
	void moveFront() {
		if(length > 0){
			curr = head;
		}
	}
	//places cursor under back element
	void moveBack() {
		if(length > 0){
			curr = tail;
		}
	}
	//moves cursor one step toward front of list
	void movePrev() {
		if(index() == -1){
			return;
		}
		if(index() == 0){
			curr = null;
		}
		if(index() >= 0 && index() <= length -1){
			curr = curr.prev;
		}
	}
	//moves cursor one step toward back
	void moveNext() {
		if(curr != null && index() != length -1){
			curr = curr.next;
		}
		else if (curr != null && index() == length-1){
			curr = null;
		}
	}
	//insert new element into front of list
	void prepend(int data) {
		Node N;
		if (length == 0) {
			head = new Node(data);
			tail = head;
			curr = head;
		}
		else {
			N = head;
			N.prev = new Node(data);
			head = N.prev;
			head.next = N;
		}
		//for (Node curr = tail.prev; curr != null; curr=curr.prev) {
		//	++curr.index;
		//}
		length++;
	}
	//insert new element after back of list
	void append(int data) {
		Node N;
		if (length == 0) {
			tail = new Node(data);
			head = tail;
			curr = tail;
		}
		else {
			N = tail;
			N.next = new Node(data);
			tail = N.next;
			tail.prev = N;
		}
		//for (Node curr = head.next;curr != null; curr = curr.next) {
		//	++curr.index;
		//}
		length++;
	}
	//insert element before cursor
	void insertBefore(int data) {
		Node N = new Node(data);
		if (index() == 0) {
			prepend(data);
			return;
		}
		Node cprev = curr.prev;
		N.prev = cprev;
		N.next = curr;
		cprev.next = N;
		curr.prev = N;
		length++;
	}
	//insert element after cursor
	void insertAfter(int data) {
		Node N = new Node(data);
		if (length == 0) throw new RuntimeException
			("Node does not exist");
		
		N.prev = curr;
		N.next = curr.next;
		curr.next = N;
		length++;
	}
	
	void deleteFront() {
		if (length == 0) throw new RuntimeException
			("Head node does not exist.");
		head = head.next;
		head.next = head;
		length--;
	}
	
	void deleteBack() {
		if (length == 0) throw new RuntimeException
			("Back node does not exist.");
		tail = tail.prev;
		tail.prev = tail;
		length--;
	}
	
	void delete() {
		if (length == 0) throw new RuntimeException
			("Node does not exist.");
		curr = null;
		length--;
	}
	
	// Other Methods
	
	public String toString() {
		String l = "";
		for (Node curr = head; curr != null; curr = curr.next) {
			l = l += curr.toString() + " ";
		}
		return l;
	}
	
	List copy() {
		List l = new List();
		for (Node curr = head; curr != null; curr = curr.next) {
			l.append(curr.data);
		}
		return l;
	}
	
}
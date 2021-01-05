#include <iostream>
using namespace std;

/*
DEFINING THE STRUCTURE FOR CIRCULAR LINKED LIST
*/
class Node {
public:
	int data;
	Node* next;
};

class LinkedList {
public:
	Node* lastNode;//it stores the address of last node of list
	Node* ploc;//a special variable we use in search function to store address of logical pre-decessor of value in list 
	Node* loc;//to be used by Search(value) method to store address of the node containing the searched value in a list.If it is not found it contains NULL.

	/*
	Constructor for creating the empty linked list by assigning start, loc, ploc pointer variables to null
	*/
	LinkedList() {
		loc = NULL;
		ploc = NULL;
	}

	//implementation of isEmpty() method
	bool isEmpty() {
		return lastNode == NULL;
	}

	//implementationof printList() method
	void printlist() {
		if (!isEmpty()) {
			Node* temp = lastNode->next;
			do {
				cout << temp->data << " ";
				// advance temp to successor node.
				temp = temp->next;
			} while (temp != lastNode->next);
			cout << "\n";
		}
		else
		{
			cout << "list is empty\n";
		}
		return;

	}

	//implementationof InsertAtFront() method
	void InsertAtFront(int value) {
		//first we have to allocate memory by making object of linkedlist structure
		Node* newnode = new Node();
		newnode->data = value;

		//one case is when list is empty so start and last both should be updated
		if (isEmpty()) {
			newnode->next = newnode;
			lastNode = newnode;
		}
		else
		{
			newnode->next = lastNode->next;
			lastNode->next = newnode;
			
		}
	
	}

	//implementationof InsertAtEnd() method
	void InsertAtEnd(int value) {
		//first we have to allocate memory by making object of linkedlist structure
		Node* newnode = new Node();
		newnode->data = value;

		if (isEmpty()) {
			newnode->next = newnode;
			lastNode = newnode;
		}
		else {
			newnode->next = lastNode->next;
			lastNode->next = newnode;
			lastNode = newnode;
		}
	}

	//implementationof Search() method
	void Search(int value) {
		loc = NULL;
		ploc = NULL;

		//IF LIST IS EMPTY THEN CONTROL EXITS FROM THE FUNCTION
		if (isEmpty())
		{
			cout << "list is empty\n";
			return;
		}
			
		loc = lastNode->next;
		ploc = lastNode;
		while (loc != lastNode && loc->data < value)
		{
			ploc = loc;
			loc = loc->next;
		}

		//THIS LOOP EXECUTES WHEN THE VALUE DOES NOT FOUND IN THE LIST
		if (loc->data != value)
		{
			if (value > loc->data)
			{
				ploc = lastNode;
			}
			loc = NULL;
		}
	}


	//implementationof InsertSorted() method
	//if we want to maintain a sorted list we call this function
	void InsertSorted(int value) {
		Search(value);
		if (loc != NULL) {
			//Return without insertionand print a message
			cout << "value already exists duplication not allowed\n";
			return;
		}
			
		else {
			if (ploc==NULL || ploc == lastNode && value > lastNode->data)
			{
				InsertAtEnd(value);
			}
			else if ((ploc == NULL) || (ploc == lastNode && value < (lastNode->next)->data))
				InsertAtFront(value);
			else
			{//Insert after ploc.
				Node* newnode = new Node();
				newnode->data = value;
				newnode->next = ploc->next;
				ploc->next = newnode;

			}	
		}
	}

	

	//implementationof DeleteValue() method
	void DeleteValue(int value) {
		Search(value);
		if (loc != NULL)//if value is found in list
		{
			if (lastNode->next == lastNode)
			{
				lastNode = NULL;
				delete loc;
			}
			else
			{
				if (loc == lastNode) {
					lastNode = ploc;
					ploc->next = loc->next;
					delete loc;
				}
				else
				{
					ploc->next = loc->next;
					delete loc;
				}
			}
		}
		else
		{
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nVALUE NOT FOUND!!!!!!!! SO DELETION NOT POSSIBLE\n^^^^^^^^^^^^^^^^^^^^^^^\n" << endl;
		}

	}
	

	//implementationof DestroyList() method
	void DestroyList() {
		Node* temp;
		temp = lastNode->next;
		while (lastNode->next != lastNode)
		{
			temp = lastNode->next;
			lastNode->next = lastNode->next->next;
			delete temp;
		}
		delete lastNode;//delete the only remaining node
		lastNode = NULL;
		cout << "******************************\n yayyyyyy !! all elements of list are destroyed\n*********************************\n";
	}
};

/*
HERE GOES OWR MAIN CODE FOR TESTING THE METHODS OF SINGLY LINKED LIST
*/
int main() {
	LinkedList* obj = new LinkedList();
	Node* node = new Node();
	cout << "------------------------------------------------------------\n\t\" CIRCULAR LINKED LIST\"\t\n------------------------------------------------------------\n";
	cout << endl << "INSERTING 1 AT FRONT using InsertAtFront(1)\n" << endl;
	obj->InsertAtFront(1);
	obj->printlist();

	cout << endl << "INSERTING 3,5,4,6,2 USING  InsertSorted()\n" << endl;
	obj->InsertSorted(2);
	obj->InsertSorted(4);
	obj->InsertSorted(3);
	obj->InsertSorted(5);
	obj->InsertSorted(6);
	obj->printlist();

	cout << endl << "INSERTING 7 AT END using  InsertAtEnd(7)\n" << endl;
	obj->InsertAtEnd(7);
	obj->printlist();

	cout << endl << "Deleting value 5 using DeleteValue(5) \n" << endl;
	obj->DeleteValue(5);
	obj->printlist();

	cout << endl << "Deleting value 10 which is not in list so list remains the same\n" << endl;
	obj->DeleteValue(10);
	obj->printlist();

	cout << endl << "Destroying full linked list so that it contained no elements \n" << endl;
	obj->DestroyList();
	cout << endl << "printing list\n";
	obj->printlist();

}

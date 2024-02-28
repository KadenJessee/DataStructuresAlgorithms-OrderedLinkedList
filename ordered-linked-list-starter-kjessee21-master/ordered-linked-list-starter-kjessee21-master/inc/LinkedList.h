#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

template <class Type>
struct Node
{
	Type data;
	Node *next;
};

template <class Type>
class OrderedLinkedList;

template <class Type>
std::ostream& operator<<(std::ostream&, const OrderedLinkedList<Type>& list);


template <class Type>
class OrderedLinkedList
{
protected:
    Node<Type>* front;
    Node<Type>* back;
    int counter;
public:
	OrderedLinkedList();
	OrderedLinkedList(const OrderedLinkedList& other);
	OrderedLinkedList<Type>& operator=(const OrderedLinkedList<Type>& other);
	~OrderedLinkedList();

    int size() const;
    bool empty() const;
	Type get(int) const;
	Type getFirst() const;
	Type getLast() const;
	int insert(const Type&);
	int find(const Type&) const;
	void remove(const Type&);
    void clear();
    OrderedLinkedList<Type> everyOtherOdd();
    OrderedLinkedList<Type> everyOtherEven();
    friend std::ostream& operator<< <>(std::ostream&, const OrderedLinkedList<Type>& list);
};


template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList()
{
    //initialize to empty state
    front = nullptr;
    back = nullptr;
    counter = 0;
}

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList(const OrderedLinkedList<Type>& other)
{
    //creates a deep copy of the other list
    front = nullptr;
    back = nullptr;
    counter = 0;
    for(int i = 0; i < other.counter; i++){
        insert(other.get(i));
    }
}

template <class Type>
OrderedLinkedList<Type>& OrderedLinkedList<Type>::operator=(const OrderedLinkedList& other)
{
    clear();
    //creates a deepp copy and cleans up any previous memory
    counter = 0;
    front = nullptr;
    back = nullptr;

    for(int i = 0; i < other.counter; i++){
        insert(other.get(i));
    }
    return *this;
}

template <class Type>
OrderedLinkedList<Type>::~OrderedLinkedList()
{
    //destructor
    clear();
}

template <class Type>
int OrderedLinkedList<Type>::size() const
{
    //returns size
    return counter;
}

template <class Type>
bool OrderedLinkedList<Type>::empty() const
{
    //returns true if empty
    if(counter == 0){
        return true;
    }else{
        return false;
    }
}

template <class Type>
Type OrderedLinkedList<Type>::get(int pos) const
{
    int i = 0;
    //set current node to front
    auto currentNode = front;
    //if pos >= counter or < 0, out of range
    if(pos >= counter || pos < 0){
        throw std::out_of_range("Out of range.");
    }
    //if i not equal to position, go through nodes
    while(i != pos){
        i++;
        currentNode = currentNode->next;
    }
    //return data at the position
    if(i == pos){
        return currentNode->data;
    }
}

template <class Type>
Type OrderedLinkedList<Type>::getFirst() const
{
    //if 0, out of range
    if(counter == 0){
        throw std::out_of_range("Out of range.");
    }
    //get front of node and return
    auto currentNode = front;
    return currentNode->data;
}

template <class Type>
Type OrderedLinkedList<Type>::getLast() const
{
    //0 is out of range
    if(counter == 0) {
        throw std::out_of_range("Out of range.");
    }
    //start at front
    int nodeNum = 0;
    auto currentNode = front;
    //loop through to end and retrieve last node
    for(int i = 0; i < counter - 1; i++){
        nodeNum++;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template <class Type>
int OrderedLinkedList<Type>::insert(const Type& item)
{
    //create temp node to put item into
    Node<Type>* temp = new Node<Type>;
    temp->data = item;
    temp->next = nullptr;
    //if front is null, create front and back pointers
    if(front == nullptr){
        this->front = temp;
        this->back = temp;
        counter++;
        return -1;
    }else{
        //set currentNode to front
        auto currentNode = this->front;
        //if current node is not the back
        while(currentNode != this->back){
            //if data at temp is < next data & greater than/equal to current data
            if(temp->data < currentNode->next->data && temp->data >= currentNode->data){
                //set temp next to next node
                temp->next = currentNode->next;
                //current node then takes next of temp node
                currentNode->next = temp;
                counter++;
                return -1;
            }else{
                //else just set currentnode to next
                currentNode = currentNode->next;
            }
        }
    }
    //if data is less than fronts data, set next to front
    if(temp->data < front->data){
        temp->next = front;
        this->front = temp;
        counter++;
    }//else set it to back
    else{
        temp->next = nullptr;
        back->next = temp;
        back = temp;
        counter++;
        return -1;
    }
}

template <class Type>
int OrderedLinkedList<Type>::find(const Type& item) const
{
    //set currentNode to front
    int nodeNum = 0;
    auto currentNode = front;
    for(int i = 0; i < counter; i++){
        //if front is null, end
        if(currentNode == nullptr){
            return -1;
        }
        //return data at item
        if(currentNode->data == item){
            return nodeNum;
        }
        //otherwise keep looping through nodes
        nodeNum++;
        currentNode = currentNode->next;
    }
    return -1;
}

template <class Type>
void OrderedLinkedList<Type>::remove(const Type& item)
{
    //set to front
    auto currentNode = front;
    //find item
    auto location = find(item);
    if(location == -1) {
        return;
    }
    //remove at 0, set front to next
    if (location == 0) {
        front = currentNode->next;
        delete currentNode;
        counter--;
        return;
    }
    //loop through nodes
    for (int i = 0; i < counter; ++i) {
        //if not item, go to next
        if(currentNode->next->data != item){
            currentNode = currentNode->next;
        }
        //if not back
        else if (currentNode->next != back) {
            //set next node to next/next
            auto temp = currentNode->next;
            currentNode->next = currentNode->next->next;
            delete temp;
            counter--;
            return;
        }
        else {
             //set back to current node and remove item
            counter--;
            auto temp = currentNode->next;
            back = currentNode;
            delete temp;
            currentNode->next = nullptr;
            return;
        }
    }
}

template <class Type>
void OrderedLinkedList<Type>::clear()
{
    //get front
    auto currentNode = front;
    auto& temp = front;
    auto count = counter;
    for(int i = 0; i < count; i++){
        //set temp to current node
        temp = currentNode;
        //set current to next
        currentNode = currentNode->next;
        //free temp
        delete temp;
        counter--;
    }
    //set front to null
    front = nullptr;
}


template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherOdd(){
    OrderedLinkedList<Type> retVal;
    //start at 0 and go every other
    for(int i = 0; i < counter; i += 2){
        retVal.insert(get(i));
    }
    return retVal;
}

template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherEven(){
    OrderedLinkedList<Type> retVal;
    //start at 1 and go every other
    for(int i = 1; i < counter; i += 2){
        retVal.insert(get(i));
    }
    return retVal;
}

template <class Type>
std::ostream& operator<<(std::ostream& out, const OrderedLinkedList<Type>& list)
{
    //if empty, don't throw out of range
    if(list.counter == 0){
        int temp = 0;
    }else{
        //print off array
        for (int i = 0; i < list.counter - 1; i++) {
            out << list.get(i);
            out << "->";
        }
        out << list.get(list.counter - 1);
        return out;
    }
}
#endif

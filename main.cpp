#include <iostream>

using namespace std;

class Node {
  public:
   static int number_of_carts;
   double cash = 0; // data 1
   int id = 0; // data 2
   bool isInUse = false;
   Node *next; //pointer

   Node(){
       cash = 0;
   }
   Node(double cash) {
     ++number_of_carts;
     this->id = number_of_carts;
     this->cash = cash;
     next = NULL;
   }
   ~Node(){}
};

int Node::number_of_carts = 0;

class Stack {
  public:
   Node *top;

   Stack() {
    top = NULL;
   }

   void push(Node *n) { // insert
    n->next = top;
    top = n;
   }
   void pop() { // delete
    Node* n = top;
    top = top->next;
    delete(n); // i guess i should use other database
   }
   void print() { // display
    Node* ptr = top;
    cout << "Cart id | Cash in Cart" << endl;
    while(ptr != NULL) {
     cout << " " << ptr->id << "          " << ptr->cash <<endl;
     ptr = ptr->next;
    }
   }
   Node getTop(){
       return *top;
   }

   ~Stack(){}
};

int main()
{
    system("color a");

    Stack *stackOfCarts = new Stack;
    Node cartsInUse[10];

    for(int i=0; i<10; i++){ // Filling cart stack with 10 carts
        stackOfCarts->push(new Node(0.0));
    }
    int cartId = 0;
    int choice = 1;
    double cash;

    main_menu:

    while(choice){
        cout << "1. Take cart" << endl;
        cout << "2. Put cart" << endl;
        cout << "3. Cart details" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: "; cin >> choice;
        cout << endl; system("cls");

        switch(choice){
            step1:
            case 1:{
                cout << "Enter a cash before taking: "; cin >> cash;
                if(cash < 1){
                    cout << "You did not put enough money!" << endl;
                    goto step1;
                } else if(Node::number_of_carts < 1){
                    cout << "We don't have free cart!" << endl;
                    goto main_menu;
                }
                stackOfCarts->top->cash = cash;
                cartsInUse[(Node::number_of_carts)-1] = stackOfCarts->getTop();
                cartsInUse[(Node::number_of_carts)-1].isInUse = true;
                stackOfCarts->pop();
                (Node::number_of_carts)--;

                break;
            }
            case 2:{
                if(Node::number_of_carts >= 10){
                    cout << "Stack of carts is full" << endl;
                    goto main_menu;
                }
                else{
                    cout << "Which cart you are taking back: "; cin >> cartId;
                    if(cartId > 0 && cartId < 11){
                        if(cartsInUse[cartId-1].isInUse){
                            stackOfCarts->push(&cartsInUse[cartId-1]);
                            cout << "Thank you! Here is the your " << (cartsInUse[cartId-1]).cash << "$" << endl;
                            cartsInUse[cartId-1].cash = 0;
                            cartsInUse[cartId-1].isInUse = false;
                            Node::number_of_carts++;
                        } else{
                            cout << "This cart is already taken back!" << endl;
                        }
                    } else{
                        cout << "This is not our cart!" << endl;
                    }
                }
                break;
            }
            case 3:{
                stackOfCarts->print();
                break;
            }
            case 0:{
                stackOfCarts->~Stack();
                for(int i=0; i<10; i++){
                    cartsInUse[i].~Node();
                }
                delete stackOfCarts;

                break;
            }
            default:{
                cout << "You entered wrong choice!" << endl;
                break;
            }
        }

    }

    return 0;
}

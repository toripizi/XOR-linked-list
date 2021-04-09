#include <iostream>
#include <string>

using namespace std;

class Node {
    int value = NULL;
    Node* XOR = nullptr;
public:
    void setValue(int newValue) {
        value = newValue;
    }
    void setXOR(Node* newXOR) {
        XOR = newXOR;
    }
    const int getValue() {
        return value;
    }
    Node* getXOR() {
        return XOR;
    }
};

Node* XOR(Node* a, Node* b) {
    return (Node*)(uintptr_t(a) ^ uintptr_t(b));
}

Node* XOR(Node* a, Node* b, Node* c) {
    return (Node*)(uintptr_t(a) ^ uintptr_t(b) ^ uintptr_t(c));
}

class List {
    Node* first = nullptr;
    Node* actual = nullptr;
    Node* last = nullptr;
public:
    void ADD_BEG(int value) {
        if (first == nullptr) {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(NULL);
            first = newNode;
            actual = newNode;
            last = newNode;
        }
        else if(first == last) {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(first);
            first = newNode;
            last->setXOR(newNode);
        }
        else {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(first);
            first->setXOR(XOR(newNode, first->getXOR()));
            first = newNode;
        }
    }
    void ADD_END(int value) {
        if (first == nullptr) {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(NULL);
            first = newNode;
            actual = newNode;
            last = newNode;
        }
        else if (first == last) {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(last);
            last = newNode;
            first->setXOR(newNode);
        }
        else {
            Node* newNode = new Node;
            newNode->setValue(value);
            newNode->setXOR(last);
            last->setXOR(XOR(newNode, last->getXOR()));
            last = newNode;
        }
    }
    void ADD_ACT(int value) {
        if (first == nullptr) ADD_BEG(value);
        else if (first == last) ADD_BEG(value);
        else {
            if (actual == first) ADD_BEG(value);
            else {
                Node* newNode = new Node;
                newNode->setValue(value);
                if (actual != last) {
                    Node* temporaryPrevious = nullptr;
                    Node* temporary = first;
                    Node* memory;
                    while (temporary != actual) {
                        memory = temporary;
                        temporary = XOR(temporaryPrevious, temporary->getXOR());
                        temporaryPrevious = memory;
                    }
                    newNode->setXOR(XOR(temporaryPrevious, actual));
                    temporaryPrevious->setXOR(XOR(temporaryPrevious->getXOR(), actual, newNode));
                    actual->setXOR(XOR(newNode, temporaryPrevious, actual->getXOR()));
                }
                else {
                    Node* secend = actual->getXOR();
                    newNode->setXOR(XOR(secend, actual));
                    secend->setXOR(XOR(secend->getXOR(), actual, newNode));
                    actual->setXOR(newNode);

                }
            }
        }
    }
    const void PRINT_FORWARD() {
        if (first != nullptr) {
            Node* temporaryPrevious = nullptr;
            Node* temporary = first;
            Node* memory;
            do {
                cout << temporary->getValue() << " ";
                memory = temporary;
                temporary = XOR(temporaryPrevious, temporary->getXOR());
                temporaryPrevious = memory;
            } while (temporary != nullptr);
            cout << endl;
        }
        else cout << "NULL" << endl;
    }
    const void PRINT_BACKWARD() {
        if (first != nullptr) {
            Node* temporaryPrevious = nullptr;
            Node* temporary = last;
            Node* memory;
            do {
                cout << temporary->getValue() << " ";
                memory = temporary;
                temporary = XOR(temporaryPrevious, temporary->getXOR());
                temporaryPrevious = memory;
            } while (temporary != nullptr);
            cout << endl;
        }
        else cout << "NULL" << endl;
    }
    const void ACTUAL() {
        if (actual == nullptr) {
            cout << "NULL" <<endl;
        }
        else {
            cout << actual->getValue() <<endl;
        }
    }
    void NEXT() {
        if (actual != last) {
            Node* temporaryPrevious = nullptr;
            Node* temporary = first;
            Node* memory;
            while (temporary != actual) {
                memory = temporary;
                temporary = XOR(temporaryPrevious, temporary->getXOR());
                temporaryPrevious = memory;
            }
            actual = XOR(temporaryPrevious, actual->getXOR());
        }
        else {
            actual = first;
        }
        ACTUAL();
    }
    void PREV() {
        if (actual != first) {
            Node* temporaryPrevious = nullptr;
            Node* temporary = last;
            Node* memory;
            while (temporary != actual) {
                memory = temporary;
                temporary = XOR(temporaryPrevious, temporary->getXOR());
                temporaryPrevious = memory;
            }
            actual = XOR(temporaryPrevious, actual->getXOR());
        }
        else {
            actual = last;
        }
        ACTUAL();
    }
    void DEL_BEG() {
        if (first == last) {
            delete actual;
            first = nullptr;
            actual = nullptr;
            last = nullptr;
        }
        else {
            if (actual == first) actual = last;
            Node* secend = first->getXOR();
            secend->setXOR(XOR(first, secend->getXOR()));
            delete first;
            first = secend;
        }
    }
    void DEL_END() {
        if (first == last) DEL_BEG();
        else {
            if (actual == last) actual = actual->getXOR();
            Node* secend = last->getXOR();
            secend->setXOR(XOR(last, secend->getXOR()));
            delete last;
            last = secend;
        }
    }
    void DEL_ACT() {
        if (first == last) DEL_BEG();
        else {
            if (actual == first) DEL_BEG();
            else if (actual == last) DEL_END();
            else {
                Node* temporaryPrevious = nullptr;
                Node* temporary = first;
                Node* memory;
                while (temporary != actual) {
                    memory = temporary;
                    temporary = XOR(temporaryPrevious, temporary->getXOR());
                    temporaryPrevious = memory;
                }
                memory = XOR(temporaryPrevious, temporary->getXOR());
                temporaryPrevious->setXOR(XOR(temporary, temporaryPrevious->getXOR(), memory));
                memory->setXOR(XOR(temporary, memory->getXOR(), temporaryPrevious));
                delete actual;
                actual = temporaryPrevious;
            }
        }
    }
    void DEL_VAL(int value) {
        if (first == last && first->getValue() == value) DEL_BEG();
        else {
            Node* temporaryPrevious = nullptr;
            Node* temporary = first;
            Node* memory = nullptr;
            while (temporary != nullptr) {
                if (temporary->getValue() == value) {
                    if (temporary == actual) {
                        DEL_ACT();
                    }
                    else {
                        memory = actual;
                        actual = temporary;
                        temporary = XOR(temporaryPrevious, temporary->getXOR());
                        DEL_ACT();
                        actual = memory;
                        memory = temporaryPrevious;
                    }
                }
                else {
                    memory = temporary;
                    temporary = XOR(temporaryPrevious, temporary->getXOR());
                }
                temporaryPrevious = memory;
            }
        }
    }
};

int main()
{
    List list;
    string commend;
    int value = NULL;
    while (!cin.eof())
    {
        commend = "";
        cin >> commend;
        if (commend == "ADD_BEG") {
            cin >> value;
            list.ADD_BEG(value);
        }
        else if (commend == "ADD_END") {
            cin >> value;
            list.ADD_END(value);
        }
        else if (commend == "ADD_ACT") {
            cin >> value;
            list.ADD_ACT(value);
        }
        else if (commend == "PRINT_FORWARD") {
            list.PRINT_FORWARD();
        }
        else if (commend == "PRINT_BACKWARD") {
            list.PRINT_BACKWARD();
        }
        else if (commend == "ACTUAL") {
            list.ACTUAL();
        }
        else if (commend == "NEXT") {
            list.NEXT();
        }
        else if (commend == "PREV") {
            list.PREV();
        }
        else if (commend == "DEL_BEG") {
            list.DEL_BEG();
        }
        else if (commend == "DEL_END") {
            list.DEL_END();
        }
        else if (commend == "DEL_ACT") {
            list.DEL_ACT();
        }
        else if (commend == "DEL_VAL") {
            cin >> value;
            list.DEL_VAL(value);
        }
    }

    return 0;
}
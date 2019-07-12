/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kouckma
 *
 * Created on November 3, 2018, 10:30 AM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Node {
    int value;
    Node * left;
    Node * right;
    Node * parent;
    Node * otherTree;
public:
    int height;
    //    int balance;

    Node(int value, Node * parent) {
        this->value = value;
        this->parent = parent;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
        //        this->balance = 0;
    }

    int getValue() {
        return value;
    }

    void setValue(int val) {
        value = val;
    }

    Node * toOtherTree() {
        return otherTree;
    }

    void setOtherTree(Node * other) {
        otherTree = other;
    }

    Node* getParent() {
        return parent;
    }

    Node* getLeft() {
        return left;
    }

    Node* getRight() {
        return right;
    }

    void setLeft(Node* succ) {
        left = succ;
    }

    void setRight(Node * succ) {
        right = succ;
    }

    void setParent(Node * succ) {
        parent = succ;
    }

    int getLeftHeight() {
        if (left)
            return left->height;
        else
            return 0;
    }

    int getRightHeight() {
        if (right)
            return right->height;
        else
            return 0;
    }
};

class StartNode {
public:
    Node* startNode = NULL;

    StartNode(Node * start) {
        this->startNode = start;
    }

    void changeStart(Node * newStart) {
        startNode = newStart;
    }

    Node* getStart() {
        return startNode;
    }

    //    ~StartNode() {
    //        delete startNode;
    //    }
};

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

Node* findNode(int value, StartNode* start) {
    Node * current = start->getStart();

    while (current != NULL) {
        if (current->getValue() < value) {
            current = current->getRight();
        } else if (current->getValue() > value) {
            current = current->getLeft();
        } else
            return current;
    }
    return NULL;
}

Node* findFromWhich(int value, StartNode* start) {
    //nevimneivmnevim
    Node * current = start->getStart();

    while (current) {
        //desired wasnt in the heap
        if (current->getValue() < value) {
            if (current->getRight())
                current = current->getRight();
            else
                return current;
        }//desired wasnt in the heap
        else if (current->getValue() > value) {
            if (current->getLeft())
                current = current->getLeft();
            else
                return current;
        }//if the desired is aready in the heap
        else
            return current;
    }
    //cant happen probably
    return NULL;














    ////////////////////////////



}

Node* findOtherInAVL(int value, StartNode* start) {
    Node * current = start->getStart();

    while (current != NULL) {
        if (current->getValue() < value) {
            current = current->getRight();
        } else if (current->getValue() > value) {
            current = current->getLeft();
        } else {
            if (current->toOtherTree())
                return current->toOtherTree();
            else
                return NULL;
        }
    }
    return NULL;
}

Node* findMin(Node* startNode) {
    Node * current = startNode;

    while (current->getLeft()) {
        current = current->getLeft();
    }
    return current;
}

Node* findMax(Node* startNode) {
    Node * current = startNode;

    while (current->getRight()) {
        current = current->getRight();
    }
    return current;
}

Node * rotate(int value, Node* peak, StartNode * bothStart, int direction) {
    if (!peak)
        cout << "notfound" << endl;
    else {
        Node * parent = peak->getParent();
        Node * newPeak;
        if (direction == 1) {
            newPeak = peak->getRight();
            if (!newPeak)
                cout << "norotate" << endl;
            else {
                if (peak->getParent()) {
                    if (parent->getValue() > value) {
                        parent->setLeft(newPeak);
                    } else {
                        parent->setRight(newPeak);
                    }
                }
                if (peak->getValue() == bothStart->startNode->getValue())
                    bothStart->changeStart(newPeak);
                peak->setParent(newPeak);
                peak->setRight(newPeak->getLeft());
                if (newPeak->getLeft())
                    newPeak->getLeft()->setParent(peak);
                newPeak->setLeft(peak);
                newPeak->setParent(parent);

                peak->height = max(peak->getLeftHeight(), peak->getRightHeight()) + 1;
                newPeak->height = max(newPeak->getLeftHeight(), newPeak->getRightHeight()) + 1;
                return newPeak;
            }

        } else {
            //y je newP a x je peak
            newPeak = peak->getLeft();
            if (!newPeak)
                cout << "norotate" << endl;
            else {
                if (peak->getParent()) {
                    if (parent->getValue() > value) {
                        parent->setLeft(newPeak);
                    } else {
                        parent->setRight(newPeak);
                    }
                }
                if (peak->getValue() == bothStart->startNode->getValue())
                    bothStart->changeStart(newPeak);
                peak->setParent(newPeak);
                peak->setLeft(newPeak->getRight());
                if (newPeak->getRight())
                    newPeak->getRight()->setParent(peak);
                newPeak->setRight(peak);
                newPeak->setParent(parent);

                peak->height = max(peak->getLeftHeight(), peak->getRightHeight()) + 1;
                newPeak->height = max(newPeak->getLeftHeight(), newPeak->getRightHeight()) + 1;

                return newPeak;
            }
        }
        //        newPeak->height = max(newPeak->getLeftHeight(), newPeak->getRightHeight()) + 1;
        return peak;
    }
    return peak;
}

Node * addNode(int value, Node * start) {
    Node * current = start;

    int side = 0;
    while (1) {
        if (current->getValue() < value) {
            if (current->getRight() == NULL) {
                side = 1;
                break;
            } else
                current = current->getRight();
        } else {
            if (current->getLeft() == NULL) {
                side = 0;
                break;
            } else
                current = current->getLeft();
        }
    }
    Node * newNode = new Node(value, current);
    if (side)
        current->setRight(newNode);
    else
        current->setLeft(newNode);
    return newNode;
}

Node * AVLaddNode(int value, Node * current, Node * parent, Node * other, StartNode*start) {
    if (current == NULL) {
        Node * tmp = new Node(value, parent);
        tmp->setOtherTree(other);
        other->setOtherTree(tmp);
        return tmp;
    }
    if (current->getValue() < value) {
        //        if (!current->getRight()) {
        //            current->getRight() = AVLaddNode(value, current->getRight(), current);
        //            return current->getRight();
        //        }
        //        return AVLaddNode(value, current->getRight(), current);
        current->setRight(AVLaddNode(value, current->getRight(), current, other, start));
        //        current->balance++;
    } else if (current->getValue() > value) {
        current->setLeft(AVLaddNode(value, current->getLeft(), current, other, start));
        //        current->balance--;
    } else
        return current;

    current->height = 1 + max(current->getLeftHeight(), current->getRightHeight());

    int balance = 0;
    if (current)
        balance = current->getRightHeight() - current->getLeftHeight();

    //left left, 2 means rotation to right
    if (balance < -1 && current->getLeft()->getValue() > value) {
        //        current->balance = 0;
        return rotate(current->getValue(), current, start, 2);
    }
    //right right
    if (balance > 1 && current->getRight()->getValue() < value) {
        //        current->balance = 0;
        return rotate(current->getValue(), current, start, 1);
    }
    //hopefully left right case
    if (balance < -1 && current->getLeft()->getValue() < value) {
        current->setLeft(rotate(current->getLeft()->getValue(), current->getLeft(), start, 1));
        //            current->getLeft()->setParent(current);
        return rotate(current->getValue(), current, start, 2);
    }

    if (balance > 1 && current->getRight()->getValue() > value) {
        current->setRight(rotate(current->getRight()->getValue(), current->getRight(), start, 2));
        return rotate(current->getValue(), current, start, 1);
    }
    return current;

}

void removeNode(int value, StartNode* start, Node * wanted) {
    if (wanted != NULL) {
        bool isLeftChild = 0;
        Node * parent = NULL;
        if (wanted->getParent()) {
            parent = wanted->getParent();
            isLeftChild = parent->getValue() > value;
        }
        if (wanted->getLeft() == NULL && wanted->getRight() == NULL) {
            if (wanted == start->startNode) {
                start->changeStart(NULL);
            } else if (isLeftChild)
                parent->setLeft(NULL);
            else
                parent->setRight(NULL);
            wanted->toOtherTree()->setOtherTree(NULL);
//            delete wanted;
        } else if (wanted->getLeft() != NULL && wanted->getRight() == NULL) {
            if (wanted == start->startNode) {
                start->changeStart(wanted->getLeft());
            } else if (isLeftChild)
                parent->setLeft(wanted->getLeft());
            else
                parent->setRight(wanted->getLeft());
            wanted->getLeft()->setParent(parent);
            wanted->toOtherTree()->setOtherTree(NULL);
//            delete wanted;
        } else if (wanted->getLeft() == NULL && wanted->getRight() != NULL) {
            if (wanted == start->startNode) {
                start->changeStart(wanted->getRight());
            } else if (isLeftChild)
                parent->setLeft(wanted->getRight());
            else
                parent->setRight(wanted->getRight());
            wanted->getRight()->setParent(parent);
            wanted->toOtherTree()->setOtherTree(NULL);
//            delete wanted;
        }//this will be long
        else {
            Node * replacement = findMin(wanted->getRight());
            wanted->setValue(replacement->getValue());
            Node* tobeNULLed = wanted->toOtherTree();
            wanted->setOtherTree(replacement->toOtherTree());
            wanted->toOtherTree()->setOtherTree(wanted);
            replacement->setOtherTree(tobeNULLed);
            removeNode(replacement->getValue(), start, replacement);
        }
    }
}

int bal(Node * a) {
    if (a)
        return a->getRightHeight() - a->getLeftHeight();
    else
        return 0;
}

Node * AVLremove(Node * wanted, int value, StartNode * start) {
    if (wanted == NULL)
        return wanted;
    if (value < wanted->getValue())
        wanted->setLeft(AVLremove(wanted->getLeft(), value, start));
    else if (value > wanted->getValue())
        wanted->setRight(AVLremove(wanted->getRight(), value, start));

    else {
        if ((wanted->getLeft() == NULL) || (wanted->getRight() == NULL)) {
            Node *temp = wanted->getLeft() ? wanted->getLeft() :
                    wanted->getRight();
            //both null
            if (temp == NULL) {
                if (start->startNode == wanted)
                    start->changeStart(NULL);
                temp = wanted;
                wanted = NULL;
            } else //one null
            {
                if (temp->getLeft())
                    temp->getLeft()->setParent(wanted);
                if (temp->getRight())
                    temp->getRight()->setParent(wanted);

                wanted->setOtherTree(temp->toOtherTree());
                temp->toOtherTree()->setOtherTree(wanted);

                wanted->setRight(temp->getRight());
                wanted->setLeft(temp->getLeft());

                wanted->setValue(temp->getValue());



            }


//            delete temp;
        } else {
            Node* temp = findMin(wanted->getRight());

            wanted->setValue(temp->getValue());

            wanted->setOtherTree(temp->toOtherTree());
            temp->toOtherTree()->setOtherTree(wanted);

            wanted->setRight(AVLremove(wanted->getRight(), temp->getValue(), start));
        }
    }

    if (wanted == NULL)
        return wanted;

    wanted->height = 1 + max(wanted->getLeftHeight(),
            wanted->getRightHeight());

    int balance = wanted->getRightHeight() - wanted->getLeftHeight();

    if (balance < -1 && bal(wanted->getLeft()) <= 0)
        return rotate(wanted->getValue(), wanted, start, 2);

    if (balance < -1 && bal(wanted->getLeft()) > 0) {
        wanted->setLeft(rotate(wanted->getLeft()->getValue(), wanted->getLeft(), start, 1));
        return rotate(wanted->getValue(), wanted, start, 2);
    }

    if (balance > 1 && bal(wanted->getRight()) >= 0)
        return rotate(wanted->getValue(), wanted, start, 1);

    if (balance > 1 && bal(wanted->getRight()) < 0) {
        wanted->setRight(rotate(wanted->getRight()->getValue(), wanted->getRight(), start, 2));
        return rotate(wanted->getValue(), wanted, start, 1);
    }

    return wanted;
}

void findParentNode(int value, StartNode* start, StartNode* AVLstart) {
    Node * curr = findOtherInAVL(value, AVLstart);
    if (curr == NULL)
        cout << "notfound" << endl;
    else if (curr == start->startNode)
        cout << "noparent" << endl;
    else
        cout << curr->getParent()->getValue() << endl;
}

Node * findBiggerParent(int value, Node * parent) {
    Node * tmp = parent;
    while (tmp) {
        if (tmp->getValue() > value)
            return tmp;
        else
            tmp = tmp->getParent();
    }
    return NULL;
}

Node * findSmallerParent(int value, Node * parent) {
    Node * tmp = parent;
    while (tmp) {
        if (tmp->getValue() < value)
            return tmp;
        else
            tmp = tmp->getParent();
    }
    return NULL;
}

void findSuccessorNode(int value, Node* curr) {
    if (curr == NULL)
        cout << "notfound" << endl;
    else if (curr->getRight() != NULL) {
        Node * succ = findMin(curr->getRight());
        cout << succ->getValue() << endl;
    }//    else if(curr->getParent()->getValue() > curr->getValue())
        //    {
        //    cout<<curr->getParent()->getValue()<<endl;
        //    }
    else if (curr->getParent() != NULL) {
        Node * succ = findBiggerParent(value, curr->getParent());
        if (succ)
            cout << succ->getValue() << endl;
        else
            cout << "nosuccessor" << endl;
    } else
        cout << "nosuccessor" << endl;
}

Node * AVLfindSuccessorNode(int value, Node* curr) {
    if (curr->getRight() != NULL) {
        Node * succ = findMin(curr->getRight());
        return succ;
    }//    else if(curr->getParent()->getValue() > curr->getValue())
        //    {
        //    cout<<curr->getParent()->getValue()<<endl;
        //    }
    else if (curr->getParent() != NULL) {
        Node * succ = findBiggerParent(value, curr->getParent());
        if (succ)
            return succ;
        else
            return NULL;
    } else
        return NULL;
}

Node * AVLfindPredNode(int value, Node* curr) {
    if (curr->getLeft() != NULL) {
        Node * pred = findMax(curr->getLeft());
        return pred;
    }//    else if(curr->getParent()->getValue() > curr->getValue())
        //    {
        //    cout<<curr->getParent()->getValue()<<endl;
        //    }
    else if (curr->getParent() != NULL) {
        Node * pred = findSmallerParent(value, curr->getParent());
        if (pred)
            return pred;
        else
            return NULL;
    } else
        return NULL;
}

void deleteAll(Node * src) {
    if (src->getLeft() != NULL)
        deleteAll(src->getLeft());
    if (src->getRight() != NULL)
        deleteAll(src->getRight());
    delete src;
}

int main(int argc, char** argv) {
    int mode = 0;
    int value = 0;
    int rotDirection = 0;
    //    Node * start = NULL;
    StartNode* start = new StartNode(NULL);
    StartNode* AVLstart = new StartNode(NULL);

    while (1) {
        cin >> mode;
        if (mode == 6)
            break;
        cin >> value;

        switch (mode) {
            case 1:
            {
                if (start->getStart() == NULL) {
                    Node * firstNode = new Node(value, NULL);
                    start->changeStart(firstNode);
                    //firstfirst case
                    if (AVLstart->getStart() == NULL) {
                        Node* AVLfirstNode = new Node(value, NULL);
                        firstNode->setOtherTree(AVLfirstNode);
                        AVLfirstNode->setOtherTree(firstNode);
                        AVLstart->changeStart(AVLfirstNode);
                    }//  
                        //this wont be called, ever
                    else {
                        Node * thereAlredy = findNode(value, AVLstart);
                        if (thereAlredy) {
                            thereAlredy->setOtherTree(firstNode);
                            firstNode->setOtherTree(thereAlredy);
                        } else
                            AVLaddNode(value, AVLstart->getStart(), NULL, firstNode, AVLstart);
                    }
                } else {
                    Node * hello = findNode(value, AVLstart);
                    if (hello) {
                    } else {

                        //                    Node * thereAlredy = NULL;
                        Node * bst = NULL;
                        Node * succORpr = NULL;
                        Node * found = findFromWhich(value, AVLstart);
                        //                    if (found->getValue() == value) {
                        //                        thereAlredy = found;
                        //                        
                        //                    } 
                        if (found->getValue() < value) {
                            if (!found->toOtherTree()->getRight())
                                bst = addNode(value, found->toOtherTree());
                            else {
                                succORpr = AVLfindSuccessorNode(found->getValue(), found);
                                bst = addNode(value, succORpr->toOtherTree());
                            }
                        } else {
                            if (!found->toOtherTree()->getLeft())
                                bst = addNode(value, found->toOtherTree());
                            else {
                                succORpr = AVLfindPredNode(found->getValue(), found);
                                bst = addNode(value, succORpr->toOtherTree());
                            }
                        }

                        //~~~~~~~~~~~~~AVLinsert~~~~~~~~~~
                        //                    if (thereAlredy) {
                        //                        thereAlredy->setOtherTree(bst);
                        //                        bst->setOtherTree(thereAlredy);
                        //                    } else
                        AVLaddNode(value, AVLstart->getStart(), NULL, bst, AVLstart);


                    }
                }
                break;
            }
            case 2:
            {
                if (AVLstart->startNode) {
                    Node * wanted = findOtherInAVL(value, AVLstart);
                    if (wanted) {
                        removeNode(value, start, wanted);
                        AVLremove(AVLstart->startNode, value, AVLstart);
                    }
                }
                break;
            }
            case 3:
            {
                //                cout << "v BVS: ";
                //                findParentNode(value, start);
                //                cout << "v AVL: ";
                findParentNode(value, start, AVLstart);
                break;
            }
            case 4:
            {
                //
                //THIS HAS BEEN ALTERED RECENTLY
                Node * curr = findNode(value, AVLstart);
                findSuccessorNode(value, curr);
                break;
            }
            case 5:
            {
                cin >> rotDirection;
                //                Node * tmp = 
                Node * peak = findOtherInAVL(value, AVLstart);
                rotate(value, peak, start, rotDirection);
                break;
            }
        }

    }
//    if (start != NULL) {
//        if (start->startNode != NULL)
//            deleteAll(start->startNode);
//        delete start;
//    }
//    if (AVLstart != NULL) {
//        if (AVLstart->startNode != NULL)
//            deleteAll(AVLstart->startNode);
//        delete AVLstart;
//    }

    return 0;
}
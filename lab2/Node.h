
#ifndef NODE_H
#define NODE_H

class Node{
public:
	Node();
	int getValue();
	Node* getLeft();
	Node* getRight();
	void setValue(int value);
	void setLeft(Node* left);
	void setRight(Node* right);


private:
	int m_value;
	Node* m_left;
	Node* m_right;
};


#endif

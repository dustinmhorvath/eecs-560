#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

class Node {
public:
	int m_value;
	Node* m_left;
	Node* m_right;

	Node(int value){
		m_value = value;
		m_left = nullptr;
		m_right = nullptr;
	}
};

Node* getNewNode(int value){
	Node* newNode = new Node(value);
	(*newNode).m_value = value;
	newNode -> m_left = nullptr;
	newNode -> m_right = nullptr;
	return newNode;
}

Node* add(int value, Node* root){
	if(!root){
		root = getNewNode(value);
		return root;
	}
	else if(value <= root -> m_value){
		root -> m_left = add(value, root -> m_left);
	}
	else{
		root -> m_right = add(value, root -> m_right);
	}
	return root;
}

void printTreeHelper(Node* subtree){
	if(subtree != nullptr){
		std::cout << subtree -> m_value << " ";
		printTreeHelper(subtree -> m_left);
		printTreeHelper(subtree -> m_right);
	}
}

void printTree(Node* subtree){
	printTreeHelper(subtree);
	std::cout << std::endl;
}

void printTreeLevelOrder(Node* root)
{
	std::queue<Node*> q;
	if (root) {
		q.push(root);
	}
	while (!q.empty())
	{
		const Node * const temp_node = q.front();
		q.pop();
		std::cout << temp_node -> m_value << " " ;
		if (temp_node -> m_left) {
			q.push(temp_node -> m_left);
		}
		if (temp_node -> m_right) {
			q.push(temp_node -> m_right);
		}
	}
	std::cout << std::endl;
}
int main(int argc, char* argv[]){
	Node* tree = nullptr;

        int size = 10;

        int arr[size];

	std::ifstream file("data2.txt");
        std::string line;

	while(std::getline(file, line)){
		std::stringstream  lineStream(line);
		int value;
		int index = 0;
                while(lineStream >> value){
			arr[index] = value;
			index++;
		}
	}

	for(int i = 0; i < size; i++){
		tree = add(arr[i], tree);
	}

	printTree(tree);
	printTreeLevelOrder(tree);

	std::cout << "Exiting...\n";

	
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

void printTree(Node* subTree){
	if(subTree != nullptr){
		std::cout << subTree -> m_value << " ";
		printTree(subTree -> m_left);
		printTree(subTree -> m_right);
	}
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
		std::cout << arr[i] << " ";
		tree = add(arr[i], tree);
	}

	printTree(tree);

	std::cout << "Exiting...\n";
}

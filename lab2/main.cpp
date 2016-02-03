
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

class Node {
    public:
        int m_height;
	int m_value;
        Node* m_left;
	Node* m_right;

	Node(){
            m_left = nullptr;
            m_right = nullptr;
            m_value = 0;
            m_height = 0;
        }

        Node(int n){
            m_left = nullptr;
            m_right = nullptr;
            m_value = n;
            m_height = 0;
        }
};

class BinarySearchTree {
    private:
        Node* m_root;
    public:
         BinarySearchTree(){
             m_root = nullptr;
         }

         bool isEmpty(){
             return m_root == nullptr;
         }

         void insert(int m_value){
             m_root = insert(m_value, m_root);
         }

         int height(Node* node){
		if(!node){
			return -1;
		}
		else{
			return node -> m_height;
		}
         }

         int max(int lhs, int rhs){
		if(lhs > rhs){
			return lhs;
		}
		else {
			return rhs;
		}
         }

         Node* insert(int value, Node* node){
             if (!node){
                 node = new Node(value);
		}
             else if (value < node -> m_value){
                 node -> m_left = insert(value, node -> m_left);
                 if (height(node -> m_left) - height(node -> m_right) == 2){
                     if (value < node -> m_left -> m_value){
                         node = rotateWithLeftChild(node);
			}
                     else{
                         node = doubleWithLeftChild(node);
			}
		}
             }
             else if (value > node -> m_value){
                 node -> m_right = insert(value, node -> m_right);
                 if (height(node -> m_right) - height(node -> m_left) == 2){
                     if (value > node -> m_right -> m_value){
                         node = rotateWithRightChild(node);
			}
                     else{
                         node = doubleWithRightChild(node);
			}
		}
             }
             node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
             return node;
         }

         Node* rotateWithLeftChild(Node* node){
             Node* temp = node->m_left;
             node -> m_left = temp -> m_right;
             temp -> m_right = node;
             node -> m_height = max(height(node->m_left), height(node->m_right)) + 1;
             temp -> m_height = max(height(temp->m_left), node->m_height) + 1;
             return temp;
         }

         Node* rotateWithRightChild(Node* node){
             Node* temp = node->m_right;
             node -> m_right = temp->m_left;
             temp -> m_left = node;
             node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
             temp -> m_height = max(height(temp -> m_right), node -> m_height) + 1;
             return temp;
         }

         Node *doubleWithLeftChild(Node* k3){
             k3->m_left = rotateWithRightChild(k3->m_left);
             return rotateWithLeftChild(k3);
         }

         Node *doubleWithRightChild(Node* node){
             node->m_right = rotateWithLeftChild(node->m_right);
             return rotateWithRightChild(node);
         }

	void preOrderHelper(Node* subtree){
	        if(subtree != nullptr){
        	        std::cout << subtree -> m_value << " ";
	                preOrderHelper(subtree -> m_left);
                	preOrderHelper(subtree -> m_right);
        	}
	}

	void printPreOrder(){
	        preOrderHelper(m_root);
        	std::cout << std::endl;
	}

	void printLevelOrder()
	{
        	std::queue<Node*> q;
	        if (m_root) {
        	        q.push(m_root);
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
};

int main()
{
	BinarySearchTree tree;

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
                tree.insert(arr[i]);
        }

        tree.printPreOrder();
        tree.printLevelOrder();

        std::cout << "Exiting...\n";



    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BinarySearchTree.h"

int main(int argc, char* argv[]){
	BinarySearchTree tree = BinarySearchTree();

	std::ifstream file("data2.txt");
        std::string line;

        while(std::getline(file, line)){
                std::stringstream  lineStream(line);
                int value;
                // Read an integer at a time from the line
                while(lineStream >> value){
                        tree.add(value);
                }
        }

	tree.printTree();
	tree.search(4);

	std::cout << "Exiting...\n";
}

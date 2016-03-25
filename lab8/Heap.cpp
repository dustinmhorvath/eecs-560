/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Heap.h"
#include <iostream>
#include <math.h>


Heap::Heap() {
    m_array = nullptr;
    m_size = 0;
}

Heap::Heap(int* arr, int size) {
    m_array = arr;
    m_size = size;
    buildHeap();
}

void Heap::buildHeap() {
    int index = (m_size - 1) / 2;
    for (int i = index; i >= 0; i--) {
        TrickleDown(i);
    }
}

Heap::~Heap() {
    delete m_array;
    m_array = nullptr;
}

void Heap::BubbleUp(int i) {
    int index = (int) floor(log2(i + 1)) % 2;
    int parent = floor((i - 1) / 2);
    if (index == 0) //i is on the min level
    {
        if (m_array[i] > m_array[parent]) {
            swap(i, parent);
            BubbleUpMax(parent);
        } else {
            BubbleUpMin(i);
        }
    } else //i is on the max level
    {
        if (m_array[i] < m_array[parent]) {
            swap(i, parent);
            BubbleUpMin(parent);
        } else {
            BubbleUpMax(i);
        }
    }
}

void Heap::BubbleUpMin(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0 || parent == 1) // have a grand parent
    {
        if (m_array[i] < m_array[grandparent]) {
            swap(i, grandparent);
            BubbleUpMin(grandparent);
        }
    }
}

void Heap::BubbleUpMax(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0) // have a grand parent
    {
        if (m_array[i] > m_array[grandparent]) {
            swap(i, grandparent);
            BubbleUpMax(grandparent);
        }
    }
}

void Heap::TrickleDown(int i) {
    int index = (int) floor(log2(i + 1)) % 2;
    if (index == 0) //i is on the min level
    {
        TrickleDownMin(i);
    } else //i is on the max level
    {
        TrickleDownMax(i);
    }
}

void Heap::TrickleDownMin(int i) {
    if (m_array[2 * i + 1] != 0) //if m_array[i] has children
    {
        int firstchildrenPos = 2 * i + 1;
        int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

        int m = smallestIndex(i); //find the index of the smallest node
        int parent = floor((m - 1) / 2);
        if (m >= firstgrandchildrenPos) //m_array[m] is a grandchild
        {
            if (m_array[m] < m_array[i]) {
                swap(m, i);
                if (m_array[m] > m_array[parent]) {
                    swap(m, parent);
                }
                TrickleDownMin(m);
            }
        } else //m_array[m] is a child
        {
            if (m_array[m] < m_array[i])
                swap(m, i);
        }
    }
}

void Heap::TrickleDownMax(int i) {
    if (m_array[2 * i + 1] != 0) //if m_array[i] has children
    {
        int firstchildrenPos = 2 * i + 1;
        int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

        int m = biggestIndex(i); //find the index of the smallest node
        int parent = floor((m - 1) / 2);
        if (m >= firstgrandchildrenPos) //m_array[m] is a grandchild
        {
            if (m_array[m] > m_array[i]) {
                swap(m, i);
                if (m_array[m] < m_array[parent]) {
                    swap(m, parent);
                }
                TrickleDownMin(m);
            }
        } else //m_array[m] is a child
        {
            if (m_array[m] > m_array[i])
                swap(m, i);
        }
    }
}

void Heap::insert(int val) {
    if(m_array == nullptr) {
	int* temp = new int[2000];
	m_array = temp;
    }
    if (val > 0) {
       	m_size++;
        m_array[m_size - 1] = val;
        BubbleUp(m_size - 1);
    } else {
        std::cout << "invalid input" << "\n";
    }
}

void Heap::deletemin() {
    if (m_size != 0) {
        m_array[0] = m_array[m_size - 1];
        m_array[m_size - 1] = 0;
        m_size--;
        TrickleDown(0);
    } else {
        std::cout << "Heap Empty" << "\n";
    }
}

void Heap::deletemax() {
    //compare which index has the biggest value
    if (m_array[1] > m_array[2]) {
        m_array[1] = m_array[m_size - 1];
        m_array[m_size - 1] = 0;
        m_size--;
        TrickleDown(1);
    } else {
        m_array[2] = m_array[m_size - 1];
        m_array[m_size - 1] = 0;
        m_size--;
        TrickleDown(2);
    }
}

void Heap::levelorder() {
    if (m_size != 0) {
        std::cout << "Level order: " << "\n";
        int height = 0;
        int size = m_size;
        while (size > pow(2, height)) {
            size - pow(2, height);
            height++;
        }
        int index = 0;
        for (int i = 0; i <= height; i++) {
            for (int j = 0; j < pow(2, i); j++) {
                if (m_array[index] != 0) {

                    std::cout << m_array[index] << " ";
                    index++;
                } else {
                    break;
                }
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Heap empty " << "\n";
    }
}

void Heap::swap(int pos1, int pos2) {
    int temp = m_array[pos1];
    m_array[pos1] = m_array[pos2];
    m_array[pos2] = temp;
}

int Heap::smallestIndex(int i) {
    int smallestindex = 0;
    int lastchildrenPos = 2 * i + 2;
    int lastgrandchildrenPos = 2 * (2 * i + 2) + 2;

    if ((m_size - 1 <= lastchildrenPos) || m_size - 1 <= lastgrandchildrenPos - 4) //if m_array[i] has no grandchildren
    {
        if (m_size - 1 < lastchildrenPos) //has only one child
        {
            smallestindex = m_size - 1;
        }
        else //has two children
        {
            if (m_array[lastchildrenPos - 1] > m_array[lastchildrenPos]) {
                smallestindex = lastchildrenPos;
            } else {
                smallestindex = lastchildrenPos - 1;
            }
        }
        return smallestindex;
    }
    if ((m_size - 1 <= lastgrandchildrenPos) && (m_size - 1 > lastgrandchildrenPos - 4)) //if m_array[i] has grandchildren
    {
        //find the smallest node among all the children and grandchildren
        if (m_array[lastchildrenPos - 1] > m_array[lastchildrenPos]) {
            smallestindex = lastchildrenPos;
        } else {
            smallestindex = lastchildrenPos - 1;
        }
        for (int i = lastgrandchildrenPos - 3; i <= m_size - 1; i++) {
            if (m_array[i] < m_array[smallestindex]) {
                smallestindex = i;
            }
        }
        return smallestindex;
    }
    if (m_size - 1 > lastgrandchildrenPos) {
        //find the smallest node among all the children and grandchildren
        if (m_array[lastchildrenPos - 1] > m_array[lastchildrenPos]) {
            smallestindex = lastchildrenPos;
        } else {
            smallestindex = lastchildrenPos - 1;
        }
        for (int i = lastgrandchildrenPos - 3; i <= lastgrandchildrenPos; i++) {
            if (m_array[i] < m_array[smallestindex]) {
                smallestindex = i;
            }
        }
        return smallestindex;
    }
}

int Heap::biggestIndex(int i) {
    int biggestIndex = 0;
    int lastchildrenPos = 2 * i + 2;
    int lastgrandchildrenPos = 2 * (2 * i + 2) + 2;

    if ((m_size - 1 <= lastchildrenPos) || m_size - 1 <= lastgrandchildrenPos - 4) //if m_array[i] has no grandchildren
    {
        if (m_size - 1 < lastchildrenPos) //has only one child
        {
            biggestIndex = m_size - 1;
        }
        else //has two children
        {
            if (m_array[lastchildrenPos - 1] < m_array[lastchildrenPos]) {
                biggestIndex = lastchildrenPos;
            } else {
                biggestIndex = lastchildrenPos - 1;
            }
        }
        return biggestIndex;
    }
    if ((m_size - 1 <= lastgrandchildrenPos) && (m_size - 1 > lastgrandchildrenPos - 4)) //if m_array[i] has grandchildren
    {
        //find the biggest node among all the children and grandchildren
        if (m_array[lastchildrenPos - 1] < m_array[lastchildrenPos]) {
            biggestIndex = lastchildrenPos;
        } else {
            biggestIndex = lastchildrenPos - 1;
        }
        for (int i = lastgrandchildrenPos - 3; i <= m_size - 1; i++) {
            if (m_array[i] > m_array[biggestIndex]) {
                biggestIndex = i;
            }
        }
        return biggestIndex;
    }
    if (m_size - 1 > lastgrandchildrenPos) {
        //find the biggest node among all the children and grandchildren
        if (m_array[lastchildrenPos - 1] < m_array[lastchildrenPos]) {
            biggestIndex = lastchildrenPos;
        } else {
            biggestIndex = lastchildrenPos - 1;
        }
        for (int i = lastgrandchildrenPos - 3; i <= lastgrandchildrenPos; i++) {
            if (m_array[i] > m_array[biggestIndex]) {
                biggestIndex = i;
            }
        }
        return biggestIndex;
    }
}

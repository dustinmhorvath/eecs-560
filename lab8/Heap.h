/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Heap.h
 * Author: nicholas roudebush
 * EECS 560 Lab 8 Min-Max Heap
 * Created on March 21, 2016, 10:21 PM
 */

#ifndef HEAP_H
#define HEAP_H

class Heap {
public:
    Heap();
    Heap(int* arr, int size);
    ~Heap();
    void buildHeap();
    void BubbleUp(int i);
    void BubbleUpMin(int i);
    void BubbleUpMax(int i);
    void TrickleDown(int i);
    void TrickleDownMin(int i);
    void TrickleDownMax(int i);
    void insert(int val);
    void deletemin();
    void deletemax();
    void levelorder();

private:
    int* m_array;
    int m_size;
    void swap(int pos1, int pos2);
    int smallestIndex(int i);
    int biggestIndex(int i);
};


#endif /* HEAP_H */


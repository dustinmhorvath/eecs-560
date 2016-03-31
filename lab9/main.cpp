/*
 * Dustin Horvath
 * MINMAXHEAP VS MINHEAP WWF THROWDOWN
 * ONE ENTERS ONLY ONE WILL LEAVE
 *
 *
 */

#include <iostream>
#include <math.h>

#define SIZE 2000

//void generate(int size, int*& arr){
int* generate(int size, int lower, int upper){
  // Allocate arrays for heap and sorted list.
  int* arr = new int[size+1];

  // Store a magic number in index 0.
  arr[0] = -1111;

  std::cout << "Generating " << size << " random values.\n";
  int floor = lower;
  int ceiling = upper;
  int range = (ceiling - floor);

  for(int i = 1; i <= size; i++){
    arr[i] = floor + ( std::rand() % ( ceiling - floor + 1 ) );
  }
  return arr;

}

class MinMaxHeap{

public:
  int* arr;
  int m_length;

  MinMaxHeap(int size, int* unsortedarray){
    arr = unsortedarray;
    m_length = size;

    buildHeap();
  }

  ~MinMaxHeap() {
    delete arr;
  }

  void buildHeap() {
    int start = (m_length - 1) / 2;
    for (int i = start; i >= 0; i--) {
      trickleDown(i);
    }
  }

  bool checkArr(int value, int start, int end){
    for(int i = start; i < end; i++){
      if(arr[i] == value){
        return true;
      }
    }
    return false;

  }


  void swap(int x, int y) {
    int temp = arr[y];
    arr[y] = arr[x];
    arr[x] = temp;
  }

  void trickleUp(int i) {
    int parentIndex = floor((i - 1) / 2);
    int index = (int) floor(log2(i + 1)) % 2;
    // index=0 on min level
    if (index == 0){ 
      if (arr[i] > arr[parentIndex]) {
        swap(i, parentIndex);
        trickleUpMax(parentIndex);
      } 
      else {
        trickleUpMin(i);
      }
    } 
    // index=1 on max level
    else{ 
      if (arr[i] < arr[parentIndex]) {
        swap(i, parentIndex);
        trickleUpMin(parentIndex);
      }
      else {
        trickleUpMax(i);
      }
    }
  }

  void trickleUpMax(int i) {
    int parentIndex = floor((i - 1) / 2);
    int grandparent = floor((parentIndex - 1) / 2);
    if (grandparent != 0){ // have a grand parent
      if (arr[i] > arr[grandparent]) {
        swap(i, grandparent);
        trickleUpMax(grandparent);
      }
    }
  }

  void trickleUpMin(int i) {
    int parentIndex = floor((i - 1) / 2);
    int grandparent = floor((parentIndex - 1) / 2);
    if (grandparent != 0 || parentIndex == 1){ // have a grand parent
      if (arr[i] < arr[grandparent]) {
        swap(i, grandparent);
        trickleUpMin(grandparent);
      }
    }
  }

  void trickleDown(int i) {
    // expression confirmed producing correct values
    int index = (int) floor(log2(i + 1)) % 2;
    // i=0 for min level
    if (index == 0){
      int temp = trickleDownToMinLevel(i);
      temp = trickleDownToMinLevel(temp);
    }
    // i=1 for max level
    else{
      int temp = trickleDownToMaxLevel(i);
      temp = trickleDownToMaxLevel(temp);

    }
  }

  int trickleDownToMinLevel(int i) {
    // arr[i] is not leaf
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      // gets the smallest node
      int m = getSmallestIndex(i);
      int parentIndex = floor((m - 1) / 2);


      // if m is a grandchild
      if (m >= firstgrandchildrenPos){
        if (arr[m] < arr[i]) {
          swap(m, i);
          if (arr[m] > arr[parentIndex]) {
            swap(m, parentIndex);
          }
          trickleDownToMinLevel(m);
        }
      } 



      // else m is a child
      else{
        if (arr[m] < arr[i]){
          swap(m, i);
        }
      }
      // return last index evaluated
      return m;
    }
    return i;
  }

  int trickleDownToMaxLevel(int i) {
    // i is not leaf
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      // gets smallest node
      int m = getLargestIndex(i);
      int parentIndex = floor((m - 1) / 2);


      // m is a grandchild
      if (m >= firstgrandchildrenPos){
        if (arr[m] > arr[i]) {
          swap(m, i);
          if (arr[m] < arr[parentIndex]) {
            swap(m, parentIndex);
          }
          trickleDownToMinLevel(m);
        }
      }


      // else m is a child
      else{
        if (arr[m] > arr[i])
          swap(m, i);
      }
      return m;
    }
    return i;
  }

  void insert(int val) {
    if(arr == nullptr) {
      int* temp = new int[SIZE];
      arr = temp;
    }
    if (val > 0) {
      m_length++;

      arr[m_length - 1] = val;
      trickleUp(m_length - 1);
    }
    else {
      std::cout << "Cannot insert bad value" << "\n";
    }
  }

  int deleteMin() {
    int temp;
    if (m_length != 0) {
      // swap last value into root
      temp = arr[0];
      arr[0] = arr[m_length - 1];
      // shorten arr
      arr[m_length - 1] = 0;
      m_length--;
      // push the new root down to proper position
      trickleDown(0);
      std::cout << "Deleted min " << temp << ".\n";
      return temp;
    }
    else {
      std::cout << "Heap is empty" << "\n";
      return 0;
    }
  }

  int deleteMax() {
    if(m_length > 0){
      //compare which root child has the biggest value
      if (arr[1] > arr[2]) {
        int temp = arr[1];
        // swap from end
        arr[1] = arr[m_length - 1];
        // shorten
        arr[m_length - 1] = 0;
        m_length--;
        // push down to proper location
        trickleDown(1);
        std::cout << "Deleted max " << temp << ".\n";
        return temp;
      }
      else {
        int temp = arr[2];
        arr[2] = arr[m_length - 1];
        arr[m_length - 1] = 0;
        m_length--;
        trickleDown(2);
        std::cout << "Deleted max " << temp << ".\n";
        return temp;
      }
    }
    else {
      std::cout << "Heap is empty" << "\n";
      return 0;
    }
  }

  void printArr(){
    for(int i = 0; i < m_length; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  void levelorder(){
    if (m_length > 0) {
      std::cout << "Printing level order..." << "\n";
      int size = m_length;
      int height = 0;
      while (size > pow(2, height)) {
        size - pow(2, height);
        height++;
      }
      int index = 0;
      for (int i = 0; i <= height; i++) {
        for (int j = 0; j < pow(2, i); j++) {

          if (arr[index] != 0) {

            std::cout << arr[index] << " ";
            index++;
          }
        }

        std::cout << "\n";
      }
    }
    else {
      std::cout << "No elements in heap\n";
    }
  }


  int getSmallestIndex(int i) {
    int lastChild = 2*i+2;
    int lastGrandchild = 2*(2*i+2)+2;

    int index = 0;
    // index has no grandchildren
    if ((m_length - 1 <= lastChild) || m_length - 1 <= lastGrandchild - 4){
      // only one child
      if (m_length - 1 < lastChild){
        index = m_length - 1;
      }
      // has children in both positions
      else{
        if (arr[lastChild - 1] > arr[lastChild]) {
          index = lastChild;
        }
        else {
          index = lastChild - 1;
        }
      }
      return index;
    }
    // index has values in grandchildren
    if ( (m_length - 1 <= lastGrandchild) && (m_length - 1 > lastGrandchild - 4) ){
      //find the smallest node among all the children and grandchildren
      if (arr[lastChild - 1] > arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= m_length - 1; i++) {
        if (arr[i] < arr[index]) {
          index = i;
        }
      }
      return index;
    }
    if (m_length - 1 > lastGrandchild) {
      //find the smallest node among all the children and grandchildren
      if (arr[lastChild - 1] > arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= lastGrandchild; i++) {
        if (arr[i] < arr[index]) {
          index = i;
        }
      }
      return index;
    }
  }

  int getLargestIndex(int i) {
    int lastChild = 2*i+2;
    int lastGrandchild = 2*(2*i+2)+2;

    int index = 0;
    if ((m_length - 1 <= lastChild) || m_length - 1 <= lastGrandchild - 4){
      // only one child
      if (m_length - 1 < lastChild){
        index = m_length - 1;
      }
      // two children
      else{
        if (arr[lastChild - 1] < arr[lastChild]) {
          index = lastChild;
        }
        else {
          index = lastChild - 1;
        }
      }
      return index;
    }
    // index has grandchildren
    if ((m_length - 1 <= lastGrandchild) && (m_length - 1 > lastGrandchild - 4)){
      //find the biggest node among all the children and grandchildren
      if (arr[lastChild - 1] < arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= m_length - 1; i++) {
        if (arr[i] > arr[index]) {
          index = i;
        }
      }
      return index;
    }
    if (m_length - 1 > lastGrandchild) {
      //find the biggest node among all the children and grandchildren
      if (arr[lastChild - 1] < arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= lastGrandchild; i++) {
        if (arr[i] > arr[index]) {
          index = i;
        }
      }
      return index;
    }
  }

};

class MinHeap{

  int *arr;
  int *sorted;
  int arrLength;
  int sortedLength;

public:

  MinHeap(int size, int* unsortedarray){
    arr = new int[size+1];
    for(int i = 0; i <= size; i++){
      arr[i] = unsortedarray[i];
    }
    arrLength = size;
    sortedLength = 0;
    sorted = new int[size+1];
    buildHeap();
  }

  ~MinHeap(){
    delete [] arr;
    delete [] sorted;
  }


  void buildHeap(){
    //std::cout << "Building heap...\n";

    for(int i = floor(arrLength/2); i > 0; i--){
      push_down(i);
    }
  }


  void push_down(int i){
    // moves an item down the heap until the correct spot for it is found
    // The item being moved down the heap starts in position i
    int val = arr[i];
    int position = i;
    bool cont = true;
    while( cont ){
      int k;
      if(arr[2*position] > arr[2*position + 1] && 2*position + 1 <= arrLength){
        k = 2*position + 1;
      }
      else if(2*position <= arrLength){
        k = 2*position;
      }
      else{
        arr[position] = val;
        cont = false;
      }

      if(val > arr[k]){
        arr[position] = arr[k];
        position = k;
      }
      else{
        arr[position] = val;
        cont = false;
      }

    }
  }

  void deleteMin(){
    if(arrLength == 0){
      return;
    }

    // Grab copy of top, replace with last
    int temp = arr[1];
    arr[1] = arr[arrLength];
    arrLength--;

    // Store the front into a new sorted array.
    sortedLength++;
    sorted[sortedLength] = temp;

    push_down(1);
  }

  void heapSort(){
    sortedLength = 0;


    std::cout << "Running heapsort...\n";
    // Keep popping off front and downheaping until the array is gone
    while(arrLength > 0){
      deleteMin();
    }

  }

  // Verify function was tested by manually adding very high values to the
  // start of the heap and attempting to verify. Returned failure with bad
  // value.
  bool verifyHeap(){
    if(arrLength == 0){
      std::cout << "No heap to print\n.";
      return false;
    }
    bool verified = true;
    std::cout << "Verifying heap...";
    // Needs equals here? 
    // Nah, last one will be implied correct after checking all the others.
    for(int i = 1; i < arrLength; i++){
      if( (arr[2*i + 1] < arr[i] && 2*i+1 <= arrLength ) ||
          (arr[2*i] < arr[i] && 2*i <= arrLength)  ){
        verified = false;
      }
    }
    if(verified){
      std::cout << "SUCCESS: Heap is built in MinHeap order.\n";
    }
    else{
      std::cout << "FAIL: Heap was not built in MinHeap order.\n";
    }
    return verified;
  }

  bool verifySorted(){
    bool verified = true;
    std::cout << "Verifying sorted list...";
    if(sortedLength == 0){
      std::cout << "No sorted array to print.\n";
      return false;
    }
    for(int i = 1; i < sortedLength; i++){
      if(sorted[i] > sorted[i+1]){
        verified = false;
      }
    }
    if(verified){
      std::cout << "SUCCESS: Sorted array verified in order.\n";
    }
    else{
      std::cout << "FAIL: Sorted array is not in order.\n";
    }
    return verified;
  }

  void printHeap(){
    if(arrLength > 0){
      for(int i = 1; i <= arrLength; i++){
        std::cout << arr[i] << " ";
      }
    }
    else{
      std::cout << "No heap to print.";
    }
    std::cout << "\n";
  }

  void printSorted(){
    if(sortedLength > 0){
      for(int i = 1; i <= sortedLength; i++){
        std::cout << sorted[i] << " ";
      }
    }
    else{
      std::cout << "No array to print.";
    }
    std::cout << "\n";
  }


};


int main(){

  int seed = 0;
  srand (seed);

  int sizes[] = {100000, 200000, 400000};
  int numsizes = sizeof(sizes)/sizeof(*sizes);
  
  clock_t t0, t1;

  for(int trial = 0; trial < numsizes; trial++){

    t0 = clock();

    int* arr = generate(sizes[trial], -sizes[trial], sizes[trial]);
    int* arr2 = new int[sizes[trial]];

    for(int i = 0; i < sizes[trial]; i++){
      arr2[i] = arr[i+1];
    }

    /*for(int i = 0; i <= sizes[trial]; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    for(int i = 0; i < sizes[trial]; i++){
      std::cout << arr2[i] << " ";
    }
    std::cout << "\n";
    */

    MinMaxHeap minmaxheap = MinMaxHeap(sizes[trial], arr2);
    MinHeap minheap = MinHeap(sizes[trial], arr);

    //minmaxheap.levelorder();
    //minheap.printHeap();

    std::cout << clock()-t0 << "\n";
  }

}


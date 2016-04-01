/*
 * Dustin Horvath
 * MINMAXHEAP VS MINHEAP WWF THROWDOWN
 * ONE ENTERS ONLY ONE WILL LEAVE
 *
 *
 */

#include <iostream>
#include <math.h>
#include <iomanip>

#define SIZE 500000

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

class MinMaxHeap2{
public:
  int* arr;
  int m_length;

  MinMaxHeap2(int *array, int cSize){
    arr = new int[cSize + 1000];
    for(int i = 0; i < cSize; i++){
      arr[i] = array[i];
    }
    m_length = cSize;
    //buildHeap();
  }

  ~MinMaxHeap2(){
    delete [] arr;
  }

  int GetMaxGrandChild(int pos){
    bool maxValInit = false;
    int maxVal;
    int maxIndex = pos;
    int curIndex;

    /* Get a grandchild */
    curIndex = 2*(2*pos);

    /* Check for valid position */
    if (curIndex <= m_length){
      /* Check if maxVal isn't initialized or 
       * current index is greater than maxVal
       */
      if ((!maxValInit) || (curIndex > maxVal)) {
        maxIndex = curIndex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    /* Get the other grandchild */
    curIndex = 2*((2*pos)+1);
    if (curIndex <= m_length){
      if ((!maxValInit) || (curIndex > maxVal)){
        maxIndex = curIndex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    curIndex = 2*(2*pos)+1;
    if (curIndex <= m_length){
      if ((!maxValInit) || (curIndex > maxVal)){
        maxIndex = curIndex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    curIndex = (2*((2*pos)+1))+1;
    if (curIndex <= m_length){
      if ((!maxValInit) || (curIndex > maxVal)){
        maxIndex = curIndex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }
    return maxIndex;
  }

  /* Returns the position of the minimum */

  int GetMinGrandChild(int pos){
    bool maxValInit = false;
    int minVal;
    int minIdx = pos;
    int curIndex;

    curIndex = 2*(2*pos);
    if (curIndex <= m_length){
      if ((!maxValInit) || (curIndex < minVal)){
        minIdx = curIndex;
        minVal = minIdx;
        maxValInit = true;
      }
    }

    curIndex = 2*((2*pos)+1);
    if (curIndex <= m_length){
      if ((!maxValInit) || (curIndex < minVal))
      {
        minIdx = curIndex;
        minVal = minIdx;
        maxValInit = true;
      }
    }

    curIndex = 2*(2*pos)+1;
    if (curIndex <= m_length)
    {
      if ((!maxValInit) || (curIndex<minVal))
      {
        minIdx = curIndex;
        minVal = minIdx;
        maxValInit = true;
      }
    }

    curIndex = (2*((2*pos)+1))+1;
    if (curIndex <= m_length)
    {
      if ((!maxValInit) || (curIndex < minVal))
      {
        minIdx = curIndex;
        minVal = minIdx;
        maxValInit = true;
      }
    }
    return minIdx;
  }


  int getLargestDes(int pos)
  {
    bool maxValInit = false;
    int maxVal;
    int maxIndex = pos;
    int curIndex;

    maxIndex = GetMaxGrandChild(pos);
    if (maxIndex != pos)
    {
      maxVal = maxIndex;
      maxValInit = false;
    }

    curIndex = 2*pos;
    if ((curIndex <= m_length)&&(isLeafPos(curIndex)))
    {
      if ((!maxValInit)||(curIndex > maxVal))
      {
        maxIndex = curIndex;
        maxVal = curIndex;
        maxValInit = true;
      }
    }

    curIndex = (2*pos)+1;
    if ((curIndex <= m_length)&&(isLeafPos(curIndex)))
    {
      if ((!maxValInit)||(curIndex > maxVal))
      {
        maxIndex = curIndex;
        maxVal = curIndex;
        maxValInit = true;
      }
    }
    return maxIndex;
  }

  /* Returns the minimum element of a position. */

  int GetMinDescendant(int pos) // opposite of getLargestDes Idx
  {
    bool maxValInit = false;
    int minVal;
    int minIdx = pos;
    int curIndex;

    minIdx = GetMinGrandChild(pos);
    if (minIdx != pos)
    {
      minVal = minIdx;
      maxValInit = true;
    }

    curIndex = 2*pos;
    if ((curIndex <= m_length)&&(isLeafPos(curIndex)))
    {
      if ((!maxValInit)||(curIndex < minVal))
      {
        minIdx = curIndex;
        minVal = curIndex;
        maxValInit = true;
      }
    }

    curIndex = (2*pos)+1;
    if ((curIndex <= m_length)&&(isLeafPos(curIndex)))
    {
      if ((!maxValInit)||(curIndex < minVal))
      {
        minIdx = curIndex;
        minVal = curIndex;
        maxValInit = true;
      }
    }
    return minIdx;
  }

  /* Perculates down maximum levels until a position is in its correct location. 
  */

  bool isLeafPos(int pos)
  {
    bool isLeaf = false;
    if ((2*pos > m_length) && ((2*pos)+1 > m_length)){
      isLeaf = true;
    }
    return isLeaf;
  }


  /* Builds the Min-Max Heap Tree. */

  void buildHeap(){
    for ( int i = m_length/2; i >= 0; i--){
      trickleDown(i);
    }
  }

  /* Determines the level of a position and percolates it down maximum if level 
   * * is max and percolates down minimum if level is min.
   */

  void trickleDown(const int pos){
    if (isMaxLevel(pos)){
      trickleDownToMaxLevel( pos );
    }
    else{
      trickleDownToMinLevel( pos );
    }
  }

  void trickleDownToMinLevel(const int pos){
    /* Find the smallest child/grandchild position */
    int minPos = GetMinDescendant(pos);

    /* Check if we have a child */
    if (minPos > 0) 
    {
      /* Check if minimum is a grandchild */
      if (minPos >= pos * 4) 
      {
        /* Swap if less than grandparent */
        if (minPos < pos) 
        {
          swap(pos, minPos);

          /* Swap if greater than parent */
          if (minPos > minPos/2){
            swap(minPos, minPos/2);
          }
          trickleDownToMinLevel( minPos );
        }
      }
      /* We don't have a grandchild */
      else 
      {
        /* Swap if less than parent */
        if (minPos < pos){
          swap(pos, minPos);
        }
      }
    }
  }

  void trickleDownToMaxLevel( int pos ){
    // Returns index of largest descendent
    int maxPos = getLargestDes(pos);

    /* Check if we have a child */
    if (maxPos > 0) {
      /* Check if position is a grandchild */
      if (maxPos >= pos * 4) {
        /* Swap if greater than grandparent */
        if (maxPos > pos) {
          swap(pos, maxPos);

          /* Swap if less than parent */
          if (maxPos < maxPos/2){
            swap(maxPos, maxPos/2);
          }
          trickleDownToMaxLevel( maxPos );
        }
      }
      /* Position is a child */
      else {
        // swap into correct order
        if (maxPos > pos){
          swap(pos, maxPos);
        }
      }
    }
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
      //std::cout << "Deleted min " << temp << ".\n";
      return temp;
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

  void insert(int val) {
    if(arr == nullptr) {
      int* temp = new int[m_length + 1];
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

  bool isMaxLevel(int pos){
    return (int) (log(pos+1.0)/log(2.0))%2 == 1;
  }

  void swap(int a, int b)
  {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
  }


};


class MinMaxHeap{

public:
  int* arr;
  int m_length;

  MinMaxHeap(int size, int* unsortedarray){
    arr = new int[size];
    for(int i = 0; i < size; i++){
      arr[i] = unsortedarray[i];
    }
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
    int index = (int) (log(i+1.0)/log(2.0))%2;
    // i=0 for min level
    if (index == 0){
      int temp = trickleDownToMinLevel(i);
      //temp = trickleDownToMinLevel(temp);
    }
    // i=1 for max level
    else{
      int temp = trickleDownToMaxLevel(i);
      //temp = trickleDownToMaxLevel(temp);

    }
  }

  int trickleDownToMinLevel(int i) {
    // arr[i] is not leaf
    if (arr[2*i+1] != 0 && 2*i+1 < m_length ){
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
    if (arr[2*i+1] != 0 && 2*i+1 < m_length){
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
    //buildHeap();
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

  void insert(int val) {
    if(arr == nullptr) {
      int* temp = new int[arrLength + 1];
      arr = temp;
    }
    arrLength++;

    arr[arrLength] = val;
    trickleUp(arrLength);
  
  }

  void trickleUp(int index){
    int parentIndex = (int) floor((index - 1)  / 2);

    while(arr[parentIndex] > arr[index]){
      int temp = arr[parentIndex];
      arr[parentIndex] = arr[index];
      arr[index] = temp;
      
      index = parentIndex;
      parentIndex = (int) floor((index - 1)  / 2);
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
  int numtrials = 8;
  int numsizes = sizeof(sizes)/sizeof(*sizes);
  int minBuildHeapResults[numsizes][numtrials]; 
  int minMaxBuildHeapResults[numsizes][numtrials]; 
  int minMaxCoinOpResults[numsizes][numtrials]; 
  int minCoinOpResults[numsizes][numtrials]; 
  int kResults[numsizes][numtrials]; 

  clock_t t0, t1;

  for(int sizerun = 0; sizerun < numsizes; sizerun++){
    for(int trial = 0; trial < numtrials; trial++){

      int* arr = generate(sizes[sizerun], -sizes[sizerun], sizes[sizerun]);
      int* arr2 = new int[sizes[sizerun]];

      for(int i = 0; i < sizes[sizerun]; i++){
        arr2[i] = arr[i+1];
      }


      MinMaxHeap2 minmaxheap = MinMaxHeap2(arr2, sizes[sizerun]);
      MinHeap minheap = MinHeap(sizes[sizerun], arr);
  
      t0 = clock();
      // Modified constructors for explicit buildheap calls for the timing
      minmaxheap.buildHeap();
      minMaxBuildHeapResults[sizerun][trial] = (int)(clock()-t0);

      t0 = clock();
      minheap.buildHeap();
      minBuildHeapResults[sizerun][trial] = (int)(clock()-t0);
      
      int floor = 1;
      int ceiling = 50000;
      int ops = floor + ( std::rand() % ( ceiling - floor + 1 ) );
      minMaxCoinOpResults[sizerun][trial] = 0;
      minCoinOpResults[sizerun][trial] = 0;
      for(int op = 0; op < ops; op++){
        int coin = (double)rand() / RAND_MAX;
        if(coin < 0.5){
          t0 = clock();
          minmaxheap.deleteMin();
          minMaxCoinOpResults[sizerun][trial] += (int)(clock()-t0);

          t0 = clock();
          minheap.deleteMin();
          minCoinOpResults[sizerun][trial] += (int)(clock()-t0);

        }
        else{
          int tempfloor = -sizes[sizerun];
          int tempceiling = sizes[sizerun];
          int num = tempfloor + ( std::rand() % ( tempceiling - tempfloor + 1 ) );

          t0 = clock();
          minmaxheap.insert(num);
          minMaxCoinOpResults[sizerun][trial] += (int)(clock()-t0);

          t0 = clock();
          minheap.insert(num);
          minCoinOpResults[sizerun][trial] += (int)(clock()-t0);

        }

      }
      kResults[sizerun][trial] = ops;

    }
  }

  
  int width = 9;
  for(int sizerun = 0; sizerun < numsizes; sizerun++){
    std::cout << "\n~~~~~ ROUND " << sizerun+1 << " ~~~~~";
    std::cout << "\nMinMaxHeap buildHeap times:\n";
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::right << std::setw(width) << minMaxBuildHeapResults[sizerun][trial];
    }
    std::cout << "\nMinHeap buildHeap times:\n";
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::right << std::setw(width) << minBuildHeapResults[sizerun][trial];
    }
    std::cout << "\nNumber of operations:\n";
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::right << std::setw(width) << kResults[sizerun][trial];
    }

    std::cout << "\nMinMaxHeap operation times:\n";
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::right << std::setw(width) << minMaxCoinOpResults[sizerun][trial];
    }
    std::cout << "\nMinHeap operation times:\n";
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::right << std::setw(width) << minCoinOpResults[sizerun][trial];
    }
    std::cout << "\n";



  }
  std::cout << "\n";

}


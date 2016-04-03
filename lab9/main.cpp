/*
 * Dustin Horvath
 * MINMAXHEAP VS MINHEAP WWF THROWDOWN
 * SUNDAY SUNDAY SUNDAY
 * ONE ENTERS ONLY ONE WILL LEAVE
 *
 *
 */

#include <iostream>
// used for floor
#include <math.h>
// used for pretty output
#include <iomanip>

#define BSIZE 1000

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

  MinMaxHeap(int *array, int size){
    arr = new int[size + BSIZE];
    for(int i = 0; i < size; i++){
      arr[i] = array[i];
    }
    m_length = size;
    //buildHeap();
  }

  ~MinMaxHeap(){
    delete [] arr;
  }

  int getSmallestGrandchild(int position){
    bool flag = false;
    int minimum;
    int smallestIndex = position;
    int tempindex;

    tempindex = 2*(2*position);
    if (tempindex <= m_length){
      if ((!flag) || (tempindex < minimum)){
        smallestIndex = tempindex;
        minimum = smallestIndex;
        flag = true;
      }
    }

    tempindex = 2*((2*position)+1);
    if (tempindex <= m_length){
      if ((!flag) || (tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        flag = true;
      }
    }

    tempindex = 2*(2*position)+1;
    if (tempindex <= m_length)
    {
      if ((!flag) || (tempindex<minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        flag = true;
      }
    }

    tempindex = (2*((2*position)+1))+1;
    if (tempindex <= m_length)
    {
      if ((!flag) || (tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        flag = true;
      }
    }
    return smallestIndex;
  }

  int getLargestGrandchild(int position){
    int maxIndex = position;
    bool flag = false;
    int maxVal;
    int tempindex;

    tempindex = 2 * (2 * position);

    if (tempindex <= m_length){
      if ((!flag) || (tempindex > maxVal)) {
        maxIndex = tempindex;
        maxVal = maxIndex;
        flag = true;
      }
    }

    tempindex = 2*((2*position)+1);

    if (tempindex <= m_length){
      if ((!flag) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        flag = true;
      }
    }

    tempindex = 2*(2*position)+1;

    if (tempindex <= m_length){
      if ((!flag) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        flag = true;
      }
    }

    tempindex = (2*((2*position)+1))+1;

    if (tempindex <= m_length){
      if ((!flag) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        flag = true;
      }
    }
    return maxIndex;
  }



  int getLargestDes(int position){
    bool flag = false;
    int maxVal;
    int maxIndex = position;
    int tempindex;

    maxIndex = getLargestGrandchild(position);
    if (maxIndex != position){
      maxVal = maxIndex;
      flag = false;
    }

    tempindex = 2*position;
    if ((tempindex <= m_length)&&(isLeaf(tempindex))){
      if ((!flag)||(tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = tempindex;
        flag = true;
      }
    }

    tempindex = (2*position)+1;
    if ((tempindex <= m_length)&&(isLeaf(tempindex))){
      if ((!flag)||(tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = tempindex;
        flag = true;
      }
    }
    return maxIndex;
  }

  int GetMinDescendant(int position){
    bool flag = false;
    int minimum;
    int smallestIndex = position;
    int tempindex;

    smallestIndex = getSmallestGrandchild(position);
    if (smallestIndex != position){
      minimum = smallestIndex;
      flag = true;
    }

    tempindex = 2*position;
    if ((tempindex <= m_length)&&(isLeaf(tempindex))){
      if ((!flag)||(tempindex < minimum)){
        smallestIndex = tempindex;
        minimum = tempindex;
        flag = true;
      }
    }

    tempindex = (2*position)+1;
    if ((tempindex <= m_length)&&(isLeaf(tempindex))){
      if ((!flag)||(tempindex < minimum)){
        smallestIndex = tempindex;
        minimum = tempindex;
        flag = true;
      }
    }

    return smallestIndex;
  }

  bool isLeaf(int position){
    bool flag = false;
    if ((2*position > m_length) && ((2*position)+1 > m_length)){
      flag = true;
    }
    return flag;
  }

  void buildHeap(){
    for ( int i = m_length/2; i >= 0; i--){
      trickleDown(i);
    }
  }

  void trickleDown(const int position){
    if (isMaxLevel(position)){
      trickleDownToMaxLevel( position );
    }
    else{
      trickleDownToMinLevel( position );
    }
  }

  void trickleDownToMinLevel(const int position){
    int minPos = GetMinDescendant(position);

    if (minPos > 0) {
      if (minPos >= position * 4) {
        if (minPos < position) {
          swap(position, minPos);

          if (minPos > minPos/2){
            swap(minPos, minPos/2);
          }
          trickleDownToMinLevel( minPos );
        }
      }
      else {
        if (minPos < position){
          swap(position, minPos);
        }
      }
    }
  }

  void trickleDownToMaxLevel( int position ){
    int maxPos = getLargestDes(position);

    if (maxPos > 0) {
      if (maxPos >= position * 4) {
        if (maxPos > position) {
          swap(position, maxPos);

          if (maxPos < maxPos/2){
            swap(maxPos, maxPos/2);
          }
          trickleDownToMaxLevel( maxPos );
        }
      }
      else {
        if (maxPos > position){
          swap(position, maxPos);
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
    m_length++;
    arr[m_length-1] = val;
    trickleUp(m_length-1);
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

  bool isMaxLevel(int position){
    return (int) (log(position+1.0)/log(2.0))%2 == 1;
  }

  void swap(int a, int b)
  {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
  }


};

class MinHeap{

  int *arr;
  int *sorted;
  int arrLength;

public:

  MinHeap(int size, int* unsortedarray){
    arr = new int[size+BSIZE];
    for(int i = 0; i <= size; i++){
      arr[i] = unsortedarray[i];
    }
    arrLength = size;
    //buildHeap();
  }

  ~MinHeap(){
    delete [] arr;
  }


  void buildHeap(){
    //std::cout << "Building heap...\n";

    for(int i = floor(arrLength/2); i > 0; i--){
      push_down(i);
    }
  }

  void insert(int val) {
    /*if(arr == nullptr) {
      int* temp = new int[arrLength + 1];
      arr = temp;
      }*/
    arrLength++;

    arr[arrLength] = val;
    trickleUp(arrLength);

  }

  void trickleUp(int index){
    int parentIndex = (int) floor((index - 1) / 2);

    while(arr[parentIndex] > arr[index] && index >= 0){
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
      if(2*position + 1 <= arrLength){
        if(arr[2*position] > arr[2*position + 1]){
          k = 2*position + 1;
        }
        else{
          k = 2*position;
        }
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

    arr[1] = arr[arrLength];
    arrLength--;

    push_down(1);
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


};


int main(){

  int seed = 0;
  srand (seed);

  int sizes[] = {100000, 200000, 400000};
  int numtrials = 8;
  int numsizes = sizeof(sizes)/sizeof(*sizes);

  // Used for storing all this output whoa nelly. Decided to just
  // be overly verbose rather than trying to condense.
  int minBuildHeapResults[numsizes][numtrials]; 
  int minMaxBuildHeapResults[numsizes][numtrials]; 
  int minMaxCoinOpResults[numsizes][numtrials]; 
  int minCoinOpResults[numsizes][numtrials]; 
  int kResults[numsizes][numtrials]; 

  clock_t t0;

  for(int sizerun = 0; sizerun < numsizes; sizerun++){
    for(int trial = 0; trial < numtrials; trial++){

      int* arr = generate(sizes[sizerun], -sizes[sizerun], sizes[sizerun]);
      int* arr2 = new int[sizes[sizerun]];

      for(int i = 0; i < sizes[sizerun]; i++){
        arr2[i] = arr[i+1];
      }


      MinMaxHeap minmaxheap = MinMaxHeap(arr2, sizes[sizerun]);
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
        double coin = (double)rand() / RAND_MAX;
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


  int width = 11;


  std::string toptitle[] = {"", "", "|", "MINHEAP", "", "|", "MINMAXHEAP", "", "|"};
  std::string titlelist[] = {"Size", "Seed", "Buildtime", "NumOps", "OpTime", "Buildtime", "NumOps", "OpTime"};
  int numtitles = sizeof(titlelist)/sizeof(*titlelist);
  int toptitles = sizeof(toptitle)/sizeof(*toptitle);

  std::cout << "\n";
  for(int toptitleprint = 0; toptitleprint < toptitles; toptitleprint++){
    std::cout << std::left << std::setw(width) << toptitle[toptitleprint];
  }
  std::cout << "\n";
  for(int titleprint = 0; titleprint < numtitles; titleprint++){
    std::cout << std::left << std::setw(width) << titlelist[titleprint];
  }
  std::cout << "\n";

  for(int sizerun = 0; sizerun < numsizes; sizerun++){
    for(int trial = 0; trial < numtrials; trial++){
      std::cout << std::left << std::setw(width) << sizes[sizerun];
      std::cout << std::left << std::setw(width) << seed;

      std::cout << std::left << std::setw(width) << minBuildHeapResults[sizerun][trial];
      std::cout << std::left << std::setw(width) << kResults[sizerun][trial];
      std::cout << std::left << std::setw(width) << minCoinOpResults[sizerun][trial];

      std::cout << std::left << std::setw(width) << minMaxBuildHeapResults[sizerun][trial];
      std::cout << std::left << std::setw(width) << kResults[sizerun][trial];
      std::cout << std::left << std::setw(width) << minMaxCoinOpResults[sizerun][trial];

      std::cout << "\n";

    }
    std::cout << "\n";



  }

}


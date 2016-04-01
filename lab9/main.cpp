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

  MinMaxHeap(int *array, int cSize){
    arr = new int[cSize + 1000];
    for(int i = 0; i < cSize; i++){
      arr[i] = array[i];
    }
    m_length = cSize;
    //buildHeap();
  }

  ~MinMaxHeap(){
    delete [] arr;
  }

  int getSmallestGrandchild(int position){
    bool maxValInit = false;
    int minimum;
    int smallestIndex = position;
    int tempindex;

    tempindex = 2*(2*position);
    if (tempindex <= m_length){
      if ((!maxValInit) || (tempindex < minimum)){
        smallestIndex = tempindex;
        minimum = smallestIndex;
        maxValInit = true;
      }
    }

    tempindex = 2*((2*position)+1);
    if (tempindex <= m_length){
      if ((!maxValInit) || (tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        maxValInit = true;
      }
    }

    tempindex = 2*(2*position)+1;
    if (tempindex <= m_length)
    {
      if ((!maxValInit) || (tempindex<minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        maxValInit = true;
      }
    }

    tempindex = (2*((2*position)+1))+1;
    if (tempindex <= m_length)
    {
      if ((!maxValInit) || (tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = smallestIndex;
        maxValInit = true;
      }
    }
    return smallestIndex;
  }

  int getLargestGrandchild(int position){
    bool maxValInit = false;
    int maxVal;
    int maxIndex = position;
    int tempindex;

    /* Get a grandchild */
    tempindex = 2*(2*position);

    /* Check for valid position */
    if (tempindex <= m_length){
      /* Check if maxVal isn't initialized or 
       * current index is greater than maxVal
       */
      if ((!maxValInit) || (tempindex > maxVal)) {
        maxIndex = tempindex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    /* Get the other grandchild */
    tempindex = 2*((2*position)+1);
    if (tempindex <= m_length){
      if ((!maxValInit) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    tempindex = 2*(2*position)+1;
    if (tempindex <= m_length){
      if ((!maxValInit) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }

    tempindex = (2*((2*position)+1))+1;
    if (tempindex <= m_length){
      if ((!maxValInit) || (tempindex > maxVal)){
        maxIndex = tempindex;
        maxVal = maxIndex;
        maxValInit = true;
      }
    }
    return maxIndex;
  }



  int getLargestDes(int position)
  {
    bool maxValInit = false;
    int maxVal;
    int maxIndex = position;
    int tempindex;

    maxIndex = getLargestGrandchild(position);
    if (maxIndex != position)
    {
      maxVal = maxIndex;
      maxValInit = false;
    }

    tempindex = 2*position;
    if ((tempindex <= m_length)&&(isLeafPos(tempindex)))
    {
      if ((!maxValInit)||(tempindex > maxVal))
      {
        maxIndex = tempindex;
        maxVal = tempindex;
        maxValInit = true;
      }
    }

    tempindex = (2*position)+1;
    if ((tempindex <= m_length)&&(isLeafPos(tempindex)))
    {
      if ((!maxValInit)||(tempindex > maxVal))
      {
        maxIndex = tempindex;
        maxVal = tempindex;
        maxValInit = true;
      }
    }
    return maxIndex;
  }

  /* Returns the minimum element of a position. */

  int GetMinDescendant(int position) // opposite of getLargestDes Idx
  {
    bool maxValInit = false;
    int minimum;
    int smallestIndex = position;
    int tempindex;

    smallestIndex = getSmallestGrandchild(position);
    if (smallestIndex != position)
    {
      minimum = smallestIndex;
      maxValInit = true;
    }

    tempindex = 2*position;
    if ((tempindex <= m_length)&&(isLeafPos(tempindex)))
    {
      if ((!maxValInit)||(tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = tempindex;
        maxValInit = true;
      }
    }

    tempindex = (2*position)+1;
    if ((tempindex <= m_length)&&(isLeafPos(tempindex)))
    {
      if ((!maxValInit)||(tempindex < minimum))
      {
        smallestIndex = tempindex;
        minimum = tempindex;
        maxValInit = true;
      }
    }
    return smallestIndex;
  }

  /* Perculates down maximum levels until a position is in its correct location. 
  */

  bool isLeafPos(int position)
  {
    bool isLeaf = false;
    if ((2*position > m_length) && ((2*position)+1 > m_length)){
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

  void trickleDown(const int position){
    if (isMaxLevel(position)){
      trickleDownToMaxLevel( position );
    }
    else{
      trickleDownToMinLevel( position );
    }
  }

  void trickleDownToMinLevel(const int position){
    /* Find the smallest child/grandchild position */
    int minPos = GetMinDescendant(position);

    /* Check if we have a child */
    if (minPos > 0) 
    {
      /* Check if minimum is a grandchild */
      if (minPos >= position * 4) 
      {
        /* Swap if less than grandparent */
        if (minPos < position) 
        {
          swap(position, minPos);

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
        if (minPos < position){
          swap(position, minPos);
        }
      }
    }
  }

  void trickleDownToMaxLevel( int position ){
    // Returns index of largest descendent
    int maxPos = getLargestDes(position);

    /* Check if we have a child */
    if (maxPos > 0) {
      /* Check if position is a grandchild */
      if (maxPos >= position * 4) {
        /* Swap if greater than grandparent */
        if (maxPos > position) {
          swap(position, maxPos);

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


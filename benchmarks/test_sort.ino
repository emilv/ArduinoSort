#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

#define MSORT(arr, ns, type) qsort(arr, ns, sizeof(type), myCompareFunction<type>)
#define MSORT2(arr, type) if(arr[0] > arr[1]) {SWAP(arr[0], arr[1], type);}
#define MSORT3(arr, type) if(arr[0] > arr[1]) {SWAP(arr[0], arr[1], type);} if(arr[1] > arr[2]) {SWAP(arr[1], arr[2], type);} if(arr[0] > arr[1]) {SWAP(arr[0], arr[1], type);}

template<typename T> int myCompareFunction (const void * arg1, const void * arg2)
{
  T * a = (T *) arg1;  // cast to pointers to type T
  T * b = (T *) arg2;
  // a less than b? 
  if (*a < *b)
    return -1;
  // a greater than b?
  if (*a > *b)
    return 1;
  // must be equal
  return 0;
}  // end of myCompareFunction

int intcmp (const void * arg1, const void * arg2) {
  int *a = (int *) arg1;
  int *b = (int *) arg2;
  return *a - *b;
}

template<typename T> void msort2_impl(T *arr) {
  T tmp;
  if (arr[0] > arr[1]) {
    tmp = arr[0];
    arr[0] = arr[1];
    arr[1] = tmp;
  }
}

inline void msort2_impl_int(int *arr) {
  if (arr[0] > arr[1]) {
    arr[0] ^= arr[1];
    arr[1] ^= arr[0];
    arr[0] ^= arr[1];
  }
}

template<typename T> void msort3_impl(T *arr) {
  T tmp;
  if(arr[0] > arr[1]) {SWAP(arr[0], arr[1], T);}
  if(arr[1] > arr[2]) {SWAP(arr[1], arr[2], T);}
  if(arr[0] > arr[1]) {SWAP(arr[0], arr[1], T);}
}

template<typename T> void bubblesort(T *d, size_t s) {
  bool swapped;
  do {
    swapped = false;
    for (size_t i = 0; i < s-1; i++) {
      if (d[i] > d[i+1]) {
        SWAP(d[i], d[i+1], T);
        swapped = true;
      }
    }
  } while(swapped);
}

template<typename T> void gnomesort(T *arr, size_t count) {
  int pos = 0;
  int off = 1;
  while (pos < count) {
    if (pos == 0 || arr[pos] >= arr[pos-1]) {
      pos+=off;
      off=1;
    } else {
      SWAP(arr[pos], arr[pos-1], T);
      --pos;
      ++off;
    }
  }
}

template<typename T> bool lg(T a, T b) {
  return a > b;
}

template<> bool lg(char* a, char* b) {
  return strcmp(a, b) > 0;
}

template<typename T> void insertionsort(T *arr, size_t count, bool reverse, bool (*largerThan)(T, T)) {
  for (size_t i = 1; i < count; i++) {
    for (size_t j = i; j > 0 && (largerThan(arr[j-1], arr[j]) != reverse); j--) {
      SWAP(arr[j-1], arr[j], T);
    }
  }
}

template<typename T> void insertionsort(T *arr, size_t count, bool reverse) {
  insertionsort(arr, count, reverse, lg);
}

template<typename T> void insertionsort(T *arr, size_t count) {
  insertionsort(arr, count, false);
}


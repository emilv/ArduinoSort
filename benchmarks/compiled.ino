#define ELEMENTS 3
#define TYPE int

void setup () {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("\n\nBegin!");
  benchmark();
}

void benchmark() {
  int count = ELEMENTS;
  TYPE arr[ELEMENTS];
  seeder(arr, count);
  //MSORT(arr, count, TYPE);
  //msort2_impl(arr);
  //bubblesort(arr, count);
  //gnomesort(arr, count);
  insertionsort(arr, count);
  printArr(arr, count);
}

template<typename T> void seeder(T *arr, int count) {
  for (int i = 0; i < count; i++) {
    arr[i] = (T) random(-160, 1337);
  }
}

template<> void seeder(char** arr, int count) {
  Serial.setTimeout(60*1000);
  for (int i = 0; i < count; i++) {
    arr[i] = calloc(10, sizeof(char));
    Serial.print("Input: ");
    Serial.readBytesUntil(10, arr[i], 9);
    Serial.println(arr[i]);
  }
  Serial.setTimeout(1000);
}

template<> void seeder(String *arr, int count) {
  Serial.setTimeout(60*1000);
  for (int i = 0; i < count; i++) {
    Serial.print("Input: ");
    arr[i] = Serial.readStringUntil(10);
    Serial.println(arr[i]);
  }
  Serial.setTimeout(1000);
}

void printArr(TYPE *arr, size_t count) {
  for (int i = 0; i < count; i++) {
    Serial.println(arr[i]);
  }
}

void loop(){
  delay(1000000);
}
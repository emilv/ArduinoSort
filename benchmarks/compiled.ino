#define ELEMENTS 2
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
  seeder(arr, count, -15, 15);
  //MSORT(arr, count, TYPE);
  //msort2_impl(arr);
  //bubblesort(arr, count);
  //gnomesort(arr, count);
  //insertionsort(arr, count);
  printArr(arr, count);
}

void seeder(TYPE *arr, int count, int min, int max) {
  for (int i = 0; i < count; i++) {
    arr[i] = (TYPE) random(min, max);
  }
}

void printArr(TYPE *arr, size_t count) {
  for (int i = 0; i < count; i++) {
    Serial.println(arr[i]);
  }
}

void loop(){
  delay(1000000);
}

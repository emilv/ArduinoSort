#define ELEMENTS 2

void setup () {
  randomSeed(analogRead(0));
  benchmark();
}

void benchmark() {
  int arr[ELEMENTS];
  seeder(arr, -15, 15);
  MSORT(arr, ELEMENTS, int);
}

void seeder(int *arr, int min, int max) {
  for (int i = 0; i < ELEMENTS; i++) {
    arr[i] = random(min, max);
  }
}

void loop(){
  delay(1000000);
}


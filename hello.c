//This program will print "hello,world!" to the screen
#include <stdio.h>

int square(int number);

int main(void) {
  int age = 21;

  int square_age = square(age);

  printf("Hello, Joe! The square of your age is  %d.", square_age);

  return(0);
}

//This program will print "hello,world!" to the screen
#include <stdio.h>

int main(void) {
  //Get user name
  char userName[10];
  printf("Enter your name: ");
  scanf("%s", &userName);
  

  //Get user age
  int userAge;
  printf("Enter your age: ");
  scanf("%d", &userAge);
    
  printf("Hello, %s! You are %d years old.\n",userName, userAge);

  return(0);
}

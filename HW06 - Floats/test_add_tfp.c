#include "add_tfp.h"
#include <stdio.h>

int main() {
   /*
      1) Same Exponent
      2) Positive
      3) Normalized
      4) Mantissa overflows such that M1 + M2 = 0b0001X.XXX, and adjust exponent as needed
      5) Rounding
   */
   tfp case1 = add_tfp(0b01000101, 0b01000100);
   printf("Case 1: 01001101 = %08b | %u\n", case1, (case1 == 0b01001101));
   tfp case2 = add_tfp(0b01000111, 0b01000111);
   printf("Case 2: 01001111 = %08b | %u\n", case2, (case2 == 0b01001111));
   tfp case3 = add_tfp(0b01000001, 0b01000001);
   printf("Case 3: 01001001 = %08b | %u\n", case3, (case3 == 0b01001001));   
   /*
      1) Different Exponent
      2) Positive
      3) Normalized
      4) Mantissa overflows such that M1 + M2 = 0b0001X.XXX, and adjust exponent as needed
      5) Rounding
   */
   tfp case4 = add_tfp(0b01001001, 0b01000001);
   printf("Case 4: 01001101 = %08b | %u\n", case4, (case4 == 0b01001101));
   tfp case5 = add_tfp(0b00001111, 0b00010111);
   printf("Case 5: 00011011 = %08b | %u\n", case5, (case5 == 0b00011011));
   /*
      1) Same exponent
      2) Positive
      3) Denormalized 
   */
   tfp case6 = add_tfp(0b00000101, 0b00000010);
   printf("Case 6: 00000111 = %08b | %u\n", case6, (case6 == 0b00000111));
   tfp case7 = add_tfp(0b00000111, 0b00000001);
   printf("Case 7: 00001000 = %08b | %u\n", case7, (case7 == 0b00001000));

   /*
      1) Mixed case: One normalized, one denormalized 
   */
   tfp case8 = add_tfp(0b01000111, 0b00000001);
   printf("Case 8: 01000111 = %08b | %u\n", case8, (case8 == 0b01000111));

   /* 
      1) Same exponent
      2) Same (negative) Sign
      3) Normalized 
   */
   tfp case9 = add_tfp(0b11000101, 0b11000010);
   printf("Case 9: 11000111 = %08b | %u\n", case9, (case9 == 0b11000111));
   /* 
      1) Same exponent
      2) Different Negative Sign
      3) Normalized 
   */
  tfp case10 = add_tfp(0b11000101, 0b01000010);
  printf("Case 10: 10110100 = %08b | %u\n", case10, (case10 == 0b10110100));
  tfp case11 = add_tfp(0b11001101, 0b01000110);
  printf("Case 11: 11000100 = %08b | %u\n", case11, (case11 == 0b11000100));
  tfp case12 = add_tfp(0b10001111, 0b00000001);
  printf("Case 12: 10001110 = %08b | %u\n", case12, (case12 == 0b10001110));
}
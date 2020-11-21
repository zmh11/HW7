#include <iostream>
#include "recursive.h"
#include "hw4.h"

list_t fib_hash( list_t list){
  list_t hash = list_make();
  int sumTotal = sum(list);
  int hashValue;
  while( !list_isEmpty(list) ){
    hashValue = fib( list_first(list) ) + sumTotal;
    hash = list_make( hashValue, hash );
    list = list_rest(list);
  }
  hash = reverse(hash);
  return hash;
}

int main(){
  list_t input = list_make();
  list_t hashFib = list_make();
  for (int i= 1; i <= 6; i++)
    input =  input = list_make( i , input);
  input = reverse( input );
  list_print(input);
  hashFib = fib_hash(input);
  list_print(hashFib);
  return 0;

}
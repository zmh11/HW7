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

bool prime( int num){
  if (num == 0 || num ==1)
    return true; 
  else {
    for(int k = 2; k <= num / 2; num++)
      if (num  % k == 0)
        return true;
  }
    return false;
}

list_t hash_2( list_t list ){
  list_t hash = list_make();
  list_t odd = list_make();
  list_t odd_fn = list_make();
  list_t list2 = list;
  odd = filter_odd( list );
  int productOdd = product( odd );

  while( !list_isEmpty(list2) ){
     int temp = list_first( list2 );
     int insert;
     if ( temp % 2 != 0){
      insert = productOdd + temp;
      odd_fn = list_make( insert, odd_fn);
     }
    list2 = list_rest(list2);
}  
  list_t noPrime = list_make();
  noPrime = filter (odd_fn , (*prime) );
  int sumNoPrime = sum(noPrime);
   while( !list_isEmpty(list) ){
     int temp = list_first( list );
     int insert;
     if ( temp % 2 == 0)
      insert = sumNoPrime + temp;
    else 
      insert = productOdd + temp;

    hash = list_make( insert, hash);
    list = list_rest(list);
   }
   hash = reverse(hash);
   return hash;
}



int main(){
  list_t input = list_make();
  list_t hashFib = list_make();
  list_t hash2 = list_make();

  for (int i= 1; i <= 6; i++)
    input =  input = list_make( i , input);
  input = reverse( input );
  std::cout<<"hash test" << std::endl;
  list_print(input);
  hashFib = fib_hash(input);
  list_print(hashFib);

  std::cout<<std::endl<<"hash2 test" << std::endl;
  list_print(input);
  hash2 = hash_2(input);
  list_print(hash2);

  return 0;

}
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "recursive.h"
#include "hw4.h"

/*
  given a list retrun a new list using the folowing has function
  the hash value is the Fibonacci number of the key + the sum of all the items in the list.
*/
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

/*
  retruns true if number is not prime
*/
bool prime( int num){
  if (num == 0 || num ==1)
    return true;
  else {
    for(int k = 2; k <= num / 2; num++)
      if (num % k == 0)
        return true;
  }
    return false;
}

/*
  create a list for keys given in list using the folowing rules
  odd_fn =  product of the odd number + key
  even_fn =  (sum the results of the odd_fn hash after removing any prime numbers) + key
 */
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

/*
  returns number of repeating numbers
*/
int collision( list_t list ){

  int temp;
  int collision = 0;
  std::unordered_map< int,int > compare;
  while( !list_isEmpty(list) ){
    temp = list_first( list )%16;
    if ( compare.find( temp ) == compare.end() )
      compare[temp]++;
    else
      collision++;
    list = list_rest( list );
  }
  return collision;
}

/*
  retruns difreance in lists
*/

list_t compare( list_t list, list_t list2){
  list_t compare = list_make();
  int dif;
  while( !list_isEmpty(list) ){
    dif = list_first( list ) - list_first( list2);
    dif = std::abs(dif);
    compare = list_make( dif, compare);
    list = list_rest( list );
    list2= list_rest(list2);
  }
  compare = reverse (compare);
  return compare;

}

int main(){

 
  list_t hashInput1 = list_make();
  list_t hashOutput1 = list_make();
  list_t dif1 = list_make();

  list_t hashInput2 = list_make();
  list_t hashOutput2 = list_make();
  list_t dif2 = list_make();
  std::string line; // only grabs first int gix in mornig

  int value;
  int list = 0;
  while(getline(std::cin, line)){
    std::stringstream lineStream(line);
    while(lineStream >> value){
      if( list == 0)
        hashInput1 = list_make( value, hashInput1 );
      if( list == 1)
        hashOutput1 = list_make( value, hashOutput1 );
      if( list == 2)
        hashInput2 = list_make( value, hashInput2 );
      if( list == 3)
        hashOutput2 = list_make( value, hashOutput2 );
    }
    list++;
  }
  hashInput1= reverse(hashInput1);
  hashOutput1 = reverse(hashOutput1);
  hashInput2 = reverse(hashInput2);
  hashOutput2 = reverse(hashOutput2);


  hashInput1 =  fib_hash(hashInput1);
  dif1 = compare( hashInput1, hashOutput1);
  std::cout<<"Test1 final_diff_output : ";
  list_print(dif1);
  std::cout<<std::endl;

  std::cout<<"Test2 final_diff_output : ";
  hashInput2 =  hash_2(hashInput2);
  dif2 = compare( hashInput2, hashOutput2);
  list_print(dif2);
  std::cout<<std::endl;

  std::cout << std::endl << "collision cnt" << std::endl;
  std::cout << "test 1 " << std::endl;
  std::cout << "new_code : " << collision(hashInput1)  << std::endl;
  std::cout << "old_code : " <<  collision(hashOutput1)  << std::endl;

  std::cout << std::endl << "collision cnt" << std::endl;
  std::cout << "test 2 " << std::endl;
  std::cout << "new_code : " << collision(hashInput2)  << std::endl;
  std::cout << "old_code : " <<  collision(hashOutput2)  << std::endl;


  return 0;

}

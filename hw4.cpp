#include <iostream>
#include <cassert>
#include "recursive.h"
/***
 * sum  
 * for each item in list 
 * add them to a varibule called sum
 * return sum
 ***/
static int sum_helper( list_t list, int sum )
{
  if( list_isEmpty(list) )
    return sum;
 
  return sum_helper(list_rest(list), sum + list_first(list));
}

int sum(list_t list){
  if( list_isEmpty(list))
    return 0;
  return sum_helper(list,0);

}
/***
 * product
 * int product = 1
 * for each item in list
 * product *= item in list
 * return product
 ***/

static int product_helper( list_t list, int product){
  if ( list_isEmpty(list) )
    return product;
  return product_helper(list_rest(list), product * list_first(list));
}

int product( list_t list ){
  if( list_isEmpty(list) )
    return 1;
  return product_helper(list, 1);
}

/***
 * accumlate 
 * given a finction 
 * return the sum of all elements in that list acording 
 * to the function
 ***/
int accumulate(list_t list, int (*fn)(int, int), int identity){
  if (list_isEmpty(list))
    return identity;
  return ( (*fn)(list_first(list),identity ) + accumulate(list_rest(list), (*fn), identity ));
}

/***
 * given a list 
 * for each element in the list starting from the front
 * add it to the back of a new list 
 * return the new list
 ***/
static list_t reverse_helper( list_t list, list_t reverse){
  if( list_isEmpty(list) )
    return reverse;
  return reverse_helper( list_rest(list), list_make(list_first(list), reverse) );
}

list_t reverse(list_t list){
  return reverse_helper( list, list_make() );
}

/***
 * append 
 * given two lists
 * make a new list that is the 
 * first list added to the front 
 * of the second
 * return a new list
 * 
 ***/
static list_t append_helper( list_t add, list_t append){
  if ( list_isEmpty(add) )
    return append;
  return append_helper( list_rest(add), list_make(list_first(add), append));
}
list_t append(list_t first, list_t second){
  list_t list = list_make();
  if( !list_isEmpty(first) )
    list = append_helper(first, list);
  if ( !list_isEmpty(second) )
    list = append_helper(second, list);
  return reverse(list);
}

/***
 * given a list  
 * loop through list 
 * add odd elements to a new list
 * return new list
 ***/
static list_t filter_odd_helper( list_t list, list_t odd ){
  if( list_isEmpty(list) )
    return odd;

  if( (list_first(list) % 2) == 1 )
    return filter_odd_helper( list_rest(list), list_make(list_first(list), odd));
  
  return filter_odd_helper( list_rest(list), odd);
}
list_t filter_odd( list_t list ){
  list_t odd = list_make();
  odd = filter_odd_helper( list, odd );
  return reverse( odd );
}

/***
 * given a list  
 * loop through list 
 * add even elements to a new list
 * return new list
 ***/
static list_t filter_even_helper( list_t list, list_t even ){
  if( list_isEmpty(list) )
    return even;
    
  if( (list_first(list) % 2) == 0 )
    return filter_even_helper( list_rest(list), list_make(list_first(list), even));
  
  return filter_even_helper( list_rest(list), even);
}
list_t filter_even( list_t list ){
  list_t even = list_make();
  even = filter_even_helper( list, even );
  return reverse( even );
}

/***
 * filter 
 * for each item in list
 * if ( *fn item)
 *  add item to new list
 * return new list
 ***/
static list_t filter_helper( list_t list, bool(*fn)(int), list_t pass_test ){
  if(list_isEmpty(list))
    return reverse(pass_test);

  if( (*fn)(list_first(list)) )
    return filter_helper( list_rest(list), (*fn), list_make(list_first(list), pass_test));

  return filter_helper( list_rest(list), (*fn), pass_test);
}
list_t filter(list_t list, bool (*fn)(int)){
  return filter_helper( list, (*fn), list_make());
}

/***
 * for a number n 
 * add the first element to the 
 * back of the list
 ***/
static list_t rotate_helper(list_t list, unsigned int n, list_t rotated){
  if( n==0 )
    return append( list, reverse(rotated) );  
  if( list_isEmpty(list) ){
    list = reverse(rotated);
    rotated = list_make();
  }
  return rotate_helper( list_rest(list), n-1, list_make(list_first(list), rotated));
  
}
list_t rotate(list_t list, unsigned int n){
  if ( n == 0 )
    return list;
  return rotate_helper(list, n, list_make() );
}

/***
 * insert 
 * for i=0 i<n i++
 * add item in first list to new list
 * 
 * add second list
 * add rest of first list
 ***/
static list_t insert_list_helper(list_t end, list_t middle, unsigned int n, list_t insert){
  if( n == 0 )
    return append( reverse(insert), append (middle,end ));
  return insert_list_helper( list_rest(end), middle, n-1, list_make(list_first(end), insert));
}

list_t insert_list(list_t first, list_t second, unsigned int n){
  return insert_list_helper( first, second, n, list_make() );
}

/***
 * chop
 * for item in ( list length - n )
 *  add item to new list
 * return new list
 ***/
static list_t chop_helper( list_t list, unsigned int n, list_t chop){
  if( n == 0 )
    return reverse(list);
  return chop_helper( list_rest(list), n-1, list_make(list_first(list), chop));
}
list_t chop( list_t list, unsigned int n){
  return chop_helper( reverse(list), n, list_make() );
}

/***
 * fib (n)
 * if n == 0
 * return 0
 * if n==1
 * return 1
 * return fib(n-1) + fib(n-2) 
 ***/
int fib( int n){
  if (n == 0)
    return 0;
  if (n==1)
    return 1;
  return fib(n-1) + fib(n-2);
}

/***
 * fib (n)
 * if n == 0
 * return 0
 * if n==1
 * return 1
 * return fib(n-1) + fib(n-2) 
 ***/
static int fib_tail_helper(int n, int total, int a, int b ){
  if (n == 1)
    return total;
  return fib_tail_helper( n-1, a + b, b, a+b );
}
int fib_tail(int n){
  return fib_tail_helper(n ,0, 0, 1);
}
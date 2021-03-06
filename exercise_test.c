/* File:     exercise_test.c
 *
 * Purpose:  Unit tests for functions defined in exercise.c 
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercise_test.c
 * Run:      ./exercise
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"
#include "exercise.h"


/*-------------------------------------------------------------------
 * Test exchange() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *exchange_test(void) {
  int  valA = 20;   
  int  *ptrA;        
  ptrA = &valA;
  int valB = 5;
  int *ptrB;
  ptrB = &valB;
  exchange(ptrA, ptrB);
  // printf("ptrA = %d, ptrB = %d", *ptrA, *ptrB);
  mu_assert("ptrA expected to be 5 and ptrB expected to be 20", *ptrA == 5 && *ptrB == 20);
  return NULL;
  
}  

/*-------------------------------------------------------------------
 * Test reverse_array() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *reverse_array_test(void) {
  int arr[5] = {1 ,2 ,3 ,4 ,5};
  int array[5] = {5,4,3,2,1};



  reverse_array(arr, 5);
  // for(int i = 0; i < 5; i++){
  //   printf("%d\n", arr[i]);
  // }
  for (int i = 0; i < 5; i++){
    mu_assert("array not reversed correctly", arr[i] == array[i]);
  }
  
  return NULL;
}  

/*-------------------------------------------------------------------
 * Test match_add() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *match_add_test(void) {
  /*Your solution*/
  int add1 = match_add("add1", 3);
  int add2 = match_add("add2", 4);
  int add3 = match_add("add3", 5);
  
  mu_assert("add1 not calculated correctly", add1 == 4);
  mu_assert("add2 not calculated correctly", add2 == 6);
  mu_assert("add3 not calculated correctly", add3 == 8);

  return NULL;
}  

/*-------------------------------------------------------------------
 * Check the result of testing after calling  set_key_action() 
 * If failed, return a message string showing the failed point
 * If succesful, return NULL 
 */
char *check_key_action_return(char *expected_key,int (*expected_func)(int),  int ret, struct key_action *rec) {
  mu_assert("Error in set_key_action with del1 key", strcmp(expected_key, rec->cmd)==0);
  mu_assert("Error in set_key_action with del1 value", rec->func == expected_func);
  mu_assert("Error in set_key_action with del1 value", ret== SUCC);
  return NULL;
}

/*-------------------------------------------------------------------
 * Test set_key_action() 
 * If failed, return a message string showing the failed point
 * If succesful, return NULL 
 */
int del1(int x){
  return x-1;
}

int del2(int x){
  return x-2;
}

char * set_key_action_test(void){
  char *key="del1";
  int ret=set_key_action(NULL, key, del1);
  mu_assert("Error in set_key_action with NULL value", ret == FAIL);

  struct key_action *rec = (struct key_action *) malloc(sizeof(struct key_action));
  ret = set_key_action(rec, key, del1);
  char *msg = check_key_action_return(key, del1, ret, rec);
  free(rec);
  /*All comparisons/tests are valid*/
  return msg;
}

/*-------------------------------------------------------------------
 * Test match_action() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
struct key_action map[] = {
  { "del1", del1 },
  { "del2", del2 },
  { 0, 0 }
};

char *match_action_test(void){
  /*Your solution*/
  int arg = match_action(map, "del2", 4);
  mu_assert("Expected the value 2", arg == 2);
  return NULL;
}  

/*-------------------------------------------------------------------
 * Test if the  matrix-vector multiplicatioon result is expected.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 * m is number of rows and n is the number of columns
 */
char*  test_vect(double y[], int m, int n){
  int i;
  double expected= n*(n-1)/2;
  for (i = 0; i < m; i++){
#ifdef DEBUG1
    printf("Expected %f actual %f in mat_vect_mult\n", expected, y[i]); 
#endif
    mu_assert("Error in mat_vect_mult, one mismatch", y[i] ==expected); 
  }
  return NULL;
}

/*-------------------------------------------------------------------
 * Test matrix vector multiplciation 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char* mat_vect_mult_test1(int m, int n) {
  int i,j;
  char *msg;
  double *A = malloc(m*n*sizeof(double));
  double *x = malloc(n*sizeof(double));
  double *y = malloc(m*sizeof(double));
  for (j = 0; j < n; j++) {
    x[j]=j;
  }
  for (i = 0; i < m; i++) {
    y[i]=0;
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) A[i*n+j]=1;
  }

  int ret=mat_vect_mult(A, x, y, m, n);
  msg=test_vect(y, m, n);  
  free(A);
  free(x);
  free(y);

  if(msg !=NULL)
    return msg;

  if(ret!=SUCC)
    return "Error in mat_vect_mult return value";

  return NULL;
}  

/*-------------------------------------------------------------------
 * Test matrix vector multiplication.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_vect_mult_test(void) {
  return  mat_vect_mult_test1(2,4);
}  

char *mat_vect_mult_test_null(void) {
  double A=1; 
  int n=1;  
  int ret=mat_vect_mult(NULL, NULL, NULL, n, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  ret=mat_vect_mult(&A, &A, &A, 0, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  return  NULL;
}  

/*-------------------------------------------------------------------
 * Test matrix matrix multiplication 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_mat_mult_test(void){
  double A[] = {1,2,3,4};
  double B[] = {1,1,1,1};
  double C[] = {0,0,0,0};
  double expected[] = {3,3,7,7};
  mat_mat_mult(A,B,C,2);
  for (int i = 0; i < 4; i++){
    mu_assert("matrix_C not equal to expected", expected[i]);
  }
  return NULL;
}  

/*-------------------------------------------------------------------
 * Run all tests.  Ignore returned messages.
 */
void run_all_tests(void) {
  /* Call all tests.  You can add more tests*/
  mu_run_test(exchange_test);
  mu_run_test(reverse_array_test);
  mu_run_test(match_add_test);
  mu_run_test(set_key_action_test);
  mu_run_test(match_action_test);
  mu_run_test(mat_vect_mult_test);
  mu_run_test(mat_vect_mult_test_null);
  mu_run_test(mat_mat_mult_test);
}

/*-------------------------------------------------------------------
 * The main entrance to run all tests.  
 * If failed, return a message string showing the first failed point
 * Print the test stats
 */
int main(int argc, char* argv[]) {
  run_all_tests();
  
  mu_print_test_summary("Summary:");  
  return 0;
}

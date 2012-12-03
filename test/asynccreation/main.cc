#include "POPObject.ph"

#include <unistd.h>
#include <time.h>

/** 
 * @author  clementval
 * @date    2012.08.22
 * This program tests asynchronous parallel object allocation
 */
int main(int argc, char** argv)
{
  try {
    time_t t1, t2, t3, t4, t5;
    time(&t1); 
    printf("Asynchronous allocation of parallel object\n");
    printf("Before creating POPObject o1\n");
    POPObject o1(0);
    printf("Before creating POPObject o2\n");
    POPObject o2(2);
    printf("Before creating POPObject o3\n");		
    POPObject o3(3);
    time(&t2); 
    printf("Before calling method 1 on POPObject o1\n");		
    o1.firstMethod();
    time(&t3); 
    printf("Before calling method 1 on POPObject o2\n");		
    o2.firstMethod();
    time(&t4);
    printf("Before calling method 1 on POPObject o3\n");		
    o3.firstMethod();
    time(&t5);		
    printf("Before calling method 2 on POPObject o1\n");		
    o1.secondMethod();		
    printf("Before calling method 2 on POPObject o2\n");		
    o2.secondMethod();		
    printf("Before calling method 2 on POPObject o3\n");		
    o3.secondMethod();	

    double call_construct_time = difftime(t2, t1); 
    double o1_call = difftime(t3, t1); 
    double o2_call = difftime(t4, t1); 
    double o3_call = difftime(t5, t1); 

    printf("\n\nTime information:\n"); 
    printf("Elapsed time before waiting on the 1st call: %f\n", call_construct_time); 
    printf("Elapsed time before calling method on o1: %f\n", o1_call); 
    printf("Elapsed time before calling method on o2: %f\n", o2_call); 
    printf("Elapsed time before calling method on o3: %f\n", o3_call); 
    if(call_construct_time < 10.0 && (o2_call > 4.0 && o2_call < 6.0)) {
      printf("Asynchronous Parallel Object Allocation test succeed\n"); 
    } else {
      printf("Asynchronous Parallel Object Allocation test failed ... APOA is maybe not enable !\n"); 
      return 1;
    }
  } catch (POPException e) {
    printf("Method with void parameter: test failed, error no.%d, destroying objects:\n", e.Code()); return 1;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl; 
    return 1;
  }
  return 0;
}

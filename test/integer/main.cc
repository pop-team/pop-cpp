#include "integer.ph"
#include <iostream.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int x[5000];
  for (int i=0;i<5000;i++) x[i]=i;

  try {
    Integer o1(60,40);
    Integer o2(paroc_system::GetHost());
 
    Integer o3(100,20);
    o1.Set(1); o2.Set(2); o3.Set(3);
    	
    cout<<"O1="<< o1.Get() << "; O2=" << o2.Get() << "; O3=" << o3.Get() << "\n";
    o1.Add(o2);
    cout<<"O1=O1+O2; O1="<< o1.Get()<<"\n";
    o1.Add(o2,o3);
    cout<<"O1=O2+O3, O1=" << o1.Get() << "\n";
    cout<<"Sum x="<< o1.Sum(x) <<"\n";
    cout<<"Now waiting...\n";
    
    o1.Wait(10);
    o2.Wait(160);
    o3.Wait(45);	
   // sleep(30);
	
    
  }
  catch (paroc_exception *e)
    {
      cout<<"Object creation failure"<<"\n";
      return -1;
    }
  return 0;


}

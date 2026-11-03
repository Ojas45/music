#include<iostream>
#include<chrono>
using namespace std;
using namespace chrono;


long long fibonacciR(int n)
{
  if(n<=1)
    return n;
  return fibonacciR(n-1)+fibonacciR(n-2);
}

long long fibonacciI(int n){
  if(n<=1)
    return n;
  
  long long a=0,b=1;
  for(int i=2;i<=n;i++)
  {
    long long c=a+b;
    a=b;
    b=c;
  }
  return b;
} 


int main(void)
{
cout<<"------FibonacciR START----------------"<<endl;
auto start1=high_resolution_clock::now();
long long result=fibonacciR(5);
auto end1=high_resolution_clock::now();

double time1=duration<double,milli>(end1-start1).count();
cout<<"5th fibonacci number is:"<<result<<endl;
cout<<"Time taken by recursive method"<<time1<<endl;
cout<<"---------FibonacciR END------------"<<endl;

cout<<"------FibonacciI START----------------"<<endl;
auto start2=high_resolution_clock::now();
long long result2=fibonacciI(5);
auto end2=high_resolution_clock::now();

double time2=duration<double,milli>(end2-start2).count();
cout<<"5th fibonacci number is:"<<result2<<endl;
cout<<"Time taken by Iterative method"<<time2<<endl;
cout<<"---------FibonaccI END------------"<<endl;

  return 0;
}

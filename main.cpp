#include <iostream>
#include "geocomp.hpp"
using namespace std;
int main()
{
  PolyCh case1; //a<b<c
  Point ptA(1,2);
  Point ptB(3, 4);
  Point ptC(5,6);
  Segment segmentoTest(ptA, ptC);
  case1.push_back(ptA);
  case1.push_back(ptB);
  case1.push_back(ptC);
  cout << "Testing case 1.A(a<b<c)" << endl;
  if(is_monotone(case1, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;}

  PolyCh case2; // a > b > c 
  Point c2A(5,6);
  Point c2B(3,4);
  Point c2C(1,2);
  case2.push_back(c2A);
  case2.push_back(c2B);
  case2.push_back(c2C);
  cout << "Testing case 1.B(a>b>c)" << endl;
  if(is_monotone(case2, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;} 

  PolyCh case3;//(a = b < c) o (a < b = c) 
  Point c3A(1,2);
  Point c3B(1,2);
  Point c3C(3,5);
  case3.push_back(c3A);
  case3.push_back(c3B);
  case3.push_back(c3C);
  cout << "Testing case 2.A(a = b < c)" << endl;
  if(is_monotone(case3, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;} 

  PolyCh case3B;
  Point c3AA(1,2);
  Point c3BB(3,5);
  Point c3CC(3,5);
  case3B.push_back(c3AA);
  case3B.push_back(c3BB);
  case3B.push_back(c3CC);
  cout << "Testing case 2B (a < b = c)" << endl;
  if(is_monotone(case3B, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;} 


  PolyCh case4; //(a = b > c) o (a > b = c) 
  Point c4A(3,5);
  Point c4B(3,5);
  Point c4C(1,2);
  case4.push_back(c4A);
  case4.push_back(c4B);
  case4.push_back(c4C);
  cout << "Testing case 3A (a = b > c)" << endl;
  if(is_monotone(case4, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;} 

  PolyCh case4B;
  Point c4AA(3,5);
  Point c4BB(1,2);
  Point c4CC(1,2);
  case4B.push_back(c4AA);
  case4B.push_back(c4BB);
  case4B.push_back(c4CC);
  cout << "Testing case 3B (a > b = c)" << endl;
  if(is_monotone(case4B, segmentoTest)){cout << "Is monotone!" << endl;}
  else{cout << "NOT MONOTONE!" << endl;} 


//Clase 2. Area de un triangulo
//Anti clock wise = Positive Area
  Point a(1,1);
  Point c(3,2);
  Point b(2,3);




  int a2 = area2(a,b,c);
  cout << "2A = " << a2 << endl;

  PolyCh pc;
  pc.push_back(a);
   pc.push_back(b);
 pc.push_back(c);

  cout << "chain = " << pc << endl;


return 0;
}



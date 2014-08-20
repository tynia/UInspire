#include <iostream>
#include "InspireUtil.h"

int main()
{
   int a = 0 ;
   std::cout << "input a number: " ;
   std::cin >> a ;

   if ( a > 100 )
   {
      LogError( "basketball is funny." ) ;

      char* pstr = "Hello World";
      INSPIRE_INTERNAL::CharConverter con( pstr ) ;
      std::cout << con.GetUnicode() << std::endl ;
   }
}
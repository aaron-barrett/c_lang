/* Courtest of https://web.archive.org/web/20091104065428/http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html */

#include <stdio.h>
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)

int main()
{
   TRY
   {
      printf("In Try Statement\n");
      THROW;
      printf("I do not appear\n");
   }
   CATCH
   {
      printf("Got Exception!\n");
   }
   ETRY;

   return 0;
}
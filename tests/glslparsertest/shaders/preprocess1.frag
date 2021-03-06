// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// # NOTE: Config section was auto-generated from file
// # NOTE: 'glslparser.tests' at git revision
// # NOTE: 6cc17ae70b70d150aa1751f8e28db7b2a9bd50f0
// [end config]

// tests for macro redifinition (t2) and the #if and #else nestings.
// takes care of elif also. 

#define t1 (1+2) 
#define t2 2
#define t2 3 

// testing the if depth
#if (t1==3)
  #define t3 3
  #if defined t2
    #define t4 4
      #if defined(t3)
          #define t5 5
             #ifdef t5
               #define t6 6
                 #ifndef t7
                   #define t7 7
                 #else
                   #define t8 8
                 #endif
             #endif
      #else
         #ifndef t8
             #define t8 8
         #elif (t8==8)
            #define t9 9
         #else
            #if defined t7
              #define t9 9
            #endif
         #endif
      #endif
  #else
    #define t10 10
  #endif
#endif


#define t8 8 
#define t9 9 
#define t10 10

void main(void) 
{
 int sum=1 ;
 sum = t1+t2;
 sum = t3+t4;
 sum = t5+t6;
 sum = t7+t8;
 sum = t9+t10;
}    
              

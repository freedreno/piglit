// [config]
// expect_result: pass
// glsl_version: 1.10
// glsles_version: 1.00
//
// # NOTE: Config section was auto-generated from file
// # NOTE: 'glslparser.tests' at git revision
// # NOTE: 6cc17ae70b70d150aa1751f8e28db7b2a9bd50f0
// [end config]

// Extensive testing on #if #else #elif #ifdef, #ifndef and #endif.


#define t1 1
 
#if(t1==1)
  #define t2 2
#endif

#if (t2!=2)
  #define t3 33
#else
  #define t3 3
#endif

#if (t3!=3)
 #define t4 4
#elif (t3==3)
 #define t4 44
#else 
  #define t4 0
#endif

#if defined(t5)
 #define t6 6
#elif (t3!=3)
 #define t5 5
#elif (t3==3)
 #define t5 5
#endif

#ifdef t5
 #define t6 6
#else
 #define t7 7
#endif

#ifndef t8 
 #define t8 8
#endif

#if defined t8 
 #define t9
 #ifdef t9
  #define  t10 10
 #endif
#elif
 #define t11 11
#endif

#ifndef t8
 #define t12 12
#else
 #define t12 12
 #ifndef t13
  #define t13 13
 #endif
 #ifdef t14
  #define t15 15
 #else
  #if defined t8
   #define t16 16
  #endif
 #endif
#endif

#ifdef t1
   #ifdef t10
      #if defined t8
         #if defined(t3)
               #ifndef t20
                  #define t25 25
               #endif
         #else
            #define t15 15
            #define t24 24
         #endif
      #endif   
   #endif
#else
   #ifdef t21
     #define t22 22
   #else
     #define t23 23
   #endif
#endif
#define t7 7
#define t11 11
#define t14 14
#define t15 15
#define t20 20
#define t22 22
#define t23 23
#define t24 42

void main(void)
{
 int sum =0;
 sum = t1+t2+t3+t4+t5; 
 sum = t6+t7+t8+t9+t10;
 sum = t11+t12+t13+t14+t15;
 sum = t16+t20+t22+t23+t25+t24;
}         


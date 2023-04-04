#pragma once

#ifndef HCLASS
#define HCLASS 1

#if HCLASS

   template<typename T>
   struct vec2
   {
	  T x;
	  T y;
   };

   template<typename T>
   struct vec3
   {
	   T x;
	   T y;
	   T z;

   };


   template<typename T>
   struct vec4
   {
	   T x;
	   T y;
	   T z;
	   T w;

   };

   template<long int size , typename T>
   struct vec_n
   {

	   T members[size];

   };


#endif // INITIALIZE

#endif // !1



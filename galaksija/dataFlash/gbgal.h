#ifndef _GB_GAL_H
 #define _GB_GAL_H

 #include "gbCompileDataOpt.h"

 //#include <stddef.h>

 #ifdef gb_use_lib_compile_arduinodroid  
  #include "galFastMode.h"
  #include "galP.h"
  #include "galpomeri.h"
  #include "galprint.h"
  #include "galProba.h"
  #include "galSat.h" 
  #include "galSuperSahPageSoftware.h"
 #else  
  #include "gal/galFastMode.h"
  #include "gal/galP.h"
  #include "gal/galpomeri.h"
  #include "gal/galprint.h"
  #include "gal/galProba.h"
  #include "gal/galSat.h"
  #include "gal/galSuperSahPageSoftware.h"
 #endif


 #define max_list_gal 7
 
 //GAL
 //Title
 static const char * gb_list_gal_title[max_list_gal]={  
  "Fast Mode",
  "P",
  "Pomeri",
  "Print",
  "Proba",
  "Sat",
  "Super Sah Page Software"
 };
 
 //Size of bytes
 static const unsigned short int gb_list_gal_size[max_list_gal]={  
  8268,
  8268,
  8268,
  8268,
  8268,
  8268,
  8268
 };
 
 
 //Data
 static const unsigned char * gb_list_gal_data[max_list_gal]={  
  gb_gal_data_FastMode,
  gb_gal_data_P,
  gb_gal_data_Pomeri,
  gb_gal_data_Print,
  gb_gal_data_Proba,
  gb_gal_data_Sat,
  gb_gal_data_SuperSahPageSoftware
 };


#endif


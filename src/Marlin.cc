#include "lcio.h"


#ifdef LCIO_MAJOR_VERSION 
 #if LCIO_VERSION_GE( 1,2)  
  #include "LCIOSTLTypes.h"
 #endif
#else
  #include "MarlinLCIOSTLTypes.h"
#endif

#include "marlin/ProcessorMgr.h"
#include "marlin/Processor.h"
#include "IO/LCReader.h"

#include "marlin/Parser.h"

#include "marlin/Global.h"

#include <sstream>
#include <fstream>
#include <string>
#include <assert.h>


using namespace lcio ;
using namespace marlin ;


void createProcessors( Parser&  parser ) ;

/** LCIO framework that can be used to analyse LCIO data files
 *  in a modular way. All tasks have to be implemented in Subclasses
 *  of Processor. They will be called in the order specified in the steering file.
 *
 */
int main(int argc, char** argv ){
  
  const char* steeringFileName ;
  
  // read file name from command line
  if( argc > 1 ){
    steeringFileName = argv[1] ;
  } else {
    std::cout << " usage: Marlin lcioframe.steer" << std::endl 
	 << " steering file name "
	 << std::endl ;
    exit(1) ;
  }
  
  
  Parser  parser( steeringFileName ) ;
  assert( ( Global::parameters = parser.getParameters("Global") ) != 0 ) ;

  std::cout <<  "Global parameters : " << std::endl 
	    << *Global::parameters  <<  std::endl ;

  createProcessors( parser ) ;
  

  StringVec lcioInputFiles ; 

  assert( (Global::parameters->getStringVals("LCIOInputFiles" , lcioInputFiles ) ).size() > 0 ) ;

  // create lcio reader 
  LCReader* lcReader = LCFactory::getInstance()->createLCReader() ;
  

  lcReader->registerLCRunListener( ProcessorMgr::instance() ) ; 
  lcReader->registerLCEventListener( ProcessorMgr::instance() ) ; 


  // process the data
  lcReader->open( lcioInputFiles[0]  ) ; 
  // FIXME - read list of files
  //  lcReader->open( lcioInputFiles  ) ; 

  ProcessorMgr::instance()->init() ; 
  lcReader->readStream() ;
  ProcessorMgr::instance()->end() ; 
  lcReader->close() ;

  return 0 ;
}







void  createProcessors(Parser&  parser) {
  
  StringVec activeProcessors ;
  Global::parameters->getStringVals("ActiveProcessors" , activeProcessors ) ;

  for( StringVec::iterator m = activeProcessors.begin() ; m != activeProcessors.end() ; m++){

    StringParameters* p = parser.getParameters( *m )  ;
    

//     std::cout << " Parameters for processor " << *m 
// 	      << std::endl 
// 	      << *p ; ;

    if( p!=0 ){
      std::string type = p->getStringVal("ProcessorType") ;
      
      if( ProcessorMgr::instance()->addActiveProcessor( type , *m , p )  ){

// 	Processor* processor =  ProcessorMgr::instance()->getActiveProcessor( *m ) ;
//	processor->setParameters( p ) ;
      }
    }

  }
}


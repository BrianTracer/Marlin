#include "marlin/TestProcessor.h"
#include <iostream>

namespace marlin{

TestProcessor aTestProcessor ;


TestProcessor::TestProcessor() : Processor("TestProcessor") {

  _description = "Simple processor to test the marlin application. Prints run and event number." ;
}


void TestProcessor::init() { 

  std::cout << "TestProcessor::init()  " << name() 
	    << std::endl 
	    << "  parameters: " << std::endl 
	    << *parameters()  ;

  _nRun = 0 ;
  _nEvt = 0 ;
  
}

void TestProcessor::processRunHeader( LCRunHeader* run) { 
  std::cout << "TestProcessor::processRun()  " << name() 
	    << " in run " << run->getRunNumber() 
	    << std::endl ;

  _nRun++ ;
} 

void TestProcessor::processEvent( LCEvent * evt ) { 
  std::cout << "TestProcessor::processEvent()  " << name() 
	    << " in event " << evt->getEventNumber() << " (run " << evt->getRunNumber() << ") "
	    << std::endl ;
  _nEvt ++ ;

  // always return true  for ProcessorName
  setReturnValue( true ) ;
  
  // set ProcessorName.EvenNumberOfEvents == true if this processor has been called 2n (n=0,1,2,...) times 
  if( !( _nEvt % 2 )  )  
    setReturnValue("EvenNumberOfEvents", true ) ;
  
}

void TestProcessor::check( LCEvent * evt ) { 
  std::cout << "TestProcessor::check()  " << name() 
	    << " in event " << evt->getEventNumber() << " (run " << evt->getRunNumber() << ") "
	    << std::endl ;
}

void TestProcessor::end(){ 
  std::cout << "TestProcessor::end()  " << name() 
	    << " processed " << _nEvt << " events in " << _nRun << " runs "
	    << std::endl ;
  
}

}// namespace marlin

#ifndef marlin_LogStream_h
#define marlin_LogStream_h


#include <iostream>
#include <sstream>

#ifdef MARLIN_DEBUG
 #define MARLIN_SILENCE_LEVEL 0
#else
 #define MARLIN_SILENCE_LEVEL 1
#endif

namespace marlin{
  struct DEBUG{
    static const int level = 0 ;
    static const bool active = ( DEBUG::level >= MARLIN_SILENCE_LEVEL ) ;
    static const char* level_name() { return "DEBUG" ; }
  };
  
  struct MESSAGE{
    static const int level = 1 ;
    static const bool active = ( MESSAGE::level >= MARLIN_SILENCE_LEVEL ) ;
    static const char* level_name() { return "MESSAGE" ; }
  };
  
  struct WARNING{
    static const int level = 2 ;
    static const bool active = ( WARNING::level >= MARLIN_SILENCE_LEVEL ) ;
    static const char* level_name() { return "WARNING" ; }
  };
  
  struct ERROR{
    static const int level = 3 ;
    static const bool active = ( ERROR::level >= MARLIN_SILENCE_LEVEL ) ;
    static const char* level_name() { return "ERROR" ; }
  };
  
  
  /** Helper class for log streams - used by Processor. Prints VERBOSITY level of message
   * and processor name at every line. Template parameter of message method has to be one of DEBUG, MESSAGE, WARNING, ERROR.
   * All messages with a lower verbosity level then the one given at construction are not printed by this logger.. 
   * If marlin is not compiled in DEBUG mode, DEBUG and MESSAGE are suppressed at complie time, i.e. no runtime
   * overhead is created for calls to message<DEBUG>("...") and message<MESSAGE>("..."). 
   *
   * @author F.Gaede, DESY
   * @version $Id: LogStream.h,v 1.1 2007-04-29 14:29:17 gaede Exp $
   */
 
  class LogStream {
    
  protected:
    std::string _name ;
    int _level ;
    
    LogStream() : _name("UNKNOWN"), _level(0) {
    }
    
  public:
    
    LogStream(const std::string& name, int level) : _name(name), _level(level)  {
    }
    
    template <class T>
    void message(const std::string& s){
      
      if( T::active ){  // give the compiler a chance to optimize this away
	
	if( T::level >= _level ) {
	  
	  lineHeader<T>() ;
	  
	  int len = s.length() ;
	  
	  for( int i=0 ; i < len ; ++i ) {
	    
	    std::cout.put( s[i] ) ;
	    
	    if( s[i] == '\n' && i<len-1 )
	      lineHeader<T>() ;
	  }
	  
	  std::cout << std::endl ;
	}   
	
      }
    }
    
  protected :
    
    template<class T>
    void lineHeader() {
      std::cout << "  [ " << T::level_name() << " \"" << _name << "\" ] "  ;
    }
    
  };
}
#endif
// int main() {


//   LogStream<DEBUG> log( "AProcessor" )  ;
// //   LogStream<ERROR> log ;


//   if( DEBUG::active ) {

//     std::stringstream str ;
//     str <<   " helloworld ! " << std::endl 
// 	<<  42  << "   is a number "  
// 	<< std::endl 
// 	<< std::endl ;
  
//     log.message<DEBUG>( str.str()  ) ;
//   }


//   log.message<MESSAGE>( " just discoverd pi to be 3.141592... " ) ;



// } 

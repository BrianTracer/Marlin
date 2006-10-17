
/*
 * this class handles information about LCIO collections
 * needed by MarlinSteerCheck
 *
 * @author: Benjamin Eberhardt, Jan Engels
 *
 */

#ifndef CCCOLLECTION_H
#define CCCOLLECTION_H

#include <string>

namespace marlin {

  class CCProcessor;
  
  class CCCollection{
    
  public:
    
    CCCollection();
    
    const std::string& getValue() const { return _value; }
    const std::string& getType() const { return _type; }
    const std::string& getName() const { return _name; }
    CCProcessor* getSrcProc(){ return _srcProc; } 
    
    void setValue( const std::string& value );
    void setType( const std::string& type );
    void setName( const std::string& name );
    void setSrcProc( CCProcessor* srcProc );
    
  private:
    
    std::string _value;	    // lcio collection name
    std::string _type;	    // lcio collection type
    std::string _name;	    // parameter "name" of the collection in the xml file
    CCProcessor* _srcProc;  // CCProcessor associated to this collection
  };

} // namespace
#endif

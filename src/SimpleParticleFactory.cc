#ifdef USE_CLHEP  // only if CLHEP is available !


#include "marlin/SimpleParticleFactory.h"

#include "IMPL/ReconstructedParticleImpl.h"

#include "CLHEP/HepPDT/ParticleID.hh"


#define CLHEP
#include "UTIL/LCFourVector.h"
#undef CLHEP

using namespace lcio ;


namespace marlin{
  
  SimpleParticleFactory::SimpleParticleFactory() :
    _momentumCut( 0.0000000001 )  {

    _smearingVec.resize( NUMBER_OF_FASTMCPARTICLETYPES ) ;
  }
  

  void SimpleParticleFactory::setMomentumCut( double mCut ) {
    _momentumCut = mCut ;
  }

  void SimpleParticleFactory::registerIFourVectorSmearer( IFourVectorSmearer* sm , 
							  FastMCParticleType type ) {
    _smearingVec[ type ] = sm ;
    
  }
  
  
  FastMCParticleType SimpleParticleFactory::getParticleType( const lcio::MCParticle* mcp ) {


    // assumes that mcp is a stable particle !

    FastMCParticleType type( UNKNOWN )  ;
    
    //     if( mcp->getCharge() > 0.001 ||  mcp->getCharge() < -.001 ){  // mcp->getCharge() != 0.00 
    //     NOTE: the charge is currently (LCIO v01-04) not filled when reading StdHep

    float charge = getCharge( mcp->getPDG() ) ;

    if( charge > 1e-10 || charge < -1e-10  ){  

      type = CHARGED ;
      
    } else if(  mcp->getPDG() == 22 )  { // photon
      
      type = PHOTON ;
      
    } else if(  mcp->getPDG() == 12 || mcp->getPDG() == 14 ||
		mcp->getPDG() == 16 || mcp->getPDG() == 18 )  { // neutrinos

      type = NEUTRINO ;


    } else {  // treat everything else neutral hadron  
      
      type = NEUTRAL_HADRON ;
    }
    
    return type ;
  }
  
  float SimpleParticleFactory::getCharge( int pdgCode ) {

    return  double( HepPDT::ParticleID( pdgCode ).threeCharge() / 3.00 )   ;

  }



  ReconstructedParticle* SimpleParticleFactory::createReconstructedParticle( const MCParticle* mcp ) {
    
    // this is where we do the fast Monte Carlo ....
    
    LCFourVector<MCParticle>  mc4V( mcp ) ;
    
    FastMCParticleType type = getParticleType(mcp ) ;
    
  
    IFourVectorSmearer* sm = _smearingVec[ type ] ;

    HepLorentzVector reco4v(0.,0.,0.,0.)  ;
    
    if( sm != 0 ){

      reco4v = sm->smearedFourVector( mc4V , mcp->getPDG() ) ;
    }
    
    ReconstructedParticleImpl* rec = 0 ;
    
    if(  reco4v.vect().mag() >  _momentumCut  ) {  
      
      rec = new ReconstructedParticleImpl ;
      
      float p[3] ;
      p[0] = reco4v.px() ;
      p[1] = reco4v.py() ;
      p[2] = reco4v.pz() ;
      
      rec->setMomentum( p ) ;
      rec->setEnergy( reco4v.e() ) ;
      rec->setMass( reco4v.m() ) ;

      rec->setCharge( getCharge( mcp->getPDG() ) ) ;
    
      float vtx[3] ;
      vtx[0] = mcp->getVertex()[0] ;
      vtx[1] = mcp->getVertex()[1] ;
      vtx[2] = mcp->getVertex()[2] ;
      rec->setReferencePoint( vtx ) ;

      rec->setType( type ) ;
    }
    
    return  rec ;
  }


} // namespace


#endif

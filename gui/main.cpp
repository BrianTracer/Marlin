#include <QApplication>

#ifdef MARLIN_USE_DLL
#include "marlin/Parser.h"
#include "marlin/ProcessorLoader.h"
#endif

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    std::cout << "\nPlease be patient, loading GUI...\n";

#ifdef MARLIN_USE_DLL

  //------ load shared libraries with processors ------
                                                                                                                                                            
  StringVec libs ;
  LCTokenizer t( libs, ':' ) ;
                                                                                                                                                            
  std::string marlinProcs("") ;
                                                                                                                                                            
  char * var =  getenv("MARLIN_PROCESSOR_LIBS" ) ;
                                                                                                                                                            
  if( var != 0 ) {
    marlinProcs = var ;
  } else {
    std::cout << std::endl << " You have no MARLIN_PROCESSOR_LIBS variable in your environment "
      " - so no processors will be loaded. ! " << std::endl << std::endl ;
  }
                                                                                                                                                            
  std::for_each( marlinProcs.begin(), marlinProcs.end(), t ) ;
                                                                                                                                                            
  ProcessorLoader loader( libs.begin() , libs.end()  ) ;
                                                                                                                                                            
  //------- end processor libs -------------------------
                                                                                                                                                            
#endif
	
    QApplication app(argc, argv);

    //set the selection color to blue instead of black ;)
    QPalette pal = QApplication::palette();
    pal.setColor(QPalette::Highlight, QColor(0,90,126, 128) );
    QApplication::setPalette(pal);

    MainWindow window;

    if( argc == 2 ){ 
	window.setMarlinSteerCheck(argv[1]);
    }
    
    window.show();

    return app.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "marlin/MarlinSteerCheck.h"

class QListWidget;
class QTableWidget;
class QTableWidgetItem;
class QGroupBox;
class QMenu;
class QSplitter;
class QPushButton;
class QByteArray;
class QTextEdit;
class QLabel;
class QString;
class QActionGroup;
class QTextBrowser;

using namespace marlin;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void setMarlinSteerCheck( const char* filename=NULL );

signals:
    void modifiedContent();

public slots:
    void aProcNameChanged();
    void iProcNameChanged();

    void editAProcessor(int row=-1);

protected slots:
    virtual void closeEvent(QCloseEvent *e);
	
private slots:
    void changeStyle(bool checked);
    void aboutGUI();
    void help();
    void madeChanges();
    void selectionChanged(int row);
    void hideIProcessors(bool checked);
    void hideAProcErrors(bool checked);
    
    void addAProcessor();
    void remAProcessor();
    void remIProcessor();
    void editIProcessor();
    void activateProcessor();
    void deactivateProcessor();
    void moveLCIOFileUp();
    void moveLCIOFileDown();
    void moveProcessorUp();
    void moveProcessorDown();
    void changeGearFile();
    void addLCIOFile();
    void remLCIOFile();
    void newXMLFile();
    void openXMLFile();
    void saveXMLFile();
    void saveAsXMLFile();

private:
    void setupViews();
    void updateProcessors();
    void updateAProcessors( int pos=-1 );
    void updateIProcessors( int pos=-1 );
    void updateFiles( int pos=-1 );
    void updateGlobalSection();
    void selectRow( QTableWidget* t, int row, bool colors=false );
    void selectLCIORow( QListWidget* t, int row );
    void createMenus();
    void checkCurrentStyle();

    //variables
    bool _modified;
    std::string _file;
    MarlinSteerCheck* msc;

    QGroupBox *aProcErrorsGBox;
    QGroupBox *viewButtonsGBox;
    QGroupBox *aProcButtonsGBox;
    QGroupBox *iProcButtonsGBox;
    QGroupBox *aProcGBox;
    QGroupBox *iProcGBox;
    QGroupBox *lcioFilesGBox;
    QGroupBox *lcioColsGBox;
    QGroupBox *globalSectionGBox;
    
    QTableWidget *aProcTable;
    QTableWidget *iProcTable;
    QTableWidget *globalSectionTable;
    QTableWidget *lcioColsTable;
    QListWidget *lcioFilesList;

    QTextEdit *aProcErrors;
    
    QString saveChangesMsg;
    QString aboutGUIMsg;
    
    QPushButton *hideProcs;
    QPushButton *hideErrors;
    QList<int> vSizes;
    int vSplitterESize;
    int vSplitterISize;
    QSplitter *vSplitter;
    QSplitter *hSplitter;
    
    QWidget *centralWidget;

    QActionGroup *styleActionGroup;

    QTextBrowser *browser;
};

#endif

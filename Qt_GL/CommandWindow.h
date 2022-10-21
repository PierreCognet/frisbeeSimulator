#ifndef PRJ_COMMANDWINDOW_H
#define PRJ_COMMANDWINDOW_H

#include <QtWidgets>
#include <QGridLayout>
#include "GLWidget.h"
#include "InfoWindow.h"
// #include "Liaison.h"
// #include "Tissu.h"
// #include "TissuDisque.h"
// #include "TissuRectangle.h"
// #include "Masse.h"


class CommandWindow : public QWidget {

Q_OBJECT

public :

    CommandWindow (QWidget *parent);

private slots :

    void simulate();              // Needed to display and quit window (OpenGL).

    void setFrisbeeState();
    void toggleUvwBodyEarthAxes();

    // void saveFile();

    // void loadFile();

    // void quit();

    // void quit2();



private :

    QTabWidget *tabs;
    QWidget* masterPage;
    QWidget* frisbeePage;
    QWidget* timePage;
    // QWidget *page3 ;
    QWidget* cameraPage;
    // QWidget *page5 ;
    // QWidget *page6 ;
    // QWidget *page7 ;
    // QLabel *nomF;

    // QPushButton* save;
    // QPushButton* load;
    // QComboBox *TypeTissu;
    // QComboBox *TypeContraintes;
    // QComboBox *TissuComp;
    

    QLabel* camPositionTitle;


    QPushButton* resetTimeButton;
    // QPushButton *boutonTri ;
    // QPushButton *boutonSpring ;
    // QPushButton *boutonMass ;

    QGridLayout* integratorGrid;

    
    // QPushButton *boutonIntegrateurEuler;
    // QPushButton *boutonIntegrateurNewmark;
    QPushButton* rk4Button;


    QPushButton* startStopButton;
    QPushButton* stopButton;
    QPushButton* startButton;

    QPushButton* zButton;
    QPushButton* zzButton;
    QPushButton* xButton;
    QPushButton* xxButton;
    QPushButton* yButton;
    QPushButton* yyButton;
    
    // QPushButton *boutonCDM; // set camera on fribee ? ***

    // QPushButton *ToggleContr;
    // QPushButton *ToggleCass;
    //QPushButton *boutonOK;

    QSlider* playbackSpeedSlider;
    
    QGridLayout* masterGrid;
    QGridLayout* frisbeeGrid;
    QGridLayout* timeGrid;
    QGridLayout* cameraGrid;
    // QGridLayout *box4;
    // QGridLayout *box5;
    // QGridLayout *fileSaveLoadGrid;
    // QGridLayout *box7;

    QLabel* playbackSpeedLabel;
    
    // QPushButton* ClearTT;
    // QLineEdit* filename;
    // QLabel* infofile;
    QLabel* integratorLabel;

    // QPushButton *Del_Tissu;
    // QPushButton *Del_Contr;


    // QGridLayout *ChoixTissu;
    // QWidget *ChoixT;

    QDoubleSpinBox* xSpinBox;
    QDoubleSpinBox* ySpinBox;
    QDoubleSpinBox* zSpinBox;
    QDoubleSpinBox* phiSpinBox;
    QDoubleSpinBox* thetaSpinBox;
    QDoubleSpinBox* psiSpinBox;
    QDoubleSpinBox* uSpinBox;
    QDoubleSpinBox* vSpinBox;
    QDoubleSpinBox* wSpinBox;
    QDoubleSpinBox* pSpinBox;
    QDoubleSpinBox* qSpinBox;
    QDoubleSpinBox* rSpinBox;

    QLabel* xLabel;
    QLabel* yLabel;
    QLabel* zLabel;
    QLabel* phiLabel;
    QLabel* thetaLabel;
    QLabel* psiLabel;
    QLabel* uLabel;
    QLabel* vLabel;
    QLabel* wLabel;
    QLabel* pLabel;
    QLabel* qLabel;
    QLabel* rLabel;

    QPushButton* setFrisbeeStateButton;
    QPushButton* toggleUvwBodyEarthAxesButton;
    bool uvwIsBodyNotEarthAxes;



    // QDoubleSpinBox* MasseGet ;
    // QDoubleSpinBox* MasseGet1;
    // QDoubleSpinBox* LambdaGet ;
    // QDoubleSpinBox* loGet  ;
    // QDoubleSpinBox* KGet  ;
    // QSpinBox* tailleGet;
    // QDoubleSpinBox* PasRadialGet;
    // QDoubleSpinBox* PasAngulaireGet;

    // QDoubleSpinBox* VecXGet ;
    // QDoubleSpinBox* VecYGet ;
    // QDoubleSpinBox* VecZGet ;
    // QDoubleSpinBox* VecXGet1 ;
    // QDoubleSpinBox* VecYGet1 ;
    // QDoubleSpinBox* VecZGet1 ;
    // QDoubleSpinBox* VecXGet2 ;
    // QDoubleSpinBox* VecYGet2 ;
    // QDoubleSpinBox* VecZGet2 ;

    // // For the popup window
    // QPushButton* create;
    // QPushButton* Compose;
    // QPushButton* pop;
    // QPushButton* Quit;

    // void tissuchaine();                 //Fonctions pour les champs variables
    // void tissuCarre();
    // void tissuHexagone();
    // void tissuDisque();
    // void tissuRectangle();
    // void tissulibre();
    // void tissuCarre2();
    // void tissuComp();




    // QGridLayout* ChoixContraintes;
    // QWidget* ChoixC;
    // QGridLayout* set;

    // QDoubleSpinBox* CentreGet1;
    // QDoubleSpinBox* CentreGet2;
    // QDoubleSpinBox* CentreGet3;
    // QDoubleSpinBox* RayonGet;
    // QDoubleSpinBox* GetTpDebut;
    // QDoubleSpinBox* GetTpFin;
    // QDoubleSpinBox* Force1;
    // QDoubleSpinBox* Force2;
    // QDoubleSpinBox* Force3;
    // QDoubleSpinBox* Freq;
    // QPushButton* CreateC;
    // QDialog* PopUp;
    // QSpinBox* massedep;
    // QSpinBox* massearr;



    // void crochet();
    // void Impulsion();
    // void Sinusoidale();
    // void levitateur();
    // void Boule();
    // void trounoir();

    // std::vector <Liaison> Liasons;
    // std::vector <Masse> Masses;
    // std::vector <Tissu*> Tissus;


    // void Init_champC();
    // void Init_champT(QGridLayout* Q);           //Pour un code plus comprehensible


    GLWidget* w;
    InfoWindow* infoWin; // Information window.

};


#endif


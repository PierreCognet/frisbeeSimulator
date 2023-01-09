#ifndef PRJ_GLWIDGET_H
#define PRJ_GLWIDGET_H

#include <QGLWidget>
#include <QObject>
#include <QTime>
#include "CommandWindow.h"
#include "OpenGLViewer.h"
#include "System.h"
#include "Integrator.h"

class CommandWindow;

// enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime };

class GLWidget : public QGLWidget {

Q_OBJECT

public:

	// GLWidget(IntegratorType type = RungeKutta, QWidget* parent = nullptr);
	GLWidget(IntegratorType type = RungeKutta, CommandWindow* parent = nullptr);


	virtual ~GLWidget();  // Delete dyamically allocated integrator.

public slots :

	// void quit() { close(); }    // To close window. Deleted because close is directly used.

	// *** to do: find a way to pass argument to slot without passing through the signal
	void setcamX();
	void setcamXX();
	void setcamY();
	void setcamYY();
	void setcamZ();
	void setcamZZ();
	void toggleFrisbeeTrackingCameraMode();

	// void toggle_tri ();             //setters pour les
	// void toggle_Mass();             //modes de dessin
	// void toggle_springs();

	// void set_Euler();
	// void set_Newmark();	
	void setRK4();

	// void delete_last_tissu ();
	// void delete_last_contrainte();
	// void clear_tissu();

	void toggleTime();
	void setPlaybackSpeed(int a);
	double getCurrentTime();
	void resetTime();

	// void Toggle_Cassures();
	// void Toggle_Contr();


public :

	//----------------------Enregistrer le système----------------------
	// void sauvegarderFichier(std::string const& nomFichierSANSLExtension) const;
	// void chargerFichier(std::string const& nomFichierSANSLExtension);
	

	
	// //--------------------------Gestion Tissus--------------------------
	// void create_tissu (FormeTissu forme		//fabrique le tissu désiré
	// 									 ,size_t taille
	// 									 ,double masse
	// 									 ,double lam 				= Masse::lambda_defaut
	// 									 ,double k 					= Ressort::k_defaut
	// 									 ,double l0					= Ressort::l0_defaut
	// 									 ,Vecteur3D const& position	= cste::vectnul );

	// 	void create_tissu (std::vector<Masse> const& masses		 //appelle constructeur de tissu (donc copie les masses)
	// 										,std::vector<Liaison> const& liaisonsAFaire );

	// void create_tissuChaine( double m
	// 					,double lambda
	// 					,double k
	// 					,double l0
	// 					,std::vector<Vecteur3D> const& positions  );

	// void create_tissuRectangle( double m
	// 							,Vecteur3D const& origine
	// 							,Vecteur3D const& l		//largeur
	// 							,Vecteur3D const& L		//Longueur
	// 							,double densite
	// 							,double lambda
	// 							,double k
	// 							,double l0 );
								
	// void create_tissuDisque( double m 	//utilisera pasAngulaire par defaut
	// 					,Vecteur3D const& centre
	// 					,Vecteur3D const& Rn	//rayon normale
	// 					,double pasRadial
	// 					,double lambda
	// 					,double k );	//en degres	

	// void create_tissuDisque( double m 
	// 						,Vecteur3D const& centre
	// 						,Vecteur3D const& Rn	//rayon normale
	// 						,double pasRadial
	// 						,double lambda
	// 						,double k 
	// 						,double pasAngulaire);	//en degres

	// 	void create_tissuCompose( std::vector<Tissu*> const& tissus );




	// //----------------------Gestion Contraintes-------------------------
	// void create_Crochet(Vecteur3D const& centre , double const& rayon);
	
	// void create_Impulsion(Vecteur3D const& centre ,double const& R
	// 					,double tDebut, double tFin
	// 					,Vecteur3D const& force
	// 					,std::vector<size_t> const& tissusCible = {});

	// void create_ImpulsionSinusoidale(Vecteur3D const& centre ,double const& R
	// 							,double tDebut, double tFin
	// 							,Vecteur3D const& force
	// 							,double freq
	// 							,std::vector<size_t> const& tissusCible = {});
	
	// void create_Levitateur(Vecteur3D const& centre , double const& rayon);
	
	// void create_BouleRigide(Vecteur3D const& centre , double const& rayon);

	// 	void create_TrouNoir(Vecteur3D const& centre , double const& rayon, double const& M);

//=============Getters pour le CDM / Integrateur======================================

	// std::vector<Vecteur3D> Get_CdM_pos () const {return s->get_CDM();}

	void setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr, bool const& uvwIsBodyNotEarthAxes);
	void coutSystem();
	
	const Vector3 getFrisbeePosition() const;
	System* getSystem();

	IntegratorType getIntegratorType() { return integrator->getType(); }

	// bool gettri() const {return view.get_tri();}
	// bool getmas() const {return view.get_mas();}
	// bool getspr() const {return view.get_spr();}
	// bool getContrDess() const {return view.get_contr();}
	// bool getCass() const {return s->get_Cassable();}

	void saveCurrentState(std::string fileName) const;
	void loadState(std::string const& fileName);



//====================================================================================

private:
	// The 3 key methods of class QGLWidget to reimplement.
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;

	// Methods for event handling. 
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void timerEvent(QTimerEvent* event)  override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event)  override;

	void stop();

	bool frisbeeTrackingCameraMode;
	int timerId; // Timer.
	QTime chronometer; // To make objects evolve at the correct time step.
	QPoint lastMousePosition;
	OpenGLViewer view; // Canvas.
	System* s; // Objects to draw and make evolve.
	Integrator* integrator; // delete
	double playbackSpeed; // To change the speed at which time flows (multiplier). *** delete

	// std::map<int, KeyAction> keyActionMap;
	// // std::map<Qt::Key, KeyAction> keyActionMap;
	CommandWindow* parent; // The parent window.


};

#endif

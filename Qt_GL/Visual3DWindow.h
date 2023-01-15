#ifndef PRJ_VISUAL3DWINDOW_H
#define PRJ_VISUAL3DWINDOW_H

#include <QGLWidget>
#include <QObject>
#include "VisualSimulation.h"
#include "OpenGLViewer.h"

// class VisualSimulation;
class KeyActionWindow;

class Visual3DWindow : public QGLWidget {

Q_OBJECT

public:

	// Visual3DWindow(IntegratorType type = RungeKutta, QWidget* parent = nullptr);
	// Visual3DWindow(VisualSimulation* parent = nullptr);
	Visual3DWindow(KeyActionWindow* parent);

	virtual ~Visual3DWindow();  // Delete dyamically allocated integrator.

	OpenGLViewer* getView() { return &view; }

	void lookAt(System* s);
	// void rotate(double const& angle, Vector3 const& v);	
	// void translate(Vector3 const& v);


public slots :

	// *** to do: find a way to pass argument to slot without passing through the signal
	void setcamX();
	void setcamXX();
	void setcamY();
	void setcamYY();
	void setcamZ();
	void setcamZZ();


public :
	// void setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr, bool const& uvwIsBodyNotEarthAxes);
	

private:
	// The 3 key methods of class QGLWidget to reimplement.
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;

	// Methods for event handling. 
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event)  override;
	void closeEvent(QCloseEvent* event);


	QPoint lastMousePosition;
	OpenGLViewer view; // Canvas.

	// std::map<int, KeyAction> keyActionMap;
	// // std::map<Qt::Key, KeyAction> keyActionMap;
	// VisualSimulation* parent; // The parent window.
	KeyActionWindow* parent; // The parent window.


};

#endif

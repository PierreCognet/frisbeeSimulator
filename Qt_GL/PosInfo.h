#ifndef PRJ_POSINFO_H
#define PRJ_POSINFO_H

#include <QGLWidget>
#include <QTime>
#include "OpenGLViewer.h"
#include <QObject>
#include "VisualSimulation.h"

class VisualSimulation;

enum AxisType {XY , Z};

class PosInfo : public QGLWidget {

public:

	PosInfo(QWidget* parent = nullptr, AxisType check = XY) // **** added
		: QGLWidget(parent), axisType(check), v() {} // **** added
	// PosInfo(VisualSimulation* vs, AxisType check = XY,  QWidget* parent = nullptr)
	// 	: QGLWidget(parent), vs(vs), axisType(check) {}
	// PosInfo(QWidget* parent, System* sys, AxisType check = XY) // **** deleted
	// 	: QGLWidget(parent), sys(sys), axisType(check) {} // **** deleted

	virtual ~PosInfo() {}
	void updateData(Vector3 const& v); // **** added

private:

	// The 3 key methods of the QGLWidget class to reimplement.
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;


	// virtual void timerEvent(QTimerEvent* event)  override; // **** deleted

	OpenGLViewer view; // We use the same view where we add a function. We could re create a view but we lack the required competences. 

	// VisualSimulation* vs;
	Vector3 v; // **** added
	AxisType axisType;

	// System* sys; // **** deleted
	// QTime chronometre;
};



#endif

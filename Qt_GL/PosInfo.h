#ifndef PRJ_POSINFO_H
#define PRJ_POSINFO_H

#include <QGLWidget>
#include <QTime>
#include "OpenGLViewer.h"
#include <QObject>
#include "GLWidget.h"

class GLWidget;

enum AxisType {XY , Z};

class PosInfo : public QGLWidget {

public:

	PosInfo(GLWidget* i, AxisType check = XY,  QWidget* parent = nullptr)
		: QGLWidget(parent), GetInfo(i), axisType(check) {}

	virtual ~PosInfo() {}

private:

	// The 3 key methods of the QGLWidget class to reimplement.
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;

	virtual void timerEvent(QTimerEvent* event)  override;

	OpenGLViewer view; // We use the same view where we add a function. We could re create a view but we lack the required competences. 

	GLWidget* GetInfo;
	QTime chronometre;
	AxisType axisType;
};



#endif

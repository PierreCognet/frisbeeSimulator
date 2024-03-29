#ifndef PRJ_INFOWINDOW_H
#define PRJ_INFOWINDOW_H
#include <QtWidgets>
#include <QGridLayout>
#include "PosInfo.h"
#include "VisualSimulation.h"

class VisualSimulation;
class PosInfo;

class InfoWindow : public QWidget {
Q_OBJECT
	public :
		InfoWindow (QWidget *parent); // **** delete
		// InfoWindow (QWidget *parent, System* sys, Integrator* integ); // **** deleted
		// InfoWindow (QWidget *parent, VisualSimulation* vs);

	virtual ~InfoWindow();  // Delete dyamically allocated integrator.

	void refreshLabels(System* sys);
	// void refreshLabels(System* sys, Integrator* integ); // **** should have added it but it was already there


	public slots :
		// void quitter() { close();}

	private :
		// QTime chronometre;

		// QLabel* triangle;
		// QLabel* springs;
		// QLabel* Masses;
		// QLabel* m;
		// QLabel* s;
		// QLabel* t;

		QGridLayout* mainGrid;

		QGridLayout* posGrid;
		QLabel* xyAxesTitleLabel;
		QLabel* zAxisTitleLabel;
		PosInfo* xyAxes;
		PosInfo* zAxis;


		QGridLayout* infoGrid;

		QLabel* integratorTitleLabel; // *** delete this ?
		QLabel* timeTitleLabel;
		QLabel* xTitleLabel;
		QLabel* yTitleLabel;
		QLabel* zTitleLabel;
		QLabel* phiTitleLabel;
		QLabel* thetaTitleLabel;
		QLabel* psiTitleLabel;
		QLabel* uTitleLabel;
		QLabel* vTitleLabel;
		QLabel* wTitleLabel;
		QLabel* pTitleLabel;
		QLabel* qTitleLabel;
		QLabel* rTitleLabel;
		
		QLabel* integratorLabel;
		QLabel* timeLabel;
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


		// VisualSimulation* vs; // This is where we get the info to be displayed.
		// System* sys; // This is where we get the info to be displayed. // **** deleted
		// Integrator* integ; // This is where we get the info to be displayed. // **** deleted

		// void refreshLabels(); // **** deleted
		// void setIntegratorLabel(); // **** deleted
		void setIntegratorLabel(Integrator* integ); // **** added
		// virtual void timerEvent(QTimerEvent* event) override; // **** deleted

		void closeEvent(QCloseEvent* event) override;

};

#endif
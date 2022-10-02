#include "InfoWindow.h"

InfoWindow::InfoWindow(QWidget *parent, GLWidget* w)
	: QWidget(parent), w(w) {

	startTimer(20);

	// Set shape.
	setFixedSize(700, 480);
	setGeometry(0, 1000, 700, 480);

	// Create widgets.
	xyAxesTitleLabel = new QLabel("Projection on XY axes:");
	zAxisTitleLabel = new QLabel("Projection on Z axis:");

	xyAxes = new PosInfo(w,XY,this);
	zAxis = new PosInfo(w,Z,this);


	integratorTitleLabel = new QLabel("Current integrator: ");
	integratorLabel = new QLabel("");
	timeTitleLabel = new QLabel("Time");
	timeLabel = new QLabel ("");

	xTitleLabel = new QLabel("x");
	yTitleLabel = new QLabel("y");
	zTitleLabel = new QLabel("z");
	phiTitleLabel = new QLabel("phi");
	thetaTitleLabel = new QLabel("theta");
	psiTitleLabel = new QLabel("psi");
	uTitleLabel = new QLabel("u");
	vTitleLabel = new QLabel("v");
	wTitleLabel = new QLabel("w");
	pTitleLabel = new QLabel("p");
	qTitleLabel = new QLabel("q");
	rTitleLabel = new QLabel("r");

	xLabel = new QLabel("");
	yLabel = new QLabel("");
	zLabel = new QLabel("");
	phiLabel = new QLabel("");
	thetaLabel = new QLabel("");
	psiLabel = new QLabel("");
	uLabel = new QLabel("");
	vLabel = new QLabel("");
	wLabel = new QLabel("");
	pLabel = new QLabel("");
	qLabel = new QLabel("");
	rLabel = new QLabel("");

	// triangle = new QLabel ("Triangles : ");
	// springs = new QLabel ("Ressorts : ");
	// Masses = new QLabel ("Masses : ");
	// t = new QLabel ("OFF");
	// s = new QLabel ("ON");
	// m = new QLabel ("ON");

	// QLabel* titreContr  = new QLabel("     Contraintes : ");
	// QLabel* titreCass  = new QLabel("      Ressorts Cassables : ");

	// QLabel* titreCDM = new QLabel("    Centre de Masse du Tissu (X,Y et Z)");

	// Contr = new QLabel("ON");
	// Cass = new QLabel("ON");


	// Parametrize our Widgets
	xyAxes->setGeometry(10, 10, 100, 100);
	zAxis->setGeometry(300, 400, 100, 100);
	xyAxes->show();


	// Set main layout.
	posGrid = new QGridLayout;
	posGrid->addWidget(xyAxesTitleLabel, 1, 2, 1, 1);
	posGrid->addWidget(zAxisTitleLabel, 1, 3, 1, 1);
	posGrid->addWidget(xyAxes, 2, 2, 3, 1);
	posGrid->addWidget(zAxis, 2, 3, 3, 1);


	infoGrid = new QGridLayout;
	infoGrid->addWidget(integratorTitleLabel, 0, 0);
	infoGrid->addWidget(integratorLabel, 0, 1);
	infoGrid->addWidget(timeTitleLabel, 0, 2);
	infoGrid->addWidget(timeLabel, 0, 3);

	infoGrid->addWidget(xTitleLabel, 2, 0);
	infoGrid->addWidget(yTitleLabel, 3, 0);
	infoGrid->addWidget(zTitleLabel, 4, 0);
	infoGrid->addWidget(xLabel, 2, 1);
	infoGrid->addWidget(yLabel, 3, 1);
	infoGrid->addWidget(zLabel, 4, 1);

	infoGrid->addWidget(phiTitleLabel, 2, 2);
	infoGrid->addWidget(thetaTitleLabel, 3, 2);
	infoGrid->addWidget(psiTitleLabel, 4, 2);
	infoGrid->addWidget(phiLabel, 2, 3);
	infoGrid->addWidget(thetaLabel, 3, 3);
	infoGrid->addWidget(psiLabel, 4, 3);

	infoGrid->addWidget(uTitleLabel, 5, 0);
	infoGrid->addWidget(vTitleLabel, 6, 0);
	infoGrid->addWidget(wTitleLabel, 7, 0);
	infoGrid->addWidget(uLabel, 5, 1);
	infoGrid->addWidget(vLabel, 6, 1);
	infoGrid->addWidget(wLabel, 7, 1);

	infoGrid->addWidget(pTitleLabel, 5, 2);
	infoGrid->addWidget(qTitleLabel, 6, 2);
	infoGrid->addWidget(rTitleLabel, 7, 2);
	infoGrid->addWidget(pLabel, 5, 3);
	infoGrid->addWidget(qLabel, 6, 3);
	infoGrid->addWidget(rLabel, 7, 3);

	// box1 = new QGridLayout;
	// box1->addWidget(triangle , 0 , 0);
	// box1->addWidget(Masses , 1 , 0);
	// box1->addWidget(springs , 2 , 0);
	// box1->addWidget(t , 0 , 1);
	// box1->addWidget(m , 1 , 1);
	// box1->addWidget(s , 2 , 1);

	// box2 = new QGridLayout;
	// box2->addWidget(titreContr , 0 , 1);
	// box2->addWidget(titreCass , 1 , 1);
	// box2->addWidget(Contr , 0 , 2);
	// box2->addWidget(Cass , 1 , 2);
	// box2->addWidget(titreCDM , 2, 1);


	mainGrid = new QGridLayout;
	// mainGrid->addLayout(box1 , 2 , 1);
	// mainGrid->addLayout(box2,1 , 2 );
	

	// mainGrid->addLayout(infoGrid, 1, 1, 2, 1);
	// mainGrid->addWidget(xyAxesTitleLabel, 1, 2);
	// mainGrid->addWidget(zAxisTitleLabel, 1, 3);
	// mainGrid->addWidget(xyAxes, 2, 2);
	// mainGrid->addWidget(zAxis, 2, 3);


	mainGrid->addLayout(infoGrid, 1, 1);
	mainGrid->addLayout(posGrid, 1, 2);


	this->setLayout(mainGrid);

	refreshLabels();
}

void InfoWindow::setIntegratorLabel(){
	switch (w->getIntegratorType()) {
		// case Euler:
		//     integratorLabel->setText("Euler");
		//     break;
		// case Newmark:
		//     integratorLabel->setText("Newmark");
		//     break;
		case RungeKutta:
			integratorLabel->setText("RungeKutta");
			break;
	}
}

void InfoWindow::refreshLabels(){
	QString currentTime = QString::number(w->getCurrentTime());
	timeLabel->setText(currentTime);

	// if (w->gettri())
	//     {t->setText("ON");}
	//     else {t->setText("OFF");}

	// if (w->getmas())
	//     {m->setText("ON");}
	//     else {m->setText("OFF");}

	// if (w->getspr())
	//     {s->setText("ON");}
	//     else {s->setText("OFF");}

	// if (w->getContrDess())
	//     {Contr->setText("ON");}
	//     else {Contr->setText("OFF");}

	// if (w->getCass())
	//     {Cass->setText("ON");}
	//     else {Cass->setText("OFF");}

	setIntegratorLabel();


	System* s (w->getSystem());
	Frisbee* f (s->getFrisbee());
	Vector3 v;
	v = f->xyz();
	xLabel->setText(QString::number(v[0]));
	yLabel->setText(QString::number(v[1]));
	zLabel->setText(QString::number(v[2]));

	v = f->phiThetaPsi();
	phiLabel->setText(QString::number(v[0]));
	thetaLabel->setText(QString::number(v[1]));
	psiLabel->setText(QString::number(v[2]));

	v = f->uvw();
	uLabel->setText(QString::number(v[0]));
	vLabel->setText(QString::number(v[1]));
	wLabel->setText(QString::number(v[2]));

	v = f->pqr();
	pLabel->setText(QString::number(v[0]));
	qLabel->setText(QString::number(v[1]));
	rLabel->setText(QString::number(v[2]));
}


void InfoWindow::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);
	refreshLabels();
}

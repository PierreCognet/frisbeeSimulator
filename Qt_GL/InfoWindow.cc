#include "InfoWindow.h"

// InfoWindow::InfoWindow(QWidget *parent, VisualSimulation* vs)
// 	: QWidget(parent), vs(vs) {
// InfoWindow::InfoWindow(QWidget *parent, System* sys, Integrator* integ) // **** deleted
// 	: QWidget(parent), sys(sys), integ(integ) { // **** deleted
InfoWindow::InfoWindow(QWidget *parent) // **** added
	: QWidget(parent) { // **** added

	// startTimer(20); // **** deleted

	// Set shape.
	setFixedSize(700, 480);
	setGeometry(0, 1000, 700, 480);

	// Create widgets.
	xyAxesTitleLabel = new QLabel("Projection on XY axes:");
	zAxisTitleLabel = new QLabel("Projection on Z axis:");

	// xyAxes = new PosInfo(vs,XY,this);
	// zAxis = new PosInfo(vs,Z,this);
	// xyAxes = new PosInfo(this, sys, XY); // **** deleted
	// zAxis = new PosInfo(this, sys, Z); // **** deleted
	xyAxes = new PosInfo(this, XY); // **** added
	zAxis = new PosInfo(this, Z); // **** added


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

	// Parametrize our Widgets
	xyAxes->setGeometry(10, 10, 100, 100);
	zAxis->setGeometry(300, 400, 100, 100);
	xyAxes->show(); // *** why not Axis show as well ? maybe this line is useless 

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

	mainGrid = new QGridLayout;
	mainGrid->addLayout(infoGrid, 1, 1);
	mainGrid->addLayout(posGrid, 1, 2);

	this->setLayout(mainGrid);

	// refreshLabels(); // **** deleted
}

InfoWindow::~InfoWindow() {
	delete xyAxes;
	delete zAxis;
	// cerr << "InfoWindow::~InfoWindow()" << endl;
}


// void InfoWindow::setIntegratorLabel(){
// 	switch (vs->getIntegratorType()) {
// void InfoWindow::setIntegratorLabel(){ // **** deleted
// 	switch (integ->getType()) { // **** deleted
void InfoWindow::setIntegratorLabel(Integrator* integ){ // **** added
	switch (integ->getType()) { // **** added
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

// **** added thee following
void InfoWindow::refreshLabels(System* sys){
// void InfoWindow::refreshLabels(System* sys, Integrator* integ){
	QString currentTime = QString::number(sys->time());
	timeLabel->setText(currentTime);

	// setIntegratorLabel();
	// setIntegratorLabel(integ); *****

	// System* s (vs->getSystem());
	// Frisbee* f (s->getFrisbee());
	Frisbee* f (sys->getFrisbee());
	Vector3 v;
	v = f->xyz();
	xLabel->setText(QString::number(v[0]));
	yLabel->setText(QString::number(v[1]));
	zLabel->setText(QString::number(v[2]));

	xyAxes->updateData(v);
	zAxis->updateData(v);

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

// **** deleted thee following
// void InfoWindow::refreshLabels(){
// 	// QString currentTime = QString::number(vs->getCurrentTime());
// 	QString currentTime = QString::number(sys->time());
// 	timeLabel->setText(currentTime);

// 	setIntegratorLabel();

// 	// System* s (vs->getSystem());
// 	// Frisbee* f (s->getFrisbee());
// 	Frisbee* f (sys->getFrisbee());
// 	Vector3 v;
// 	v = f->xyz();
// 	xLabel->setText(QString::number(v[0]));
// 	yLabel->setText(QString::number(v[1]));
// 	zLabel->setText(QString::number(v[2]));

// 	xyAxes->updateData(v); // **** added
// 	zAxis->updateData(v); // **** added

// 	v = f->phiThetaPsi();
// 	phiLabel->setText(QString::number(v[0]));
// 	thetaLabel->setText(QString::number(v[1]));
// 	psiLabel->setText(QString::number(v[2]));

// 	v = f->uvw();
// 	uLabel->setText(QString::number(v[0]));
// 	vLabel->setText(QString::number(v[1]));
// 	wLabel->setText(QString::number(v[2]));

// 	v = f->pqr();
// 	pLabel->setText(QString::number(v[0]));
// 	qLabel->setText(QString::number(v[1]));
// 	rLabel->setText(QString::number(v[2]));
}


// **** deleted fct
// void InfoWindow::timerEvent(QTimerEvent* event) {
// 	Q_UNUSED(event);
// 	refreshLabels();
// }

void InfoWindow::closeEvent(QCloseEvent* event) {
	// cerr << "InfoWindow::closeEvent(QCloseEvent* event)" << endl;
	// vs->close();
	parentWidget()->close();
	event->accept();
}


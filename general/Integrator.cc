#include "Integrator.h"
#include "Frisbee.h"

using namespace std;

Integrator::~Integrator() {}

void Integrator::setVariables(Frisbee& fris, Vector3 const& newXyz, Vector3 const& newPhiThetaPsi, Vector3 const& newUvw, Vector3 const& newPqr) const {
	fris.setXyz(newXyz);
	fris.setPhiThetaPsi(newPhiThetaPsi);
	fris.setUvw(newUvw);
	fris.setPqr(newPqr);

// fris.computeDerivatives(); ?
// fris.applyConstraints(); ?
}

void Integrator::computeDerivatives(Frisbee& fris, Vector3& xyzDot, Vector3& phiThetaPsiDot, Vector3& uvwDot, Vector3& pqrDot) const {
	xyzDot = fris.xdot_ydot_zdot();
	phiThetaPsiDot = fris.phidot_thetadot_psidot();
	uvwDot = fris.udot_vdot_wdot();
	pqrDot = fris.pdot_qdot_rdot();
}








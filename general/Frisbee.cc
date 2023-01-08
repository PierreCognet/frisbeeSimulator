#include "Frisbee.h"
// #include "Integrateur.h"
#include "Canvas.h"
// #include <sstream>
#include <cmath>
using namespace std;





// Constructors and destructors
Frisbee::Frisbee(Canvas* canvas, Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr)
	: Drawable(canvas), xyz_(xyz), phiThetaPsi_(phiThetaPsi), uvw_(uvw), pqr_(pqr) { }


	
void Frisbee::draw() const { canvas_->draw(*this); }


// Setters
void Frisbee::setXdotYdotZdot(Vector3 const& v) {
	setUvw( T_12()*v ); // Convert v from earth to body axes. 
}


// Getters
const Vector3 Frisbee::xyz() const { return xyz_; }
const double Frisbee::x() const { return xyz()[0]; }
const double Frisbee::y() const { return xyz()[1]; }
const double Frisbee::z() const { return xyz()[2]; }

const Vector3 Frisbee::phiThetaPsi() const { return phiThetaPsi_; }
const double Frisbee::phi() const { return phiThetaPsi()[0]; }
const double Frisbee::theta() const { return phiThetaPsi()[1]; }
const double Frisbee::psi() const { return phiThetaPsi()[2]; }

const Vector3 Frisbee::uvw() const { return uvw_; }
const double Frisbee::u() const { return uvw()[0]; }
const double Frisbee::v() const { return uvw()[1]; }
const double Frisbee::w() const { return uvw()[2]; }

const Vector3 Frisbee::pqr() const { return pqr_; }
const double Frisbee::p() const { return pqr()[0]; }
const double Frisbee::q() const { return pqr()[1]; }
const double Frisbee::r() const { return pqr()[2]; }

const Vector3 Frisbee::bodyZAxis() const {
	// return T_a21()*Vector3(0.,0.,1.);
	return T_21()*Vector3(0.,0.,1.);
}

const vector<Vector3> Frisbee::bodyAxes() const {
	vector<Vector3> axes(0);
	Matrix3x3 T_21_(T_21());
	// Matrix3x3 T_21_(T_a21());
	for (size_t i=0; i<3; ++i) {
		axes.push_back( Vector3(T_21_.get(0,i), T_21_.get(1,i), T_21_.get(2,i)) );
	}
	return axes;
}



// Evolution
const Matrix3x3 Frisbee::T_21(double const& phi, double const& theta, double const& psi) const { // to go from coordinates in body axes (2) to coordinates in earth axes (1).
	double cph (cos(phi));
	double cth (cos(theta));
	double cps (cos(psi));
	double sph (sin(phi));
	double sth (sin(theta));
	double sps (sin(psi));
	
	// return Matrix3x3(cth*cps, sph*sth*cps-cph*sps, cph*sth*cps+sph*sps, // Earth axes with z pointing down.
	// 				 cth*sps, sph*sth*sps+cph*cps, cph*sth*sps-sph*cps,
	// 				 -sth,    sph*cth,             cph*cth);
	return Matrix3x3(cth*cps,  sph*sth*cps-cph*sps,  cph*sth*cps+sph*sps, // Earth axes with z pointing up.
					 -cth*sps, -sph*sth*sps-cph*cps, sph*cps-cph*sth*sps,
					 sth,      -sph*cth,             -cph*cth);
}

const Matrix3x3 Frisbee::T_21() const {
	return T_21(phi(), theta(), psi());
}

const Matrix3x3 Frisbee::T_12(double const& phi, double const& theta, double const& psi) const {
	return T_21(phi, theta, psi).getTranspose();
}

const Matrix3x3 Frisbee::T_12() const {
	return T_12(phi(), theta(), psi());
}

const Matrix3x3 Frisbee::T_32(double const& beta) const { // to go from coordinates in slipside axes (3) to coordinates in body axes (2).
	double cb (cos(beta));
	double sb (sin(beta));
	
	return Matrix3x3(cb, -sb, 0.,
					 sb, cb,  0.,
					 0., 0.,  1.);
}

const Matrix3x3 Frisbee::T_32() const {
	return T_32(beta());
}

const Matrix3x3 Frisbee::T_23(double const& beta) const {
	// return T_32.transpose();
	return T_32(-beta); // More efficient way than transposing the matrix.
}

const Matrix3x3 Frisbee::T_23() const {
	return T_23(beta());
}

const Matrix3x3 Frisbee::T_43(double const& alpha) const { // to go from coordinates in angle of attack axes (4) to coordinates in slipside axes (3).
	double ca (cos(alpha));
	double sa (sin(alpha));
	
	return Matrix3x3(ca, 0., -sa,
					 0., 1., 0.,
					 sa, 0., ca);
}

const Matrix3x3 Frisbee::T_43() const {
	return T_43(alpha());
}

const Matrix3x3 Frisbee::T_34(double const& alpha) const {
	// return T_43.transpose();
	return T_43(-alpha); // More efficient way than transposing the matrix.
}

const Matrix3x3 Frisbee::T_34() const {
	return T_34(alpha());
}

const Matrix3x3 Frisbee::T_r(double const& phi, double const& theta) const { // Multiply this matrix with vector [ \dot{phi},\dot{theta},\dot{psi} ] to get [p,q,r].
	double cos_phi (cos(phi));
	double sin_phi (sin(phi));
	double cos_theta (cos(theta));

	return Matrix3x3(1., 0., 		-sin(theta),
					 0., cos_phi, 	sin_phi*cos_theta,
					 0., -sin_phi, 	cos_phi*cos_theta);
}

const Matrix3x3 Frisbee::T_r() const {
	return T_r(phi(), theta());
}

const Matrix3x3 Frisbee::T_r_inv(double const& phi, double const& theta) const { // Inverse matrix. Multiply this matrix with vector (p,q,r) to get the Euler rates (dot{phi},dot{theta},dot{psi}).
	double cp (cos(phi));
	double sp (sin(phi));
	double tt (tan(theta));
	// double st (1./cos(theta));

	double ct (cos(theta));
	double st;
	if (ct==0.) { st = 10000.; }
	else { st = 1./ct; }

	return Matrix3x3(1., sp*tt, cp*tt,
					 0., cp,	-sp,
					 0., sp*st, cp*st);
}

const Matrix3x3 Frisbee::T_r_inv() const { // Inverse matrix. Multiply this matrix with vector (p,q,r) to get the Euler rates (dot{phi},dot{theta},dot{psi}).
	return T_r_inv(phi(), theta());
}

const double Frisbee::atan2(double const& x, double const& y) const {
	if(x>0.) { return atan(y/x); }
	else if(x<0.) {
		if (y>=0.) { return atan(y/x)+M_PI; }
		else { return atan(y/x)-M_PI; }
	}
	else {
		if (y>0.) { return 0.5*M_PI; }
		if (y<0.) { return -0.5*M_PI; }
		else { return 0.; }	// Even though it is technically undefined.
	}
}

const Vector3 Frisbee::xdot_ydot_zdot() const {
	return T_21()*uvw();
}

const Vector3 Frisbee::phidot_thetadot_psidot() const {
	return T_r_inv()*pqr();
}

const double Frisbee::beta() const { // Slipside angle
	return atan2(u(),v());
}

const Vector3 Frisbee::udot_vdot_wdot() const {
	return f_2()/m()-omegaTilde()*uvw();
}

const Vector3 Frisbee::f_2aero() const {
	return T_32()*( T_43()*f_4() );
}

const Vector3 Frisbee::f_2() const {
	return f_2aero() + T_12()*mg();
}

const Vector3 Frisbee::mult_I_inv(Vector3 const& v) const {
	return Vector3(	i_para_inv()*v[0],
					i_para_inv()*v[1],
					i_perp_inv()*v[2]);
}

const Vector3 Frisbee::i_inv_omega_I_omega() const {
	return Vector3(i_perp_over_i_para_minus_i_para_over_I_perp()*q()*r(),
				   -i_perp_over_i_para_minus_i_para_over_I_perp()*r()*p(),
				   0.);
}

const Vector3 Frisbee::pdot_qdot_rdot() const {
	return mult_I_inv(m_2())-i_inv_omega_I_omega();
}


const Vector3 Frisbee::m_2() const {
	// return T_32()*m_4(); // test this one ?
	return T_32()*( T_43()*m_4() );
}

const Vector3 Frisbee::xdot_3() const {
	return T_23()*uvw();
}

const Vector3 Frisbee::omega_3() const {
	return T_23()*pqr();
}

const double Frisbee::alpha() const {
	Vector3 xdot_3_ (xdot_3());
	return atan2(xdot_3_[0],xdot_3_[2]);
}

const double Frisbee::rho_inf() const {
	return 1.204; // air density in [kg/m3] at 101.325 kPa (abs) and 20°C
}

const double Frisbee::q_inf() const {
	return 0.5*rho_inf()*(uvw().norm2());
}

const double Frisbee::S() const {
	// return 0.06?; // surface of frisbee [m^2], pi*diametre^2/4
	return M_PI*c()*c()*0.25; // surface of frisbee [m^2], pi*diametre^2/4
}

const double Frisbee::c() const {
	return 0.274; // diameter of frisbee [m]
}

const double Frisbee::radius() const {
	return 0.5*c(); // radius of frisbee [m]
}

const double Frisbee::height() const {
	return 0.032; // height of frisbee [m]
}

const double Frisbee::m() const {
	return 0.175; // mass [kg]
}


// const Matrix3x3 i() const  {
// 	return Matrix3x3(i_para(), 0.,       0.,
// 					 0.,       i_para(), 0.,
// 					 0.,       0.,       i_perp());
// }

// const double Frisbee::i_para() const {
// 	return 0.5*i_perp(); // [kg*m^2]
// }

// const double Frisbee::i_perp() const {
// 	return 0.0024; // [kg*m^2]
// }

const double Frisbee::i_para_inv() const {
	return 833.;
	// return 1./i_para();
}

const double Frisbee::i_perp_inv() const {
	return 417.; // [1/(kg*m^2)]
	// return 1./i_perp(); // [1/(kg*m^2)]
}

const double Frisbee::i_perp_over_i_para_minus_i_para_over_I_perp() const {
	return 1.5; // [-]
}

const double Frisbee::v_inf() const {
	return uvw().norm();
}

const double Frisbee::c_Drag(double const& alpha) const { 
	double c_Drag0 (0.085);
	double c_Dragalpha (3.30);
	double alpha_0 (-0.052);
	double dAlpha (alpha-alpha_0); // (alpha = AoA = angle of attack)
	return c_Drag0+c_Dragalpha*dAlpha*dAlpha; // formula taken from figure 7.4

	// *** This approximation is very bad for big angle of attacks

	// Try: return 0.1+1.5*(alpha+0.035)*(alpha+0.035) formula taken from equation 2.26 ?
}

const double Frisbee::c_Yr(double const& r, double const& v_inf) const {	
	if (v_inf==0.) {
		return 0.;
	} else {
		double x = advR(r, v_inf);
		return x*(0.00521461257+x*x*0.00972148905); // From linear regression of Fig 5.20c
	}

	// *** Make sure that the range is correct, otherwise the approximation is increasingly incorrect
	// *** Improve the formula for higher angles of attack.
}

const double Frisbee::c_Side(double const& r, double const& v_inf) const {
	return c_Yr(r, v_inf);
}

const double Frisbee::c_Lift(double const& alpha) const {
	double c_Lift0 (0.13);
	double c_Liftalpha (3.09);
	return c_Lift0+c_Liftalpha*alpha; // Formula taken from figure 7.4

	// return 2.44*alpha+0.085; (alpha = AoA = angle of attack) formula taken from equation 2.19 don't use
}

const double Frisbee::c_L(double const& p, double const& v_inf) const {
	if (v_inf==0.) {
		return 0.;
	} else {
		double c_Lp (-1.30);
		return c_Lp*p*c()/(2.*v_inf);
	}
}

const double Frisbee::c_M(double const& alpha, double const& q, double const& v_inf) const {
	if (v_inf==0.) {
		return 0.;
	} else {
		double c_M0 (-0.01);
		double c_Malpha (0.057);
		double c_Mq (-1.40);
		return c_M0+c_Malpha*alpha + c_Mq*q*c()/(2*v_inf);
	}
}

const double Frisbee::c_N(double const& r, double const& v_inf) const {
	// if (v_inf==0.) {
	// 	return 0.;
	// } else {
	// 	double c_Nr (??);
	// 	return c_Nr*r*c()/(2*v_inf);
	// }
	return 0.; // This supposes no spin loss because in typical Frisbee flights, there is very little spin loss.
}

const Vector3 Frisbee::f_4() const {
	double alpha_ (alpha());

	return q_inf()*S()*Vector3(-c_Drag(alpha_), c_Side(omega_3()[2], v_inf()), -c_Lift(alpha_));
}

const Vector3 Frisbee::m_4() const {
	Vector3 omega_3_ (omega_3());
	double v_inf_ (v_inf());
	return q_inf()*S()*c()*Vector3(c_L(omega_3_[0], v_inf_), c_M(alpha(), omega_3_[1], v_inf_), c_N(omega_3_[2], v_inf_)); // *** improvements : avoid recomputing alpha multiple times.
}

const Matrix3x3 Frisbee::omegaTilde() const { // A shortcut to thee cross product with pqr.
	return Matrix3x3(0.,  -r(),q(),
					 r(), 0.,  -p(),
					 -q(),p(), 0.); // *** improve by not recomputing many times.
}

const Vector3 Frisbee::mg() const {
	double g (9.81); // [m/s^2]
	// return Vector3(0., 0., m()*g); // For Earth axes with z pointing down.
	return Vector3(0., 0., -m()*g); // For Earth axes with z pointing up.
}

const double Frisbee::advR(double const& r, double const& v_inf) const { // advance ratio
	if(v_inf==0.) {
		throw string("Frisbee::advR v_inf==0.");
	} else {
		return r*c()/(2.*v_inf);
	}
}


// //------------------------Contraintes-----------------------------------
// void Frisbee::appliqueContraintes(){
// 	for (auto m : listMasses) m->appliqueContraintes();
// }

// void Frisbee::supprimeContraintes(){
// 	for (auto m : listMasses) m->supprimeContraintes();
// }

// void Frisbee::annuleForces(size_t numMass){
// 	if (numMass >= listMasses.size() ) throw string ("Frisbee::annuleForces(size_t)  num>=nbMasses");
// 	listMasses[numMass]->annuleForces();
// }

// void Frisbee::annuleForces(initializer_list<size_t> const& listnum){
// 	for (auto const& num : listnum){
// 		annuleForces(num);
// 	}
// }

// void Frisbee::annuleForces(){
// 	for(size_t i(0); i<listMasses.size() ; ++i) annuleForces(i);
// }

// void Frisbee::annuleForce_z(size_t numMass){
// 	if (numMass >= listMasses.size() ) throw string ("Frisbee::annuleForce_z(size_t)  num>=nbMasses");
// 	listMasses[numMass]->annuleForce_z();
// }

// void Frisbee::annuleForce_z(initializer_list<size_t> const& listnum){
// 	for (auto const& num : listnum) annuleForce_z(num);
// }

// void Frisbee::annuleForce_z(){
// 	for(size_t i(0); i<listMasses.size() ; ++i) annuleForce_z(i);
// }

// void Frisbee::arrete(size_t numMass){	//met la vitesse à 0
// 	if (numMass >= listMasses.size() ) throw string ("Frisbee::arrete(size_t)  num>=nbMasses");
// 	listMasses[numMass]->arrete();
// }

// void Frisbee::arrete(std::initializer_list<size_t> const& listnum){
// 	for (auto const& num : listnum) arrete(num);
// }

// void Frisbee::arrete(){
// 	for(size_t i(0); i<listMasses.size() ; ++i) arrete(i);
// }

// string Frisbee::getHeaders() const {
// 	// in future if there are multiple Frisbees, add the frisbee number.
// 	string pre ("Frisbee_");
// 	string sep (",");
// 	string output = "";
// 	output += pre+"x"+sep;
// 	output += pre+"y"+sep;
// 	output += pre+"z"+sep;
// 	output += pre+"phi"+sep;
// 	output += pre+"theta"+sep;
// 	output += pre+"psi"+sep;
// 	output += pre+"u"+sep;
// 	output += pre+"v"+sep;
// 	output += pre+"w"+sep;
// 	output += pre+"p"+sep;
// 	output += pre+"q"+sep;
// 	output += pre+"r";
// 	return output;
// }

void Frisbee::addHeaders(vector<string> & outputVec) const {
	// To do : In future if there are multiple Frisbees, add the frisbee number.
	string pre ("Frisbee_");
	outputVec.push_back(pre+"x");
	outputVec.push_back(pre+"y");
	outputVec.push_back(pre+"z");
	outputVec.push_back(pre+"phi");
	outputVec.push_back(pre+"theta");
	outputVec.push_back(pre+"psi");
	outputVec.push_back(pre+"u");
	outputVec.push_back(pre+"v");
	outputVec.push_back(pre+"w");
	outputVec.push_back(pre+"p");
	outputVec.push_back(pre+"q");
	outputVec.push_back(pre+"r");	
}


// string Frisbee::getCurrentState() const {
// 	string sep (",");
// 	string output = "";
// 	output += to_string(x())+sep;
// 	output += to_string(y())+sep;
// 	output += to_string(z())+sep;
// 	output += to_string(phi())+sep;
// 	output += to_string(theta())+sep;
// 	output += to_string(psi())+sep;
// 	output += to_string(u())+sep;
// 	output += to_string(v())+sep;
// 	output += to_string(w())+sep;
// 	output += to_string(p())+sep;
// 	output += to_string(q())+sep;
// 	output += to_string(r());
// 	return output;
// }


void Frisbee::addCurrentState(vector<string> & outputVec) const {
	// To do : In future if there are multiple Frisbees, add the frisbee number.
	outputVec.push_back(to_string(x()));
	outputVec.push_back(to_string(y()));
	outputVec.push_back(to_string(z()));
	outputVec.push_back(to_string(phi()));
	outputVec.push_back(to_string(theta()));
	outputVec.push_back(to_string(psi()));
	outputVec.push_back(to_string(u()));
	outputVec.push_back(to_string(v()));
	outputVec.push_back(to_string(w()));
	outputVec.push_back(to_string(p()));
	outputVec.push_back(to_string(q()));
	outputVec.push_back(to_string(r()));
}


ostream& Frisbee::display(ostream& out) const{
	out << "Frisbee " << this << " : " << endl
		<< "  xyz : " << xyz() << endl
		<< "  phiThetaPsi : " << phiThetaPsi() << endl
		<< "  uvw : " << uvw() << endl
		<< "  pqr : " << pqr() << endl;	
	return out;
}

ostream& operator<<(ostream& out, Frisbee const& f){
	f.display(out);
	return out;
}





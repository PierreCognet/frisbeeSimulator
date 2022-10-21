#ifndef PRJ_FRISBEE_H
#define PRJ_FRISBEE_H

#include <vector>
// #include <array>
// #include <fstream>

// #include "Masse.h"
// #include "Ressort.h"
#include "Drawable.h"
// #include "Vector3.h"
#include "Matrix3x3.h"
#include "Integrator.h"

// class BouleRigide;
// class TrouNoir;

using namespace std; // should I delete it ?


class Frisbee : public Drawable {

public :
	// Constructors and destructors
	Frisbee(Canvas* canvas, Vector3 const& xyz=Vector3(0.,0.,0.), Vector3 const& phiThetaPsi=Vector3(0.,0.,0.), Vector3 const& uvw=Vector3(0.,0.,0.), Vector3 const& pqr=Vector3(0.,0.,0.));

	// Frisbee(Frisbee const& t) = delete;		//il faudrait faire copie profonde (pour ressorts)
	// Frisbee& operator=(Frisbee const& t) = delete;	//il faut copie profonde
	
	// virtual ~Frisbee() override;	// delete les masses+ressorts dynamiquement alloués



	virtual void draw() const override;

	// Setters
	void setXyz(Vector3 const& v) { xyz_ = v; }
	void setPhiThetaPsi(Vector3 const& v) { phiThetaPsi_ = v; }
	void setUvw(Vector3 const& v) { uvw_ = v; }
	void setPqr(Vector3 const& v) { pqr_ = v; }

	void setXdotYdotZdot(Vector3 const& v); // Set the velocity using earth axis (unlike setUvW which is in body axis).


	// Getters
	const Vector3 xyz() const;

	const Vector3 phiThetaPsi() const;
	const double phi() const;
	const double theta() const;
	const double psi() const;

	const Vector3 uvw() const;
	const double u() const;
	const double v() const;
	const double w() const;

	const Vector3 pqr() const;
	const double p() const;
	const double q() const;
	const double r() const;

	const Vector3 bodyZAxis() const;
	const vector<Vector3> bodyAxes() const;

	
	// Evolution
	const Matrix3x3 T_21(double const& phi, double const& theta, double const& psi) const; // To go from coordinates in body axes (2) to coordinates in earth axes (1).
	const Matrix3x3 T_21() const;
	const Matrix3x3 T_12(double const& phi, double const& theta, double const& psi) const;
	const Matrix3x3 T_12() const;
	const Matrix3x3 T_32(double const& beta) const; // To go from coordinates in slipside axes (3) to coordinates in body axes (2).
	const Matrix3x3 T_32() const;
	const Matrix3x3 T_23(double const& beta) const;
	const Matrix3x3 T_23() const;
	const Matrix3x3 T_43(double const& alpha) const; // To go from coordinates in angle of attack axes (4) to coordinates in slipside axes (3).
	const Matrix3x3 T_43() const;
	const Matrix3x3 T_34(double const& alpha) const;
	const Matrix3x3 T_34() const;


	const Matrix3x3 T_r(double const& phi, double const& theta) const;
	const Matrix3x3 T_r() const;
	const Matrix3x3 T_r_inv(double const& phi, double const& theta) const;
	const Matrix3x3 T_r_inv() const;

	const double atan2(double const& x, double const& y) const;

	const Vector3 xdot_ydot_zdot() const;
	const Vector3 phidot_thetadot_psidot() const;
	const double beta() const; // Slipside angle
	const Vector3 udot_vdot_wdot() const;
	const Vector3 f_2aero() const;
	const Vector3 f_2() const;
	const Vector3 mult_I_inv(Vector3 const& v) const;
	const Vector3 i_inv_omega_I_omega() const;
	const Vector3 pdot_qdot_rdot() const;
	const Vector3 m_2() const;

	const Vector3 xdot_3() const;
	const Vector3 omega_3() const;
	const double alpha() const; // Angle of attack

	const double rho_inf() const;
	const double q_inf() const;
	const double S() const;
	const double c() const;
	const double radius() const;
	const double height() const;
	const double m() const;
	// const Matrix3x3 i() const;
	// const double i_para() const;
	// const double i_perp() const;
	const double i_para_inv() const;
	const double i_perp_inv() const;
	const double i_perp_over_i_para_minus_i_para_over_I_perp() const;
	const double v_inf() const;
	const double c_Drag(double const& alpha) const;
	const double c_Yr(double const& r, double const& v_inf) const;
	const double c_Side(double const& r, double const& v_inf) const;
	const double c_Lift(double const& alpha) const;
	const double c_L(double const& p, double const& v_inf) const; // moment on roll axis
	const double c_M(double const& alpha, double const& q, double const& v_inf) const; // moment on pitch axis
	const double c_N(double const& r, double const& v_inf) const; // moment on yaw axis (Frisbee spin)
	const Vector3 f_4() const;
	const Vector3 m_4() const;

	const Matrix3x3 omegaTilde() const;
	const Vector3 mg() const;


	// void updateForcesMoments();
	// void add_force(Vector3 const& v);
	// void evolve(Integrator& I, double dt);

	const double advR(double const& r, double const& v_inf) const; // advance ratio

	
	// // Constraints
	// void appliqueContraintes();	//a toutes les masses
	// void supprimeContraintes();	//a toutes les masses
	// void annuleForces(size_t numMass);
	// void annuleForces(std::initializer_list<size_t> const& listnum);
	// void annuleForces();
	// void annuleForce_z(size_t numMass);	//annule force verticale 
	// void annuleForce_z(std::initializer_list<size_t> const& listnum);
	// void annuleForce_z();
	// void arrete(size_t numMass);	//force l'arrêt
	// void arrete(std::initializer_list<size_t> const& listnum);
	// void arrete();

	ostream& display(ostream& out) const;
	
	
private :
	// Vector3 position; // x, y, z in Earth axis.
	// Vector3 orientation; // Euler angles phi, theta, psi.
	// Vector3 velocity; // dot{x}, dot{y}, dot{z} in Earth axis.
	// Vector3 angularVelocity; // Euler rates dot{phi}, dot{theta}, dot{psi}.
	Vector3 xyz_; // x, y, z in Earth axis.
	Vector3 phiThetaPsi_; // Euler angles phi, theta, psi.
	Vector3 uvw_; // Velocity in body axis.
	Vector3 pqr_; // Rotation vector in body axis.

};


std::ostream& operator<<(std::ostream& out, Frisbee const& f);


#endif

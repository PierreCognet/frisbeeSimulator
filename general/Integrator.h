#ifndef PRJ_INTEGRAT0R_H
#define PRJ_INTEGRAT0R_H


class Vector3;
class Frisbee;

// enum IntegratorType {Euler, Newmark, RungeKutta};
enum IntegratorType {RungeKutta};

class Integrator{
public :
	
	virtual ~Integrator();
	
	virtual IntegratorType getType () const = 0;
	
	virtual void integrate(Frisbee& fris, double const& dt) const = 0;
	
	void setVariables(Frisbee& fris, Vector3 const& newXyz, Vector3 const& newPhiThetaPsi, Vector3 const& newUvw, Vector3 const& newPqr) const;
	void computeDerivatives(Frisbee& fris, Vector3& xyzDot, Vector3& phiThetaPsiDot, Vector3& uvwDot, Vector3& pqrDot) const;

};




#endif

#ifndef PRJ_INTEGRATORRK4_H
#define PRJ_INTEGRATORRK4_H

#include "Integrator.h"

class IntegratorRK4 : public Integrator{
public :
	virtual ~IntegratorRK4() override {}
	
	virtual IntegratorType getType() const override;
	
	virtual void integrate(Frisbee& fris, double const& dt) const override;
};




#endif

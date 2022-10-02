#include "IntegratorRK4.h"
#include "Frisbee.h"

using namespace std;


void IntegratorRK4::integrate(Frisbee& fris, double const& dt) const { 
	
	Vector3 xyz_0 (fris.xyz());
	Vector3 phiThetaPsi_0 (fris.phiThetaPsi());
	Vector3 uvw_0 (fris.uvw());
	Vector3 pqr_0 (fris.pqr());

	Vector3 k1_xyz;
	Vector3 k1_phiThetaPsi;
	Vector3 k1_uvw;
	Vector3 k1_pqr;
	computeDerivatives(fris, k1_xyz, k1_phiThetaPsi, k1_uvw, k1_pqr);

	setVariables(fris, xyz_0+dt*0.5*k1_xyz,
					   phiThetaPsi_0+dt*0.5*k1_phiThetaPsi,
					   uvw_0+dt*0.5*k1_uvw,
					   pqr_0+dt*0.5*k1_pqr);
	Vector3 k2_xyz;
	Vector3 k2_phiThetaPsi;
	Vector3 k2_uvw;
	Vector3 k2_pqr;
	computeDerivatives(fris, k2_xyz, k2_phiThetaPsi, k2_uvw, k2_pqr);

	setVariables(fris, xyz_0+dt*0.5*k2_xyz,
					   phiThetaPsi_0+dt*0.5*k2_phiThetaPsi,
					   uvw_0+dt*0.5*k2_uvw,
					   pqr_0+dt*0.5*k2_pqr);
	Vector3 k3_xyz;
	Vector3 k3_phiThetaPsi;
	Vector3 k3_uvw;
	Vector3 k3_pqr;
	computeDerivatives(fris, k3_xyz, k3_phiThetaPsi, k3_uvw, k3_pqr);

	setVariables(fris, xyz_0+dt*k3_xyz,
					   phiThetaPsi_0+dt*k3_phiThetaPsi,
					   uvw_0+dt*k3_uvw,
					   pqr_0+dt*k3_pqr);
	Vector3 k4_xyz;
	Vector3 k4_phiThetaPsi;
	Vector3 k4_uvw;
	Vector3 k4_pqr;
	computeDerivatives(fris, k4_xyz, k4_phiThetaPsi, k4_uvw, k4_pqr);

	setVariables(fris, xyz_0+dt*( k1_xyz+2.*k2_xyz+2.*k3_xyz+k4_xyz )/6.,
					   phiThetaPsi_0+dt*( k1_phiThetaPsi+2.*k2_phiThetaPsi+2.*k3_phiThetaPsi+k4_phiThetaPsi )/6.,
					   uvw_0+dt*( k1_uvw+2.*k2_uvw+2.*k3_uvw+k4_uvw )/6.,
					   pqr_0+dt*( k1_pqr+2.*k2_pqr+2.*k3_pqr+k4_pqr )/6.);
}


IntegratorType IntegratorRK4::getType() const { return RungeKutta; }


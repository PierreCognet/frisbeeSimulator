// #include <iostream>
#include "TextViewer.h"
#include "System.h"
// #include "Vector3.h"
#include "IntegratorRK4.h"

using namespace std;


// //------initialisation des attributs de classe-------
// 	double Masse::lambda_defaut(1.);
// 	double Ressort::k_defaut(1.);
// 	double Ressort::l0_defaut(0.5);



int main() {
	try{
			
		TextViewer terminal(cout);
		System s(&terminal);

		Vector3 xyz(0.01, 0.01, 1.);
		Vector3 phiThetaPsi(0.01, 0.01, 0.01);
		Vector3 uvw(1., 0.01, 0.01);
		Vector3 pqr(0.01, 0.01, 1.);

		s.setFrisbeeState(xyz, phiThetaPsi, uvw, pqr);

		IntegratorRK4 rk4;

		cout << endl << endl << "================================================================"
			<< "Initial state:" << endl;
		s.draw();
		
		
		s.evolve(rk4,0.1);
		cout << endl << endl << "================================================================"
			<< "After one step:" << endl;
		s.draw();

		s.evolve(rk4,0.1);
		cout << endl << endl << "================================================================"
			<< "After two steps:" << endl;
		s.draw();

	} catch (string s) {
		cerr << endl << endl << "ERROR : " << s << endl;
	}
	return 0;
}

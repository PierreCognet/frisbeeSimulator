#include <iostream>
#include "TextViewer.h"
#include "System.h"
// #include "Contrainte.h"
// #include "Crochet.h"
// #include "ImpulsionSinusoidale.h"
// #include "Levitateur.h"
// #include "TrouNoir.h"

using namespace std;

void TextViewer::draw(System const& s)  {
	s.drawFrisbee();
}

void TextViewer::draw(Frisbee const& f)  {
	flow << f << endl;
}

// void TextViewer::dessine(Masse const& M)  {
// 	flot << M << endl;
// 	// ou bien
// 	//flot << "Une Masse : " << &M << endl; 
// }

// void TextViewer::dessine(Ressort const& R)  {
// 	//flot << R << endl;
// 	// ou bien
// 	flot << "Un Ressort : " << &R << endl;
// }

// void TextViewer::dessine(ChampAction const& a_dessiner) {
//     flot << a_dessiner;
// }

// void TextViewer::dessine(Crochet const& a_dessiner) {
//     flot << a_dessiner;
// }

// void TextViewer::dessine(Impulsion const& a_dessiner) {
//     flot << a_dessiner;
// }

// /*void TextViewer::dessine(ImpulsionSinusoidale const& a_dessiner) {
//     //flot << a_dessiner;
// }*/

// void TextViewer::dessine(Levitateur const& a_dessiner) {
//     flot << a_dessiner;
// }

// void TextViewer::dessine(BouleRigide const& a_dessiner) {
//     flot << a_dessiner;
// }

// void TextViewer::dessine(TrouNoir const& a_dessiner) {
//     flot << a_dessiner;
// }




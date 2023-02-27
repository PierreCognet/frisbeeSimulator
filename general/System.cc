// #include <sstream>

// #include "Liaison.h"
#include "System.h"
#include "Canvas.h"
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;





System::System(Canvas* canvas, double const& t)
	: Drawable(canvas), time_(t), f(new Frisbee(canvas)), pf(new PlayingField(canvas)) { }


System::~System() {
	// delete_all_Contrainte();
	delete f;
	delete pf;
}



// //--------------------EnregistrerFichier----------------------------
// double System::fromStr(string const& str) const{	//pour lire les fichiers, transforme les string lu en double
// 	double extracted;
// 	istringstream is(str);
// 	is >> extracted;
// 	return extracted;
// }

// System::System(SupportADessin* support, ifstream& entree)
// 	: Dessinable(support) {
	
// 	vector<Masse> masses;	//on y ajoute les masses lus, a la fin on construit tissu avec toutes ces masses
// 	vector<Liaison> liaisons;
	
// 	string s;
// 	entree >> s;
// 	if (s!="Temps") throw string("System::System(istream)  ne commence pas par 'Temps'");
// 	entree >> temps_;
	
// 	entree >> s;
// 	if (s!="Tissus") throw string("System::System(istream) pas 'Tissus'");
	
// 	entree >> s;
// 	while (s!="FinTissus" and !entree.eof() ) {
		
// 		if (s!="Tissu") throw string("System::System(istream) pas 'Tissu'");
		
// 		entree >> s;
// 		if (s!="Masses") throw string("System::System(istream) pas 'Masses'");
		
// 		double m, posiX, posiY, posiZ, vitX, vitY, vitZ, lambda;
// 		entree >> s;
// 		while (s!="FinMasses" and !entree.eof()) {
// 			m = fromStr(s);
// 			entree >> posiX >> posiY >> posiZ >> vitX >> vitY >> vitZ >> lambda;
// 			masses.push_back( Masse(m, Vecteur3D(posiX,posiY,posiZ), Vecteur3D(vitX,vitY,vitZ), lambda ) );	//ajoute la masse au vector
// 			entree >> s;
// 		}
		
// 		entree >> s;
// 		if (s!="Liaisons") throw string("System::System(istream) pas 'Liaisons'");
		
// 		size_t mDep, mArr;
// 		double k, l0;
		
// 		entree >> s;
// 		while (s!="FinLiaisons" and !entree.eof()){
// 			mDep = fromStr(s);
// 			entree >> mArr;
// 			entree >> k;
// 			entree >> l0;
// 			liaisons.push_back( Liaison (mDep, {mArr}, k, l0) );	//ajoute la liaison au vector
// 			entree >> s;
// 		}
		
// 		create_tissu(masses, liaisons);
// 		masses.clear();		//clear pour le prochain tissu
// 		liaisons.clear();
		
// 		entree >> s;
// 	}
	
// 	entree >> s;
// 	if (s!="Contraintes") throw string("System::System(istream) pas 'Contraintes'");
	
// 	entree >> s;
// 	while (s!="FinContraintes" and !entree.eof() ) {
		
// 		if (s.size()!=1) throw string("System::System(istream) mauvaise syntaxe contraintes");
		
// 		double posX,posY,posZ,r,tDeb,tFin,fX,fY,fZ,freq,masse;
// 		switch(s[0]){
// 			case 'c':	//Crochet
// 				entree >> posX >> posY >> posZ >> r;
// 				create_Crochet( Vecteur3D(posX,posY,posZ),r);
// 				break;
// 			case 'i':	//Impulsion
// 				entree >> posX >> posY >> posZ >> r >> tDeb >> tFin >> fX >> fY >> fZ;
// 				create_Impulsion(Vecteur3D(posX,posY,posZ),r,tDeb,tFin,Vecteur3D(fX,fY,fZ), {});	//l'impulsion sera initialiser (si on avait sauvegarder en cours de simulation avec certaines masses soumises à l'impulsion, ça reset)
// 				break;
// 			case 's':	//ImpulsionSinusoidale
// 				entree >> posX >> posY >> posZ >> r >> tDeb >> tFin >> fX >> fY >> fZ >> freq;
// 				create_ImpulsionSinusoidale( Vecteur3D(posX,posY,posZ),r,tDeb,tFin,Vecteur3D(fX,fY,fZ), freq, {});
// 				break;
// 			case 'l':	//Levitateur
// 				entree >> posX >> posY >> posZ >> r;
// 				create_Levitateur(Vecteur3D(posX,posY,posZ),r);
// 				break;
// 			case 'b':	//BouleRigide
// 				entree >> posX >> posY >> posZ >> r;
// 				create_BouleRigide(Vecteur3D(posX,posY,posZ),r);
// 				break;
// 			case 't':	//TrouNoir
// 				entree >> posX >> posY >> posZ >> r >> masse;
// 				create_TrouNoir(Vecteur3D(posX,posY,posZ),r,masse);
// 				break;
// 		}
		
// 		entree >> s;
// 	}
// }

// void System::sauvegarderFichier(ofstream& sortie) const {	//sauvegarde dans un flot
// 	sortie << "Temps " << temps() << endl << endl
// 		<< "Tissus" << endl;
// 	for (auto const& T : listTissu){
// 		T->sauvegarderFichier(sortie);
// 	}
// 	sortie << "FinTissus" << endl
// 		<< "Contraintes" << endl;
// 	for (auto const& C : listContrainte){
// 		C->sauvegarderFichier(sortie);
// 	}
// 	sortie << "FinContraintes" << endl;


queue<string> System::getLineMakeQ(string s) const { // ***
// queue<string> System::getLineMakeQ(ifstream& input) const { *** change this, put a string insteadd of a ifstream
	string tmp;
// 	if (!getline(input, tmp)) { throw string("System::getLineMakeQ(ifstream) end of file'"); }
// 	stringstream str_strm(tmp);
	stringstream str_strm(s);
	queue<string> q; 
	char sep (',');
	while (getline(str_strm, tmp, sep)) {
		q.push(tmp);
	}
	return q;
}


// *** System::System(Canvas* canvas, ifstream& input) *** change this, put a string insteadd of a ifstream
System::System(Canvas* canvas, string headers_str, string values_str)
	: Drawable(canvas) {

	// queue<string> headers (getLineMakeQ(input));
	// queue<string> values (getLineMakeQ(input));
	queue<string> headers (getLineMakeQ(headers_str));
	queue<string> values (getLineMakeQ(values_str));

	// if (!input.eof()) { throw string("System::System(Canvas*, ifstream&) loaded file has too many lines"); }

	if (headers.front()!="time") { throw string("System::System(Canvas*, ifstream&, string, string) 'time' header missing"); }
	headers.pop();
	time_ = stod(values.front());
	values.pop();

	f = new Frisbee(canvas, headers, values); // Create new Frisbee. Note that this process can fail if there are format errors.

	pf = new PlayingField(canvas);
}


string System::connectWithSep(queue<string> q, string sep) const {
	string out ("");
	while(!q.empty()) {
		out += q.front();
		q.pop();
		if (!q.empty()) {
			out += sep;
		}
	}
	return out;
}


string System::getHeaders() const {
	queue<string> outputQ;
	outputQ.push("time");
	f->addHeaders(outputQ);

	// playingfield ? add headers ?

	string sep (",");
	return connectWithSep(outputQ,sep);
}


string System::getCurrentState() const {
	queue<string> outputQ;
	outputQ.push(to_string(time()));
	f->addCurrentState(outputQ);

	// playingfield ? add headers ?

	string sep (",");
	return connectWithSep(outputQ,sep);
}


void System::draw() const { canvas_->draw(*this); }

void System::drawFrisbee() const {
	f->draw();
}

void System::drawPlayingField() const {
	pf->draw();
}

// void System::dessineContrainte() const{
// 	for (auto const& C : listContrainte){
// 		C->dessine();
// 	}
// }




void System::setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr, bool const& uvwIsBodyNotEarthAxes) {
	f->setXyz(xyz);
	f->setPhiThetaPsi(phiThetaPsi);
	if (uvwIsBodyNotEarthAxes) 	{ f->setUvw(uvw); }
	else 						{ f->setXdotYdotZdot(uvw); }
	f->setPqr(pqr);
}

Frisbee* System::getFrisbee() {
	return f;
}





// //------------------------Gestion Contraintes---------------------------
// void System::create_Crochet(Vecteur3D const& centre , double const& rayon){
//     listContrainte.push_back( ContraintePtr ( new Crochet(centre, rayon, this->support_) ) );
// }

// void System::create_Impulsion(Vecteur3D const& centre ,double const& R
// 					,double tDebut, double tFin
// 					,Vecteur3D const& force
// 					,vector<size_t> const& tissusCible){	//on passe les numéros des Tissus (car l'extérieur n'a pas acces aux pointeurs)
	
// 	vector<Tissu*> tissus(numToTissus(tissusCible));	//transforme les size_t en Tissus
	
//     listContrainte.push_back( ContraintePtr ( new Impulsion(centre, R, tDebut, tFin, force, tissus, this->support_) ) );
// }

// void System::create_ImpulsionSinusoidale(Vecteur3D const& centre ,double const& R
// 										,double tDebut, double tFin
// 										,Vecteur3D const& force
// 										,double freq
//                                         ,vector<size_t> const& tissusCible){	//on passe les numéros des Tissus (car l'extérieur n'a pas acces aux pointeurs)

// 	vector<Tissu*> tissus(numToTissus(tissusCible));	//transforme les size_t en Tissus

//     listContrainte.push_back( ContraintePtr ( new ImpulsionSinusoidale(centre, R, tDebut, tFin, force, freq, tissus, this->support_) ) );
// }

// void System::create_Levitateur(Vecteur3D const& centre, double const& rayon){
//     listContrainte.push_back( ContraintePtr ( new Levitateur(centre, rayon, this->support_) ) );
// }

// void System::create_BouleRigide(Vecteur3D const& centre ,double const& R ){
//     listContrainte.push_back( ContraintePtr ( new BouleRigide(centre, R, this->support_) ) );
// }

// void System::create_TrouNoir(Vecteur3D const& centre ,double const& R, double const& masse){
// 	listContrainte.push_back( ContraintePtr ( new TrouNoir(centre, R, masse, this->support_) ) );
// }


// //cette méthode est pour impulsion, au cas où on n'aurait envie que la contrainte ne s'applique qu'à quelques tissus
// vector<Tissu*> System::numToTissus(vector<size_t> const& listNum) const{	//si la liste est vide, return tous les tissus
// 	vector<Tissu*> tissus(0);
// 	if (listNum.size() == 0){
// 		tissus = listTissu; 	//si rien n'est préciser l'impulsion s'appliquera sur tous les Tissus
// 	}
// 	else{
// 		for (auto const& nb : listNum ){
// 			if (nb >= listTissu.size() ) throw string ("System::tissusCibles(...)  nb (donné en argument) >= listTissu.size()");
// 			tissus.push_back( listTissu[nb] );
// 		}
// 	}
// 	return tissus;
// }

// void System::delete_all_Contrainte(){
// 	for (auto& c : listContrainte)	delete c;
// 	listContrainte.clear();
// }


// void System::delete_last_Contrainte(){
// 	if (!listContrainte.empty()) {
// 		delete listContrainte.back();
// 		listContrainte.pop_back();
// 	}
// }


//----------------------Accesseurs--------------------------------------
// const size_t System::nbTissus () const  {	return listTissu.size(); }

const double System::time() const{ return time_; }

const double System::time(string values) const {
	string value;
	stringstream str_strm(values);
	char sep (',');
	getline(str_strm, value, sep);
	return stod(value);
}


void System::display(ostream& out) const{
	out << "Canvas : " << canvas_ << endl
		<< "Time : " << time() << endl
		<< "Frisbee : " << *f << endl
		<< "PlayingField : " << *pf << endl << endl;
}

void System::evolve(Integrator& i, double const& dt){
	
	time_ += dt;
	i.integrate(*f, dt);
	
	// for (auto& T : listTissu) {

	// 	T->mise_a_jour_force();	//recalcule poid+frot+forcesRappels
	// 	for (auto const& C : listContrainte ) C->avertir(*T, temps_);	//ajoute les contraintes aux masses qui vont les subir
	// 	T->appliqueContraintes();	//applique les contriantes (change vitess/forcesSubi...)
	// 	T->evolue(I,dt);	//integre les masses
	// 	T->supprimeContraintes();	//remets à zéro les contraintes subies dans les masses
	// }
}


const Vector3 System::getFrisbeePosition() const {
	return f->xyz();
}


void System::resetTime(){
	time_ = 0. ;
}



ostream& operator<<(ostream& out, System const& s){
    s.display(out);
    return out;
}





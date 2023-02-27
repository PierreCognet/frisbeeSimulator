#ifndef PRJ_SYSTEM_H
#define PRJ_SYSTEM_H

#include "Drawable.h"
#include "Frisbee.h"
#include "PlayingField.h"


// typedef Tissu* TissuPtr;			//pour pouvoir changer plus facilement
// typedef Contrainte* ContraintePtr;


class System : public Drawable {

public:

	System(Canvas* canvas, double const& t = 0.);

	System(System const& s) = delete; // Contains dynamically allocated attributs, so delete the copie function.
	System operator=(System const& s) = delete;

	virtual ~System() override;
	
	// //--------------------File input / output----------------------------
	// double fromStr(std::string const& str) const;
	// System(SupportADessin* support, std::ifstream& fichier);	//constructeur qui lit un fichier
	System(Canvas* canvas, std::string headers_str, std::string values_str);	// Constructor when loading a file.
	std::string getHeaders() const;
	std::string getCurrentState() const;
	

	
	virtual void draw() const override;
	void drawFrisbee() const;
	void drawPlayingField() const;
	// void dessineContrainte() const;
	// bool get_Cassable() ;


	void setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr, bool const& uvwIsBodyNotEarthAxes=true);
	
	Frisbee* getFrisbee();

	// void create_Crochet(Vecteur3D const& centre , double const& rayon);

	// void delete_all_Contrainte();
	// void delete_last_Contrainte();
	
	

	const double time() const;
	const double time(string values) const;
	void display(std::ostream& out) const;
	// std::vector<Vecteur3D> get_CDM () const;
	const Vector3 getFrisbeePosition() const;


	void resetTime();


	void evolve(Integrator& i, double const& dt);



private :
	// std::string connectWithSep(std::vector<std::string> vec, std::string sep) const;
	std::queue<std::string> getLineMakeQ(std::string input) const;
	std::string connectWithSep(std::queue<std::string> q, std::string sep) const;

	Frisbee* f;
	PlayingField* pf;
	// std::vector<ContraintePtr> listContrainte;
	double time_; // Total time since system evolves.
};



std::ostream& operator<<(std::ostream& out, System const& s);



#endif


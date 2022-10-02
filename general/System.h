#ifndef PRJ_SYSTEM_H
#define PRJ_SYSTEM_H

#include "Drawable.h"
#include "Frisbee.h"


// typedef Tissu* TissuPtr;			//pour pouvoir changer plus facilement
// typedef Contrainte* ContraintePtr;


class System : public Drawable {

public:

	System(Canvas* support, double const& t = 0.);

	// System(System const& s) = delete;
	// System operator=(System const& s) = delete;

	virtual ~System() override;
	
	// //--------------------EnregistrerFichier----------------------------
	// double fromStr(std::string const& str) const;
	// System(SupportADessin* support, std::ifstream& fichier);	//constructeur qui lit un fichier
	// void sauvegarderFichier(std::ofstream& sortie) const;	//enregistre le système sur un fichier
	
	
	
	virtual void draw() const override;
	void drawFrisbee() const;
	// void dessineContrainte() const;
	// bool get_Cassable() ;


	void setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr);
	
	Frisbee* getFrisbee();

	// void create_Crochet(Vecteur3D const& centre , double const& rayon);

	// void delete_all_Contrainte();
	// void delete_last_Contrainte();
	
	

	const double time() const;
	void display(std::ostream& out) const;
	// std::vector<Vecteur3D> get_CDM () const;
	const Vector3 getFrisbeePosition() const;


	void resetTime();


	void evolve(Integrator& i, double const& dt);


private :
	Frisbee* f;
	// std::vector<ContraintePtr> listContrainte;
	double time_; // Total time since system evolves.
};



std::ostream& operator<<(std::ostream& out, System const& s);



#endif


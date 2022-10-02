#ifndef PRJ_CANVAS_H
#define PRJ_CANVAS_H

class System;
class Frisbee;
// class Masse;
// class Ressort;
// class ChampAction;
// class Crochet;
// class Impulsion;
// class ImpulsionSinusoidale;
// class Levitateur;
// class BouleRigide;
// class TrouNoir;


class Canvas
{
 public:

  virtual ~Canvas() {}

	virtual void draw(System const& toDraw) = 0;
	virtual void draw(Frisbee const& toDraw) = 0;

	// virtual void dessine(Systeme const& a_dessiner)  = 0;
	// virtual void dessine(Tissu const& a_dessiner)  = 0;
	// virtual void dessine(Masse const& a_dessiner)  = 0;
	// virtual void dessine(Ressort const& a_dessiner) = 0;
	// virtual void dessine(ChampAction const& a_dessiner) = 0;
	// virtual void dessine(Crochet const& a_dessiner) = 0;
	// virtual void dessine(Impulsion const& a_dessiner) = 0;
	// //  virtual void dessine(ImpulsionSinusoidale const& a_dessiner) = 0;	//se dessine 
	// virtual void dessine(Levitateur const& a_dessiner) = 0;
	// virtual void dessine(BouleRigide const& a_dessiner) = 0;
	// virtual void dessine(TrouNoir const& a_dessiner) = 0;



};

#endif

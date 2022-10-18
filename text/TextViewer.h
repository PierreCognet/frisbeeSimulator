#ifndef PRJ_TEXTVIEWER_H
#define PRJ_TEXTVIEWER_H

#include <iostream>
#include "Canvas.h"



class TextViewer : public Canvas {
 public:
 
	TextViewer(std::ostream& flow)
	: flow(flow) {}
	
	virtual ~TextViewer() {}
	
	virtual void draw(System const& s) override;
	virtual void draw(Frisbee const& f) override;
	virtual void draw(PlayingField const& f) override;
	virtual void draw(Cone const& c) override;
	virtual void draw(Line const& l) override;

	//-------------------------Dessine------------------------------------
	// virtual void dessine(Systeme const& S)  override;
	// virtual void dessine(Tissu const& T)  override;
	// virtual void dessine(Masse const& M)  override;
	// virtual void dessine(Ressort const& R)  override;
	// virtual void dessine(ChampAction const& a_dessiner) override;
	// virtual void dessine(Crochet const& a_dessiner) override;
	// virtual void dessine(Impulsion const& a_dessiner) override;
	// //  virtual void dessine(ImpulsionSinusoidale const& a_dessiner) override;
	// virtual void dessine(Levitateur const& a_dessiner) override;
	// virtual void dessine(BouleRigide const& a_dessiner) override;
	// virtual void dessine(TrouNoir const& a_dessiner) override;

 private:
	std::ostream& flow;	// Where to write (e.g. cout or a text file)
};


#endif

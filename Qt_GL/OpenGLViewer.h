#ifndef PRJ_VUEOPENGL_H
#define PRJ_VUEOPENGL_H

#include <QGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "GLSphere.h"
#include "Canvas.h"
#include "System.h"
#include "PlayingField.h"


// enum PtVue {Zplus, Zminus, Xplus , Xminus , Yplus , Yminus};	// Camera point of view.


class OpenGLViewer : public Canvas {

public:

  // Drawing methods inherited from Canvas.

  virtual void draw(System const& toDraw) override;
  virtual void draw(Frisbee const& toDraw) override;
  virtual void draw(PlayingField const& toDraw) override;
  virtual void draw(Cone const& toDraw) override;
  virtual void draw(Line const& toDraw) override;
//   virtual void dessine(Tissu const& a_dessiner) override;
//   virtual void dessine(Masse const& a_dessiner)override;
//   virtual void dessine(Ressort const& a_dessiner) override;
//   virtual void dessine(ChampAction const& a_dessiner) override;
//   virtual void dessine(Crochet const& a_dessiner) override;
//   virtual void dessine(Impulsion const& a_dessiner) override;
// //  virtual void dessine(ImpulsionSinusoidale const& a_dessiner) override;	//se dessine pareil qu'une impulsion
//   virtual void dessine(Levitateur const& a_dessiner) override;
//   virtual void dessine(BouleRigide const& a_dessiner) override;
//   virtual void dessine(TrouNoir const& a_dessiner) override;


  void setPOV(string const& pov);
  // void toggle_tri();
  // void toggle_mas();
  // void toggle_springs();
  // void toggle_Contr();


  // bool get_tri() const { return tri_on;}
  // bool get_spr() const { return springs_on;}
  // bool get_mas() const { return masses_on;}
  // bool get_contr() const { return Contr_on;}


  // To draw the axes on the InfoWindow.
  void drawXY(Vector3 const& camPos);
  void drawZ(Vector3 const& camPos);


  void init();
  void initializePosition();

  void setProjection(QMatrix4x4 const& projection) { prog.setUniformValue("projection", projection); }

  void translate(Vector3 translation);
  void rotate(double angle, Vector3 rotation);

  Vector3 getViewPosition() const;


  void drawLine(QMatrix4x4 const& pov , Vector3 Point1 ,Vector3 Point2 ,Vector3 couleur );
  // void drawTriangle(QMatrix4x4 const& pov, Vector3 const& v1, Vector3 const& v2, Vector3 const& v3, Vector3 const& c1, Vector3 const& c2, Vector3 const& c3);
  // void drawTriangle(QMatrix4x4 const& pov, vector<Vector3> const& vertices, vector<Vector3> const& colors);
  void drawTriangle(QMatrix4x4 const& pov, array<Vector3,3> const& vertices, array<Vector3,3> const& colors);
  void drawQuad(QMatrix4x4 const& pov, Vector3 p1 , Vector3  p2, Vector3 p3, Vector3 p4);
  void drawSphere(QMatrix4x4 const& pov = QMatrix4x4() ,Vector3 couleur = Vector3(1.,1.,1.) );
  // void drawCube(QMatrix4x4 const& pov = QMatrix4x4() );

 private:
  // OpenGL shader incapsulated in a Qt class
  QGLShaderProgram prog;
  GLSphere sphere;
  QMatrix4x4 viewMatrix;
  // bool tri_on;		//bool pour savoir si on dessine les masses/ressorts/triangles
  // bool masses_on;
  // bool springs_on;
  // bool Contr_on;
};

#endif

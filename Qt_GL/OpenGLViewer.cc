// #include "ChampAction.h"
// #include "Crochet.h"
// #include "Impulsion.h"
// #include "ImpulsionSinusoidale.h"
// #include "Levitateur.h"
// #include "BouleRigide.h"
// #include "TrouNoir.h"
#include <vector>
#include <cmath>
#include "OpenGLViewer.h"
#include "VertexShader.h" // Qt identifieers of our different attributes.

using namespace std;

// To show where the camera is.

void OpenGLViewer::drawXY(Vector3 const& camPos){
	QMatrix4x4 matrix;
	drawLine(matrix, Vector3(15,0,0),Vector3(-15,0,0),Vector3(0,1,0));
	drawLine(matrix, Vector3(0,15,0),Vector3(0,-15,0),Vector3(0,1,0));

	// for (auto  pos : camPos){
		matrix.setToIdentity();
		matrix.translate(camPos[0],camPos[1],0);
		// matrix.translate(pos[0],pos[1],0);
		matrix.scale(0.2);
		drawSphere(matrix, Vector3 (1, 1, 1));
	// }
}

void OpenGLViewer::drawZ(Vector3 const& camPos){
	QMatrix4x4 matrix;
	drawLine(matrix, Vector3(15,0,0),Vector3(-15,0,0),Vector3(0,1,0));
	drawLine(matrix, Vector3(0,-1,0),Vector3(0,1,0),Vector3(0,1,0));

	// for(auto pos : camPos) {
		matrix.setToIdentity();
		matrix.translate(camPos[2],0,0);
		// matrix.translate(pos[2],0,0);
		matrix.scale(0.3);
		drawSphere(matrix, Vector3 (1, 1, 1));
	// }
}



// Draw.
void OpenGLViewer::draw(System const& toDraw) {

	toDraw.drawFrisbee();
	toDraw.drawPlayingField();

	// if (Contr_on){
	// toDraw.dessineContrainte();
	// }
}

void OpenGLViewer::draw(Frisbee const& toDraw) {

	Vector3 red(1.,0.,0.);
	Vector3 green(0.,1.,0.);
	Vector3 blue(0.,0.,1.);
	Vector3 discCenter(toDraw.xyz());
	Vector3 discCenterColor(0.5,0.5,0.5);
	vector<Vector3> bodyAxes (toDraw.bodyAxes());
	double r (toDraw.radius());
	double h (toDraw.height());

	QMatrix4x4 matrix;
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // "Wireframe" mode.
	// matrix.setToIdentity();
	// matrix.translate( discCenter[0], discCenter[1], discCenter[2] );
	// matrix.scale(0.2);
	// drawSphere(matrix, blue); // Color blue. *** to improve make these color vector as constants ?
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// draw the normal vector ? make the spinning visible ? ******************
	// draw velocity vector ect


	// Draw the velocity vector (origin at frisbee position).
	matrix.setToIdentity();
	drawLine(matrix, discCenter, discCenter+toDraw.xdot_ydot_zdot(), red);

	// Draw the z body axis (origin at frisbee position).
	matrix.setToIdentity();
	drawLine(matrix, discCenter, discCenter+bodyAxes[2], green);

	// Draw the frisbee disc and rim.
	size_t n(8); // Number of points drawn at the circumference off the disc. n=infty means perfect circle, but takes long to compute.
	Vector3 circ_i(discCenter+r*bodyAxes[0]);
	Vector3 circ_iplus1;
	Vector3 rim_i(circ_i+h*bodyAxes[2]);
	Vector3 rim_iplus1;
	Vector3 color_i(red-blue);
	Vector3 color_iplus1;

	for(size_t i=0; i<n; ++i) {
		double angle(2.*M_PI*(i+1.)/n);
		circ_iplus1 = discCenter+r*(cos(angle)*bodyAxes[0]+sin(angle)*bodyAxes[1]);
		rim_iplus1 = circ_iplus1+h*bodyAxes[2];
		color_iplus1 = cos(angle)*red+cos(angle+M_PI)*blue;

		matrix.setToIdentity();
		// drawTriangle(matrix, vector<Vector3>({ discCenter, circ_i, circ_iplus1 }), vector<Vector3>({ discCenterColor, color_i, color_iplus1 }) );
		drawTriangle(matrix, array<Vector3,3>({ discCenter, circ_i, circ_iplus1 }), array<Vector3,3>({ discCenterColor, color_i, color_iplus1 }) );
		matrix.setToIdentity();
		// drawTriangle(matrix, vector<Vector3>({ circ_i, rim_i, circ_iplus1 }), vector<Vector3>({ color_i, color_i, color_iplus1 }) );
		drawTriangle(matrix, array<Vector3,3>({ circ_i, rim_i, circ_iplus1 }), array<Vector3,3>({ color_i, color_i, color_iplus1 }) );
		matrix.setToIdentity();
		// drawTriangle(matrix, vector<Vector3>({ circ_iplus1, rim_iplus1, rim_i }), vector<Vector3>({ color_iplus1, color_iplus1, color_i }) );
		drawTriangle(matrix, array<Vector3,3>({ circ_iplus1, rim_iplus1, rim_i }), array<Vector3,3>({ color_iplus1, color_iplus1, color_i }) );

		circ_i = circ_iplus1;
		rim_i = rim_iplus1;
		color_i = color_iplus1;
	}

	// something like thatn: matrice.translate( toDraw.position()[0], toDraw.position()[1], toDraw.position()[2] );
	// then draw a disc, make a mark on the disc so that we can see the rotation

	// if (masses_on) {
	// 	toDraw.dessineMasses(); //dessine les masses
	// }

	// if (springs_on){
	// 	toDraw.dessineRessorts();  //dessine les ressorts
	// }

	// if (tri_on) {
	// 	vector<Triangle> triangles (toDraw.trianglesEntreMasses() );
	// 	QMatrix4x4 matrice;

	// 	for ( auto const& t : triangles ){  //dessine des triangles entre chaque boucle de 3 masses
	// 		matrice.setToIdentity();
	// 		drawTriangle(matrice, t);
	// 	}
	// }
}

void OpenGLViewer::draw(PlayingField const& toDraw) { ///*** implement same functions for textviewer  
	array<Cone,8> cones (toDraw.cones());
	array<Line,10> lines (toDraw.lines());

	for (auto c : cones) {
		draw(c);
	}
	for (auto l : lines) {
		draw(l);
	}

	array<array<Vector3,3>,2> triangles (toDraw.trianglesToDraw());
	Vector3 green(0.,1.,0.);
	QMatrix4x4 matrix;
	matrix.setToIdentity();
	drawTriangle(matrix, triangles[0], array<Vector3,3>({ green, green, green }) );
	matrix.setToIdentity();
	drawTriangle(matrix, triangles[1], array<Vector3,3>({ green, green, green }) );
	
}

void OpenGLViewer::draw(Cone const& toDraw) {

	Vector3 coneCenter(toDraw.xyz());
	double r (toDraw.radius());
	double h (toDraw.height());
	Vector3 yellow(1.,1.,0.);

	QMatrix4x4 matrix;

	size_t n(8); // Number of points drawn at the circumference off the cone. n=infty means perfect circle, but takes long to compute.
	Vector3 circ_i(coneCenter+r*Vector3(1.,0.,0.));
	Vector3 circ_iplus1;
	Vector3 tip(coneCenter+h*Vector3(0.,0.,1.));
	
	for(size_t i=0; i<n; ++i) {
		double angle(2.*M_PI*(i+1.)/n);
		circ_iplus1 = coneCenter+r*Vector3(cos(angle),sin(angle),0.);

		matrix.setToIdentity();
		// drawTriangle(matrix, vector<Vector3>({ tip, circ_i, circ_iplus1 }), vector<Vector3>({ yellow, yellow, yellow }) );
		drawTriangle(matrix, array<Vector3,3>({ tip, circ_i, circ_iplus1 }), array<Vector3,3>({ yellow, yellow, yellow }) );

		circ_i = circ_iplus1;
	}
}


void OpenGLViewer::draw(Line const& toDraw) {
	Vector3 v1 (toDraw.vertex1());
	Vector3 v2 (toDraw.vertex2());
	double t (toDraw.thickness());
	Vector3 lineParaUnitVec ((v1-v2).unitary());
	Vector3 linePerpUnitVec (lineParaUnitVec^Vector3(0.,0.,1.));
	Vector3 white(1.,1.,1.);
	
	QMatrix4x4 matrix;

	Vector3 corner1 (v1+0.5*t*linePerpUnitVec);
	Vector3 corner2 (v1-0.5*t*linePerpUnitVec);
	Vector3 corner3 (v2-0.5*t*linePerpUnitVec);
	Vector3 corner4 (v2+0.5*t*linePerpUnitVec);

	matrix.setToIdentity();
	// drawTriangle(matrix, vector<Vector3>({ corner1, corner2, corner3 }), vector<Vector3>({ white, white, white }) );
	drawTriangle(matrix, array<Vector3,3>({ corner1, corner2, corner3 }), array<Vector3,3>({ white, white, white }) );
	matrix.setToIdentity();
	// drawTriangle(matrix, vector<Vector3>({ corner1, corner3, corner4 }), vector<Vector3>({ white, white, white }) );
	drawTriangle(matrix, array<Vector3,3>({ corner1, corner3, corner4 }), array<Vector3,3>({ white, white, white }) );

}





// void OpenGLViewer::dessine(Masse const& toDraw){

// 	QMatrix4x4 matrice;
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
// 	matrice.setToIdentity();
// 	matrice.translate( toDraw.position()[0], toDraw.position()[1], toDraw.position()[2] );
// 	matrice.scale(0.2);
// 	drawSphere(matrice, cste::jaune );
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// }

// void OpenGLViewer::dessine(Ressort const& toDraw){

// 	QMatrix4x4 matrice;
// 	matrice.setToIdentity();
// 	drawLine(matrice, toDraw.masseDep()->position(), toDraw.masseArr()->position() , cste::rouge);
// }

// void OpenGLViewer::dessine(ChampAction const& toDraw) {
// 	QMatrix4x4 matrice;
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
// 	matrice.setToIdentity();
// 	matrice.translate( toDraw.centre()[0], toDraw.centre()[1], toDraw.centre()[2] );
// 	matrice.scale(toDraw.rayon());	//meme taille que en vrai
// 	drawSphere(matrice, cste::violet );
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// }

// void OpenGLViewer::dessine(Crochet const& toDraw) {
// 	toDraw.dessineChamp();
// }

// void OpenGLViewer::dessine(Impulsion const& toDraw) {
// 	QMatrix4x4 matrice;
// 	matrice.setToIdentity();
// 	for ( auto const& masseCible : toDraw.get_massesCible() ){
// 		drawLine(matrice, masseCible->position(), masseCible->position()+toDraw.getForceAppliquee() , cste::violet);
// 	}
// }

// /*void OpenGLViewer::dessine(ImpulsionSinusoidale const& toDraw) {
	
// }*/

// void OpenGLViewer::dessine(Levitateur const& toDraw) {
// 	QMatrix4x4 matrice;
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
// 	matrice.setToIdentity();
// 	matrice.translate( toDraw.get_champ().centre()[0], toDraw.get_champ().centre()[1], toDraw.get_champ().centre()[2] );
// 	matrice.scale(toDraw.get_champ().rayon());	//meme taille que en vrai
// 	drawSphere(matrice, cste::vert );
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// }

// void OpenGLViewer::dessine(BouleRigide const& toDraw) {
// 	toDraw.dessineChamp();	//violet
// }

// void OpenGLViewer::dessine(TrouNoir const& toDraw) {
// 	QMatrix4x4 matrice;
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
// 	matrice.setToIdentity();
// 	matrice.translate( toDraw.get_champ().centre()[0], toDraw.get_champ().centre()[1], toDraw.get_champ().centre()[2] );
// 	matrice.scale(toDraw.get_champ().rayon());	//meme taille que en vrai
// 	drawSphere(matrice, cste::blanc );	//oui le trou noir se dessine en blanc, mais sinon on le verrai pas!
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// }



void OpenGLViewer::drawLine(QMatrix4x4 const& pov, Vector3 point1, Vector3 point2 ,Vector3 color) {
	prog.setUniformValue("model_view", viewMatrix * pov);

	glBegin(GL_LINES);

	prog.setAttributeValue(colorId, color[0], color[1], color[2]);
	prog.setAttributeValue(vertexId, point1[0], point1[1], point1[2]);
	prog.setAttributeValue(vertexId, point2[0], point2[1], point2[2]);

	glEnd();
}


// void OpenGLViewer::drawTriangle(QMatrix4x4 const& pov, Triangle const& t) {
// void OpenGLViewer::drawTriangle(QMatrix4x4 const& pov, Vector3 const& v1, Vector3 const& v2, Vector3 const& v3, Vector3 const& c1, Vector3 const& c2, Vector3 const& c3) {
// void OpenGLViewer::drawTriangle(QMatrix4x4 const& pov, vector<Vector3> const& vertices, vector<Vector3> const& colors) {
void OpenGLViewer::drawTriangle(QMatrix4x4 const& pov, array<Vector3,3> const& vertices, array<Vector3,3> const& colors) {

	prog.setUniformValue("model_view", viewMatrix* pov);

	glBegin(GL_TRIANGLES);
	for (size_t i=0; i<3; ++i) {
		prog.setAttributeValue(colorId, colors[i][0], colors[i][1], colors[i][2]);
		prog.setAttributeValue(vertexId, vertices[i][0], vertices[i][1], vertices[i][2]);		
	}
	// prog.setAttributeValue(colorId, 1., 0., 0.);
	// prog.setAttributeValue(vertexId, t[0]-position()[0], t[0]->position()[1], t[0]->position()[2]);

	// prog.setAttributeValue(colorId, 0.75,0.75,0.75);
	// prog.setAttributeValue(vertexId, t[1]-position()[0], t[1]->position()[1], t[1]->position()[2]);

	// prog.setAttributeValue(colorId, 0., 0., 1.);
	// prog.setAttributeValue(vertexId, t[2]-position()[0], t[2]->position()[1], t[2]->position()[2]);
	glEnd();

	glBegin(GL_TRIANGLES); // Need to draw the triangles in clockwise and counter clockwise directions to make them visible in both directions.
	for (size_t i=0; i<3; ++i) {
		prog.setAttributeValue(colorId, colors[2-i][0], colors[2-i][1], colors[2-i][2]);
		prog.setAttributeValue(vertexId, vertices[2-i][0], vertices[2-i][1], vertices[2-i][2]);		
	}
	// prog.setAttributeValue(colorId, 1., 0., 0.);
	// prog.setAttributeValue(vertexId, t[0]-position()[0], t[0]->position()[1], t[0]->position()[2]);

	// prog.setAttributeValue(colorId, 0.75,0.75,0.75);
	// prog.setAttributeValue(vertexId, t[2]-position()[0], t[2]->position()[1], t[2]->position()[2]);

	// prog.setAttributeValue(colorId, 0., 0., 1.);
	// prog.setAttributeValue(vertexId, t[1]-position()[0], t[1]->position()[1], t[1]->position()[2]);
	glEnd();
}


void OpenGLViewer::drawQuad(QMatrix4x4 const& pov, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) {

	prog.setUniformValue("model_view", viewMatrix* pov);

	glBegin(GL_QUADS);

	prog.setAttributeValue(colorId, 0.0, 0.2, 0.95); // rouge
	prog.setAttributeValue(vertexId, p1[0], p1[1], p1[2]);

	prog.setAttributeValue(colorId, 0.1, 0.0, 0.8); // vert
	prog.setAttributeValue(vertexId, p2[0], p2[1], p2[2]);

	prog.setAttributeValue(colorId, 0.0, 0.0, 1.0); // bleu
	prog.setAttributeValue(vertexId, p3[0], p3[1], p3[2]);

	prog.setAttributeValue(colorId, 0.0, 1.0, 1.0); //violet
	prog.setAttributeValue(vertexId, p4[0], p4[1], p4[2]);

	glEnd();

}


void OpenGLViewer::drawSphere(QMatrix4x4 const& pov, Vector3 color) {
	prog.setUniformValue("model_view", viewMatrix* pov);
	prog.setAttributeValue(colorId, color[0], color[1], color[2]); // Sets color.
	sphere.draw(prog, vertexId); // Draws sphere.
}


// void OpenGLViewer::drawCube (QMatrix4x4 const& pov) {
// 	prog.setUniformValue("model_view", viewMatrix * pov);

// 	glBegin(GL_QUADS);
// 	// face coté X = +1
// 	prog.setAttributeValue(colorId, 1.0, 0.0, 0.0); // rouge
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, +1.0);
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, +1.0);

// 	// face coté X = -1
// 	prog.setAttributeValue(colorId, 0.0, 1.0, 0.0); // vert
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, -1.0);
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, +1.0);
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, +1.0);
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, -1.0);

// 	// face coté Y = +1
// 	prog.setAttributeValue(colorId, 0.0, 0.0, 1.0); // bleu
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, -1.0);
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, +1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, +1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, -1.0);

// 	// face coté Y = -1
// 	prog.setAttributeValue(colorId, 0.0, 1.0, 1.0); // cyan
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, +1.0);
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, +1.0);

// 	// face coté Z = +1
// 	prog.setAttributeValue(colorId, 1.0, 1.0, 0.0); // jaune
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, +1.0);
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, +1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, +1.0);
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, +1.0);

// 	// face coté Z = -1
// 	prog.setAttributeValue(colorId, 1.0, 0.0, 1.0); // magenta
// 	prog.setAttributeValue(vertexId, -1.0, -1.0, -1.0);
// 	prog.setAttributeValue(vertexId, -1.0, +1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, +1.0, -1.0);
// 	prog.setAttributeValue(vertexId, +1.0, -1.0, -1.0);

// 	glEnd();
// }




void OpenGLViewer::setPOV(string const& pov) {
	if(pov=="Zplus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
	} else if(pov=="Zminus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
		viewMatrix.rotate(90, 1.0, 0.0, 0.0);
		viewMatrix.rotate(90, 1.0, 0.0, 0.0);
	} else if(pov=="Xplus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
		viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
		viewMatrix.rotate(180, 0.0, 0.0, 1.0);
	} else if(pov=="Xminus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
		viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
	} else if(pov=="Yplus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
		viewMatrix.rotate(90, 0.0, 1.0, 0.0);
		viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
	} else if(pov=="Yminus") {
		viewMatrix.setToIdentity();
		viewMatrix.translate(0.0, 0.0, -15);
		viewMatrix.rotate(-90, 0.0, 1.0, 0.0);
		viewMatrix.rotate(-90, 1.0, 0.0, 0.0);
	} else {
		throw string("OpenGLViewer::setPOV(...) unknown point of view '"+pov+"'");
	}		
}

// void OpenGLViewer::toggle_tri(){ if (tri_on) {tri_on = false;}
// 							else {tri_on = true;}}

// void OpenGLViewer::toggle_mas(){if (masses_on) {masses_on = false;}
// 							else {masses_on = true;}}

// void OpenGLViewer::toggle_springs(){if (springs_on) {springs_on = false;}
// 							else {springs_on = true;}}

// void OpenGLViewer::toggle_Contr(){if (Contr_on) {Contr_on = false;}
// 							else {Contr_on = true;}}




void OpenGLViewer::init() {
	/* Initialise notre vue OpenGL.
	* Dans cet exemple, nous créons et activons notre shader.
	*
	* En raison du contenu des fichiers *.glsl, le shader de cet exemple
	* NE permet QUE de dessiner des primitives colorées
	* (pas de textures, brouillard, reflets de la lumière ou autres).
	*
	* Il est séparé en deux parties VERTEX et FRAGMENT.
	* Le VERTEX :
	* - récupère pour chaque sommet des primitives de color (dans
	*     l'attribut color) et de position (dans l'attribut vertex)
	* - multiplie l'attribut sommet par les matrices 'model_view' et
	*     'projection' et donne le résultat à OpenGL
	*   - passe la color au shader FRAGMENT.
	*
	* Le FRAGMENT :
	*   - applique la color qu'on lui donne
	*/

	prog.addShaderFromSourceFile(QGLShader::Vertex, ":/VertexShader.glsl");
	prog.addShaderFromSourceFile(QGLShader::Fragment, ":/FragmentShader.glsl");

	/* Identifie les deux attributs du shader de cet exemple
	* (voir VertexShader.glsl).
	*
	* L'attribut identifié par 0 est particulier, il permet d'envoyer un
	* nouveau "point" à OpenGL
	*
	* C'est pourquoi il devra obligatoirement être spécifié et en dernier
	* (après la color dans cet exemple, voir plus bas).
	*/

	prog.bindAttributeLocation("vertex", vertexId);
	prog.bindAttributeLocation("color", colorId);

	// Compilation du shader OpenGL
	prog.link();

	// Activation du shader
	prog.bind();

	/* Activation du "Test de profondeur" et du "Back-face culling"
	* Le Test de profondeur permet de dessiner un objet à l'arrière-plan
	* partielement caché par d'autres objets.
	*
	* Le Back-face culling consiste à ne dessiner que les face avec ordre
	* de déclaration dans le sens trigonométrique.
	*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	sphere.initialize();
	initializePosition();


	// tri_on = false;
	// masses_on = true; // on initialise avec le dessin des spheres / ressorts
	// springs_on = true;
	// Contr_on = true;
}


void OpenGLViewer::initializePosition() {
	// position initiale
	/*viewMatrix.setToIdentity();
	viewMatrix.translate(0.0, 0.0, -4.0);
	viewMatrix.rotate(60.0, 0.0, 1.0, 0.0);
	viewMatrix.rotate(45.0, 0.0, 0.0, 1.0);*/

	viewMatrix.setToIdentity();
	viewMatrix.translate(0.0, 0.0, -15);
	viewMatrix.rotate(90, 0.0, 0.0, 1.0);
}


void OpenGLViewer::translate(Vector3 translation)
{
	/* Multiplie la matrice de vue par LA GAUCHE.
	 * Cela fait en sorte que la dernière modification apportée
	 * à la matrice soit appliquée en dernier (composition de fonctions).
	 */
	QMatrix4x4 translation_supplementaire;
	translation_supplementaire.translate(translation[0], translation[1], translation[2]);
	viewMatrix = translation_supplementaire * viewMatrix;
    getCameraPosition(); // ***
}


void OpenGLViewer::rotate(double angle, Vector3 rotation) {
	// Multiplie la matrice de vue par LA GAUCHE
	QMatrix4x4 rotation_supplementaire;
	rotation_supplementaire.rotate(angle, rotation[0], rotation[1], rotation[2]);
	viewMatrix = rotation_supplementaire * viewMatrix;
}


void OpenGLViewer::lookAt(System* s) {

	// QVector3D eye (0.f, 0.f, 10.f);
	// 	// 001 goes up world z axis
	// 	// 010 goes to world left
	// 	// 100 wtf rotates camera
	// QVector3D target (0.f, 0.f, 1.f);  //   up, ,forward
	// QVector3D up (0.f, 1.f, 0.f);  //       turn, up, 
	// 	// 000 black screen
	// 	// 001 black screen
	// 	// up parallele to target : black screen
	// 	// 010 still, but mini flickers
	// 	// 110 alternates with 45 degrees counterclockwise
	// 	// 100 alternates with 90 degrees counterclockwise

 //        viewMatrix.lookAt(eye, target, up);



	// QVector3D eye (0.f, 0.f, 10.f);
	// QVector3D target (0.f, 0.f, 0.f);
	// QVector3D up (1.f, 1.f, 0.f);
	// viewMatrix.setToIdentity();
	// viewMatrix.lookAt(eye, target, up);



	// Vector3 eye_ (0.,10.,2.);
	Vector3 eye_ (getCameraPosition());
	QVector3D eye (eye_[0], eye_[1], eye_[2]);
	Vector3 target_ (s->getFrisbeePosition());
	// Vector3 target_ (worldToCameraCoord(s->getFrisbeePosition()));
	QVector3D target (target_[0], target_[1], target_[2]);
	Vector3 up_ (0., 0., 1.);
	QVector3D up (up_[0], up_[1], up_[2]);
	viewMatrix.setToIdentity();
	viewMatrix.lookAt(eye, target, up);

	// // Multiplie la matrice de vue par LA GAUCHE

	// // Vector3 eye_ (getCameraPosition()); // In world coordinates.
	// // glm::vec3 eye (glm::vec3(eye_[0], eye_[1], eye_[2]));
	// Vector3 eye_ (0., 0., 0.);
	// QVector3D eye (eye_[0], eye_[1], eye_[2]);
		
	// Vector3 target_ (worldToCameraCoord(s->getFrisbeePosition())); // In world coordinates.
	// // glm::vec3 target(glm::vec3(target_[0], target_[1], target_[2]));
	// QVector3D target (target_[0], target_[1], target_[2]);
	
	// // glm::vec3 up (glm::vec3(0.f, 0.f, 1.f));
 //        QVector3D up (0.f, 1.f, 0.f);
 //        // QVector3D up (0.f, 0.f, 0.f);

	// // viewMatrix = glm::lookAt(eye, target, up);
 //        viewMatrix.lookAt(eye, target, up);

 //        cerr << "eye" << eye_ << endl << "target" << target_ << endl;
}


Vector3 OpenGLViewer::worldToCameraCoord(Vector3 const& v) const {
	Matrix3x3 viewOrientation (-viewMatrix(0,0),-viewMatrix(0,1),-viewMatrix(0,2),-viewMatrix(1,0),-viewMatrix(1,1),-viewMatrix(1,2), -viewMatrix(2,0),-viewMatrix(2,1),-viewMatrix(2,2));	
	return viewOrientation*v;
}


Vector3 OpenGLViewer::getCameraPosition() const {

	// Vector3 viewPosition (viewMatrix[12], viewMatrix[13], viewMatrix[14]);
	
	Vector3 viewPosition (viewMatrix(0,3), viewMatrix(1,3), viewMatrix(2,3));
	Matrix3x3 viewOrientation (-viewMatrix(0,0),-viewMatrix(1,0),-viewMatrix(2,0),-viewMatrix(0,1),-viewMatrix(1,1),-viewMatrix(2,1), -viewMatrix(0,2),-viewMatrix(1,2),-viewMatrix(2,2));
	Vector3 cameraWorldCoordinates (viewOrientation*viewPosition);

	// cerr << viewOrientation << endl << endl;
	// cerr << viewPosition << endl << endl;
    // cerr << cameraWorldCoordinates << endl << endl;

	return cameraWorldCoordinates;

	// const float rotation = *viewMatrix.data();

	// cerr << viewPosition << endl;
	// cerr << viewMatrix(0,0) << '\t' << viewMatrix(1,0) << '\t' << viewMatrix(2,0) << '\t' << viewMatrix(3,0) << endl << viewMatrix(1,0) << '\t' << viewMatrix(1,1) << '\t' << viewMatrix(1,2) << '\t' << viewMatrix(1,3) << endl << viewMatrix(2,0) << '\t' << viewMatrix(2,1) << '\t' << viewMatrix(2,2) << '\t' << viewMatrix(2,3) << endl << viewMatrix(3,0) << '\t' << viewMatrix(3,1) << '\t' << viewMatrix(3,2) << '\t' << viewMatrix(3,3) << endl;

}



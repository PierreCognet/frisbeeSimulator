#include <cmath>
#include "PlayingField.h"
#include "Canvas.h"
#include "Drawable.h"

using namespace std;


PlayingField::PlayingField(Canvas* canvas, Vector3 const& centerPosition, double const& orientation)
	: Drawable(canvas) {

	Vector3 lengthBaseVector (cos(orientation), sin(orientation), 0.);
	Vector3 widthBaseVector (-sin(orientation), cos(orientation), 0.);

	trianglesToDraw_[0][0] = centerPosition+50.*lengthBaseVector+0.5*37.*widthBaseVector;
	trianglesToDraw_[0][1] = centerPosition+50.*lengthBaseVector-0.5*37.*widthBaseVector;
	trianglesToDraw_[0][2] = centerPosition-50.*lengthBaseVector+0.5*37.*widthBaseVector;
	trianglesToDraw_[1][0] = centerPosition-50.*lengthBaseVector-0.5*37.*widthBaseVector;
	trianglesToDraw_[1][1] = centerPosition+50.*lengthBaseVector-0.5*37.*widthBaseVector;
	trianglesToDraw_[1][2] = centerPosition-50.*lengthBaseVector+0.5*37.*widthBaseVector;


	vector<double> xPositions ({50., 50.-18., -50.+18., -50.});
	vector<double> yPositions ({0.5*37., -0.5*37.});
	size_t i (0);
	Vector3 pos;
	for (auto xPos : xPositions) {
		for (auto yPos : yPositions) {
			pos = centerPosition+xPos*lengthBaseVector+yPos*widthBaseVector;
			cones_[i] = Cone(pos);
			i++;
		}
	}

	Vector3 verticalDisplacement (0.,0.,0.01); // The field lines are drawn slightly above the field to make sure that they are visible. 
	// Exterior lines.
	lines_[0] = Line(cones_[0].xyz()+verticalDisplacement, cones_[1].xyz()+verticalDisplacement);
	lines_[1] = Line(cones_[1].xyz()+verticalDisplacement, cones_[7].xyz()+verticalDisplacement);
	lines_[2] = Line(cones_[7].xyz()+verticalDisplacement, cones_[6].xyz()+verticalDisplacement);
	lines_[3] = Line(cones_[6].xyz()+verticalDisplacement, cones_[0].xyz()+verticalDisplacement);

	// Endzone lines.
	lines_[4] = Line(cones_[2].xyz()+verticalDisplacement, cones_[3].xyz()+verticalDisplacement);
	lines_[5] = Line(cones_[4].xyz()+verticalDisplacement, cones_[5].xyz()+verticalDisplacement);

	// Brick mark lines.
	double semiDiag = 0.5*sqrt(2);
	Vector3 brickPosition;
	brickPosition = centerPosition+(50.-18.-18.)*lengthBaseVector;
	lines_[6] = Line(brickPosition+semiDiag*(lengthBaseVector+widthBaseVector)+verticalDisplacement, brickPosition-semiDiag*(lengthBaseVector+widthBaseVector)+verticalDisplacement);
	lines_[7] = Line(brickPosition+semiDiag*(lengthBaseVector-widthBaseVector)+verticalDisplacement, brickPosition-semiDiag*(lengthBaseVector-widthBaseVector)+verticalDisplacement);
	
	brickPosition = centerPosition-(50.-18.-18.)*lengthBaseVector;
	lines_[8] = Line(brickPosition+semiDiag*(lengthBaseVector+widthBaseVector)+verticalDisplacement, brickPosition-semiDiag*(lengthBaseVector+widthBaseVector)+verticalDisplacement);
	lines_[9] = Line(brickPosition+semiDiag*(lengthBaseVector-widthBaseVector)+verticalDisplacement, brickPosition-semiDiag*(lengthBaseVector-widthBaseVector)+verticalDisplacement);
}


// double PlayingField::fromStr(string const& str) const{	//pour lire les fichiers, transforme les string lu en double
// 	double extracted;
// 	istringstream is(str);
// 	is >> extracted;
// 	return extracted;
// }

void PlayingField::draw() const { canvas_->draw(*this); }

void PlayingField::display(ostream& out) const{
    out << "Canvas : " << canvas_ << endl
		<< "*** to complete : " << endl; // Draw cones and lines.
}


ostream& operator<<(ostream& out, PlayingField const& f){
    f.display(out);
    return out;
}


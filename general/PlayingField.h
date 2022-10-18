#ifndef PRJ_PLAYINGFIELD_H
#define PRJ_PLAYINGFIELD_H

#include <vector>
#include <array>
#include <iostream>
#include "Canvas.h"
#include "Drawable.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Integrator.h"
#include "Cone.h"
#include "Line.h"


// class Cone : public Drawable {
// 	public:
// 		Cone(Canvas* canvas, Vector3 const& xyz) : Drawable(canvas), xyz_(xyz) {}
// 		virtual void draw() const override { canvas_->draw(*this); } // *** implement this
// 		void display(ostream& out) const { out << "*** to implement Cone::dislay" << endl; }
// 		const Vector3 xyz() const { return xyz_; }
// 		const double height() const { return 0.3; /*[m]*/ }
// 		const double radius() const { return 0.1; /*[m]*/ }

// 	private:
// 		Vector3 xyz_;
// };

// class Line : public Drawable {
// 	public:
// 		Line(Canvas* canvas, Vector3 const& vertex1, Vector3 const& vertex2) : Drawable(canvas), vertices(array<Vector3,2> {vertex1, vertex2}) {}
// 		virtual void draw() const override { canvas_->draw(*this); } // *** implement this
// 		void display(ostream& out) const { out << "*** to implement Line::dislay" << endl; }
// 		const Vector3 vertex1() const { return vertices[0]; }
// 		const Vector3 vertex2() const { return vertices[1]; }
// 		const double thickness() const { return 0.1; /*[m]*/ }

// 	private:
// 		array<Vector3,2> vertices;
// };


// class Cone {
// 	public:
// 		Cone(Vector3 const& xyz=Vector3(0.,0.,0.)) : xyz_(xyz) {}
// 		void display(std::ostream& out) const { out << "Cone at " << xyz() << endl; }
// 		void set(Vector3 const& xyz) { xyz_ = xyz; }
// 		const Vector3 xyz() const { return xyz_; }
// 		const double height() const { return 0.3; /*[m]*/ }
// 		const double radius() const { return 0.1; /*[m]*/ }

// 	private:
// 		Vector3 xyz_;
// };

// class Line {
// 	public:
// 		Line(Vector3 const& vertex1=Vector3(0.,0.,0.), Vector3 const& vertex2=Vector3(0.,0.,0.)) : vertices(array<Vector3,2> {vertex1, vertex2}) {}
// 		void display(std::ostream& out) const { out << "Line from " << vertex1() << " to " << vertex2() << endl; }
// 		void set(Vector3 const& v1, Vector3 const& v2) { vertices[0] = v1; vertices[1] = v2; }
// 		const Vector3 vertex1() const { return vertices[0]; }
// 		const Vector3 vertex2() const { return vertices[1]; }
// 		const double thickness() const { return 0.1; /*[m]*/ }

// 	private:
// 		std::array<Vector3,2> vertices;
// };

class PlayingField : public Drawable {

public :


	// Constructors and destructors
	PlayingField(Canvas* canvas, Vector3 const& centerPosition=Vector3(0.,0.,0.), double const& orientation=0.);

	// Frisbee(Frisbee const& t) = delete;		//il faudrait faire copie profonde (pour ressorts)
	// Frisbee& operator=(Frisbee const& t) = delete;	//il faut copie profonde
	
	// virtual ~Frisbee() override;	// delete les masses+ressorts dynamiquement alloués



	virtual void draw() const override;
	void display(std::ostream& out) const;

	// Getters
	const std::array<Cone,8> cones() const { return cones_; }
	const std::array<Line,10> lines() const { return lines_; }
	const std::array<std::array<Vector3,3>,2> trianglesToDraw() const { return trianglesToDraw_; }


	
	
private :

	// Vector3 xyz_; // Position
	// double orientation_; // An angle (fields are only in the xy plane).
	std::array<Cone,8> cones_; // At the 4 corners of the 2 endzones.
	std::array<Line,10> lines_; // 4 exterior, 2 endzone, 2 for each of the 2 brick points. 
	std::array<std::array<Vector3,3>,2> trianglesToDraw_; // To draw the rectangular green grass field, need to define the green 2 triangles. 
	// color ?
	// friction coefficient
	// bounce coefficient


};


std::ostream& operator<<(std::ostream& out, PlayingField const& f);


#endif

#ifndef PRJ_LINE_H
#define PRJ_LINE_H

#include <array>
#include <iostream>
#include "Vector3.h"


class Line {
	public:
		Line(Vector3 const& vertex1=Vector3(0.,0.,0.), Vector3 const& vertex2=Vector3(0.,0.,0.)) : vertices(array<Vector3,2> {vertex1, vertex2}) {}
		void display(std::ostream& out) const { out << "Line from " << vertex1() << " to " << vertex2() << endl; }
		void set(Vector3 const& v1, Vector3 const& v2) { vertices[0] = v1; vertices[1] = v2; }
		const Vector3 vertex1() const { return vertices[0]; }
		const Vector3 vertex2() const { return vertices[1]; }
		const double thickness() const { return 0.1; /*[m]*/ }

	private:
		std::array<Vector3,2> vertices;
};

std::ostream& operator<<(std::ostream& out, Line const& l);




#endif

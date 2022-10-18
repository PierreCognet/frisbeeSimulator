#ifndef PRJ_CONE_H
#define PRJ_CONE_H

#include <iostream>
#include "Vector3.h"

class Cone {
	public:
		Cone(Vector3 const& xyz=Vector3(0.,0.,0.)) : xyz_(xyz) {}
		void display(std::ostream& out) const { out << "Cone at " << xyz() << endl; }
		void set(Vector3 const& xyz) { xyz_ = xyz; }
		const Vector3 xyz() const { return xyz_; }
		const double height() const { return 0.3; /*[m]*/ }
		const double radius() const { return 0.1; /*[m]*/ }

	private:
		Vector3 xyz_;
};

std::ostream& operator<<(std::ostream& out, Cone const& c);




#endif

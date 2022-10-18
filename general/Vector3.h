#ifndef PRJ_VECTOR3_H
#define PRJ_VECTOR3_H


#include <array>
#include <iostream>

using namespace std;

typedef array<double,3> Rep3D; 


class Vector3 { 

public :
	// Constructors et dectructor
	Vector3();
	Vector3(double const& x, double const& y, double const& z);

	// // Getters
	// const double x() const;
	// const double y() const;
	// const double z() const;
	const double operator[](size_t const& i) const;
	const double norm() const;
	const double norm2() const;
	
	// Operations
	Vector3& operator+=(Vector3 const& v);
	Vector3& operator-=(Vector3 v);
	Vector3& operator*=(double const& lambda);	// multiply by scalar
	Vector3& operator/=(double const& lambda); // divide by scalar
	const Vector3 operator-()const; // opposite
	const Vector3 unitary()const;	// returns unitary vector of this vector
	Vector3& normalise(); // normalises the vector
	// bool isColinearWith(Vector3 const& v) const;
	// double distance(Vector3 const& v) const; // distance between two points

private :
	Rep3D coord;	// coordinates (typedef to simplify changes)


};


// External operateur overload
ostream& operator<<(ostream& sortie, Vector3 const& v); // display

bool operator==( Vector3 const& v, Vector3 const& w );
bool operator!=(Vector3 const& v, Vector3 const& w );

const Vector3 operator+(Vector3 v, Vector3 const& w);
const Vector3 operator-(Vector3 v, Vector3 const& w);

const Vector3 operator*(double const& lambda, Vector3 v);
const Vector3 operator*(Vector3 v, double const& lambda);
const Vector3 operator/(Vector3 v, double const& lambda);

const double operator*(Vector3 const& v, Vector3 const& w); // scalar product
const Vector3 operator^(Vector3 const& v, Vector3 const& w); // vectorial product





#endif

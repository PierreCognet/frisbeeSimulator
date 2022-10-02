#ifndef PRJ_MATRIX3X3_H
#define PRJ_MATRIX3X3_H


#include "Vector3.h"

#include <array>
#include <iostream>
using namespace std;



class Matrix3x3 { 

public :
	// Constructors et dectructor
	Matrix3x3();
	Matrix3x3(double const& _00, double const& _01, double const& _02,
			 double const& _10, double const& _11, double const& _12,
			 double const& _20, double const& _21, double const& _22);

	// // Getters
	// const double x () const;
	// const double y () const;
	// const double z () const;
	// const double operator[](size_t const& i) const;
	// const double norm () const;
	// const double norm2 () const;
	const double get(size_t const& i, size_t const& j) const;
	
	// Setters
	void set(size_t const& i, size_t const& j, double const& val);


	// // Operations
	Matrix3x3& transpose(); // Changes current matrix.
	const Matrix3x3 getTranspose() const; // Returns a new matrix.
	// Matrix3x3& operator+=(Matrix3x3 const& v);
	// Matrix3x3& operator-=(Matrix3x3 v);
	// Matrix3x3& operator*=(double const& lambda);	// multiply by scalar
	// Matrix3x3& operator/=(double const& lambda); // divide by scalar
	// const Matrix3x3 operator-()const; // opposite
	// const Matrix3x3 unitaire()const;	// returns unitary vector of this vector
	// Matrix3x3& normalise(); // normalises the vector
	// // bool isColinearWith(Matrix3x3 const& v) const;
	// // double distance(Matrix3x3 const& v) const; // distance between two points

private :
	array<array<double,3>,3> coord;


};


// External operateur overload
ostream& operator<<(ostream& sortie, Matrix3x3 const& m); // Display

// bool operator==( Matrix3x3 const& v, Matrix3x3 const& w );
// bool operator!=(Matrix3x3 const& v, Matrix3x3 const& w );

// const Matrix3x3 operator+(Matrix3x3 v, Matrix3x3 const& w);
// const Matrix3x3 operator-(Matrix3x3 v, Matrix3x3 const& w);

// const Matrix3x3 operator*(double const& lambda, Matrix3x3 v);
// const Matrix3x3 operator*(Matrix3x3 v, double const& lambda);
// const Matrix3x3 operator/(Matrix3x3 v, double const& lambda);

// const double operator*(Matrix3x3 const& v, Matrix3x3 const& w); // scalar product
// const Matrix3x3 operator^(Matrix3x3 const& v, Matrix3x3 const& w); // vectorial product

const Vector3 operator*(Matrix3x3 const& m, Vector3 const& v);




#endif
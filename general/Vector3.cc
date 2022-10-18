#include "Vector3.h"
// #include <iostream>
#include <cmath>
using namespace std;

// Constructors et dectructor
Vector3::Vector3()
	: Vector3(0.,0.,0.) {}	// default is nul vector

Vector3::Vector3(double const& x, double const& y, double const& z)
	: coord({x,y,z}) {}

// // Getters
// const double Vector3::x () const { return coord[0]; }

// const double Vector3::y () const { return coord[1]; }

// const double Vector3::z () const { return coord[2]; }	

const double Vector3::operator[](size_t const& i) const { // returns ith value, i from 0 to n-1
	if (2<i) throw string("Vector3::operator[] i>2");
	return coord[i];
}

const double Vector3::norm() const{
	return sqrt(norm2());
}

const double Vector3::norm2() const{
	double ret(0.);
	for (size_t i(0); i<3 ; ++i){
		ret += coord[i]*coord[i];
	}
	return ret;
}



Vector3& Vector3::operator+=(Vector3 const& v){
	for (size_t i(0) ; i<3 ; ++i ) coord[i] += v.coord[i];
	return *this;
}

Vector3& Vector3::operator-=(Vector3 v){
	return ( (*this) += (v*=(-1.)) );
}

Vector3& Vector3::operator*=(double const& lambda){
	for (auto& valeur : coord ) valeur*=lambda;
	return *this;
}

// Vector3& Vector3::operator/=(double const& lambda){
// 	if (lambda==0.) throw string("Vector3::operator/= : division by zero!");
// 	for (auto& valeur : coord ) valeur/=lambda;
// 	return *this;
// }

// const Vector3 Vector3::operator-()const{
// 	return ((-1)*(*this));
// }

const Vector3 Vector3::unitary()const { // returns the unitary vector (a new Vector3)
	return Vector3(*this/norm());
}

// Vector3& Vector3::normalise(){	// normalises the vector (modifies it)
// 	return (*this)/= norme();
// }

// bool Vector3::estColineaireA(Vector3 const& v) const{
// 	return ((*this)^v) == cste::vectnul;	//deux vecteurs sont colinéaires ssi le produit vectoriel est nul
// }

// double Vector3::distance(Vector3 const& v) const{
// 	return ((*this)-v).norme();			//distance entre les deux points
// }




// External operator overload
ostream& operator<<(ostream& sortie, Vector3 const& v){
	return sortie << "(" << v[0] << " " << v[1] << " " << v[2] << ")";
}

bool operator==( Vector3 const& v, Vector3 const& w ){
	double PRECI(0.00000000001); // because 2 doubles are never exactly equal, look at difference
	bool isEqual(true);
	for (size_t i(0) ; i<3 ; ++i) isEqual = isEqual and ((abs(v[i]-w[i]))<PRECI);
	return isEqual;
}

bool operator!=(Vector3 const& v, Vector3 const& w ){
	return not(v==w);
}

const Vector3 operator+(Vector3 v, Vector3 const& w){
	return (v+=w);
}

const Vector3 operator-(Vector3 v, Vector3 const& w){
	return (v-=w);
}

const Vector3 operator*(double const& lambda, Vector3 v){
	return (v*=lambda);
}

const Vector3 operator*(Vector3 v, double const& lambda){
	return (v*=lambda);
}

const Vector3 operator/(Vector3 v, double const& lambda){
	return (v*=(1./lambda));
}

const double operator*(Vector3 const& v, Vector3 const& w){
	double prod(0.);
	for (size_t i(0); i<3 ; ++i ) prod += v[i]*w[i];
	return prod;
}

const Vector3 operator^(Vector3 const& v, Vector3 const& w){
	return Vector3( v[1]*w[2]-v[2]*w[1] , v[2]*w[0]-v[0]*w[2]  , v[0]*w[1]-v[1]*w[0] );
}





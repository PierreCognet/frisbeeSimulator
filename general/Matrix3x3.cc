#include "Matrix3x3.h"
// #include <iostream>
// #include <cmath>
using namespace std;

// Constructors et dectructor
Matrix3x3::Matrix3x3()
	: Matrix3x3(0.,0.,0.,0.,0.,0.,0.,0.,0.) {}	// default is nul matrix

Matrix3x3::Matrix3x3(double const& _00, double const& _01, double const& _02,
				     double const& _10, double const& _11, double const& _12,
				     double const& _20, double const& _21, double const& _22)
	: coord({_00,_01,_02,_10,_11,_12,_20,_21,_22}) {}
	// : coord({{_00,_01,_02},{_10,_11,_12},{_20,_21,_22}}) {}

// // Getters
// const double Matrix3x3::x () const { return coord[0]; }

// const double Matrix3x3::y () const { return coord[1]; }

// const double Matrix3x3::z () const { return coord[2]; }	

// const double Matrix3x3::operator[](size_t const& i) const {			//retourne la ième valeur, i de 0 à n-1
// 	if ( 3 <= i ) throw string("Matrix3x3::operator[] i>=3");
// 	return coord[i];
// }

// const double Matrix3x3::norme () const{
// 	return sqrt(norme2());
// }

// const double Matrix3x3::norme2 () const{
// 	double retour(0.);
// 	for (size_t i(0); i<3 ; ++i){
// 		retour += coord[i]*coord[i];
// 	}
// 	return retour;
// }

const double Matrix3x3::get(size_t const& i, size_t const& j) const { // return ith value, i from 0 to n-1
	if (3<=i or 3<=j) throw string("Matrix3x3::operator[] i>=3 or j>=3");
	return coord[i][j];
}


// Setters
void Matrix3x3::set(size_t const& i, size_t const& j, double const& val) {
	if (3<=i or 3<=j) throw string("Matrix3x3::set i>=3 or j>=3");
	coord[i][j] = val;
	return;
}



// Operations
Matrix3x3& Matrix3x3::transpose() {
	double tmp;
	for (size_t i=0; i<3; ++i) {
		for (size_t j=i+1; j<3; ++j) {
			tmp = this->get(i,j);
			set(i,j,this->get(j,i));
			set(j,i,tmp);
		}
	}
	return *this;
}

const Matrix3x3 Matrix3x3::getTranspose() const {
	Matrix3x3 ret (*this);
	ret.transpose();
	return ret;
}

// Matrix3x3& Matrix3x3::operator+=(Matrix3x3 const& v){
// 	for (size_t i(0) ; i<3 ; ++i ) coord[i] += v.coord[i];
// 	return *this;	
// }

// Matrix3x3& Matrix3x3::operator-=(Matrix3x3 v){
// 	return ( (*this) += (v*=(-1.)) );
// }

// Matrix3x3& Matrix3x3::operator*=(double const& lambda){
// 	for (auto& valeur : coord ) valeur*=lambda;
// 	return *this;
// }

// Matrix3x3& Matrix3x3::operator/=(double const& lambda){
// 	if (lambda==0.) throw string("Matrix3x3::operator/= : division by zero!");
// 	for (auto& valeur : coord ) valeur/=lambda;
// 	return *this;
// }

// const Matrix3x3 Matrix3x3::operator-()const{
// 	return ((-1)*(*this));
// }

// const Matrix3x3 Matrix3x3::unitaire()const { // returns the unitary vector (a new Matrix3x3)
// 	return Matrix3x3(*this/norme());
// }

// Matrix3x3& Matrix3x3::normalise(){	// normalises the vector (modifies it)
// 	return (*this)/= norme();
// }

// bool Matrix3x3::estColineaireA(Matrix3x3 const& v) const{
// 	return ((*this)^v) == cste::vectnul;	//deux vecteurs sont colinéaires ssi le produit vectoriel est nul
// }

// double Matrix3x3::distance(Matrix3x3 const& v) const{
// 	return ((*this)-v).norme();			//distance entre les deux points
// }




// External operator overload
ostream& operator<<(ostream& sortie, Matrix3x3 const& m){
	return sortie 	<< "(" << m.get(0,0) << " " << m.get(0,1) << " " << m.get(0,2) << ")" << endl
					<< "(" << m.get(1,0) << " " << m.get(1,1) << " " << m.get(1,2) << ")" << endl
					<< "(" << m.get(2,0) << " " << m.get(2,1) << " " << m.get(2,2) << ")" << endl;
}

// bool operator==( Matrix3x3 const& v, Matrix3x3 const& w ){
// 	double PRECI(0.00000000001); // because 2 doubles are never exactly equal, look at difference
// 	bool isEqual(true);
// 	for (size_t i(0) ; i<3 ; ++i) isEqual = isEqual and ((abs(v[i]-w[i]))<PRECI);
// 	return isEqual;
// }

// bool operator!=(Matrix3x3 const& v, Matrix3x3 const& w ){
// 	return not(v==w);
// }

// const Matrix3x3 operator+(Matrix3x3 v, Matrix3x3 const& w){
// 	return (v+=w);
// }

// const Matrix3x3 operator-(Matrix3x3 v, Matrix3x3 const& w){
// 	return (v-=w);
// }

// const Matrix3x3 operator*(double const& lambda, Matrix3x3 v){
// 	return (v*=lambda);
// }

// const Matrix3x3 operator*(Matrix3x3 v, double const& lambda){
// 	return (v*=lambda);
// }

// const Matrix3x3 operator/(Matrix3x3 v, double const& lambda){
// 	return (v*=(1./lambda));
// }

// const double operator*(Matrix3x3 const& v, Matrix3x3 const& w){
// 	double prod(0.);
// 	for (size_t i(0); i<3 ; ++i ) prod += v[i]*w[i];
// 	return prod;
// }

// const Matrix3x3 operator^(Matrix3x3 const& v, Matrix3x3 const& w){
// 	return Matrix3x3( v[1]*w[2]-v[2]*w[1] , v[2]*w[0]-v[0]*w[2]  , v[0]*w[1]-v[1]*w[0] );
// }

const Vector3 operator*(Matrix3x3 const& m, Vector3 const& v){
	return Vector3(m.get(0,0)*v[0]+m.get(0,1)*v[1]+m.get(0,2)*v[2],
				   m.get(1,0)*v[0]+m.get(1,1)*v[1]+m.get(1,2)*v[2],
				   m.get(2,0)*v[0]+m.get(2,1)*v[1]+m.get(2,2)*v[2]);
}



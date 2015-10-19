#pragma once
#include "MyVector.h"
class MyMatrix
{
public:
	float m11, m12, m13,
          m21, m22, m23,
          m31, m32, m33;
	
	MyMatrix(){
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;	
	}
	MyMatrix(double p11,double p12,double p13,double p21,double p22,double p23,double p31,double p32,double p33)
	{
		m11 = p11;
		m12 = p12;
		m13 = p13;
		m21 = p21;
		m22 = p22;
		m23 = p23;
		m31 = p31;
		m32 = p32;
		m33 = p33;
	}
	
	MyMatrix(double a,double b,double g)
	{
		double f = 3.1415926/180.0;
		double sinA = sin(a * f),cosA = cos(a * f);
		double sinB = sin(b * f),cosB = cos(b * f);
		double sinG = sin(g * f),cosG = cos(g * f);
		
		m11 = cosA * cosB;
		m12 = cosA * sinB * sinG - sinA * cosG;
		m13 = cosA * sinB * cosG + sinA * sinG;
		m21 = sinA * cosB;
		m22 = sinA * sinB * sinG + cosA * cosG;
		m23 = sinA * sinB * cosG - cosA * sinG;
		m31 = -sinB;
		m32 = cosB * sinG;
		m33 = cosB * cosG;
	}
	~MyMatrix(void){}
    MyVector operator*(const MyVector& v)
	{
		return MyVector(m11 * v.mX + m12 * v.mY + m13 * v.mZ,
						m21 * v.mX + m22 * v.mY + m23 * v.mZ,
						m31 * v.mX + m32 * v.mY + m33 * v.mZ);
	}
	MyMatrix operator*(MyMatrix rm){
        MyMatrix res;
        res.m11 = m11 * rm.m11 + m12 * rm.m21 + m13 * rm.m31;
        res.m12 = m11 * rm.m12 + m12 * rm.m22 + m13 * rm.m32;
        res.m13 = m11 * rm.m13 + m12 * rm.m23 + m13 * rm.m33;
        res.m21 = m21 * rm.m11 + m22 * rm.m21 + m23 * rm.m31;
        res.m22 = m21 * rm.m12 + m22 * rm.m22 + m23 * rm.m32;
        res.m23 = m21 * rm.m13 + m22 * rm.m23 + m23 * rm.m33;
        res.m31 = m31 * rm.m11 + m32 * rm.m21 + m33 * rm.m31;
        res.m32 = m31 * rm.m12 + m32 * rm.m22 + m33 * rm.m32;
        res.m33 = m31 * rm.m13 + m32 * rm.m23 + m33 * rm.m33;
        return res;
    }
	void transpose()
	{
		MyMatrix tmp = (*this);
        m12 = tmp.m21;
        m13 = tmp.m31;
        m21 = tmp.m12;
        m23 = tmp.m32;
        m31 = tmp.m13;
        m32 = tmp.m23;
	}
    float determinant() {
        return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
    }
    void invert() {
        double det  =  determinant();
        if(det*det<0.000001)
            return;
        float nm11  =  (m22*m33 - m23*m32)/det;
        float nm12  =  (m13*m32 - m12*m33)/det;
        float nm13  =  (m12*m23 - m13*m22)/det;
        float nm21  =  (m23*m31 - m21*m33)/det;
        float nm22  =  (m11*m33 - m13*m31)/det;
        float nm23  =  (m13*m21 - m11*m23)/det;
        float nm31  =  (m21*m32 - m22*m31)/det;
        float nm32  =  (m12*m31 - m11*m32)/det;
        float nm33  =  (m11*m22 - m12*m21)/det;
        m11 = nm11; m12 = nm12; m13 = nm13;
        m21 = nm21; m22 = nm22; m23 = nm23;
        m31 = nm31; m32 = nm32; m33 = nm33;
    }
    
	
};




/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde 
 Contact me if you want to use it for other purposes.
*/
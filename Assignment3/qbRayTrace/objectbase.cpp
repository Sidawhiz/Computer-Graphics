
#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

qbRT::ObjectBase::ObjectBase()
{

}

qbRT::ObjectBase::~ObjectBase()
{

}

bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	std::cout << "Hi in base" << std::endl;
	return false;
}

bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1-f2) < EPSILON;
}

qbVector<double> qbRT::ObjectBase::getCentre(){
	qbVector<double> intPoint(3);
	intPoint.SetElement(0,10);
	return intPoint;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::Transform &transformMatrix)
{
	m_transformMatrix = transformMatrix;
}
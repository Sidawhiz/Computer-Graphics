
#include "objsphere.hpp"
#include <cmath>

qbRT::ObjSphere::ObjSphere()
{

}

qbRT::ObjSphere::~ObjSphere()
{

}

bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{

	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);

	// std::cout << "Hi" << std::endl;
	qbVector<double> vhat = bckRay.m_lab;
	vhat.Normalize();
	
	double b = 2.0 * qbVector<double>::dot(bckRay.m_point1 - centre, vhat);
	
	double c = qbVector<double>::dot(bckRay.m_point1-centre, bckRay.m_point1 - centre) - radius*radius;
	
	double intTest = (b*b) - 4.0 * c;

	qbVector<double> temp;
	
	if (intTest > 0.0)
	{
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
		else
		{
			if (t1 < t2)
			{
				temp = bckRay.m_point1 + (vhat * t1);
			}
			else
			{
				temp = bckRay.m_point1 + (vhat * t2);
			}
		}

		intPoint = m_transformMatrix.Apply(temp, qbRT::FWDTFORM);

		qbVector<double> newObjOrigin = m_transformMatrix.Apply(centre, qbRT::FWDTFORM);

		localNormal = intPoint - newObjOrigin;
		localNormal.Normalize();

		localColor = m_baseColor;
		return true;
	}
	else
	{
		return false;
	}
	
}

qbVector<double> qbRT::ObjSphere::getCentre(){
	return centre;
}


























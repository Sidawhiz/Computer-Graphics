#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "transform.hpp"

namespace qbRT
{
	class ObjectBase
	{
		public:
			ObjectBase();
			virtual ~ObjectBase();
			
			virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);
			
			bool CloseEnough(const double f1, const double f2);

			virtual qbVector<double> getCentre();

			qbVector<double> m_baseColor {3};

			qbRT::Transform m_transformMatrix;

			void SetTransformMatrix(const qbRT::Transform &transformMatrix);
	};
}

#endif

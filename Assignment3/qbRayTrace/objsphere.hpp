#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"
#include "transform.hpp"

namespace qbRT
{
	class ObjSphere : public ObjectBase
	{
		public:
			ObjSphere();

			qbVector<double> centre{3};
			double radius;
			
			virtual ~ObjSphere() override;

			virtual qbVector<double> getCentre();
			
			virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);
			
		private:
		
		
	};
}

#endif

#ifndef GTFM_H
#define GTFM_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "ray.hpp"

namespace qbRT
{
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;
	
	class Transform
	{
        
		private:
			void Print(const qbMatrix2<double> &matrix);
			qbMatrix2<double> m_fwdtfm {4, 4};
			qbMatrix2<double> m_bcktfm {4, 4};


		public:
			Transform();
			~Transform();
			
			Transform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
			
			void SetTransform(	const qbVector<double> &translation,
						const qbVector<double> &rotation,
						const qbVector<double> &scale);
													
			qbMatrix2<double> GetForward();
			qbMatrix2<double> GetBackward();
			
			qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
			qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);
			
			friend qbRT::Transform operator* (const qbRT::Transform &lhs, const qbRT::Transform &rhs);
			
			Transform operator= (const Transform &rhs);
			
			void PrintMatrix(bool dirFlag);
			
			static void PrintVector(const qbVector<double> &vector);
	};
}

#endif

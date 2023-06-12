#include "pointlight.hpp"

qbRT::PointLight::PointLight()
{
	m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_intensity = 1.0;
}

qbRT::PointLight::~PointLight()
{

}

bool qbRT::PointLight::ComputeIllumination(	
    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
	const std::shared_ptr<qbRT::ObjectBase> &currentObject,
	qbVector<double> &color, double &intensity)
{

	qbVector<double> lightDir = (m_location - intPoint).Normalized();
	
	qbVector<double> startPoint = intPoint;
	
	double angle = acos(qbVector<double>::dot(localNormal, lightDir));
	
	if (angle > 1.5708)
	{
		color = m_color;
		intensity = 0.0;
		return false;
	}
	else
	{
		color = m_color;
		intensity = m_intensity * cos(angle);
		return true;
	}
	
	return true;
}

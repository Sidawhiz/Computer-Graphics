#include "scene.hpp"

qbRT::Scene::Scene()
{
	m_camera.SetPosition(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, -1.0}} );
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 1.0, 0.0}} );
	m_camera.SetLength(0.5);
	m_camera.SetHorzSize(1);
	m_camera.SetAspect(16/9);
	m_camera.UpdateCameraGeometry();

	// Objects

	qbRT::ObjSphere m_testSphere;
	m_testSphere.radius = 1.0;
	m_testSphere.centre = qbVector<double>{std::vector<double> {0.0, 0.0, -2.0}} ;

	qbRT::ObjSphere m_testSphere2;
	m_testSphere2.radius = 1.0;
	// m_testSphere2.centre = qbVector<double>{std::vector<double> {0.0, -2.0, -2.0}} ;

	m_objectList.push_back(std::make_shared<qbRT::ObjSphere>(m_testSphere));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere>(m_testSphere2));



	// Light sources

	qbRT::PointLight m_light;
	m_light.m_location = qbVector<double>{std::vector<double> {5.0, 5.0, 0.0}} ;
	m_light.m_color = qbVector<double>{std::vector<double> {255.0, 255.0, 255.0}} ;
	m_lighList.push_back(std::make_shared<qbRT::PointLight>(m_light));

}

bool qbRT::Scene::Render(qbImage &outputImage)
{
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	std::vector<std::vector<int>> arr(xSize, std::vector<int>(ySize,0));

	qbRT::Ray cameraRay;
	qbVector<double> intPoint(3);
	qbVector<double> localNormal(3);
	qbVector<double> localColor(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int x=0; x<xSize; ++x)
	{
		for (int y=0; y<ySize; ++y)
		{
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			m_camera.GenerateRay(normX, normY, cameraRay);

			int val = 0;

			double close = DBL_MAX;

			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject->TestIntersection(cameraRay, intPoint, localNormal, localColor);
				
				double intensity;
				qbVector<double> color {3};
				bool validIllum = false;
				for (auto currentLight : m_lighList)
				{
					validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
				}

				localNormal = intPoint - currentObject->getCentre();
				localNormal.Normalize();

				localColor.SetElement(0,localColor.GetElement(0)*255);
				localColor.SetElement(1,localColor.GetElement(1)*255);
				localColor.SetElement(2,localColor.GetElement(2)*255);

				localColor = localNormal + qbVector<double>{std::vector<double> {1.0, 1.0, 1.0}} ;

				localColor.SetElement(0,localColor.GetElement(0)*255);
				localColor.SetElement(1,localColor.GetElement(1)*255);
				localColor.SetElement(2,localColor.GetElement(2)*255);

				if (validInt)
				{
					double dist = (intPoint - cameraRay.m_point1).norm();
					if (dist > maxDist)
						maxDist = dist;
					
					if (dist < minDist)
						minDist = dist;
					
					if(dist > close){
						continue;
					}
					else{
						close = dist;
					}

					arr[x][y] = 1;
					
					if (validIllum)
					{
						outputImage.SetPixel(x, y, localColor.GetElement(0)*intensity, localColor.GetElement(1)*intensity, localColor.GetElement(2)*intensity);
					}
					else
					{
						outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
					// outputImage.SetPixel(x, y, localColor.GetElement(0), localColor.GetElement(1), localColor.GetElement(2));
				}
				else
				{
					if(arr[x][y]==0){
						outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
			}
		}
	}

	
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;
	
	return true;
}















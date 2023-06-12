#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"
#include "pointlight.hpp"
#include <memory>
namespace qbRT
{
	class Scene
	{
		public:
			Scene();
			
			bool Render(qbImage &outputImage);
		private:
			qbRT::Camera m_camera;
			
			std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;

			std::vector<std::shared_ptr<qbRT::LightBase>> m_lighList;
	
	
	};
}

#endif

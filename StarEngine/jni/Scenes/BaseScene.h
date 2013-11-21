#pragma once

#include "../defines.h"

#include "../Helpers/Stopwatch.h"

#include <vector>
#include <memory>

namespace star 
{
	struct Context;
	class Object;
	class CameraComponent;
	class CollisionManager;
	class GestureManager;
	class BaseCamera;

	class BaseScene
	{
	public:
		BaseScene(const tstring & name);
		virtual ~BaseScene();
		
		void	BaseInitialize();
		void	BaseAfterInitializedObjects();
		void	BaseOnActivate();
		void	BaseOnDeactivate();
		void	BaseUpdate(const Context& context);
		void	BaseDraw();

		virtual void OnSaveState(void** pData,size_t* pSize);
		virtual void OnConfigurationChanged();
		virtual void OnLowMemory();

		const tstring & GetName() const;
		bool IsInitialized() const;

		void AddObject(Object * object); 
		void RemoveObject(Object * object);

		void SetGroupFrozen(const tstring & tag, bool freeze);
		void SetGroupDisabled(const tstring & tag, bool disabled);
		void SetGroupVisible(const tstring & tag, bool visable);
		void GetGroup(const tstring & tag, std::vector<Object*> & group);

		void SetActiveCamera(BaseCamera* pCamera);
		BaseCamera* GetActiveCamera() const;

		void SetCullingIsEnabled(bool enabled);
		bool IsCullingEnabled() const;

		void SetCullingOffset(int32 offset);
		void SetCullingOffset(int32 offsetX, int32 offsetY);

		std::shared_ptr<Stopwatch> GetStopwatch() const;

		std::shared_ptr<GestureManager> GetGestureManager() const;
		std::shared_ptr<CollisionManager> GetCollisionManager() const;

	protected:
		virtual void CreateObjects() = 0;
		virtual void AfterInitializedObjects() = 0;
		virtual void OnActivate() = 0;
		virtual void OnDeactivate() = 0;
		virtual void Update(const Context& context) = 0;
		virtual void Draw() = 0;
		bool CheckCulling(Object* object);

		std::shared_ptr<GestureManager> m_GestureManagerPtr;
		std::shared_ptr<CollisionManager> m_CollisionManagerPtr;

		std::vector<Object*> m_Objects;
		std::vector<Object*> m_Garbage;
		BaseCamera* m_pDefaultCamera;
		std::shared_ptr<Stopwatch> m_pStopwatch;

	private:

		void CollectGarbage();

		int32 m_CullingOffsetX,
			m_CullingOffsetY;
		bool m_Initialized,
			 m_CullingIsEnabled;
		tstring m_Name;
	
		BaseScene(const BaseScene& t);
		BaseScene(BaseScene&& t);
		BaseScene& operator=(const BaseScene& t);
		BaseScene& operator=(BaseScene&& t);
	};
}

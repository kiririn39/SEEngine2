//
// Created by Vlad Boroday on 2025-01-03.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "includes.h"

namespace SE
{
	class GameObject;

	bool inline IsDetValid(Matrix m)
	{
		constexpr fp32 maxDet = 100.0f * 100.f * 100.0f;
		fp32 det = MatrixDeterminant(m);

		return det > EPSILON && det <= maxDet;
	}

	class Component
	{
	protected:
		GameObject* _owner = nullptr;
		bool _isEnabled = true;

	public:
		virtual ~Component() = default;

		virtual void Start()
		{
		}

		virtual void Update(fp32 deltaTime)
		{
		}

		virtual void OnEnable()
		{
		}

		virtual void OnDisable()
		{
		}

		bool IsActive() const
		{
			return _isEnabled;
		}

		void SetActive(bool value)
		{
			if (value == _isEnabled)
				return;

			_isEnabled = value;

			if (value == true)
				OnEnable();
			else
				OnDisable();
		}

		void SetGameObject(GameObject* owner)
		{
			_owner = owner;
		}

		GameObject* GetGameObject() const
		{
			ASSERT(_owner != nullptr);
			return _owner;
		}
	};

	class Transform : public Component
	{
	protected:
		Matrix _transformation{};

	public:
		void Start() override
		{
			_transformation = MatrixIdentity();
		}

		void SetPosition(Vector3 position)
		{
			_transformation.m12 += position.x;
			_transformation.m13 += position.y;
			_transformation.m14 += position.z;

			ASSERT_EXTRA(IsDetValid(_transformation));
		}

		Vector3 GetPosition() const
		{
			ASSERT_EXTRA(IsDetValid(_transformation));

			Vector3 result;

			result.x = _transformation.m12;
			result.y = _transformation.m13;
			result.z = _transformation.m14;

			return result;
		}

		void SetRotation(Vector3 rotationAngles)
		{
			rotationAngles.x *= DEG2RAD;
			rotationAngles.y *= DEG2RAD;
			rotationAngles.z *= DEG2RAD;

			Matrix rotation = MatrixRotateXYZ(rotationAngles);

			_transformation = MatrixMultiply(rotation, _transformation);

			ASSERT_EXTRA(IsDetValid(_transformation));
		}

		void SetRotation(Quaternion rotation)
		{
			Matrix rotationMatrix = QuaternionToMatrix(rotation);

			_transformation = MatrixMultiply(rotationMatrix, _transformation);

			ASSERT_EXTRA(IsDetValid(_transformation));
		}

		Vector3 GetRotationAngles() const
		{
			ASSERT_EXTRA(IsDetValid(_transformation));

			Quaternion quaternion = QuaternionFromMatrix(_transformation);
			Vector3 rotation = QuaternionToEuler(quaternion);

			rotation.x *= RAD2DEG;
			rotation.y *= RAD2DEG;
			rotation.z *= RAD2DEG;

			return rotation;
		}

		Quaternion GetRotation() const
		{
			ASSERT_EXTRA(IsDetValid(_transformation));

			return QuaternionFromMatrix(_transformation);
		}

		Vector3 GetScale() const
		{
			ASSERT_EXTRA(IsDetValid(_transformation));

			const fp32 det = MatrixDeterminant(_transformation);
			Vector3 abc = { _transformation.m0, _transformation.m4, _transformation.m8 };
			Vector3 def = { _transformation.m1, _transformation.m5, _transformation.m9 };
			Vector3 ghi = { _transformation.m2, _transformation.m6, _transformation.m10 };

			fp32 scalex = Vector3Length(abc);
			fp32 scaley = Vector3Length(def);
			fp32 scalez = Vector3Length(ghi);
			Vector3 s = { scalex, scaley, scalez };

			if (det < 0)
				s = Vector3Negate(s);

			return s;
		}

		void SetScale(Vector3 scale)
		{
			Vector3 abc = { _transformation.m0, _transformation.m4, _transformation.m8 };
			Vector3 def = { _transformation.m1, _transformation.m5, _transformation.m9 };
			Vector3 ghi = { _transformation.m2, _transformation.m6, _transformation.m10 };

			Vector3 xAxis = Vector3Normalize(abc) * scale.x;
			Vector3 yAxis = Vector3Normalize(def) * scale.y;
			Vector3 zAxis = Vector3Normalize(ghi) * scale.z;

			_transformation.m0 = xAxis.x;
			_transformation.m4 = xAxis.y;
			_transformation.m8 = xAxis.z;

			_transformation.m1 = yAxis.x;
			_transformation.m5 = yAxis.y;
			_transformation.m9 = yAxis.z;

			_transformation.m2 = zAxis.x;
			_transformation.m6 = zAxis.y;
			_transformation.m10 = zAxis.z;
		}

		Matrix GetTransformation() const
		{
			return _transformation;
		}

		void SetTransformation(Matrix transformation)
		{
			_transformation = transformation;
		}
	};

	class GameObject final
	{
	private:
		FixedString<64> _name{};
		bool _isEnabled = true;
		std::array<std::shared_ptr<Component>, 10> _components{};
		u8 _componentsCount = 0;

	private:
		template<typename T, typename... Args>
		T* AddComponentPrivate(Args&&... args)
		{
			s8 itemsLeft = _components.size() - _componentsCount;
			ASSERT(itemsLeft > 0);
			std::shared_ptr<T> item = std::make_shared<T>(std::forward<Args>(args)...);

			_components[_componentsCount] = std::move(item);
			auto ptr = _components[_componentsCount].get();
			_componentsCount++;

			ptr->SetGameObject(this);
			ptr->Start();

			return dynamic_cast<T*>(ptr);
		}

	public:
		static std::shared_ptr<GameObject> Create();

		static std::shared_ptr<GameObject> Create(pcstr name);

		Transform* GetTransform() const
		{
			Component* item = (*(_components.begin())).get();

			ASSERT(static_cast<Transform*>(item));

			return dynamic_cast<Transform*>(item);
		}

		pcstr GetName() const
		{
			return _name.Begin();
		}

		void SetName(pcstr name)
		{
			_name.Format(name);
		}

		template<typename T>
		T* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

			if constexpr (std::is_same_v<T, Transform>)
			{
				return GetTransform();
			}
			else
			{
				for (int i = 1; i < _components.size(); ++i)
				{
					if (auto result = dynamic_cast<T*>(_components[i].get()))
						return result;
				}

				return nullptr;
			}
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");
			if constexpr (std::is_same_v<T, Transform>)
			{
				return GetTransform();
			}

			if (auto existing = GetComponent<T>())
			{
				return existing;
			}

			return AddComponentPrivate<T>(std::forward<Args>(args)...);
		}

		bool IsEnabled() const
		{
			return _isEnabled;
		}

		void SetEnabled(bool value)
		{
			if (value == _isEnabled)
				return;

			_isEnabled = value;

			for (int i = 0; i < _componentsCount; ++i)
			{
				auto item = _components[i].get();

				if (value == false)
				{
					if (item->IsActive())
					{
						item->OnDisable();
					}
				}
				else
				{
					if (item->IsActive())
					{
						item->OnEnable();
					}
				}
			}
		}

		void Update(fp32 deltaTime)
		{
			if (!_isEnabled)
				return;

			for (int i = 0; i < _componentsCount; ++i)
			{
				auto item = _components[i].get();
				if (item->IsActive())
					item->Update(deltaTime);
			}
		}
	};

	class MeshRendererComponent : public Component
	{
	private:
		FixedString<128> _path{};
		bool _isLoaded = false;
		Model _model{};

	public:
		void SetPath(pcstr path);

		void Load();

		void Unload();

		void Render() const;
	};

	class CameraComponent : public Component
	{
	private:
		Camera _camera = {};

	public:
		void Start() override;

		void BeginRender3D() const;

		void EndRender3D() const;
	};
}


#endif //GAMEOBJECT_H

#pragma once

#include <glm/glm.hpp>

namespace ce {
	class Transform {
	 public:
		/**
	  * @brief Get a Vector globally pointing Upwards Global Up
	  * 
	  * @return glm::vec3 
	  */
		static glm::vec3 GetGlobalUp() { return glm::vec3(0.0f, 1.0f, 0.0f); }

		/**
		 * @brief Construct a new Transform object
		 * 
		 */
		Transform();
		/**
		 * @brief Destroy the Transform object
		 * 
		 */
		~Transform();

		/**
		 * @brief Get the Parent Tranform object
		 * 
		 * @return Transform* 
		 */
		Transform* getParent() { return m_parent; }
		/**
		 * @brief Set the Parent Transform object
		 * 
		 * @param parent 
		 */
		void setParent(Transform* parent) { m_parent = parent; }
		/**
		 * @brief Get the Position of the transform
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getPosition() { return m_pos; }
		/**
		 * @brief Set the Position of the transform 
		 * 
		 * @param pos New Position
		 */
		void setPosition(glm::vec3 pos) { m_pos = pos; }
		/**
		 * @brief Set the Position of the transform
		 * 
		 * @param x New X position
		 * @param y New Y position
		 * @param z New Z position
		 */
		void setPosition(float x, float y, float z) { m_pos = glm::vec3(x, y, z); }
		void setX(float x) { m_pos.x = x; }
		void setY(float y) { m_pos.y = y; }
		void setZ(float z) { m_pos.z = z; }
		/**
		 * @brief Translate (or move) the transform
		 * 
		 * @param delta  the amount to move by
		 */
		void translate(glm::vec3 delta) { m_pos += delta; }
		/**
		 * @brief Translate or move the transform by and X,Y,Z amount
		 * 
		 * @param x X delta
		 * @param y Y delta
		 * @param z Z delta
		 */
		void translate(float x, float y, float z) { m_pos += glm::vec3(x, y, z); }

		/**
		 * @brief Set the Pitch of the transfomr
		 * 
		 * @param pitch 
		 */
		void setPitch(float pitch) { m_rot.x = pitch; }
		/**
		 * @brief Rotate the transform's pitch
		 * 
		 * @param delta 
		 */
		void pitch(float delta) { m_rot.x += delta; }
		/**
		 * @brief Get the Pitch of the transform
		 * 
		 * @return float 
		 */
		float getPitch() { return m_rot.x; }

		/**
		 * @brief Set the Yaw of the transform
		 * 
		 * @param yaw 
		 */
		void setYaw(float yaw) { m_rot.y = yaw; }
		/**
		 * @brief Rotate the transform's Yaw
		 * 
		 * @param delta 
		 */
		void yaw(float delta) { m_rot.y += delta; }
		/**
		 * @brief Get the Yaw of the transform
		 * 
		 * @return float 
		 */
		float getYaw() { return m_rot.y; }

		/**
		 * @brief Set the Roll of the transform
		 * 
		 * @param roll 
		 */
		void setRoll(float roll) { m_rot.z = roll; }
		/**
		 * @brief Rotate the transform's Roll
		 * 
		 * @param delta 
		 */
		void roll(float delta) { m_rot.z += delta; }
		/**
		 * @brief Get the Roll of the transform
		 * 
		 * @return float 
		 */
		float getRoll() { return m_rot.z; }

		/**
		 * @brief Get the Rotation of the transform
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getRotation() { return m_rot; }
		/**
		 * @brief Set the Rotation of the transform
		 * 
		 * @param rot 
		 */
		void setRotation(glm::vec3 rot) { m_rot = rot; }
		/**
		 * @brief Set the Rotation of the transform
		 * 
		 * @param x Pitch
		 * @param y Yaw
		 * @param z Roll
		 */
		void setRotation(float x, float y, float z) { m_rot = glm::vec3(x, y, z); }
		/**
		 * @brief Rotate the transform by an amount
		 * 
		 * @param delta 
		 */
		void rotate(glm::vec3 delta) { m_rot += delta; }
		/**
		 * @brief Rotate the transform by an amount
		 * 
		 * @param x Pitch
		 * @param y Yaw
		 * @param z Roll
		 */
		void rotate(float x, float y, float z) { m_rot += glm::vec3(x, y, z); }

		/**
		 * @brief Get the Scale of the transform
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getScale() { return m_scale; }
		/**
		 * @brief Set the Scale of the transform
		 * 
		 * @param scale 
		 */
		void setScale(glm::vec3 scale) { m_scale = scale; }
		/**
		 * @brief Set the Scale object via X,Y,Z
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void setScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }
		/**
		 * @brief Evenly set the Scale of the transform
		 * 
		 * @param a Scale amount
		 */
		void setScale(float scale) { m_scale = glm::vec3(scale); }
		void setScaleX(float x) { m_scale.x = x; }
		void setScaleY(float y) { m_scale.y = y; }
		void setScaleZ(float z) { m_scale.z = z; }
		/**
		 * @brief Scale the transform via x,y,z
		 * 
		 * @param delta 
		 */
		void scale(glm::vec3 delta) { m_scale *= delta; }
		/**
		 * @brief Scale the transform by X,Y,Z
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void scale(float x, float y, float z) { m_scale *= glm::vec3(x, y, z); }
		/**
		 * @brief Evenly scale the transform
		 * 
		 * @param a 
		 */
		void scale(float a) { scale(a, a, a); }

		/**
		 * @brief Get the Trasnform Matrix
		 * 
		 * @return glm::mat4 
		 */
		glm::mat4 getMatrix();
		/**
		 * @brief Get transform's Forward vector
		 * 
		 * @param useYaw 
		 * @param usePitch 
		 * @param useRoll 
		 * @return glm::vec3 
		 */
		glm::vec3 getForward(bool useYaw = true, bool usePitch = true, bool useRoll = true);
		/**
		 * @brief Get transform's Right vector
		 * 
		 * @param useYaw 
		 * @param usePitch 
		 * @param useRoll 
		 * @return glm::vec3
		 */
		glm::vec3 getRight(bool useYaw = true, bool usePitch = true, bool useRoll = true);
		/**
		 * @brief Get transform's Up vector
		 * 
		 * @param useYaw 
		 * @param usePitch 
		 * @param useRoll 
		 * @return glm::vec3
		 */
		glm::vec3 getUp(bool useYaw = true, bool usePitch = true, bool useRoll = true);

	 private:
		Transform* m_parent;
		/*
		 * Pitch: X
		 * Yaw: Y
		 * Roll: Z
		 */
		glm::vec3 m_pos, m_rot, m_scale;
	};
}

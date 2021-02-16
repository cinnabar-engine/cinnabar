#ifndef _CE_TRANSFORM_H_
#define _CE_TRANSFORM_H_

#include <ce_math.h>
#include <ce_render_fundementals.h>

namespace ce {
	class Transform {
	private:
		/*
		 * Pitch:X
		 * Yaw:Y
		 * Roll: Z
		 * 
		*/
		glm::vec3
			m_pos,
			m_rot,
			m_scale;
	public:
		Transform();
		~Transform();
		
		static glm::vec3 getGloablUp() {return glm::vec3(0.0f,1.0f,0.0f);}
		
		glm::vec3 getPosition() {return m_pos;}
		void setPosition(glm::vec3 pos){m_pos=pos;}
		void setPosition(float x,float y,float z){ setPosition(glm::vec3(x,y,z));}
		void translate(glm::vec3 delta){m_pos+=delta;}
		void translate(float x,float y,float z){translate(glm::vec3(x,y,z));}
		
		void setPitch(float pitch){m_rot.x = pitch;}
		void pitch(float delta){m_rot.x+= delta;}
		float getPitch(){return m_rot.x;}
		
		void setYaw(float yaw){m_rot.y = yaw;}
		void yaw(float delta){m_rot.y += delta;}
		float getYaw(){return m_rot.y;}
		
		void setRoll(float roll) {m_rot.z = roll;}
		void roll(float delta) {m_rot.z += delta;}
		float getRoll(){return m_rot.z;}
		
		glm::vec3 getRotation() {return m_rot;}
		void setRotation(glm::vec3 rot){m_rot=rot;}
		void setRotation(float x,float y,float z){ setRotation(glm::vec3(x,y,z));}
		void rotate(glm::vec3 delta) {m_rot+=delta;}
		void rotate(float x, float y, float z) {rotate(glm::vec3(x,y,z));}
		
		glm::vec3 getScale() {return m_scale;}
		void setScale(glm::vec3 scale){m_scale=scale;}
		void setScale(float x,float y,float z){ setScale(glm::vec3(x,y,z));}
		void setScale(float a){setScale(a,a,a);}
		void scale(glm::vec3 delta) {m_scale*=delta;}
		void scale(float x, float y, float z) {scale(glm::vec3(x,y,z));}
		void scale(float a){scale(a,a,a);}
		
		glm::mat4 getMatrix();
		
		void sendToShader(ce::Shader* shader);
		glm::vec3 getForward();
	};
}

#endif // _CE_TRANSFORM_H_

// Transform.cpp: implementation of the Transform class.


#include "Transform.h"


// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	mat3 r;		//same
	mat3 m1;
	mat3 m2;
	mat3 m3;
	float angle = -degrees * pi / 180;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	m1[0] = vec3(1, 0, 0);
	m1[1] = vec3(0, 1, 0);
	m1[2] = vec3(0, 0, 1);
	m2[0] = vec3(axis[0] * axis[0], x * y, x * z);
	m2[1] = vec3(x * y, axis[1] * axis[1], y * z);
	m2[2] = vec3(x * z, y * z, axis[2] * axis[2]);
	m3[0] = vec3(0, z, -y);
	m3[1] = vec3(-z, 0, x);
	m3[2] = vec3(y, -x, 0);

	m1 = cos(angle) * m1;
	m2 = (1 - cos(angle)) * m2;
	m3 = sin(angle) * m3;
	r = m1 + m2 + m3;

	return r;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = eye * rotate(degrees, up);	//same
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 normal = glm::normalize(glm::cross(eye, up));	//same
	eye = eye * rotate(degrees, normal);
	up = up * rotate(degrees, normal); 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
	mat4 la;	//same
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::normalize(glm::cross(w, u));
	la[0] = vec4(u[0], v[0], w[0], 0);
	la[1] = vec4(u[1], v[1], w[1], 0);
	la[2] = vec4(u[2], v[2], w[2], 0);
	la[3] = vec4(-u[0]*eye[0]-u[1]*eye[1]-u[2]*eye[2], -v[0]*eye[0]-v[1]*eye[1]-v[2]*eye[2], -w[0]*eye[0]-w[1]*eye[1]-w[2]*eye[2], 1);
	return glm::transpose(la);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float near = zNear;
	float far = zFar;
    float top = near * tan(fovy/2 * pi/180);
    float bottom = -top;
    float right = aspect*top;
    float left = -right;

     mat4 persp;
	 persp[0] = vec4((2*near) / (right-left), 0, 0, 0);
     persp[1] = vec4(0, (2*near) / (top-bottom), 0, 0);
     persp[2] = vec4((right+left) / (right-left), (top+bottom) / (top-bottom), -(far+near) / (far-near), -1);
     persp[3] = vec4(0, 0, (-2*far*near) / (far-near), 0);

   return glm::transpose(persp);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
	mat4 scale;
	scale[0] = vec4(sx, 0, 0, 0);
	scale[1] = vec4(0, sy, 0, 0);
	scale[2] = vec4(0, 0, sz, 0);
	scale[3] = vec4(0, 0, 0, 1);
	return scale;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
	mat4 trans;
	trans[0] = vec4(1, 0, 0, 0);
	trans[1] = vec4(0, 1, 0, 0);
	trans[2] = vec4(0, 0, 1, 0);
	trans[3] = vec4(tx, ty, tz, 1);
	return trans;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
  vec3 x = glm::cross(up,zvec) ; 
  vec3 y = glm::cross(zvec,x) ; 
  vec3 ret = glm::normalize(y) ; 
  return ret ; 
}

//camera
void Transform::cam_y(vec3 &eye, vec3 &center, float amount) {
	vec3 cam = (center - eye) * vec3(amount);
	eye += cam;
	center += cam;

}

void Transform::cam_z(vec3 &eye, vec3 &center, float amount) {
	eye.z += amount;
	center.z += amount;
}

void Transform::cam_x(vec3 &eye, vec3 &center, vec3 &up, float amount) {
	vec3 cam = (center - eye);
	vec3 ortho = glm::cross(cam, up) * vec3(amount);
	eye.x += ortho.x;
	eye.y += ortho.y;
	center.x += ortho.x;
	center.y += ortho.y;

}

void Transform::cam_rotate(vec3 &eye, vec3 &center, float angle) {
    vec3 cam = center - eye;
    center.x = (float)(eye.x + cos(angle)*cam.x - sin(angle)*cam.y);
    center.y = (float)(eye.y + sin(angle)*cam.x + cos(angle)*cam.y);
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

#ifndef VECTOR_R

#define VECTOR_R

/* Vector Class */

typedef struct {
	void* sub;
	double values[3];
	char* toString;
}o_Vector3D;

#endif
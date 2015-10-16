#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

std::vector<float>angleData;

void PrintSpherePointData(float radius, float lati, float longi);
void PrintSphereAndAddedCentreVertexCount(float radius, float lati, float longi);
void PrintAngleData(float radius, float lati, float longi);

int main() {

	//PrintSpherePointData(0,30,30);
	PrintSphereAndAddedCentreVertexCount(0,30,30);

	return 0;
}

void PrintSpherePointData(float radius, float lati, float longi) {

	float M_PI = 3.14;

	for (float latNumber = 0; latNumber <= lati; latNumber++) {

		float theta = latNumber * M_PI / lati;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longi; longNumber++) {
			float phi = longNumber * 2 * M_PI / longi;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			cout << "Lat: " << latNumber << ", Long: " << longNumber << " x: " <<  cosPhi * sinTheta << " y: " << cosTheta << " z: " << sinPhi * sinTheta << endl;
		
		}
	}
}

void PrintSphereAndAddedCentreVertexCount(float radius, float lati, float longi) {

	float M_PI = 3.14;

	int vertexCount = 0;

	for (float latNumber = 0; latNumber <= lati; latNumber++) {

		float theta = latNumber * M_PI / lati;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longi; longNumber++) {
			float phi = longNumber * 2 * M_PI / longi;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			vertexCount++;
			//vertexCount++;
		}
	}

	cout << "Vertex count: " << vertexCount << endl;
}

void PrintAngleData(float radius, float lati, float longi) {

}
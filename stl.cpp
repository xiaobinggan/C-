#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>       /* sin cos */
#include <string>

using namespace std;

#define PI 3.14159265

void push_vertex(vector<double> &v, double x, double y, double z) {
    v.push_back(x);
    v.push_back(y);
    v.push_back(z);
}

class Shape {
protected:
    double x, y, z;
public:
    Shape(double x, double y, double z) : x(x), y(y), z(z) {}
    virtual ~Shape() {}
    virtual vector<double> getFacetsData() {}
};

class Cylinder:public Shape {
private:
    double r, h;
    int facets;
public:
    Cylinder (double x, double y, double z, double r, double h, int facets) : Shape(x, y, z), r(r), h(h), facets(facets) {}
    vector<double> getFacetsData() {
        vector<double> facetsData;
        //slice the circle to how many facets? => sin theta, cos theta, theta = 360/facets
        //deal with top and bottom first
        //top
        for (int i = 0; i < facets; i++) {
            push_vertex(facetsData, 0, 0, 1);
            push_vertex(facetsData, x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180) , z + h);
            push_vertex(facetsData, x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180) , z + h);
            push_vertex(facetsData, x, y, z + h);
        }
        //bottom
        for (int i = 0; i < facets; i++) {
            push_vertex(facetsData, 0, 0, -1);
            push_vertex(facetsData, x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180) , z);
            push_vertex(facetsData, x, y, z);
            push_vertex(facetsData, x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180) , z);
        }
        //side, theta/2
        for (int i = 0; i < facets; i++) {
            push_vertex(facetsData, sin(360 / 2 / facets * i * PI / 180), cos(360 / 2 / facets * i * PI / 180), 0);
            push_vertex(facetsData, x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180) , z + h);
            push_vertex(facetsData, x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180) , z);
            push_vertex(facetsData, x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180) , z + h);
            push_vertex(facetsData, sin(360 / 2 / facets * i * PI / 180), cos(360 / 2 / facets * i * PI / 180), 0);
            push_vertex(facetsData, x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180) , z);
            push_vertex(facetsData, x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180) , z);
            push_vertex(facetsData, x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180) , z + h);
        }
        return facetsData;
    }
};

class Cube:public Shape {
private:
    double size;
public:
    Cube (double x, double y, double z, double size): Shape(x, y, z), size(size) {}
    vector<double> getFacetsData() {
        vector<double> facetsData;
        // six facets, just iterate all of them, can't find easier solution
        // 0 0 1
        push_vertex(facetsData, 0, 0, 1);
        push_vertex(facetsData, x, y + size, z + size);
        push_vertex(facetsData, x + size, y + size, z + size);
        push_vertex(facetsData, x + size, y, z + size);
        push_vertex(facetsData, 0, 0, 1);
        push_vertex(facetsData, x, y + size, z + size);
        push_vertex(facetsData, x + size, y, z + size);
        push_vertex(facetsData, x, y, z + size);
        // 0 0 -1
        push_vertex(facetsData, 0, 0, -1);
        push_vertex(facetsData, x, y + size, z);
        push_vertex(facetsData, x + size, y, z);
        push_vertex(facetsData, x + size, y + size, z);
        push_vertex(facetsData, 0, 0, -1);
        push_vertex(facetsData, x, y + size, z);
        push_vertex(facetsData, x, y, z);
        push_vertex(facetsData, x + size, y, z);
        // 0 1 0
        push_vertex(facetsData, 0, 1, 0);
        push_vertex(facetsData, x, y + size, z + size);
        push_vertex(facetsData, x, y + size, z);
        push_vertex(facetsData, x + size, y + size, z);
        push_vertex(facetsData, 0, 1, 0);
        push_vertex(facetsData, x, y + size, z + size);
        push_vertex(facetsData, x + size, y + size, z);
        push_vertex(facetsData, x + size, y + size, z + size);
        // 0 -1 0
        push_vertex(facetsData, 0, -1, 0);
        push_vertex(facetsData, x, y, z + size);
        push_vertex(facetsData, x + size, y, z);
        push_vertex(facetsData, x, y, z);
        push_vertex(facetsData, 0, -1, 0);
        push_vertex(facetsData, x, y, z + size);
        push_vertex(facetsData, x + size, y, z + size);
        push_vertex(facetsData, x + size, y, z);
        // 1 0 0
        push_vertex(facetsData, 1, 0, 0);
        push_vertex(facetsData, x + size, y + size, z);
        push_vertex(facetsData, x + size, y, z);
        push_vertex(facetsData, x + size, y, z + size);
        push_vertex(facetsData, 1, 0, 0);
        push_vertex(facetsData, x + size, y + size, z + size);
        push_vertex(facetsData, x + size, y + size, z);
        push_vertex(facetsData, x + size, y, z + size);
        // -1 0 0
        push_vertex(facetsData, -1, 0, 0);
        push_vertex(facetsData, x, y + size, z);
        push_vertex(facetsData, x, y, z + size);
        push_vertex(facetsData, x, y, z);
        push_vertex(facetsData, -1, 0, 0);
        push_vertex(facetsData, x, y + size, z + size);
        push_vertex(facetsData, x, y, z + size);
        push_vertex(facetsData, x, y + size, z);
        return facetsData;
    }
};

class CAD {
private:
    vector<Shape*> shapes;
public:
    CAD() {}
    ~CAD() {
        int size = shapes.size();
        for (int i = 0; i < size; i++) {
            delete shapes[i];
        }
    }
    void add(Shape* s) {
        shapes.push_back(s);
    }
    //TODO: rewrite this
    void write(string fileName) {
        ofstream myfile;
        myfile.open(fileName);
        myfile << "solid test_model" << endl;
        for (Shape* s : shapes) {
            vector<double> facetsData = s->getFacetsData();
            int size = facetsData.size();
            for (int i = 0; i < size; i += 3 * 4) {
                myfile << "  facet normal " << facetsData[i] << " " << facetsData[i + 1] << " " << facetsData[i + 2] << endl;
                myfile << "    outer loop" << endl;
                myfile << "      vertex " << facetsData[i + 3] << " " << facetsData[i + 4] << " " << facetsData[i + 5] << endl;
                myfile << "      vertex " << facetsData[i + 6] << " " << facetsData[i + 7] << " " << facetsData[i + 8] << endl;
                myfile << "      vertex " << facetsData[i + 9] << " " << facetsData[i + 10] << " " << facetsData[i + 11] << endl;
                myfile << "    endloop" << endl;
                myfile << "  endfacet" << endl;
            }
        }
        myfile << "endsolid test_model" << endl;
        myfile.close();
    }
};

//https://www.stratasysdirect.com/resources/how-to-prepare-stl-files/
//https://www.viewstl.com/
int main ()
{
  CAD c;
  c.add (new Cube (0, 0, 0, 5));
  c.add (new Cylinder (100, 0, 0, 3, 10, 10));
  c.write ("test.stl");
//   c.write();
}
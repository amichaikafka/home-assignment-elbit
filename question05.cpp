//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, create a base Shape class that both Circle and Rectangle inherit from, try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  

/*Explanation:
* 1.I defined shape as an abstarct class (with pure virtual method) which has two constarcturs (one that get size and point and one that get radius and point)
* Both circle and Rectangle inherit from shape and impelments the pure virtual methods(area and name)
* 2. I defined a friend method that overload the operator "<<" to allow using this operator on Point(to print it)
* 3. I changed the return value of the member function area to return double, because area doesn't have to be an integer,
* i also changed the type of width and height of size, to support area of Rectangle that not a number.
*/							 
#include <iostream>
#include <vector>
#include <string>
#include <corecrt_math_defines.h>
using namespace std;
struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& out, const Point& p) 
	{
		out << p.x << "/" << p.y;
		return out;
	}

};

struct Size {

	Size() :
		width(0),
		height(0){}

	Size(int width_, int height_) :
		width(width_),
		height(height_){}

	double width;
	double height;
};
class Shape
{


public:

	Shape(const Point& center, const Size& size) :
		m_center(center),
		m_size(size),
		radius(0)
	{ 
	}
	Shape(const Point& center, const double radius) :
		m_center(center),
		m_size(0,0),
		radius(radius)
	{
	}

	const Point& center() const {
		return m_center;
	}

	
	virtual double area()const = 0;
	virtual string name()const = 0;

protected:
	Point m_center;
	Size  m_size;
	double radius;

};

class Rectangle :public Shape {

public:

	Rectangle(const Point& center, const Size& size) :
		Shape(center, size)
	{
	}

	 virtual double area() const {
		return m_size.width *m_size.height;
	}
	 virtual string name() const {
		 return "Rectangle";
	 }


};
class Circle :public Shape {

public:

	Circle(const Point& center, const double radius) :
		Shape(center,radius)

	{
	}

	virtual double area()const {
		
		return M_PI * radius* radius;
	}
	virtual string name()const {
		return "Circle";
	}

};


int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{&circle1, & rect1, & circle2};
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
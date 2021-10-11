#include <iostream>
#include <cmath>

class Point 
{
private:
    int x, y;
public:
    Point(int pos_x, int pos_y)
        :x{ pos_x }, y{ pos_y } {}
    int getPointX() const { return x; }
    int getPointY() const { return y; }
};

class Geometry
{
private:
    Point *point_arr[100];
    int num_points;

public:
    Geometry()
    {
        num_points = 0;
    }

    ~Geometry()
    {
        for (int i = 0; i < num_points; i++)
            delete point_arr[i];
    }

    void addPoint(int x, int y)
    {
        point_arr[num_points++] = new Point(x, y);
    }
    
    void printDistance();
};

void Geometry::printDistance()
{

    for (int i = 0; i < num_points-1; i++)
        for(int j=i+1; j< num_points; j++)
        {
            if (!((point_arr[i]->getPointX() == point_arr[j]->getPointX())&&(point_arr[i]->getPointY() == point_arr[j]->getPointY())))
                std::cout << "( " << point_arr[i]->getPointX() << " , " << point_arr[i]->getPointY() << " ) / " <<
                "( " << point_arr[j]->getPointX() << " , " << point_arr[j]->getPointY() << " ) = " <<
                sqrt(pow(point_arr[j]->getPointX() - point_arr[i]->getPointX(), 2) + pow(point_arr[j]->getPointY() - point_arr[i]->getPointY(), 2)) << std::endl;
        }
        
}

int main()
{
    Geometry g;

    for (int i = 0; i < 10; i++)
            g.addPoint(i, 9-i);

    g.printDistance();

    return 0;
}
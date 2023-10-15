#ifndef position_hpp
#define position_hpp

class Position
{
private:
    int coordX, coordY;
    
public:
    int getX()
    {
        return coordX;
    }
    int getY()
    {
        return coordY;
    }
    
    void getCoordinates (int &x, int &y);
    void setCoordinates (int x, int y);
};

#endif /* position_hpp */

#ifndef POSITIONINTERFACE_H
#define POSITIONINTERFACE_H


class PositionInterface
{
public:
    PositionInterface();
    PositionInterface(int x, int y);
    ~PositionInterface();
    virtual void set_x(int x);
    virtual void set_y(int y);
    virtual void set_position(int x, int y);
    virtual int get_x();
    virtual int get_y();
    virtual int get_z();
    virtual void set_z(int z) = 0;

protected:
    int xpos;
    int ypos;
    int z_value;
};

#endif // POSITIONINTERFACE_H

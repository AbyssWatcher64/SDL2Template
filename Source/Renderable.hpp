#ifndef RENDERABLE
#define RENDERABLE

class Renderable
{
public:
    Renderable(int layer, bool forceDrawInsideCamera)
        : layer(layer), forceDrawInsideCamera(forceDrawInsideCamera) {
    }
    virtual ~Renderable() = default;

    virtual void Draw() const = 0; 

    virtual int GetLayer() const
    {
        return layer;
    }

    virtual int GetRenderBasePoint() const
    {
        return 0;
    }

    virtual void SetRenderBasePoint(int newBasePoint)
    {
        return;
    }

    virtual int GetYPosition() const
    {
        return 0;
    }

protected:

    int layer;
    bool forceDrawInsideCamera;
};

#endif
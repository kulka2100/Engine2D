#pragma once
class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    void setPosition(float x, float y);
    void getPosition(float& x, float& y) const;
    void setRotation(float angle);
    float getRotation() const;
    void setScale(float factor);
    float getScale() const;
    float getX() const;
    float getY() const;

private:
    float go_x;
    float go_y;
    float go_rotation;
    float go_scale;
};


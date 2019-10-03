#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
    public:
        unsigned int index; // what row of the sprite sheet you are on
        unsigned int numFrames;
        unsigned int animationSpeed;
        Animation();
        Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
};

#endif
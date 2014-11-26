#pragma once
#include "DrawableEntity.h"
#include "Camera.h"
#include "header_loader.h"

class AnimatingEntity :
	public DrawableEntity
{
private:
	int firstImgID;
	int animateSpeed;
	bool animating;
	int animationStartIndex;
	int animationEndIndex;
	int currentImageIndex;
	long timeSinceLastFrame;
public:
	AnimatingEntity(int id, double x, double y, int chunkSize, int firstImgID);
	void animate(double dt);
	void setAnimation(int startIndex, int endIndex, double animateSpeed);
	void setStaticImage(int index);
	void setCurrentlyAnimating(bool animating);
	bool getCurrentlyAnimating();
	virtual ~AnimatingEntity();
};


#pragma once
#include "DrawableEntity.h"
#include "Camera.h"
#include "header_loader.h"

class AnimatingEntity :
	public DrawableEntity
{
private:
	int firstImgID;
	double animateSpeed;
	bool animating;
	int animationStartIndex;
	int animationEndIndex;
	int currentImageIndex;
	long lastFrameTime;

	bool animateLoop;
	double animationStartTime;
	double animateTime;
	int finishedIndex;

public:
	AnimatingEntity(int id, double x, double y, int chunkSize, int firstImgID);
	virtual void animate();
	void setAnimation(int startIndex, int endIndex, double animateSpeed);
	void setAnimation(int startIndex, int endIndex, double animateSpeed, double animateTime, int finishedIndex);
	void setStaticImage(int index);
	void setCurrentlyAnimating(bool animating);
	bool getCurrentlyAnimating();
	virtual ~AnimatingEntity();
};


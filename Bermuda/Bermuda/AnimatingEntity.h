#pragma once
#include "DrawableEntity.h"

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
	AnimatingEntity(int id, double x, double y, int firstImgID);
	virtual void animate();
	void startAnimationLoopType(int startIndex, int endIndex, double animateSpeed);
	void startAnimationTimerType(int startIndex, int endIndex, double animateSpeed, double animateTime, int finishedIndex, void(*callbackFunction)());
	void startAnimationCounterType(int startIndex, int endIndex, double animateSpeed, double animateTime, int finishedIndex, void(*callbackFunction)());
	void setStaticImage(int index);
	void setCurrentlyAnimating(bool animating);
	bool getCurrentlyAnimating();
	virtual ~AnimatingEntity();
};


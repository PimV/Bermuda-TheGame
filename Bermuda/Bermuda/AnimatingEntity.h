#pragma once
#include "DrawableEntity.h"
#include "AnimationType.h"

class AnimatingEntity :
	public DrawableEntity
{
private:
	//multiple animation types
	int firstImgID;
	double animateSpeed;
	AnimationType currentAnimationType;
	int animationStartIndex;
	int animationEndIndex;
	int currentImageIndex;
	long lastFrameTime;
	int finishedIndex;

	//animate timer
	double animationEndTime;

	//animate counter
	int animationCount;
	int targetAnimationCount;
protected:
	virtual void animationFinished();
public:
	AnimatingEntity(int id, double x, double y, int firstImgID);
	virtual void animate();
	void startAnimationLoopType(int startIndex, int endIndex, double animateSpeed);
	void startAnimationTimerType(int startIndex, int endIndex, double animateSpeed, double animateTime, int finishedIndex);
	void startAnimationCounterType(int startIndex, int endIndex, double animateSpeed, int animateCount, int finishedIndex);
	void setStaticImage(int index);
	void stopAnimating();
	bool getCurrentlyAnimating();
	virtual ~AnimatingEntity();
};


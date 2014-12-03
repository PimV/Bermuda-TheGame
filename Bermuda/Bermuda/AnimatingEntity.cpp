#include "AnimatingEntity.h"
#include "GameStateManager.h"
#include "GameTimer.h"
#include <iostream>

AnimatingEntity::AnimatingEntity(int id, double x, double y, int firstImgID) :
	Entity(id, x, y),
	DrawableEntity(id, x, y, nullptr)
{
	this->firstImgID = firstImgID;
	this->currentAnimationType = AnimationType::NONE;
	setStaticImage(0);
}

void AnimatingEntity::animate(double dt)
{
	if (this->getCurrentlyAnimating())
	{
		//wait for next frame
		long currentTime = GameTimer::Instance()->getGameTime();
		if (lastFrameTime + animateSpeed < currentTime)
		{
			int nextFrame = ++this->currentImageIndex;
			switch (this->currentAnimationType)
			{
			case AnimationType::TIMER:
				if (this->animationEndTime < currentTime)
				{
					setStaticImage(this->finishedIndex);
					animationFinished();
					return;
				}
				break;
			case AnimationType::COUNTER:
				if (this->animationCount >= this->targetAnimationCount)
				{
					setStaticImage(this->finishedIndex);
					animationFinished();
					return;
				}
				break;
			}

			if (nextFrame > this->animationEndIndex)
			{
				if (currentAnimationType == AnimationType::COUNTER)
				{
					animationCount++;
				}
				currentImageIndex = this->animationStartIndex;
				nextFrame = this->animationStartIndex;
			}
			setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(this->firstImgID + nextFrame));
			this->lastFrameTime = currentTime;
		}
	}
}

void AnimatingEntity::startAnimationLoopType(int startIndex, int endIndex, double animateSpeed)
{
	this->currentAnimationType = AnimationType::LOOP;

	this->currentImageIndex = startIndex;
	this->setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(this->firstImgID + startIndex));
	this->lastFrameTime = GameTimer::Instance()->getGameTime();
	this->animationStartIndex = startIndex;
	this->animationEndIndex = endIndex;
	this->animateSpeed = animateSpeed;
}

void AnimatingEntity::startAnimationTimerType(int startIndex, int endIndex, double animateSpeed, double animateTime, int finishedIndex)
{
	this->currentAnimationType = AnimationType::TIMER;
	this->animationEndTime = GameTimer::Instance()->getGameTime() + animateTime;

	this->currentImageIndex = startIndex;
	this->setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(this->firstImgID + startIndex));
	this->lastFrameTime = GameTimer::Instance()->getGameTime();
	this->animationStartIndex = startIndex;
	this->animationEndIndex = endIndex;
	this->animateSpeed = animateSpeed;
	this->finishedIndex = finishedIndex;
}

void AnimatingEntity::startAnimationCounterType(int startIndex, int endIndex, double animateSpeed, int animateCount, int finishedIndex)
{
	this->currentAnimationType = AnimationType::COUNTER;
	this->animationCount = 0;
	this->targetAnimationCount = animateCount;

	this->currentImageIndex = startIndex;
	this->setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(this->firstImgID + startIndex));
	this->lastFrameTime = GameTimer::Instance()->getGameTime();
	this->animationStartIndex = startIndex;
	this->animationEndIndex = endIndex;
	this->animateSpeed = animateSpeed;
	this->finishedIndex = finishedIndex;
}

void AnimatingEntity::animationFinished()
{
	std::cout << "animation finished" << std::endl;
}

void AnimatingEntity::setStaticImage(int index)
{
	this->stopAnimating();
	int currentImageIndex = firstImgID + index;
	this->setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(currentImageIndex));
}

void AnimatingEntity::stopAnimating()
{
	this->currentAnimationType = AnimationType::NONE;
}

bool AnimatingEntity::getCurrentlyAnimating()
{
	return this->currentAnimationType != AnimationType::NONE;
}

AnimatingEntity::~AnimatingEntity()
{
}

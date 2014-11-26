#include "AnimatingEntity.h"
#include "GameStateManager.h"


AnimatingEntity::AnimatingEntity(int id, double x, double y, int chunkSize, int firstImgID) :
	Entity(id, x, y, chunkSize),
	DrawableEntity(id, x, y, chunkSize, nullptr)
{
	this->firstImgID = firstImgID;
	this->timeSinceLastFrame = 0;
	setStaticImage(0);
}

void AnimatingEntity::animate(double dt)
{
	if (this->animating)
	{
		//wait for next frame
		this->timeSinceLastFrame += GameStateManager::Instance()->getUpdateLength() * dt;
		if (timeSinceLastFrame >= this->animateSpeed)
		{
			int nextFrame = this->currentImageIndex++;
			if (nextFrame > this->animationEndIndex)
			{
				nextFrame = this->animationStartIndex;
			}
			setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(nextFrame));
			timeSinceLastFrame = 0;
		}
	}
}

void AnimatingEntity::setAnimation(int startIndex, int endIndex, double animateSpeed)
{
	if (this->currentImageIndex < startIndex ||
		this->currentImageIndex > endIndex)
	{
		//New animation started;
		this->currentImageIndex = startIndex;
	}
	this->setCurrentlyAnimating(true);
	this->animationStartIndex = startIndex;
	this->animationEndIndex = endIndex;
	this->animateSpeed = animateSpeed;
}

void AnimatingEntity::setStaticImage(int index)
{
	this->setCurrentlyAnimating(false);
	int currentImageIndex = firstImgID + index;
	this->setDrawImage(GameStateManager::Instance()->getImageLoader()->getMapImage(currentImageIndex));
}

void AnimatingEntity::setCurrentlyAnimating(bool animating)
{
	this->animating = animating;
}

bool AnimatingEntity::getCurrentlyAnimating()
{
	return this->animating;
}

AnimatingEntity::~AnimatingEntity()
{
}

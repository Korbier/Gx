#include "Timer.h"

Timer::Timer()
{
	//Initialize the variables
	this->mStartTicks = 0;
	this->mPausedTicks = 0;

	this->mPaused = false;
	this->mStarted = false;
}

void Timer::start()
{
	//Start the timer
	this->mStarted = true;

	//Unpause the timer
	this->mPaused = false;

	//Get the current clock time
	this->mStartTicks = SDL_GetTicks();
	this->mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	this->mStarted = false;

	//Unpause the timer
	this->mPaused = false;

	//Clear tick variables
	this->mStartTicks = 0;
	this->mPausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (this->mStarted && !this->mPaused)
	{
		//Pause the timer
		this->mPaused = true;

		//Calculate the paused ticks
		this->mPausedTicks = SDL_GetTicks() - this->mStartTicks;
		this->mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (this->mStarted && this->mPaused)
	{
		//Unpause the timer
		this->mPaused = false;

		//Reset the starting ticks
		this->mStartTicks = SDL_GetTicks() - this->mPausedTicks;

		//Reset the paused ticks
		this->mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (this->mStarted)
	{
		//If the timer is paused
		if (this->mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = this->mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return this->mStarted;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return this->mPaused && this->mStarted;
}
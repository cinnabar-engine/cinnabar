#ifndef _TIME_H_
#define _TIME_H_

class Time
{
public:
	Time();
	~Time();

	void update();

	float getDeltaTime();
	float getFPS();

private:
	float now;
	float last;
	float dt;
	float fps;

	float getTime();
};

#endif // !_TIME_H_

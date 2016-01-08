#ifndef __BOWLING_H__
#define __BOWLING_H__

#define BONUS_MAX 3
#define BONUS_SPARE 1
#define BONUS_STRIKE 2

struct bowling_bonus
{
	int remain;
	int current;
};

struct bowling
{
	int current;
	int frame;

	struct bowling_bonus bonus[BONUS_MAX];
};

void bowling_init(struct bowling *bowling);
int bowling_feed(struct bowling *bowling, int score);

#endif

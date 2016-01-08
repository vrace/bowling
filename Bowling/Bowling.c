#include "bowling.h"
#include <stdlib.h>
#include <assert.h>

static void award_bonus(struct bowling *bowling, int type, int pending)
{
	int i;
	struct bowling_bonus *bonus = NULL;

	for (i = 0; i < BONUS_MAX; i++)
	{
		if (bowling->bonus[i].remain == 0)
		{
			bonus = &bowling->bonus[i];
			break;
		}
	}

	assert(bonus != NULL);

	if (bonus)
	{
		bonus->remain = type;
		bonus->current = pending;
	}
}

static void accumulate_bonus(struct bowling *bowling, int score)
{
	int i;

	assert(bowling != NULL);

	for (i = 0; i < BONUS_MAX; i++)
	{
		struct bowling_bonus *bonus = &bowling->bonus[i];

		if (bonus->remain > 0)
		{
			bonus->current += score;
			bonus->remain--;

			if (bonus->remain <= 0)
				bowling->current += bonus->current;
		}
	}
}

void bowling_init(struct bowling *bowling)
{
	int i;

	assert(bowling != NULL);

	bowling->current = 0;
	bowling->frame = -1;

	for (i = 0; i < BONUS_MAX; i++)
		bowling->bonus[i].remain = 0;
}

int bowling_feed(struct bowling *bowling, int score)
{
	assert(bowling != NULL);

	if (score < 0 || score > 10 || bowling->frame + score > 10)
		return 0;

	accumulate_bonus(bowling, score);

	if (bowling->frame < 0)
	{
		if (score == 10)
		{
			award_bonus(bowling, BONUS_STRIKE, 10);
		}
		else
		{
			bowling->frame = score;
		}
	}
	else
	{
		int total = bowling->frame + score;

		if (total == 10)
			award_bonus(bowling, BONUS_SPARE, 0);

		bowling->current += total;
		bowling->frame = -1;
	}

	return 1;
}

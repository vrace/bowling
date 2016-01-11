#include "bowling.h"
#include <stdlib.h>
#include <assert.h>

static void award_bonus(struct bowling *bowling, int type)
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
		bonus->current = PIN_TOTAL;
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
	bowling->remain = FRAME_TOTAL;

	for (i = 0; i < BONUS_MAX; i++)
		bowling->bonus[i].remain = 0;
}

int bowling_finalize(struct bowling *bowling)
{
	int i;

	assert(bowling != NULL);

	if (bowling->frame > 0)
		bowling->current += bowling->frame;

	for (i = 0; i < BONUS_MAX; i++)
	{
		struct bowling_bonus *bonus = &bowling->bonus[i];
		if (bonus->remain > 0)
			bowling->current += bonus->current;
	}

	return bowling->current;
}

static int accept_feed(struct bowling *bowling)
{
	int i;
	int remain = 0;

	assert(bowling != NULL);

	for (i = 0; i < BONUS_MAX; i++)
	{
		struct bowling_bonus *bonus = &bowling->bonus[i];
		remain += bonus->remain;
	}

	return bowling->remain + remain;
}

static int validate_feed(struct bowling *bowling, int score)
{
	assert(bowling != NULL);
	return score > 0 && score <= PIN_TOTAL && bowling->frame + score <= PIN_TOTAL;
}

int bowling_feed(struct bowling *bowling, int score)
{
	assert(bowling != NULL);

	if (!accept_feed(bowling) || !validate_feed(bowling, score))
		return 0;

	accumulate_bonus(bowling, score);

	if (bowling->frame < 0)
	{
		if (score == PIN_TOTAL)
		{
			if (bowling->remain > 0)
			{
				award_bonus(bowling, BONUS_STRIKE);
				bowling->remain--;
			}
		}
		else
		{
			bowling->frame = score;
		}
	}
	else
	{
		int total = bowling->frame + score;

		if (total == PIN_TOTAL)
		{
			if (bowling->remain > 0)
				award_bonus(bowling, BONUS_SPARE);
		}
		else
		{
			bowling->current += total;
		}

		bowling->frame = -1;
		bowling->remain--;
	}

	return 1;
}

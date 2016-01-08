#include "../Bowling/Bowling.h"
#include <stdio.h>
#include <assert.h>

void should_accumulate_basic_scores_correctly(void)
{
	struct bowling b;
	
	bowling_init(&b);
	
	bowling_feed(&b, 1);
	bowling_feed(&b, 2);
	bowling_feed(&b, 3);
	bowling_feed(&b, 4);

	assert(bowling_finalize(&b) == 10);
}

void should_accumulate_spare_correctly(void)
{
	struct bowling b;

	bowling_init(&b);

	bowling_feed(&b, 9);
	bowling_feed(&b, 1);
	bowling_feed(&b, 9);
	bowling_feed(&b, 1);

	assert(bowling_finalize(&b) == 29);
}

void should_accumulate_strike_correctly(void)
{
	struct bowling b;

	bowling_init(&b);

	bowling_feed(&b, 1);
	bowling_feed(&b, 1);
	bowling_feed(&b, 1);
	bowling_feed(&b, 1);
	bowling_feed(&b, 10);
	bowling_feed(&b, 1);
	bowling_feed(&b, 1);

	assert(bowling_finalize(&b) == 18);
}

void should_accumulate_strike_sequence_correctly(void)
{
	struct bowling b;

	bowling_init(&b);

	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);

	assert(bowling_finalize(&b) == 300);
}

void should_accumulate_ending_spare_correctly(void)
{
	struct bowling b;

	bowling_init(&b);

	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 10);
	bowling_feed(&b, 9);
	bowling_feed(&b, 1);
	bowling_feed(&b, 10);

	assert(bowling_finalize(&b) == 279);
}

int main(void)
{
	should_accumulate_basic_scores_correctly();
	should_accumulate_spare_correctly();
	should_accumulate_strike_correctly();
	should_accumulate_strike_sequence_correctly();
	should_accumulate_ending_spare_correctly();

	printf("Tests Passed.\n");

	return 0;
}

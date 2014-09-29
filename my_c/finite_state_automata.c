/*
 * http://bojan-komazec.blogspot.tw/2011/10/finite-state-machine-in-c.html
 */

#include <stdio.h>

#define EVENTS_COUNT 4
#define STATES_COUNT 4
#define EVENT_QUEUE_SIZE 4

typedef enum STATE
{ 
        STATE_INVALID,
        STATE_TURNED_OFF,
        STATE_IDLE, 
        STATE_MOVING
} STATE;

typedef enum EVENT
{
        EVENT_IGNITE,
        EVENT_ACCELERATE, 
        EVENT_BRAKE,
        EVENT_TURN_OFF
} EVENT;

typedef void (*TPF)();

typedef struct TRANSITION
{
        STATE next_state;
        TPF action;
} TRANSITION;

void ignited()
{
        printf("Whoooa! I'm turned on!\n"); 
}

void do_nothing()
{
        printf("Don't bother!\n");
}

void complain()
{
        printf("This hurts!\n");
}

void accelerating()
{
        printf("Yipee! I'm accelerating!\n"); 
}

void say_goodbye()
{
        printf("That was probably enough...\n");
}

void braking()
{
        printf("Whoops! Was I too fast?\n");
}

TRANSITION trans_tbl[EVENTS_COUNT][STATES_COUNT] = 
{                    /*STATE_INVALID*/    /*STATE_TURNED_OFF*/            /*STATE_IDLE*/                   /*STATE_MOVING*/
        /*EVENT_IGNITE*/     {{STATE_INVALID, 0}, {STATE_IDLE, ignited},          {STATE_INVALID, complain},       {STATE_INVALID, complain}}, 
        /*EVENT_ACCELERATE*/ {{STATE_INVALID, 0}, {STATE_TURNED_OFF, do_nothing}, {STATE_MOVING, accelerating},    {STATE_MOVING, accelerating}},      
        /*EVENT_BRAKE*/      {{STATE_INVALID, 0}, {STATE_TURNED_OFF, do_nothing}, {STATE_IDLE, do_nothing},        {STATE_IDLE, braking}},
        /*EVENT_TURN_OFF*/   {{STATE_INVALID, 0}, {STATE_TURNED_OFF, do_nothing}, {STATE_TURNED_OFF, say_goodbye}, {STATE_INVALID, complain}} 
};


int main()
{
        STATE state = STATE_TURNED_OFF;  
        EVENT event_queue[EVENT_QUEUE_SIZE] = {EVENT_IGNITE, EVENT_ACCELERATE, EVENT_BRAKE, EVENT_TURN_OFF}; 
        int event_index = 0;

        for(; event_index < EVENTS_COUNT; event_index++)
        {
                EVENT evt = event_queue[event_index ];

                trans_tbl[evt][state].action();
                state = trans_tbl[evt][state].next_state;
        }

        return 0;
}

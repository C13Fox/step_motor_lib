#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H



void moter_init(void);
void moter_run(int32_t speed,uint32_t num);
void moter_on(void);
void moter_off(void);

void clip_init(void);
enum{close=0,open=1}state;
void clip_state(int32_t state);

#endif

#ifndef PATCH_FEEDBACK_H
#define PATCH_FEEDBACK_H

/* Feedback sonoro dos patches: 0=perfeito, 1=estavel, 2=aplicado. */
void patch_feedback_init(void);
void patch_feedback_play_grade(int grade);
void patch_feedback_play_error(void);
void patch_feedback_shutdown(void);

#endif

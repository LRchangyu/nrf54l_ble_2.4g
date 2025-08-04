#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

/* Number of pixels by which the cursor is moved when a button is pushed. */
#define MOVEMENT_SPEED              25
/* Number of input reports in this application. */
#define INPUT_REPORT_COUNT          3
/* Length of Mouse Input Report containing button data. */
#define INPUT_REP_BUTTONS_LEN       3
/* Length of Mouse Input Report containing movement data. */
#define INPUT_REP_MOVEMENT_LEN      3
/* Length of Mouse Input Report containing media player data. */
#define INPUT_REP_MEDIA_PLAYER_LEN  1
/* Index of Mouse Input Report containing button data. */
#define INPUT_REP_BUTTONS_INDEX     0
/* Index of Mouse Input Report containing movement data. */
#define INPUT_REP_MOVEMENT_INDEX    1
/* Index of Mouse Input Report containing media player data. */
#define INPUT_REP_MPLAYER_INDEX     2
/* Id of reference to Mouse Input Report containing button data. */
#define INPUT_REP_REF_BUTTONS_ID    1
/* Id of reference to Mouse Input Report containing movement data. */
#define INPUT_REP_REF_MOVEMENT_ID   2
/* Id of reference to Mouse Input Report containing media player data. */
#define INPUT_REP_REF_MPLAYER_ID    3

void button_handler_ble(uint32_t button_state, uint32_t has_changed);
void button_handler_2_4g(uint32_t button_state, uint32_t has_changed);
int main_ble(void);
int main_2_4g(void);

#endif /* MAIN_H */
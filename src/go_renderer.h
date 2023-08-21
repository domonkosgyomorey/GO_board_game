#ifndef GO_RENDERER_H
#define GO_RENDERER_H

#include "go.h"

#define GO_PADDING 50
#define GO_WINDOW_SIZE 800
#define GO_BOARD_SIZE (GO_WINDOW_SIZE-2*GO_PADDING)
#define GO_SCORE_PAD 100
#define GO_TXT_POS_Y (GO_WINDOW_SIZE-GO_PADDING+25)
#define GO_TXT_POS_X 50
#define GO_TXT_PADD  250
#define GO_TXT_FNT_SIZE 24
void go_renderer_start(int w, int h);

#endif // GO_RENDERER_H

/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  DISPLAY                          1       /* callback function: ClosePanel */
#define  DISPLAY_CONTPAUSE                2       /* control type: textButton, callback function: GetCommand */
#define  DISPLAY_ABORT                    3       /* control type: command, callback function: GetCommand */
#define  DISPLAY_GRAPH_TYPE               4       /* control type: ring, callback function: Setting */
#define  DISPLAY_GRAPH_SCALE              5       /* control type: ring, callback function: Setting */
#define  DISPLAY_GRAPH_TRACE_2            6       /* control type: graph, callback function: (none) */
#define  DISPLAY_GRAPH_TRACE_1            7       /* control type: graph, callback function: (none) */
#define  DISPLAY_GRAPH_PLOT               8       /* control type: graph, callback function: (none) */
#define  DISPLAY_OSCILL_ZOOM_FIRST        9       /* control type: numeric, callback function: Setting */
#define  DISPLAY_OSCILL_ZOOM_LAST         10      /* control type: numeric, callback function: Setting */
#define  DISPLAY_ZOOM                     11      /* control type: textMsg, callback function: (none) */

#define  P                                2       /* callback function: ClosePanel */
#define  P_BKG_0_0_LAST                   2       /* control type: numeric, callback function: Setting */
#define  P_BKG_0_1_LAST                   3       /* control type: numeric, callback function: Setting */
#define  P_BKG_1_0_LAST                   4       /* control type: numeric, callback function: Setting */
#define  P_BKG_1_1_LAST                   5       /* control type: numeric, callback function: Setting */
#define  P_BKG_0_0_FIRST                  6       /* control type: numeric, callback function: Setting */
#define  P_BKG_0_1_FIRST                  7       /* control type: numeric, callback function: Setting */
#define  P_BKG_1_0_FIRST                  8       /* control type: numeric, callback function: Setting */
#define  P_BKG_1_1_FIRST                  9       /* control type: numeric, callback function: Setting */
#define  P_REF_LAST                       10      /* control type: numeric, callback function: Setting */
#define  P_GATE_0_0_LAST                  11      /* control type: numeric, callback function: Setting */
#define  P_GATE_0_1_LAST                  12      /* control type: numeric, callback function: Setting */
#define  P_GATE_1_0_LAST                  13      /* control type: numeric, callback function: Setting */
#define  P_GATE_1_1_LAST                  14      /* control type: numeric, callback function: Setting */
#define  P_WAIT_DISPLAY                   15      /* control type: numeric, callback function: Setting */
#define  P_WAIT_FILE                      16      /* control type: numeric, callback function: Setting */
#define  P_SPC_GAIN                       17      /* control type: numeric, callback function: Setting */
#define  P_CHANN_NUM                      18      /* control type: numeric, callback function: Setting */
#define  P_DET_LAMBDA                     19      /* control type: numeric, callback function: Setting */
#define  P_DET_NUM                        20      /* control type: numeric, callback function: Setting */
#define  P_REF_FIRST                      21      /* control type: numeric, callback function: Setting */
#define  P_BIOM_NUM                       22      /* control type: numeric, callback function: Setting */
#define  P_GATE_0_0_FIRST                 23      /* control type: numeric, callback function: Setting */
#define  P_GATE_0_1_FIRST                 24      /* control type: numeric, callback function: Setting */
#define  P_GATE_1_0_FIRST                 25      /* control type: numeric, callback function: Setting */
#define  P_GATE_1_1_FIRST                 26      /* control type: numeric, callback function: Setting */
#define  P_BIOM_TYPE                      27      /* control type: ring, callback function: Setting */
#define  P_TEXTMSG_4                      28      /* control type: textMsg, callback function: (none) */
#define  P_TEXTMSG_3                      29      /* control type: textMsg, callback function: (none) */
#define  P_TEXTMSG_2                      30      /* control type: textMsg, callback function: (none) */
#define  P_TEXTMSG_6                      31      /* control type: textMsg, callback function: (none) */
#define  P_TEXTMSG_5                      32      /* control type: textMsg, callback function: (none) */
#define  P_TEXTMSG_1                      33      /* control type: textMsg, callback function: (none) */
#define  P_FILE_DIR                       34      /* control type: string, callback function: Setting */
#define  P_FILE_EXT                       35      /* control type: string, callback function: Setting */
#define  P_FILE_NAME                      36      /* control type: string, callback function: Setting */
#define  P_FILE_TITLE                     37      /* control type: textMsg, callback function: (none) */

#define  TRACE                            3       /* callback function: ClosePanel */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENU                             1
#define  MENU_FILE                        2
#define  MENU_FILE_SAVE                   3       /* callback function: SaveSetting */
#define  MENU_FILE_LOAD                   4       /* callback function: LoadSetting */
#define  MENU_FILE_QUIT                   5       /* callback function: Quit */
#define  MENU_WINDOW                      6
#define  MENU_WINDOW_PARM                 7       /* callback function: ShowPanel */
#define  MENU_WINDOW_DISPLAY              8       /* callback function: ShowPanel */
#define  MENU_RUN                         9
#define  MENU_RUN_PROCESS                 10      /* callback function: Process */
#define  MENU_HELP                        11
#define  MENU_HELP_ABOUT                  12      /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ClosePanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GetCommand(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK LoadSetting(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Process(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Quit(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK SaveSetting(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Setting(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ShowPanel(int menubar, int menuItem, void *callbackData, int panel);


#ifdef __cplusplus
    }
#endif

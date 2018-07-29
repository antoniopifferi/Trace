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

#define  PARM                             2       /* callback function: ClosePanel */
#define  PARM_LOOP_HOME_1                 2       /* control type: numeric, callback function: Setting */
#define  PARM_T_FIBER                     3       /* control type: table, callback function: Setting */
#define  PARM_LOOP_HOME_2                 4       /* control type: numeric, callback function: Setting */
#define  PARM_LOOP_HOME_3                 5       /* control type: numeric, callback function: Setting */
#define  PARM_LOOP_HOME_4                 6       /* control type: numeric, callback function: Setting */
#define  PARM_LOOP_HOME_5                 7       /* control type: numeric, callback function: Setting */
#define  PARM_POWER_STEP                  8       /* control type: ring, callback function: Setting */
#define  PARM_TEXTMSG_5                   9       /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_4                   10      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_3                   11      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_2                   12      /* control type: textMsg, callback function: (none) */
#define  PARM_TITLE                       13      /* control type: textMsg, callback function: (none) */
#define  PARM_LOOP_TITLE                  14      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_1                   15      /* control type: textMsg, callback function: (none) */

#define  TRS                              3       /* callback function: ClosePanel */


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

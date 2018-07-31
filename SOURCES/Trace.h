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
#define  DISPLAY_PAUSE                    2       /* control type: textButton, callback function: GetCommand */
#define  DISPLAY_SAVE_RESULT              3       /* control type: command, callback function: SaveResult */
#define  DISPLAY_ABORT                    4       /* control type: command, callback function: GetCommand */
#define  DISPLAY_GRAPH_TYPE               5       /* control type: ring, callback function: Setting */
#define  DISPLAY_GRAPH_SCALE              6       /* control type: ring, callback function: Setting */
#define  DISPLAY_GRAPH_TRACE_2            7       /* control type: graph, callback function: (none) */
#define  DISPLAY_GRAPH_TRACE_1            8       /* control type: graph, callback function: (none) */
#define  DISPLAY_GRAPH_PLOT               9       /* control type: graph, callback function: (none) */
#define  DISPLAY_OSCILL_ZOOM_FIRST        10      /* control type: numeric, callback function: Setting */
#define  DISPLAY_OSCILL_ZOOM_LAST         11      /* control type: numeric, callback function: Setting */
#define  DISPLAY_ZOOM                     12      /* control type: textMsg, callback function: (none) */

#define  PARM                             2       /* callback function: ClosePanel */
#define  PARM_WINDOW_0_0_FIRST            2       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_0_1_FIRST            3       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_1_0_FIRST            4       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_1_1_FIRST            5       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_0_0_LAST             6       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_0_1_LAST             7       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_1_0_LAST             8       /* control type: numeric, callback function: Setting */
#define  PARM_WINDOW_1_1_LAST             9       /* control type: numeric, callback function: Setting */
#define  PARM_BKG_0_0_FIRST               10      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_0_1_FIRST               11      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_1_0_FIRST               12      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_1_1_FIRST               13      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_0_0_LAST                14      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_0_1_LAST                15      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_1_0_LAST                16      /* control type: numeric, callback function: Setting */
#define  PARM_BKG_1_1_LAST                17      /* control type: numeric, callback function: Setting */
#define  PARM_WAIT_FILE                   18      /* control type: numeric, callback function: Setting */
#define  PARM_WAIT_DISPLAY                19      /* control type: numeric, callback function: Setting */
#define  PARM_CLOCK_NUM                   20      /* control type: numeric, callback function: Setting */
#define  PARM_REF_FIRST                   21      /* control type: numeric, callback function: Setting */
#define  PARM_REF_LAST                    22      /* control type: numeric, callback function: Setting */
#define  PARM_BIOM_TYPE                   23      /* control type: ring, callback function: Setting */
#define  PARM_BIOM_NUM                    24      /* control type: numeric, callback function: Setting */
#define  PARM_DET_NUM                     25      /* control type: numeric, callback function: Setting */
#define  PARM_LAMBDA_NUM                  26      /* control type: numeric, callback function: Setting */
#define  PARM_CHANN_NUM                   27      /* control type: numeric, callback function: Setting */
#define  PARM_SPC_GAIN                    28      /* control type: numeric, callback function: Setting */
#define  PARM_FILE_DIR                    29      /* control type: string, callback function: Setting */
#define  PARM_FILE_EXT                    30      /* control type: string, callback function: Setting */
#define  PARM_FILE_NAME                   31      /* control type: string, callback function: Setting */
#define  PARM_TEXTMSG_4                   32      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_3                   33      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_2                   34      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_6                   35      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_5                   36      /* control type: textMsg, callback function: (none) */
#define  PARM_TEXTMSG_1                   37      /* control type: textMsg, callback function: (none) */
#define  PARM_FILE_TITLE                  38      /* control type: textMsg, callback function: (none) */

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
int  CVICALLBACK SaveResult(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SaveSetting(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Setting(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ShowPanel(int menubar, int menuItem, void *callbackData, int panel);


#ifdef __cplusplus
    }
#endif

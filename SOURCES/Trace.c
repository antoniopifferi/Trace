/* ######################################################################## */
/* 									   										*/
/* 		TRACE  Trace TRS Acquisitions Release 1.0  July              2018   */
/* 									   										*/
/* ######################################################################## */


/* ########################   HEADINGS   ################################## */
#pragma warning(disable : 4996) // Disable warnings about some functions in VS 2005
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>
#include "trace.h" 
#include "process.h"





void AddTab(int Class,int Type,int Panel,int Control,char *Label,int Row,int Col,void *Addr);
void CreateTable(void);

void SaveSet(char *FilePath);
void LoadSet(char *FilePath);
void InitPanel(void);
void UpdatePanel(void);
void ReadAll(void);

void DoProcess(void);


/* ########################   MAIN PROCEDURES   ########################### */

/* MAIN */

int main (int argc, char *argv[])
{   
	if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
		return -1;	/* out of memory */
	if ((hTrs = LoadPanel (0, PATH_UIR, TRS)) < 0) return -1;
	if ((hParm = LoadPanel (hTrs, PATH_UIR, PARM)) < 0) return -1;
	if ((hDisplay = LoadPanel (hTrs, PATH_UIR, DISPLAY)) < 0) return -1;
	
	//CreateTable();
	
	DisplayPanel(hTrs);
	DisplayPanel(hParm);
	InitPanel();
//	InitVariable();
	SetSleepPolicy (VAL_SLEEP_MORE);
	RunUserInterface ();
	return 0;
	}

void CVICALLBACK SaveSetting (int menuBar, int menuItem, void *callbackData, int panel){
	int c_panel;
	char fpath[MAX_PATHNAME_LEN];
	int status=FileSelectPopup (DIRSETTINGS, EXTSETTINGS, EXTSETTINGS,"SAVE FILE SETTINGS", VAL_SAVE_BUTTON, 0, 1,1, 1, fpath);
	if(status==VAL_NO_FILE_SELECTED) return;
	SaveSet(fpath);
	}

void SaveSet(char *FilePath){
//	int it;
//	char vchar;
//	int vint;
//	double vdouble;
//	char vstring[STRLEN];
//	FILE *pfile;
//	pfile = fopen (FilePath, "w");
//	for(it=0;it<T.Num;it++){
//		fprintf(pfile, "%d\t%d\t%s\t",T.Class[it],T.Type[it],T.Label[it]);
//		switch (T.Type[it]) {
//			case TCHAR:
//				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vchar);
//				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vchar);
//				fprintf(pfile,"%d\n",vchar);
//				break;
//			case TINT:
//				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vint);
//				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vint);
//				fprintf(pfile,"%d\n",vint);
//				break;
//			case TDOUBLE:
//				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vdouble);
//				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vdouble);
//				fprintf(pfile,"%lf\n",vdouble);
//				break;
//			case TSTRING:
//				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vstring);
//				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),vstring);
//				fprintf(pfile,"%s\n",vstring);
//				break;
//			}
//		}
//	fclose(pfile);
	}


void CVICALLBACK LoadSetting (int menuBar, int menuItem, void *callbackData,int panel){
	int c_panel;
	char fpath[MAX_PATHNAME_LEN];
	int status = FileSelectPopup (DIRSETTINGS, EXTSETTINGS, EXTSETTINGS,"SELECT FILE SETTINGS", VAL_LOAD_BUTTON, 0,0, 1, 0, fpath);
	if(status==VAL_NO_FILE_SELECTED) return;
	LoadSet(fpath);
	ReadAll();
//	CompleteParmS();
	UpdatePanel();
	}
	
void LoadSet(char *FilePath){
//	char line[STRLEN],label[STRLEN];
//	int type,class,it;
//	int vint;
//	double vdouble;
//	char vstring[STRLEN];
//	FILE *pfile;
//	pfile = fopen (FilePath, "r");
//	if(pfile==NULL) return;
//	while(fgets(line,STRLEN,pfile)!=NULL){
//		sscanf (line, "%d\t%d\t%s\t",&class,&type,label);
//		for(it=0;it<T.Num;it++){
//			if(strcmp(label,T.Label[it])==0)
//				switch (type) {
//					case TCHAR:
//					case TINT:
//						sscanf(line,"%d%d%s%d",&class,&type,label,&vint);
//						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vint);
//						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vint);
//						break;
//					case TDOUBLE:
//						sscanf(line,"%d%d%s%lf",&class,&type,label,&vdouble);
//						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vdouble);
//						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vdouble);
//						break;
//					case TSTRING:
//						Scan(line,"%d%d%s%s",&class,&type,label,vstring);
//						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vstring);
//						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vstring);
//						break;
//					}
//			}
//		} 
//	fclose(pfile);
	}
//


void CVICALLBACK Print(int menuBar, int menuItem, void *callbackData,
		int panel)
{
	PrintPanel (panel, "", 1, VAL_FULL_PANEL, 1);
}


void CVICALLBACK Quit (int menuBar, int menuItem, void *callbackData,int panel){  
	SaveSet(FILESET);
	QuitUserInterface (0);
	}


void CVICALLBACK ShowPanel (int menuBar, int menuItem, void *callbackData, int panel){
	switch (menuItem) {
		case MENU_WINDOW_PARM:    DisplayPanel (hParm); break;
		case MENU_WINDOW_DISPLAY: DisplayPanel (hDisplay); break;
		}
	}


void CVICALLBACK Process(int menuBar, int menuItem, void *callbackData,int panel)
{
	DoProcess();
}


void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	MessagePopup ("ABOUT TRACE", MESSAGE_ABOUT); 
}


void InitPanel(void){
	hPanel[PARM]=hParm;
	hPanel[DISPLAY]=hDisplay;
//	LoadSet(FILESET);
//	ReadAll();
//	CompleteParmS();
//	UpdatePanel();
	}
	

void ReadAll(void){
//	int it;
//	for(it=0;it<T.Num;it++)
//		if(T.Class[it]==CE)
//			GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],T.Addr[it]);
//		else
//			GetTableCellVal(hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),T.Addr[it]);
	}				

int CVICALLBACK Setting (int panel, int control, int event,void *callbackData, int eventData1, int eventData2){
//	int ip,it,rowT,colT,root;
//	int panelID;
//	int row=eventData1;
//	int col=eventData2;
//	if(event!=EVENT_COMMIT) return 0;
//	for(ip=0;ip<MAX_PANEL;ip++) if(hPanel[ip]==panel) panelID=ip;
//	for(it=0;it<T.Num;it++)
//		if((T.Panel[it]==panelID)&&(T.Ctrl[it]==control)){
//			if(T.Class[it]==CE)
//				GetCtrlVal(panel,control,T.Addr[it]);
//			else{
//				root = FindPattern(T.Label[it],0,-1,"_",1,0);
//				sscanf(T.Label[it]+root+1,"%d_%d",&rowT,&colT);
//				if((row==rowT)&&(col==colT))
//					GetTableCellVal(panel,control,MakePoint(col,row),T.Addr[it]);
//				}
//			}
//	if(P.Info.Appl!=APPL_SPECTRA) CompleteParmS();
//	if(P.Info.Appl!=APPL_SPECTRA) UpdatePanel();
	return 0;
	}


void UpdatePanel(void){
//	char strtime[STRLEN];
//	int it;
//	char *pchar;
//	int *pint;
//	double *pdouble;
//	for(it=0;it<T.Num;it++)
//		switch (T.Type[it]) {	   
//			case TCHAR:
//				pchar=T.Addr[it];
//				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pchar);
//				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pchar);
//				break;
//			case TINT:
//				pint=T.Addr[it];
//				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pint);
//				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pint);
//				break;
//			case TDOUBLE:
//				pdouble=T.Addr[it];
//				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pdouble);
//				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pdouble);
//				break;
//			case TSTRING:
//				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,T.Addr[it]);
//				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,T.Addr[it]);
//				break;
//			}
//	ProcessDrawEvents ();
	}

int CVICALLBACK ClosePanel (int panel, int event, void *callbackdata, int eventdata1, int eventdata2) {
	if(event!=EVENT_CLOSE) return(0);
    if(panel==hTrs) {SaveSet(FILESET);QuitUserInterface (0); return(0);}
    HidePanel(panel);
    return(0);
    }

// TABLE
void AddTab(int Class,int Type,int Panel,int Control,char *Label,int Row,int Col,void *Addr){
	T.Class[T.Num]=Class;
	T.Type[T.Num]=Type;
	T.Panel[T.Num]=Panel;
	T.Ctrl[T.Num]=Control;
	T.Row[T.Num]=Row;
	T.Col[T.Num]=Col;
	T.Addr[T.Num]=Addr;
	if(Row==0) sprintf(T.Label[T.Num],"%s",Label);
	else if(Col==0) sprintf(T.Label[T.Num],"%s_%d",Label,Row);
	else sprintf(T.Label[T.Num],"%s_%d_%d",Label,Row,Col);
	T.Num++;
	}


void CreateTable(void){
	int il,is,it,ip,id,ic,ib,iff,ir,ips;

	T.Num=0;

	AddTab(CE,TSTRING,PARM,PARM_FILE_DIR,"FileDir",0,0,P.File.Dir);
	AddTab(CE,TSTRING,PARM,PARM_FILE_EXT,"FileExt",0,0,P.File.Ext); 
	AddTab(CE,TSTRING,PARM,PARM_FILE_NAME,"FileName",0,0,P.File.Name); 
	
	AddTab(CE,TDOUBLE,PARM,PARM_WAIT_FILE,"WaitFile",0,0,P.Wait.File);
	AddTab(CE,TDOUBLE,PARM,PARM_WAIT_DISPLAY,"WaitDisplay",0,0,P.Wait.Display);
	
	AddTab(CE,TINT,PARM,PARM_CHANN_NUM,"ChannNum",0,0,&P.Chann.Num);

	AddTab(CE,TINT,PARM,PARM_DET_NUM,"DetNum",0,0,&P.Det.Num);
	
	AddTab(CE,TINT,PARM,PARM_BIOM_NUM,"BiomNum",0,0,&P.Biom.Num);
	AddTab(CE,TINT,PARM,PARM_BIOM_TYPE,"BiomType",0,0,&P.Biom.Type);
	
	AddTab(CE,TINT,PARM,PARM_CHANN_NUM,"ChannNum",0,0,&P.Chann.Num);

	AddTab(CE,TINT,PARM,PARM_CLOCK_NUM,"ClockNum",0,0,&P.Clock.Num);

	AddTab(CE,TDOUBLE,PARM,PARM_SPC_GAIN,"SpcGain",0,0,P.Spc.Gain);

	AddTab(CE,TINT,PARM,PARM_REF_FIRST,"RefFirst",0,0,&P.Ref.First);
	AddTab(CE,TINT,PARM,PARM_REF_LAST,"RefLast",0,0,&P.Ref.Last);

	AddTab(CE,TINT,PARM,PARM_GATE_0_0_FIRST,"Gate00First",0,0,&P.Gate[0][0].First);
	AddTab(CE,TINT,PARM,PARM_GATE_0_1_FIRST,"Gate01First",0,0,&P.Gate[0][1].First);
	AddTab(CE,TINT,PARM,PARM_GATE_1_0_FIRST,"Gate10First",0,0,&P.Gate[1][0].First);
	AddTab(CE,TINT,PARM,PARM_GATE_1_1_FIRST,"Gate11First",0,0,&P.Gate[1][1].First);

	AddTab(CE,TINT,PARM,PARM_GATE_0_0_LAST,"Gate00Last",0,0,&P.Gate[0][0].Last);
	AddTab(CE,TINT,PARM,PARM_GATE_0_1_LAST,"Gate01Last",0,0,&P.Gate[0][1].Last);
	AddTab(CE,TINT,PARM,PARM_GATE_1_0_LAST,"Gate10Last",0,0,&P.Gate[1][0].Last);
	AddTab(CE,TINT,PARM,PARM_GATE_1_1_LAST,"Gate11Last",0,0,&P.Gate[1][1].Last);

	AddTab(CE,TINT,PARM,PARM_BKG_0_0_FIRST,"Bkg00First",0,0,&P.Bkg[0][0].First);
	AddTab(CE,TINT,PARM,PARM_BKG_0_1_FIRST,"Bkg01First",0,0,&P.Bkg[0][1].First);
	AddTab(CE,TINT,PARM,PARM_BKG_1_0_FIRST,"Bkg10First",0,0,&P.Bkg[1][0].First);
	AddTab(CE,TINT,PARM,PARM_BKG_1_1_FIRST,"Bkg11First",0,0,&P.Bkg[1][1].First);

	AddTab(CE,TINT,PARM,PARM_BKG_0_0_LAST,"Bkg00Last",0,0,&P.Bkg[0][0].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_0_1_LAST,"Bkg01Last",0,0,&P.Bkg[0][1].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_1_0_LAST,"Bkg10Last",0,0,&P.Bkg[1][0].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_1_1_LAST,"Bkg11Last",0,0,&P.Bkg[1][1].Last);

	P.Eps[0][0]=6.770E-04;  // cm-1/uM
	P.Eps[0][1]=2.243E-03;  // cm-1/uM
	P.Eps[1][0]=6.436E-03;  // cm-1/uM
	P.Eps[1][1]=1.596E-03;  // cm-1/uM
	

//	
//	// 9*5
//	for(il=0;il<MAX_LOOP;il++){
//		AddTab(CE,TINT,PARM,PARM_LOOP_HOME_1+il,"LoopHome",il+1,0,&P.Loop[il].Home);
//		AddTab(CE,TINT,PARM,PARM_LOOP_FIRST_1+il,"LoopFirst",il+1,0,&P.Loop[il].First);
//		AddTab(CE,TINT,PARM,PARM_LOOP_LAST_1+il,"LoopLast",il+1,0,&P.Loop[il].Last); 
//		AddTab(CE,TINT,PARM,PARM_LOOP_DELTA_1+il,"LoopDelta",il+1,0,&P.Loop[il].Delta); 
//		AddTab(CE,TINT,PARM,PARM_LOOP_NUM_1+il,"LoopNum",il+1,0,&P.Loop[il].Num); 
//		AddTab(CE,TSTRING,PARM,PARM_LOOP_FNAME_1+il,"LoopFName",il+1,0,P.Loop[il].FName); 
//		AddTab(CE,TCHAR,PARM,PARM_LOOP_BREAK_1+il,"LoopBreak",il+1,0,&P.Loop[il].Break); 
//		AddTab(CE,TCHAR,PARM,PARM_LOOP_INVERT_1+il,"LoopInvert",il+1,0,&P.Loop[il].Invert);
//		AddTab(CE,TCHAR,PARM,PARM_LOOP_CONT_1+il,"LoopCont",il+1,0,&P.Loop[il].Cont);
//		}
//		
//	// 3	
//	AddTab(CE,TDOUBLE,PARM,PARM_OSCILL_TIME,"SpcTimeO",0,0,&P.Spc.TimeO);
//	AddTab(CE,TCHAR,PARM,PARM_TIME_BASE,"TimeBase",0,0,&P.Time.Time);
//	AddTab(CE,TCHAR,PARM,PARM_READ_UIR,"ReadUIR",0,0,&P.Command.ReadUIR);
//	
//	// 17*11
//	for(is=0;is<MAX_STEP;is++){
//		AddTab(CE,TCHAR,STEP,STEP_TYPE_1+is,"StepType",is+1,0,&P.Step[is].Type);
//		AddTab(CE,TCHAR,STEP,STEP_COM_1+is,"StepCom",is+1,0,&P.Step[is].Com);
//		AddTab(CE,TCHAR,STEP,STEP_AXIS_1+is,"StepAxis",is+1,0,&P.Step[is].Axis);
//		AddTab(CE,TCHAR,STEP,STEP_MODE_1+is,"StepMode",is+1,0,&P.Step[is].Mode);
//		AddTab(CE,TCHAR,STEP,STEP_SIGN_1+is,"StepSign",is+1,0,&P.Step[is].Sign);
//		AddTab(CE,TCHAR,STEP,STEP_LOOP_1+is,"StepLoop",is+1,0,&P.Step[is].Loop);
//		AddTab(CE,TCHAR,STEP,STEP_HOLD_1+is,"StepHold",is+1,0,&P.Step[is].Hold);
//		AddTab(CE,TCHAR,STEP,STEP_LCD_1+is,"StepLcd",is+1,0,&P.Step[is].Lcd);
//		AddTab(CE,TSTRING,STEP,STEP_FNAME_1+is,"StepFName",is+1,0,P.Step[is].FName);
//		AddTab(CE,TINT,STEP,STEP_MIN_1+is,"StepMin",is+1,0,&P.Step[is].Min);
//		AddTab(CE,TINT,STEP,STEP_MAX_1+is,"StepMax",is+1,0,&P.Step[is].Max);
//		AddTab(CE,TDOUBLE,STEP,STEP_FREQMIN_1+is,"StepFreqMin",is+1,0,&P.Step[is].FreqMin);
//		AddTab(CE,TDOUBLE,STEP,STEP_FREQMAX_1+is,"StepFreqMax",is+1,0,&P.Step[is].FreqMax);
//		AddTab(CE,TDOUBLE,STEP,STEP_FREQ_1+is,"StepFreq",is+1,0,&P.Step[is].Freq);
//		AddTab(CE,TDOUBLE,STEP,STEP_FREQDELTA_1+is,"StepFreqDelta",is+1,0,&P.Step[is].FreqDelta);
//		AddTab(CE,TDOUBLE,STEP,STEP_FACTOR_1+is,"StepFactor",is+1,0,&P.Step[is].Factor);
//		AddTab(CE,TCHAR,STEP,STEP_SORT_1+is,"StepSort",is+1,0,&P.Step[is].Sort);
//		}
//  
//  	// 9*10
//	for(is=0;is<MAX_SWITCH;is++){
//		AddTab(CE,TCHAR,SWITCH,SWITCH_SWITCH_1+is,"SwitchSwitch",is+1,0,&P.Switch[is].Switch);   
//		AddTab(CE,TCHAR,SWITCH,SWITCH_DEVICE_1+is,"SwitchDevice",is+1,0,&P.Switch[is].Device);
//		AddTab(CE,TCHAR,SWITCH,SWITCH_TYPE_1+is,"SwitchType",is+1,0,&P.Switch[is].Type);
//		AddTab(CE,TINT,SWITCH,SWITCH_BOARD_1+is,"SwitchBoard",is+1,0,&P.Switch[is].Board);
//		AddTab(CE,TSTRING,SWITCH,SWITCH_PORT_1+is,"SwitchPort",is+1,0,&P.Switch[is].Port);
//		AddTab(CE,TCHAR,SWITCH,SWITCH_LINE0_1+is,"SwitchLine0",is+1,0,&P.Switch[is].Line0);
//		AddTab(CE,TCHAR,SWITCH,SWITCH_MODE_1+is,"SwitchMode",is+1,0,&P.Switch[is].Mode);
//		AddTab(CE,TCHAR,SWITCH,SWITCH_LOOP_1+is,"SwitchLoop",is+1,0,&P.Switch[is].Loop);
//		AddTab(CE,TSTRING,SWITCH,SWITCH_FNAME_1+is,"SwitchFName",is+1,0,P.Switch[is].FName);
//		}
//
//
//	// 16*2+1
//	AddTab(CE,TCHAR,DISPLAY,DISPLAY_ROI_WINDOW,"RoiWindow",0,0,&P.Roi.Window);
//	for(ip=0;ip<MAX_PLOT;ip++){
//		AddTab(CE,TINT,DISPLAY,DISPLAY_PLOT_PLOT_1+ip,"PlotPlot",ip+1,0,&P.Plot.Plot[ip]);
//		AddTab(CE,TINT,DISPLAY,DISPLAY_PLOT_PAGE_1+ip,"PlotPageU",ip+1,0,&P.Plot.PageU[ip]);
//		}
//	
//	// 4
//	AddTab(CE,TCHAR,DISPLAY,DISPLAY_GRAPH_TYPE,"GraphType",0,0,&P.Graph.Type);
//	AddTab(CE,TCHAR,DISPLAY,DISPLAY_GRAPH_TYPE,"GraphType",0,0,&P.Graph.Scale);
//	AddTab(CE,TINT,DISPLAY,DISPLAY_OSCILL_ZOOM_FIRST,"OscillZoomFirst",0,0,&P.Oscill.Zoom.First);
//	AddTab(CE,TINT,DISPLAY,DISPLAY_OSCILL_ZOOM_LAST,"OscillZoomLast",0,0,&P.Oscill.Zoom.Last);
//
//	// 1
//	AddTab(CE,TCHAR,LAYOUT,LAYOUT_ORDER,"LayoutOrder",0,0,&P.Layout.Order);	
//	
//
//	// TABLES  438 = 1+6+96+64+48+48+144+18+9+1+3
//
//	// 1
//	AddTab(CT,TCHAR,DISPLAY,DISPLAY_T_VALUE,"ValueRoi",1,COL_VALUE_ROI,&P.Value.Roi);
//	
//	// 2*3
//	for(ir=0;ir<MAX_ROW_OSCILL;ir++){
//		AddTab(CT,TINT,DISPLAY,DISPLAY_T_OSCILL,"OscillFirst",ir+1,COL_OSCILL_FIRST,&P.Oscill.First[ir]);
//		AddTab(CT,TINT,DISPLAY,DISPLAY_T_OSCILL,"OscillLast",ir+1,COL_OSCILL_LAST,&P.Oscill.Last[ir]);
//		AddTab(CT,TDOUBLE,DISPLAY,DISPLAY_T_OSCILL,"OscillFract",ir+1,COL_OSCILL_FRACT,&P.Oscill.Fract[ir]);
//		}
//
//	// 32*3
//	for(ir=0;ir<MAX_ROW_ROI;ir++){
//		AddTab(CT,TINT,DISPLAY,DISPLAY_T_ROI,"RoiPage",ir+1,COL_ROI_PAGE,&P.Roi.Page[ir]);
//		AddTab(CT,TINT,DISPLAY,DISPLAY_T_ROI,"RoiFirst",ir+1,COL_ROI_FIRST,&P.Roi.First[ir]);
//		AddTab(CT,TINT,DISPLAY,DISPLAY_T_ROI,"RoiLast",ir+1,COL_ROI_LAST,&P.Roi.Last[ir]);
//		}
//		
//	// 16*4	
//	for(ip=0;ip<MAX_ROW_PROT;ip++){
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_PROT,"ProtSource",ip+1,COL_PROT_SOURCE,&P.TProt.Source[ip]);
//		AddTab(CT,TSTRING,LAYOUT,LAYOUT_T_PROT,"ProtFibers",ip+1,COL_PROT_FIBERS,P.TProt.Fibers[ip]);
//		AddTab(CT,TINT,LAYOUT,LAYOUT_T_PROT,"ProtAcqStart",ip+1,COL_PROT_ACQSTART,&P.TProt.AcqStart[ip]);
//		AddTab(CT,TINT,LAYOUT,LAYOUT_T_PROT,"ProtAcqStop",ip+1,COL_PROT_ACQSTOP,&P.TProt.AcqStop[ip]);
//		}
//		
//	// 16*3	
//	for(iff=0;iff<MAX_ROW_FIBER;iff++){
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_FIBER,"FiberBoard",iff+1,COL_FIBER_BOARD,&P.TFiber.Board[iff]);
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_FIBER,"FiberDet",iff+1,COL_FIBER_DET,&P.TFiber.Det[iff]);
//		AddTab(CT,TSTRING,LAYOUT,LAYOUT_T_FIBER,"FiberFibers",iff+1,COL_FIBER_FIBERS,P.TFiber.Fibers[iff]);
//		}
//		
//	// 16*3	
//	for(is=0;is<MAX_ROW_SOURCE;is++){
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_SOURCE,"SourceSource",is+1,COL_SOURCE_SOURCE,&P.TSource.Source[is]);
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_SOURCE,"SourceSwitch",is+1,COL_SOURCE_SWITCH,&P.TSource.Switch[is]);
//		AddTab(CT,TCHAR,LAYOUT,LAYOUT_T_SOURCE,"SourceChann",is+1,COL_SOURCE_CHANN,&P.TSource.Chann[is]);
//		}	
//	
//	// 18*8
//	for(ips=0;ips<MAX_ROW_PRES_BLOCK;ips++){
//		AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockBlock",ips+1,COL_BLOCK_DEF_BLOCK,&P.TBlock.Num[ips]);
//		AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockType",ips+1,COL_BLOCK_DEF_TYPE,&P.TBlock.Type[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockStartFrame",ips+1,COL_BLOCK_DEF_START_FRAME,&P.TBlock.StartFrame[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockStopFrame",ips+1,COL_BLOCK_DEF_STOP_FRAME,&P.TBlock.StopFrame[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockParam2",ips+1,COL_BLOCK_DEF_PARAM2,&P.TBlock.Param2[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_DEF,"BlockParam3",ips+1,COL_BLOCK_DEF_PARAM3,&P.TBlock.Param3[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_SEQUENCE,"SequenceBlock",ips+1,COL_BLOCK_SEQUENCE_BLOCK,&P.TSequence.BlockUsed[ips]);
//    	AddTab(CT,TINT,PRESENT,PRESENT_TBLOCK_SEQUENCE,"SequenceBlock",ips+1,COL_BLOCK_SEQUENCE_REPEAT,&P.TSequence.Repeat[ips]);
//    	}
//    
//    // 18
//    for(ips=0;ips<MAX_ROW_PRES_BLOCK;ips++){   
//    	AddTab(CT,TSTRING,PRESENT,PRESENT_TBLOCK_DEF,"BlockParam1",ips+1,COL_BLOCK_DEF_PARAM1,&P.TBlock.Param1[ips]);
//		}    	
//    
//    // 6+5
//    for(ips=0;ips<MAX_ROW_PRES_LOOP;ips++){
//    	AddTab(CT,TINT,PRESENT,PRESENT_TLOOP_PARTITION,"PartitionLoop",ips+1,1,&P.TPartition.LoopFactor[ips]); 
//		}	
//	AddTab(CE,TSTRING,PRESENT,PRESENT_FSTIMULI,"PresentFileStimuli",0,0,&P.Presentation.FStimuliName);
//	AddTab(CE,TSTRING,PRESENT,PRESENT_DSTIMULI,"PresentDirStimuli",0,0,&P.Presentation.FStimuliDir);
//	AddTab(CE,TSTRING,PRESENT,PRESENT_FPRESENT,"PresentFileInitPresentation",0,0,&P.Presentation.FInitPresentationName);
//	AddTab(CE,TSTRING,PRESENT,PRESENT_DPRESENT,"PresentDirInitPresentation",0,0,&P.Presentation.FInitPresentationDir);
//	AddTab(CE,TINT,PRESENT,PRESENT_SHUFFLE,"SequenceShuffle",0,0,&P.TSequence.Shuffle);
//	AddTab(CE,TINT,PRESENT,PRESENT_ALIGN,"LoopPartitionAlign",0,0,&P.TPartition.Align);
//		
//   	// 1																						//ALE
//   	AddTab(CE,TSTRING,GEOMETRY,GEOMETRY_GEO_FNAME,"GeomFname",0,0,&P.Layout.FGeometry);			//ALE 
//
//	//3
//	AddTab(CE,TINT,MOXY,MOXY_DISP_DIV,"DisplayDivisor",0,0,&P.Moxy.DisplayDivisor);
//	AddTab(CE,TINT,MOXY,MOXY_PRES_EDGE,"PresentationRise",0,0,&P.Moxy.PresentationRise);
//	AddTab(CE,TINT,MOXY,MOXY_EXT_TRIG,"ExternalTrigger",0,0,&P.Moxy.ExternalTrigger);
//	
//	//3
//	AddTab(CE,TINT,NIRS,NIRS_FREQ,"NirsFreq",0,0,&P.Spc.Nirs[0].Freq);
//	AddTab(CE,TINT,NIRS,NIRS_TIME,"NirsTime",0,0,&P.Spc.Nirs[0].UirTime);
//	AddTab(CE,TINT,NIRS,NIRS_LAMBDA,"NirsLambda",0,0,&P.Spc.Nirs[0].Lambda);
//	
//	//1
//	AddTab(CE,TINT,LUCA,LUCA_FREQ,"LucaFreq",0,0,&P.Spc.Luca[0].Freq);
//
//	for(ic=0;ic<T.Num;ic++) T.Dimmed[ic]=FALSE;
	}


/* ######################################################################## */
/* 									   										*/
/* 		TRACE  Trace TRS Acquisitions Release 1.0  July              2018   */
/* 									   										*/
/* ######################################################################## */


/* ########################   HEADINGS   ################################## */
#pragma warning(disable : 4996) // Disable warnings about some functions in VS 2005
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <formatio.h>
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
void DoSaveResult(char *FilePath);


/* ########################   MAIN PROCEDURES   ########################### */

/* MAIN */

int main (int argc, char *argv[]){   
	if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
		return -1;	/* out of memory */
	if ((hTrace = LoadPanel (0, PATH_UIR, TRACE)) < 0) return -1;
	if ((hParm = LoadPanel (hTrace, PATH_UIR, PARM)) < 0) return -1;
	if ((hDisplay = LoadPanel (hTrace, PATH_UIR, DISPLAY)) < 0) return -1;
	
	CreateTable();
	
	DisplayPanel(hTrace);
	DisplayPanel(hParm);
	InitPanel();
	SetSleepPolicy (VAL_SLEEP_MORE);
	RunUserInterface ();
	return 0;
	}

int  CVICALLBACK SaveResult(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	int c_panel;
	char fpath[MAX_PATHNAME_LEN];
	int status = FileSelectPopup (DIR_RESULT, EXT_RESULT, EXT_RESULT, "SAVE FILE RESULTS", VAL_SAVE_BUTTON, 0, 1, 1, 1,fpath);
	if(status==VAL_NO_FILE_SELECTED) return;
	DoSaveResult(fpath);
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
	int it;
	char vchar;
	int vint;
	double vdouble;
	char vstring[STRLEN];
	FILE *pfile;
	pfile = fopen (FilePath, "w");
	for(it=0;it<T.Num;it++){
		fprintf(pfile, "%d\t%d\t%s\t",T.Class[it],T.Type[it],T.Label[it]);
		switch (T.Type[it]) {
			case TCHAR:
				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vchar);
				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vchar);
				fprintf(pfile,"%d\n",vchar);
				break;
			case TINT:
				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vint);
				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vint);
				fprintf(pfile,"%d\n",vint);
				break;
			case TDOUBLE:
				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],&vdouble);
				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),&vdouble);
				fprintf(pfile,"%lf\n",vdouble);
				break;
			case TSTRING:
				if(T.Class[it]==CE) GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vstring);
				else GetTableCellVal (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),vstring);
				fprintf(pfile,"%s\n",vstring);
				break;
			}
		}
	fclose(pfile);
	}


void CVICALLBACK LoadSetting (int menuBar, int menuItem, void *callbackData,int panel){
	int c_panel;
	char fpath[MAX_PATHNAME_LEN];
	int status = FileSelectPopup (DIRSETTINGS, EXTSETTINGS, EXTSETTINGS,"SELECT FILE SETTINGS", VAL_LOAD_BUTTON, 0,0, 1, 0, fpath);
	if(status==VAL_NO_FILE_SELECTED) return;
	LoadSet(fpath);
	ReadAll();
	CompleteParm();
	UpdatePanel();
	}
	
void LoadSet(char *FilePath){
	char line[STRLEN],label[STRLEN];
	int type,class,it;
	int vint;
	double vdouble;
	char vstring[STRLEN];
	FILE *pfile;
	pfile = fopen (FilePath, "r");
	if(pfile==NULL) return;
	while(fgets(line,STRLEN,pfile)!=NULL){
		sscanf (line, "%d\t%d\t%s\t",&class,&type,label);
		for(it=0;it<T.Num;it++){
			if(strcmp(label,T.Label[it])==0)
				switch (type) {
					case TCHAR:
					case TINT:
						sscanf(line,"%d%d%s%d",&class,&type,label,&vint);
						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vint);
						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vint);
						break;
					case TDOUBLE:
						sscanf(line,"%d%d%s%lf",&class,&type,label,&vdouble);
						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vdouble);
						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vdouble);
						break;
					case TSTRING:
						Scan(line,"%d%d%s%s",&class,&type,label,vstring);
						if(T.Class[it]==CE) SetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],vstring);
						else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,vstring);
						break;
					}
			}
		} 
	fclose(pfile);
	}



void CVICALLBACK Print(int menuBar, int menuItem, void *callbackData,
		int panel){
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


void CVICALLBACK Process(int menuBar, int menuItem, void *callbackData,int panel){
	CmtThreadFunctionID functionId;
	CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, DoProcess, NULL, &functionId);
	}


void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
		int panel){
	MessagePopup ("ABOUT TRACE", MESSAGE_ABOUT); 
	}


void InitPanel(void){
	hPanel[PARM]=hParm;
	hPanel[DISPLAY]=hDisplay;
	LoadSet(FILESET);
	ReadAll();
	CompleteParm();
	UpdatePanel();
	}
	

void ReadAll(void){
	int it;
	for(it=0;it<T.Num;it++)
		if(T.Class[it]==CE)
			GetCtrlVal(hPanel[T.Panel[it]],T.Ctrl[it],T.Addr[it]);
		else
			GetTableCellVal(hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),T.Addr[it]);
	}				

int CVICALLBACK Setting (int panel, int control, int event,void *callbackData, int eventData1, int eventData2){
	int ip,it,rowT,colT,root;
	int panelID;
	int row=eventData1;
	int col=eventData2;
	if(event!=EVENT_COMMIT) return 0;
	for(ip=0;ip<MAX_PANEL;ip++) if(hPanel[ip]==panel) panelID=ip;
	for(it=0;it<T.Num;it++)
		if((T.Panel[it]==panelID)&&(T.Ctrl[it]==control)){
			if(T.Class[it]==CE)
				GetCtrlVal(panel,control,T.Addr[it]);
			else{
				root = FindPattern(T.Label[it],0,-1,"_",1,0);
				sscanf(T.Label[it]+root+1,"%d_%d",&rowT,&colT);
				if((row==rowT)&&(col==colT))
					GetTableCellVal(panel,control,MakePoint(col,row),T.Addr[it]);
				}
			}
	return 0;
	}


void UpdatePanel(void){
	char strtime[STRLEN];
	int it;
	char *pchar;
	int *pint;
	double *pdouble;
	for(it=0;it<T.Num;it++)
		switch (T.Type[it]) {	   
			case TCHAR:
				pchar=T.Addr[it];
				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pchar);
				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pchar);
				break;
			case TINT:
				pint=T.Addr[it];
				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pint);
				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pint);
				break;
			case TDOUBLE:
				pdouble=T.Addr[it];
				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,*pdouble);
				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,*pdouble);
				break;
			case TSTRING:
				if(T.Class[it]==CE) SetCtrlAttribute (hPanel[T.Panel[it]],T.Ctrl[it],ATTR_CTRL_VAL,T.Addr[it]);
				else SetTableCellAttribute (hPanel[T.Panel[it]],T.Ctrl[it],MakePoint(T.Col[it],T.Row[it]),ATTR_CTRL_VAL,T.Addr[it]);
				break;
			}
	ProcessDrawEvents ();
	}

int CVICALLBACK ClosePanel (int panel, int event, void *callbackdata, int eventdata1, int eventdata2) {
	if(event!=EVENT_CLOSE) return(0);
    if(panel==hTrace) {SaveSet(FILESET);QuitUserInterface (0); return(0);}
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
	int ic;

	T.Num=0;

	// 8
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_0_0_FIRST,"Window00First",0,0,&P.Window[0][0].First);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_0_1_FIRST,"Window01First",0,0,&P.Window[0][1].First);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_1_0_FIRST,"Window10First",0,0,&P.Window[1][0].First);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_1_1_FIRST,"Window11First",0,0,&P.Window[1][1].First);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_0_0_LAST,"Window00Last",0,0,&P.Window[0][0].Last);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_0_1_LAST,"Window01Last",0,0,&P.Window[0][1].Last);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_1_0_LAST,"Window10Last",0,0,&P.Window[1][0].Last);
	AddTab(CE,TDOUBLE,PARM,PARM_WINDOW_1_1_LAST,"Window11Last",0,0,&P.Window[1][1].Last);

	// 8
	AddTab(CE,TINT,PARM,PARM_BKG_0_0_FIRST,"Bkg00First",0,0,&P.Bkg[0][0].First);
	AddTab(CE,TINT,PARM,PARM_BKG_0_1_FIRST,"Bkg01First",0,0,&P.Bkg[0][1].First);
	AddTab(CE,TINT,PARM,PARM_BKG_1_0_FIRST,"Bkg10First",0,0,&P.Bkg[1][0].First);
	AddTab(CE,TINT,PARM,PARM_BKG_1_1_FIRST,"Bkg11First",0,0,&P.Bkg[1][1].First);
	AddTab(CE,TINT,PARM,PARM_BKG_0_0_LAST,"Bkg00Last",0,0,&P.Bkg[0][0].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_0_1_LAST,"Bkg01Last",0,0,&P.Bkg[0][1].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_1_0_LAST,"Bkg10Last",0,0,&P.Bkg[1][0].Last);
	AddTab(CE,TINT,PARM,PARM_BKG_1_1_LAST,"Bkg11Last",0,0,&P.Bkg[1][1].Last);

	//2
	AddTab(CE,TDOUBLE,PARM,PARM_WAIT_FILE,"WaitFile",0,0,&P.Wait.File);
	AddTab(CE,TDOUBLE,PARM,PARM_WAIT_DISPLAY,"WaitDisplay",0,0,&P.Wait.Display);
	
	// 3
	AddTab(CE,TINT,PARM,PARM_CLOCK_NUM,"ClockNum",0,0,&P.Clock.Num);
	AddTab(CE,TINT,PARM,PARM_REF_FIRST,"RefFirst",0,0,&P.Ref.First);
	AddTab(CE,TINT,PARM,PARM_REF_LAST,"RefLast",0,0,&P.Ref.Last);

	// 6
	AddTab(CE,TINT,PARM,PARM_BIOM_TYPE,"BiomType",0,0,&P.Biom.Type);
	AddTab(CE,TINT,PARM,PARM_BIOM_NUM,"BiomNum",0,0,&P.Biom.Num);
	AddTab(CE,TINT,PARM,PARM_DET_NUM,"DetNum",0,0,&P.Det.Num);
	AddTab(CE,TINT,PARM,PARM_LAMBDA_NUM,"LambdaNum",0,0,&P.Lambda.Num);
	AddTab(CE,TINT,PARM,PARM_CHANN_NUM,"ChannNum",0,0,&P.Chann.Num);
	AddTab(CE,TDOUBLE,PARM,PARM_SPC_GAIN,"SpcGain",0,0,&P.Spc.Gain);

	// 3
	AddTab(CE,TSTRING,PARM,PARM_FILE_DIR,"FileDir",0,0,P.File.Dir);
	AddTab(CE,TSTRING,PARM,PARM_FILE_EXT,"FileExt",0,0,P.File.Ext); 
	AddTab(CE,TSTRING,PARM,PARM_FILE_NAME,"FileName",0,0,P.File.Name); 
	
	for(ic=0;ic<T.Num;ic++) T.Dimmed[ic]=FALSE;
	}


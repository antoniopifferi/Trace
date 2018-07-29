/* ######################################################################## */
/* 									   										*/
/* 		TRACE  Trace TRS Acquisitions Release 1.0  July              2018   */
/* 									   										*/
/* ######################################################################## */


/* ########################   NOTES   ################################## */


/* ########################   HELP   ################################## */

/* ########################   HEADINGS   ################################## */

#pragma warning(disable : 4996) // Disable warnings about some functions in VS 2005
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <utility.h>
#include <ansi_c.h>
#include "process.h"   
#include "trace.h" 


/* ########################   PROCESS PROCEDURES   ########################### */

/* UIR FUNCTIONS */

// Read CONTINUE/PAUSE or ABORT button
int CVICALLBACK GetCommand(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	if(event!=EVENT_COMMIT) return 0;
	switch (control){
		case DISPLAY_CONTPAUSE:GetCtrlVal (hDisplay, control, &P.Command.Continue);break;
		case DISPLAY_ABORT:P.Command.Abort=TRUE;break;
		}
	return 0;
	}

// Replace UIR
void SimulateUir(void){
	
	P.Command.Abort=FALSE;
	P.Command.Continue=TRUE;
	
	strcpy(P.File.Dir,"D:\\Beta\\Programs\\Trace\\Data");
	strcpy(P.File.Name,"DENv0096");
	strcpy(P.File.Ext,"DAT");
	
	P.Wait.File=0.1;
	P.Wait.Display=0.2;
	
	P.Chann.Num=4096;
	
	P.Det.Num=2;
	
	P.Lambda.Num=2;
	
	P.Biom.Num=2;
	
	P.Bkg[0][0].First=2400;
	P.Bkg[0][1].First=2400;
	P.Bkg[1][0].First=2400;
	P.Bkg[1][1].First=2400;
	P.Bkg[0][0].Last=2500;
	P.Bkg[0][1].Last=2500;
	P.Bkg[1][0].Last=2500;
	P.Bkg[1][1].Last=2500;
	
	P.Gate[0][0].First=1000;
	P.Gate[0][1].First=1000;
	P.Gate[1][0].First=2000;
	P.Gate[1][1].First=2000;
	P.Gate[0][0].Last=1000;
	P.Gate[0][1].Last=1000;
	P.Gate[1][0].Last=2000;
	P.Gate[1][1].Last=2000;

	P.Clock.Num=991;
	
	P.Ref.First=0;
	P.Ref.Last=80;
	
	P.Eps[0][0]=6.770E-04;  // cm-1/uM
	P.Eps[0][1]=2.243E-03;  // cm-1/uM
	P.Eps[1][0]=6.436E-03;  // cm-1/uM
	P.Eps[1][1]=1.596E-03;  // cm-1/uM
	
	P.Spc.Gain=3;
 	}

// Complete P-Structure
void CompleteParm(void){
	P.Spc.Factor=50000/P.Spc.Gain/P.Chann.Num; // ps/ch
	
	switch(P.Biom.Type){
		case BIOM_CONTRAST:
			P.Eps[0][0]=1;
			P.Eps[0][1]=0;
			P.Eps[1][0]=0;
			P.Eps[1][1]=1;
			break;
		case BIOM_DMUA:
			P.Eps[0][0]=1.0/BIOM_PATHLEN;
			P.Eps[0][1]=0;
			P.Eps[1][0]=0;
			P.Eps[1][1]=1.0/BIOM_PATHLEN;
			break;
		case BIOM_HBHBO2:
			P.Eps[0][0]=6.770E-04/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[0][1]=2.243E-03/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[1][0]=6.436E-03/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[1][1]=1.596E-03/BIOM_PATHLEN;;  // cm-1/uM
			break;
		default:
			P.Eps[0][0]=0;
			P.Eps[0][1]=0;
			P.Eps[1][0]=0;
			P.Eps[1][1]=0;
			break;
			}
	}



/* INIT AND CLOSE FUNCTIONS */

// Initialise Memory
void InitMem(void){	
	int id,ib,il;
	
	D.Biom=malloc(P.Det.Num*sizeof(double**));
	for(id=0;id<P.Det.Num;id++){
		D.Biom[id]=malloc(P.Biom.Num*sizeof(double*));
		for(ib=0;ib<P.Biom.Num;ib++)
			D.Biom[id][ib]=calloc(P.Clock.Num,sizeof(double));
		}
		
	D.Curve=malloc(P.Det.Num*sizeof(T_DATA**));
	for(id=0;id<P.Det.Num;id++){
		D.Curve[id]=malloc(P.Lambda.Num*sizeof(T_DATA*));
		for(il=0;il<P.Lambda.Num;il++)
			D.Curve[id][il]=calloc(P.Chann.Num,sizeof(T_DATA));
		}
		
	D.Ref=malloc(P.Det.Num*sizeof(double*));
	for(id=0;id<P.Det.Num;id++)
		D.Ref[id]=calloc(P.Lambda.Num,sizeof(double));
	
	D.Gate=malloc(P.Det.Num*sizeof(double*));
	for(id=0;id<P.Det.Num;id++)
		D.Gate[id]=calloc(P.Lambda.Num,sizeof(double));
	
	D.DMua=malloc(P.Det.Num*sizeof(double*));
	for(id=0;id<P.Det.Num;id++)
		D.DMua[id]=calloc(P.Lambda.Num,sizeof(double));
	
	D.Clock=calloc(P.Clock.Num,sizeof(double));
	
	D.Time=calloc(P.Chann.Num,sizeof(double));
	
	D.Chann=calloc(P.Chann.Num,sizeof(int));
	
	D.BufChar=malloc(P.Lambda.Num*P.Det.Num*(sizeof(T_SUB)+P.Chann.Num*sizeof(T_DATA)));
	}


// Close Memory
void CloseMem(void){
	int id,ib,il;
	for(id=0;id<P.Det.Num;id++) {for(ib=0;ib<P.Biom.Num;ib++) free(D.Biom[id][ib]); free(D.Biom[id]);} free(D.Biom);
	for(id=0;id<P.Det.Num;id++) {for(il=0;il<P.Lambda.Num;il++) free(D.Curve[id][il]); free(D.Curve[id]);} free(D.Curve);
	for(id=0;id<P.Det.Num;id++) free(D.Ref[id]); free(D.Ref); 
	for(id=0;id<P.Det.Num;id++) free(D.Gate[id]); free(D.Gate); 
	for(id=0;id<P.Det.Num;id++) free(D.DMua[id]); free(D.DMua); 
	free(D.Clock);
	free(D.Time);
	free(D.Chann);
	free(D.BufChar);
	}


// Failure to load the whole data, wait a while
void WaitFile(void){
	int panel,control;
	GetCtrlVal (hDisplay, DISPLAY_ABORT, &P.Command.Abort);
	GetCtrlVal (hDisplay, DISPLAY_CONTPAUSE, &P.Command.Continue);
	GetUserEvent (0, &panel, &control);
	if(P.Command.Abort) return;
	while(!P.Command.Continue);
	Delay(P.Wait.File);
	}	


// Initialise File
void InitFile(void){
	P.Command.Failure=FALSE;
	sprintf(P.File.Path,"%s\\%s.%s",P.File.Dir,P.File.Name,P.File.Ext);
	P.File.File=fopen("D:\\Beta\\Programs\\Trace\\Data\\DENv0095.DAT","rb");
	//P.File.File=fopen("P.File.Path","rb");
	if(P.File.File==NULL){
		ConfirmPopup ("FAILURE","Error Opening the File\nPress <ENTER> to exit");
		P.Command.Failure=TRUE;
		}
	fread(&D.Head,sizeof(T_HEAD),1,P.File.File);
	}


// Close File
void CloseFile(void){
	fclose(P.File.File);
	}


// Initialise Display
void InitDisplay(void){
	int ic,ik;
	for(ic=0;ic<P.Chann.Num;ic++) D.Chann[ic]=ic;
	for(ic=0;ic<P.Chann.Num;ic++) D.Time[ic]=ic*P.Spc.Factor; // CORRECT FOR EXACT TIME BIN
	for(ik=0;ik<P.Clock.Num;ik++) D.Clock[ik]=ik; // 
	P.Color[0]=VAL_GREEN;
	P.Color[1]=VAL_RED;
	P.Color[2]=VAL_CYAN;
	P.Color[3]=VAL_MAGENTA;
	P.Color[4]=VAL_BLUE;
	P.Color[5]=VAL_YELLOW;
	P.Color[6]=VAL_DK_RED;
	P.Color[7]=VAL_DK_YELLOW;
	SetActivePanel (hDisplay);
	ProcessDrawEvents ();
	}

/* KERNEL FUNCTIONS */

// Wait for next Data and load it. Exit when Break pressed 
void ReadFile(void){
	int numchar=P.Lambda.Num*P.Det.Num*(sizeof(T_SUB)+P.Chann.Num*sizeof(T_DATA));
	fread(D.BufChar,sizeof(char),numchar,P.File.File);
	while(fread(D.BufChar,sizeof(char),numchar,P.File.File)<=0){
		if(P.Command.Abort) return;
		while(!P.Command.Continue);
		Delay(DELAY_READ);
		}
	for(int il=0;il<P.Lambda.Num;il++)
		for(int id=0;id<P.Det.Num;id++){
			int jump=(id+il*P.Det.Num)*(sizeof(T_SUB)+P.Chann.Num*sizeof(T_DATA));
			char* pChar=D.BufChar+jump;
			T_DATA* pCurve=(short*) pChar;
			for(int ic=0;ic<P.Chann.Num;ic++)
				D.Curve[id][il][ic]=pCurve[0];
			}
	}

// Wait for next Data and load it. Exit when Break pressed 
void ReadFile(void){
	for(int il=0;il<P.Lambda.Num;il++)
		for(int id=0;id<P.Det.Num;id++){
			while(fread(&D.Sub,sizeof(T_SUB),1,P.File.File)<1) WaitFile();
			while(fread(D.Curve[id][il],sizeof(T_DATA),P.Chann.Num,P.File.File)<P.Chann.Num) WaitFile();
			}
	}


// Calculate Gates
void CalcGate(void){
	int id,il,ic;
	for(id=0;id<P.Det.Num;id++)
		for(il=0;il<P.Lambda.Num;il++){
			double bkg=0;
			double gate=0;
			for(ic=P.Bkg[id][il].First;ic<=P.Bkg[id][il].Last;ic++)
				bkg+=D.Curve[id][il][ic];
			for(ic=P.Gate[id][il].First;ic<=P.Gate[id][il].Last;ic++)
				gate+=D.Curve[id][il][ic];
			//gate-=bkg;
			D.Gate[id][il]=gate;
			}
	}

// Calculate Reference
void CalcRef(void){
	if((P.Clock.Actual<P.Ref.First)||(P.Clock.Actual>P.Ref.Last)) return;
	for(int id=0;id<P.Det.Num;id++)
		for(int il=0;il<P.Lambda.Num;il++){
			double factor=1/((P.Clock.Actual-P.Ref.First)+1);			// inverse of the number of points (clock) in the REF so far
			D.Ref[id][il]=factor*D.Gate[id][il]+(1-factor)*D.Ref[id][il];		 // the reference is dynamically updated once the data are available
			}
	}

// Calculate Concentrations
void CalcBiom(void){
	int id,il;
	// calc Mua
	for(id=0;id<P.Det.Num;id++)
		for(il=0;il<P.Lambda.Num;il++)
			D.DMua[id][il]=(D.Ref[id][il]>0?-log(D.Gate[id][il]/D.Ref[id][il]):0);
	// calc Biomarker b1=O2Hb, b2=HHb
	for(id=0;id<P.Det.Num;id++){
		D.Biom[id][iB1][P.Clock.Actual]=(D.DMua[id][iL1]*P.Eps[iB2][iL2]-D.DMua[id][iL2]*P.Eps[iB2][iL1])/(P.Eps[iB1][iL1]*P.Eps[iB2][iL2]-P.Eps[iB2][iL2]*P.Eps[iB2][iL1]);
		D.Biom[id][iB2][P.Clock.Actual]=(D.DMua[id][iL2]*P.Eps[iB1][iL1]-D.DMua[id][iL1]*P.Eps[iB1][iL2])/(P.Eps[iB1][iL1]*P.Eps[iB2][iL2]-P.Eps[iB2][iL2]*P.Eps[iB2][iL1]);
		}
	}
								
								
// Update Plot Display
void UpdatePlot(void){
	int id,il,ip;
	double minplot = 1e0;
	double maxplot = 1e5;
	
	if(P.Clock.Actual==0) P.Wait.Now=Timer();
	SyncWait (P.Wait.Now, P.Wait.Display);
	P.Wait.Now+=P.Wait.Display;
	for(id=0;id<P.Det.Num;id++)
		for(il=0;il<P.Lambda.Num;il++){
			ip=il+id*P.Lambda.Num;
			PlotXY (hDisplay, DISPLAY_GRAPH_PLOT, D.Chann, D.Curve[id][il], P.Chann.Num, VAL_INTEGER, VAL_UNSIGNED_SHORT_INTEGER, VAL_SCATTER, VAL_SMALL_CROSS,
					VAL_SOLID, 1, P.Color[ip]);
			PlotLine (hDisplay, DISPLAY_GRAPH_PLOT, P.Gate[id][il].First, minplot, P.Gate[id][il].First, maxplot,  P.Color[ip]);
			PlotLine(hDisplay,DISPLAY_GRAPH_PLOT,P.Gate[id][il].Last,minplot,P.Gate[id][il].Last,maxplot, P.Color[ip]);
			}

	RefreshGraph(hDisplay,DISPLAY_GRAPH_PLOT);
	DeleteGraphPlot(hDisplay,DISPLAY_GRAPH_PLOT,-1,VAL_DELAYED_DRAW);
	}

	
// Update Trace Display
void UpdateTrace(void){
	int id,ib;
	double minplot = -100;
	double maxplot = +100;
	int display_graph_trace[2];
	display_graph_trace[0]=DISPLAY_GRAPH_TRACE_1;
	display_graph_trace[1]=DISPLAY_GRAPH_TRACE_2;

	for(id=0;id<P.Det.Num;id++){
		PlotLine(hDisplay,display_graph_trace[id],P.Ref.First,minplot,P.Ref.First,maxplot,VAL_GRAY);
		PlotLine(hDisplay,display_graph_trace[id],P.Ref.Last,minplot,P.Ref.Last,maxplot,VAL_GRAY);
		for(ib=0;ib<P.Biom.Num;ib++){
			if(ib==0)
				SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_ACTIVE_YAXIS,VAL_LEFT_YAXIS);
			else
				SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_ACTIVE_YAXIS,VAL_RIGHT_YAXIS);
			PlotXY (hDisplay, display_graph_trace[id], D.Clock, D.Biom[id][ib], P.Clock.Num, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, VAL_SMALL_CROSS,
					VAL_SOLID, 1, P.Color[ib]);
			}
		RefreshGraph(hDisplay,display_graph_trace[id]);
		DeleteGraphPlot(hDisplay,display_graph_trace[id],-1,VAL_DELAYED_DRAW);
		}
	}
	
	
// main kernel
void DoProcess(void){
	SimulateUir();
	CompleteParm();
	InitMem();
	InitFile();
	InitDisplay();
	for(P.Clock.Actual=0;P.Clock.Actual<P.Clock.Num;P.Clock.Actual++){
		if(P.Command.Failure) break;
		ReadFile();
		if(P.Command.Abort) break;
		CalcGate();
		CalcRef();
		CalcBiom();
		UpdatePlot();
		UpdateTrace();
		}
	CloseMem();
	CloseFile();
	}


/* ######################################################################## */
/* 								END of PROCESS.C							*/ 
/* ######################################################################## */


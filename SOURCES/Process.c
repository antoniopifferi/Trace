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
		case DISPLAY_PAUSE:
			GetCtrlVal (hDisplay, control, &P.Command.Pause);
			break;
		case DISPLAY_ABORT:
			P.Command.Abort=TRUE;
			break;
		}
	return 0;
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
			strcpy(P.Biom.Label[0],BIOM_LABEL_C_1);
			strcpy(P.Biom.Label[1],BIOM_LABEL_C_2);
			break;
		case BIOM_DMUA:
			P.Eps[0][0]=1.0/BIOM_PATHLEN;
			P.Eps[0][1]=1.0/BIOM_PATHLEN;
			P.Eps[1][0]=1.0/BIOM_PATHLEN;
			P.Eps[1][1]=1.0/BIOM_PATHLEN;
			strcpy(P.Biom.Label[0],BIOM_LABEL_A_1);
			strcpy(P.Biom.Label[1],BIOM_LABEL_A_2);
			break;
		case BIOM_HBHBO2:
			P.Eps[0][0]=BIOM_EPS_1_1/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[0][1]=BIOM_EPS_1_2/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[1][0]=BIOM_EPS_2_1/BIOM_PATHLEN;;  // cm-1/uM
			P.Eps[1][1]=BIOM_EPS_2_2/BIOM_PATHLEN;;  // cm-1/uM
			strcpy(P.Biom.Label[0],BIOM_LABEL_H_1);
			strcpy(P.Biom.Label[1],BIOM_LABEL_H_2);
			break;
		default:
			P.Eps[0][0]=0;
			P.Eps[0][1]=0;
			P.Eps[1][0]=0;
			P.Eps[1][1]=0;
			strcpy(P.Biom.Label[0],"");
			strcpy(P.Biom.Label[1],"");
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


// Initialise File
void InitFile(void){
	P.Command.Failure=FALSE;
	sprintf(P.File.Path,"%s\\%s.%s",P.File.Dir,P.File.Name,P.File.Ext);
	P.File.File=fopen(P.File.Path,"rb");
	if(P.File.File==NULL){
		ConfirmPopup ("FAILURE","Error Opening the File\nPress <ENTER> to exit");
		P.Command.Failure=TRUE;
		}
	fread(&D.Head,sizeof(T_HEAD),1,P.File.File);
	//P.Clock.Num=D.Head.LoopNum[LOOP1]*D.Head.LoopNum[LOOP2]*D.Head.LoopNum[LOOP3];
	}


// Close File
void CloseFile(void){
	fclose(P.File.File);
	}


// Initialise Display
void InitDisplay(void){
	int ic,ib,id,ik;
	int display_graph_trace[2],val_active_yaxis[2];
	display_graph_trace[0]=DISPLAY_GRAPH_TRACE_1;
	display_graph_trace[1]=DISPLAY_GRAPH_TRACE_2;
	val_active_yaxis[0]=VAL_LEFT_YAXIS;
	val_active_yaxis[1]=VAL_RIGHT_YAXIS;
	P.Color[0]=VAL_GREEN;
	P.Color[1]=VAL_RED;
	P.Color[2]=VAL_CYAN;
	P.Color[3]=VAL_MAGENTA;
	P.Color[4]=VAL_BLUE;
	P.Color[5]=VAL_YELLOW;
	P.Color[6]=VAL_DK_RED;
	P.Color[7]=VAL_DK_YELLOW;
	for(ic=0;ic<P.Chann.Num;ic++) D.Chann[ic]=ic;
	for(ic=0;ic<P.Chann.Num;ic++) D.Time[ic]=ic*P.Spc.Factor; // CORRECT FOR EXACT TIME BIN
	for(ik=0;ik<P.Clock.Num;ik++) D.Clock[ik]=ik; // 
	SetCtrlVal (hDisplay, DISPLAY_PAUSE, FALSE);
	P.Command.Abort=FALSE;
	P.Command.Pause=FALSE;
	P.Command.Failure=FALSE;
	for(id=0;id<P.Det.Num;id++)
		for(ib=0;ib<P.Biom.Num;ib++){
			SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_ACTIVE_YAXIS,val_active_yaxis[ib]);
			SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_YNAME,P.Biom.Label[ib]);
			SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_YLABEL_COLOR,P.Color[ib]);
			}
	SetActivePanel (hDisplay);
	}

/* KERNEL FUNCTIONS */

// Wait for next Data and load it. Exit when Break pressed 
void ReadFile(void){
	long sizefile,offset,sizeblock;
	
	// Check File Length
	sizeblock=P.Lambda.Num*P.Det.Num*(sizeof(T_SUB)+P.Chann.Num*sizeof(T_DATA));
	offset=sizeof(T_HEAD)+P.Clock.Actual*sizeblock;
	fseek (P.File.File, 0, SEEK_END);
	sizefile = ftell(P.File.File);
	while(sizefile<(offset+sizeblock)) {
		if(P.Command.Abort) return;
		while(P.Command.Pause);
		Delay (P.Wait.File);
		fseek (P.File.File, 0, SEEK_END);
		sizefile =ftell(P.File.File);
		};
	fseek (P.File.File, offset, SEEK_SET);
	
	for(int il=0;il<P.Lambda.Num;il++)
		for(int id=0;id<P.Det.Num;id++){
			fread(&D.Sub,sizeof(T_SUB),1,P.File.File);
			fread(D.Curve[id][il],sizeof(T_DATA),P.Chann.Num,P.File.File);
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
			gate-=bkg;
			D.Gate[id][il]=gate;
			}
	}

// Calculate Reference
void CalcRef(void){
	if((P.Clock.Actual<P.Ref.First)||(P.Clock.Actual>P.Ref.Last)) return;
	for(int id=0;id<P.Det.Num;id++)
		for(int il=0;il<P.Lambda.Num;il++){
			double factor=1.0/((P.Clock.Actual-P.Ref.First)+1);			// inverse of the number of points (clock) in the REF so far
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
	while(!P.Command.Abort&&(P.Command.Pause));
	}

	
// Update Trace Display
void UpdateTrace(void){
	int id,ib,ik;
	double minY = 0;
	double maxY = 0;
	int display_graph_trace[2],val_active_yaxis[2];
	display_graph_trace[0]=DISPLAY_GRAPH_TRACE_1;
	display_graph_trace[1]=DISPLAY_GRAPH_TRACE_2;
	val_active_yaxis[0]=VAL_LEFT_YAXIS;
	val_active_yaxis[1]=VAL_RIGHT_YAXIS;

	for(id=0;id<P.Det.Num;id++)
		for(ib=0;ib<P.Biom.Num;ib++)
			for(ik=0;ik<=P.Clock.Actual;ik++){
				if(D.Biom[id][ib][ik]<minY) minY=D.Biom[id][ib][ik];
				if(D.Biom[id][ib][ik]>maxY) maxY=D.Biom[id][ib][ik];
				if(maxY==minY) maxY+=1E-10;
			}
	for(id=0;id<P.Det.Num;id++){
		for(ib=0;ib<P.Biom.Num;ib++){
			SetCtrlAttribute(hDisplay,display_graph_trace[id],ATTR_ACTIVE_YAXIS,val_active_yaxis[ib]);
			SetAxisScalingMode (hDisplay,display_graph_trace[id],val_active_yaxis[ib],VAL_MANUAL,minY,maxY);
			PlotXY (hDisplay, display_graph_trace[id], D.Clock, D.Biom[id][ib], P.Clock.Num, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, VAL_SMALL_CROSS,
					VAL_SOLID, 1, P.Color[ib]);
			}
		PlotLine(hDisplay,display_graph_trace[id],P.Ref.First,minY,P.Ref.First,maxY,VAL_GRAY);
		PlotLine(hDisplay,display_graph_trace[id],P.Ref.Last,minY,P.Ref.Last,maxY,VAL_GRAY);
		RefreshGraph(hDisplay,display_graph_trace[id]);
		DeleteGraphPlot(hDisplay,display_graph_trace[id],-1,VAL_DELAYED_DRAW);
		while(!P.Command.Abort&&(P.Command.Pause));
		}
	}

// main kernel
void DoProcess(void){
	ReadAll();
	CompleteParm();
	UpdatePanel();
	InitFile();
	InitMem();
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
//	DisplayPanel(hTrace);
//	DisplayPanel(hParm);
	}


/* ######################################################################## */
/* 								END of PROCESS.C							*/ 
/* ######################################################################## */


/* ########################   CONSTANTS   ################################# */

// VERSION
#define MESSAGE_ABOUT   "TRACE visualization\nVersion: 1.0\nDate: July 2018"

// TYPE OF DATA
#define T_DATA unsigned short
#define T_HEAD struct sHeader2
#define T_SUB struct sSubHeader1

/* TOOLS */
#define SIGNUM(x)	 ((x>=0) ? 1:-1)
#define REMINDER(a,b)  	(a-b*(int)(a/b))
#define MAX(a,b)	(a>b?a:b)
#define MIN(a,b)	(a<b?a:b)
#define CEIL(a,b)	(REMINDER(a,b)==0?a/b:a/b+1)
														  
/* GENERAL CONSTANTS */
#define STRLEN 		  128
#define PATHLEN		  30
#define ns2ps         1000
#define FALSE   	 0	   	 
#define TRUE    	 1
#define NEG			-1
#define SPEED_C		0.03 // cm/ps

/* DISPLAY CONSTANTS */
#define MAX_PANEL		15
#define MAX_PLOT	16

/* BIOM CONSTANTS */
#define BIOM_PATHLEN	20  // cm = vt = c/n*1ns
#define BIOM_CONTRAST	0	// display contrast
#define BIOM_DMUA		1	// display DeltaMua
#define BIOM_HBHBO2		2	// display Hb HbO2
#define BIOM_LABEL_C_1	"Contrast @670 nm"
#define BIOM_LABEL_C_2	"Contrast @830 nm"
#define BIOM_LABEL_A_1	"DMua (cm-1) @670 nm"
#define BIOM_LABEL_A_2	"DMua (cm-1) @830 nm"
#define BIOM_LABEL_H_1	"O2Hb (uM)"
#define BIOM_LABEL_H_2	"HHB (uM)"
#define BIOM_EPS_1_1	6.770E-04
#define BIOM_EPS_1_2	2.243E-03
#define BIOM_EPS_2_1	6.436E-03
#define BIOM_EPS_2_2	1.596E-03


/* PROCESS CONSTANTS */
#define MAX_BIOM 	2 // maximum number of biomarkers (different from P.Biom.Num which is the actual number)
#define MAX_LAMBDA	2 // maximum number of wavelengths (different from P.Lambda.Num which is the actual number)
#define MAX_DET		2 // maximum number of detectors/boards (different from P.Det.Num which is the actual number)
#define MAX_COLOR	8 // maximum number of traces
#define iB1			0 // index O2Hb
#define iB2			1 // index HHb
#define iL1			0 // 670 nm
#define iL2			1 // 830
#define iDetEarly	0 // detector early gate

/* UNUSED CONSTANTS JUST FOR RE-USE OF TRS STRUCTURES */
#define MAX_LOOP	5
#define LABEL_MAX		16
#define LABEL_NAMELEN	12
#define LABEL_CONTENTLEN 22
#define MAX_ROI_SUB			4
#define LOOP1			0
#define LOOP2			1
#define LOOP3			2



/* TABLE CONSTANTS */  
#define MAX_TABLE		(8+8+12+3+2+3+6+3)
#define STRLEN_TABLE	20
#define TCHAR			0
#define TINT			1
#define TDOUBLE			2
#define	TSTRING			3
#define CE				0
#define CT				1
#define MAX_TTABLE		13
#define STRLEN_TTABLE	20
#define MAX_PANEL		15


/* FILE CONSTANTS AND ENVIRONMENT SETTINGS */  
#define EXTASCII      ".TXT"
#define FILESET		"SET\\TRACE.TRC"
#define DIRPROG		""
#define DIRSETTINGS   "SET"
#define EXTSETTINGS   "*.TRC" 
#define DIR_RESULT   "RESULT"
#define EXT_RESULT   "*.TXT" 

/* USER INTERFACE CONSTANTS */
#define PATH_UIR	".\\Sources\\TRACE.UIR"



/* ########################   TYPE DEFINITION  ############################ */




struct FileS {
	char Dir   [PATHLEN];
	char Name  [PATHLEN];
	char Ext   [PATHLEN];
	char Path  [STRLEN];
	FILE *File;
	};
	
struct RangeS {
	long First;
	long Last;
	long Num;
	long Actual;
	};

struct WaitS {
	double File;
	double Display;
	double Now;
	};

struct CommandS{
	int Abort;
	int Pause;
	int Failure;
	char ReadUIR;
	};

struct SpcS{
	double Factor;
	double Gain;
	};

struct BiomS{
	int Num;
	int Type;
	char Label[MAX_BIOM][STRLEN];
	};

struct LimitS{
	double Low;
	double High;
	int Auto;
	};

struct ZoomS{
	double Low;
	double High;
	int Auto;
	};

struct WindowS{
	double First;
	double Last;
	double Middle;
	};

struct TimeBkgS{
	double First;
	double Last;
	};

#pragma pack(push,1)
T_HEAD{
	short Ver[2];
	long SubHeader;
	long SubHeadVer;
	long SizeHeader;
	long SizeSubHeader;
	long SizeData;
	long Kind;
	long Appl;
	long Oma;
	char Date[10+1];
	char Time[8+1];
	long LoopHome[MAX_LOOP-2];	  // for compatibility with FIT, use only LOOP3,LOOP4,LOOP5
	long LoopFirst[MAX_LOOP-2];
	long LoopLast[MAX_LOOP-2];
	long LoopDelta[MAX_LOOP-2];
	long LoopNum[MAX_LOOP-2];
	long McaChannNum;
	long PageNum;
	long FrameNum;
	long RamNum;
	double McaTime;
	double McaFactor;
	long MeasNorm;
	char LabelName[LABEL_MAX][LABEL_NAMELEN];
	char LabelContent[LABEL_MAX][LABEL_CONTENTLEN];
	double Constn;
	double ConstRho;
	double ConstThick;
	long MammHeader;
	long MammIdxFirst[2];
	long MammIdxLast[2];
	long MammIdxTop[2];
	long MammRateMid[2];
	long MammRateHigh[2];
	};

T_SUB{
	char Geom;
	char Source;
	char Fiber;
	char Det;
	char Board;
	char Coord;
	char Pad;
	double Xf;
	double Yf;
	double Zf;
	double Rf;
	double Xs;
	double Ys;
	double Zs;
	double Rs;
	double Rho;
	double TimeNom;
	double TimeEff;
	double n;
	long Loop[MAX_LOOP-2];		  // for compatibility with FIT, use only LOOP3,LOOP4,LOOP5
	long Acq;
	long Page;
	char RoiNum;
	short RoiFirst[MAX_ROI_SUB];
	short RoiLast[MAX_ROI_SUB];
	double RoiLambda[MAX_ROI_SUB];
	double RoiPower[MAX_ROI_SUB];
	};
#pragma pack(pop)

struct ParmS {
	struct CommandS Command;
	struct FileS File;
	struct RangeS Chann;
	struct RangeS Det;
	struct RangeS Lambda;
	struct BiomS Biom;
	struct RangeS Bkg[MAX_DET][MAX_LAMBDA];
	struct TimeBkgS TimeBkg[MAX_DET][MAX_LAMBDA];
	struct RangeS Gate[MAX_DET][MAX_LAMBDA];
	struct WindowS Window[MAX_DET][MAX_LAMBDA];
	struct LimitS Limit[MAX_DET][MAX_BIOM];
	struct ZoomS Zoom;
	struct RangeS Clock;
	struct RangeS Ref;
	double Eps[MAX_BIOM][MAX_LAMBDA];
	struct SpcS Spc;
	struct WaitS Wait;
	int    Color[MAX_COLOR];
	int	   PeakChann[MAX_LAMBDA];
	int    AllocatedMem;
	};

// Data Structures
struct DataS {
	double **Ref;		// D.Ref[MAX_DET][MAX_LAMBDA]
	double **Gate;		// D.Gate[MAX_DET][MAX_LAMBDA] 
	double ***Biom;		// D.Biom[MAX_DET][MAX_LAMBDA][P.Clock.Num] 
	double *Clock;		// D.Clock[P.Clock.Num] 
	T_DATA ***Curve;	// D.Curve[MAX_DET][MAX_LAMBDA][P.Num.Chann] 
	char   *BufChar;	// max data in a single clock
	int    *Chann;		// channel axis
	double *Time;		// time (ps) axis
	T_HEAD Head;		// header
	T_SUB  Sub;			// subheader
	};

struct TableS {
	int   Class[MAX_TABLE]; 
	int   Ctrl[MAX_TABLE]; 
	int   Type[MAX_TABLE]; 
	int   Row[MAX_TABLE];
	int   Col[MAX_TABLE];
	void* Addr[MAX_TABLE];
	int   Panel[MAX_TABLE];
	char  Dimmed[MAX_TABLE];
	char  Label[MAX_TABLE][STRLEN_TABLE];
	int   Num;   
	};
   
   

   
/* #####################   GLOBAL VARIABLES   ########################### */

struct ParmS P;
struct DataS D;
struct TableS T;

int hTrace;
int hParm;
int hDisplay;
int hPlot[MAX_PLOT];
int hPanel[MAX_PANEL];

/* #####################   FUNCTIONS   ########################### */
void CompleteParm(void);
void UpdatePanel(void);
void ReadAll(void);

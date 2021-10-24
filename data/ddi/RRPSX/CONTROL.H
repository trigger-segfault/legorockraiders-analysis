//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Control Include File For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹



/*
	tags ending _NO_ACTION are unused at present
*/

typedef enum
{
	CONTROL_SQUARE_NO_ACTION,
	CONTROL_CIRCLE_NO_ACTION,
	CONTROL_DIG,
	CONTROL_ACTIVATION_TOGGLE,

	CONTROL_CAMERA_MODE,
	CONTROL_CAMERA_ROTATE_LEFT,
	CONTROL_CAMERA_ZOOM_TOGGLE,
	CONTROL_CAMERA_ROTATE_RIGHT,

	CONTROL_DS_LEFT,		/* these are the buttons on the analogue sticks */
	CONTROL_DS_RIGHT,

/* these are the system controls, which are not re-definable */

	CONTROL_TURN_LEFT,
	CONTROL_TURN_RIGHT,
	CONTROL_FORWARD,
	CONTROL_REVERSE,

	CONTROL_SELECT,
	CONTROL_START,

	CONTROL_SYS_SQUARE,
	CONTROL_SYS_CIRCLE,
	CONTROL_SYS_TRIANGLE,
	CONTROL_SYS_CROSS,

	CONTROL_SYS_LEFT_TOP_SHOULDER,
	CONTROL_SYS_LEFT_BOTTOM_SHOULDER,

	CONTROL_SYS_RIGHT_TOP_SHOULDER,
	CONTROL_SYS_RIGHT_BOTTOM_SHOULDER,


	MAX_CONTROLS,

}	CONTROL_TYPE;



enum
{
	WAIT_RELEASE	= -1,
	
};



/* structures */

typedef struct control_st
{
	Uint16	mask;
	char		event;
	char		transient;
	short		held_time;
	short		repeat;

}	CONTROL, *lpCONTROL;



/* prototypes */

void	Control_initialseControlSet(lpCONTROL control);
void	Control_initialseMainControlSet(void);
BOOL	Control_serviceControlSet(lpCONTROL control,int padIndex);
void	Control_serviceMainControlSet(void);


/* pad access macros */

#define	PAD_EVENT(p,n)								(p)[(n)].event
#define	PAD_TRANSIENT(p,n)						(p)[(n)].transient
#define	CLEAR_EVENT_RELEASE(p,n)				(p)[(n)].event=FALSE; (p)[(n)].repeat=WAIT_RELEASE
#define	CLEAR_EVENT_DELAY(p,n,d)				(p)[(n)].event=FALSE; (p)[(n)].repeat=(d)
#define	CLEAR_EVENT_IMMEDIATE(p,n)				(p)[(n)].event=FALSE; (p)[(n)].repeat=(0)



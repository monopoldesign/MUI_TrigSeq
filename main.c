/******************************************************************************
* MUI_TrigSeq - CustomClass for a Trigger-Sequencer
* (C)2022 M.Volkel (mario.volkel@outlook.com)
*******************************************************************************/

// Comment templates

/******************************************************************************
*
*******************************************************************************/

/*-----------------------------------------------------------------------------
-
------------------------------------------------------------------------------*/

/******************************************************************************
* Header-Files
*******************************************************************************/
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include <exec/memory.h>
#include <libraries/mui.h>
#include <proto/exec.h>

#include <pragma/muimaster_lib.h>

/******************************************************************************
* Macros
*******************************************************************************/
#define HOOKPROTONH(name, ret, obj, param) ret name(register __a2 obj, register __a1 param)
#define MakeHook(hookName, hookFunc) struct Hook hookName = {{NULL, NULL}, (HOOKFUNC)hookFunc, NULL, NULL}
#define DISPATCHER(name) LONG name(register __a0 Class *cl, register __a2 Object *obj, register __a1 Msg msg)

/******************************************************************************
* Prototypes
*******************************************************************************/
HOOKPROTONH(ButtonFunc, ULONG, Object *obj, int *msg);

void init(void);
void end(void);
struct ObjApp * CreateApp(void);
void DisposeApp(struct ObjApp * ObjectApp);

/******************************************************************************
* Definitions
*******************************************************************************/
#define MAKE_ID(a, b, c, d) ((ULONG)(a) << 24 | (ULONG)(b) << 16 | (ULONG)(c) << 8 | (ULONG)(d))
enum CBID {ID_CB0, ID_CB1, ID_CB2, ID_CB3, ID_CB4, ID_CB5, ID_CB6, ID_CB7, ID_CB8, ID_CB9, ID_CB10, ID_CB11, ID_CB12, ID_CB13, ID_CB14, ID_CB15};

struct ObjApp
{
	APTR	App;
	APTR	WI_label_0;
	APTR	BT_label_0;
};

/******************************************************************************
* Global Variables
*******************************************************************************/
struct IntuitionBase *IntuitionBase;
struct Library *MUIMasterBase;

MakeHook(hook_button, ButtonFunc);

char buffer[40];
struct ObjApp *App = NULL;

struct MUI_CustomClass *trigSeq;

/******************************************************************************
* Hooks
*******************************************************************************/
/*-----------------------------------------------------------------------------
- ButtonFunc()
- Function for Button-Hook
------------------------------------------------------------------------------*/
HOOKPROTONH(ButtonFunc, ULONG, Object *obj, int *msg)
{
	ULONG id, val;

	id = *msg++;
	val = *msg;

	switch (id)
	{
		case ID_CB0:
			printf("Button 0: %d\n", val);
			break;
		case ID_CB1:
			printf("Button 1: %d\n", val);
			break;
		case ID_CB2:
			printf("Button 2: %d\n", val);
			break;
		case ID_CB3:
			printf("Button 3: %d\n", val);
			break;
		case ID_CB4:
			printf("Button 4: %d\n", val);
			break;
		case ID_CB5:
			printf("Button 5: %d\n", val);
			break;
		case ID_CB6:
			printf("Button 6: %d\n", val);
			break;
		case ID_CB7:
			printf("Button 7: %d\n", val);
			break;
		case ID_CB8:
			printf("Button 8: %d\n", val);
			break;
		case ID_CB9:
			printf("Button 9: %d\n", val);
			break;
		case ID_CB10:
			printf("Button 10: %d\n", val);
			break;
		case ID_CB11:
			printf("Button 11: %d\n", val);
			break;
		case ID_CB12:
			printf("Button 12: %d\n", val);
			break;
		case ID_CB13:
			printf("Button 13: %d\n", val);
			break;
		case ID_CB14:
			printf("Button 14: %d\n", val);
			break;
		case ID_CB15:
			printf("Button 15: %d\n", val);
			break;
	}

	return 0;
}

/******************************************************************************
* MUI-Custom-Class
*******************************************************************************/
/*-----------------------------------------------------------------------------
- Definitions/Variables
------------------------------------------------------------------------------*/
struct MyData
{
	Object *cb[16];
};

/*-----------------------------------------------------------------------------
- OM_NEW
------------------------------------------------------------------------------*/
ULONG DoSuperNew(struct IClass *cl, Object *obj, ULONG tag1, ...)
{
	return (DoSuperMethod(cl, obj, OM_NEW, &tag1, NULL));
}

ULONG mNew(struct IClass *cl, Object *obj, Msg msg)
{
	Object *cb[16], *group;
	struct MyData *data;
	ULONG i;

	for (i = 0; i < 16; i++)
	{
		cb[i] = ImageObject,
				ImageButtonFrame,
				MUIA_InputMode,			MUIV_InputMode_Toggle,
				MUIA_Image_Spec,		MUII_CheckMark,
				MUIA_Image_FreeVert,	TRUE,
				MUIA_Selected,			FALSE,
				MUIA_Background,		MUII_ButtonBack,
				MUIA_ShowSelState,		FALSE,
				End;
	}

	group = GroupObject,
		MUIA_Group_Horiz,			TRUE,
		MUIA_Group_HorizSpacing,	0,
		Child,						cb[0],
		Child,						cb[1],
		Child,						cb[2],
		Child,						cb[3],
		Child,						cb[4],
		Child,						cb[5],
		Child,						cb[6],
		Child,						cb[7],
		Child,						cb[8],
		Child,						cb[9],
		Child,						cb[10],
		Child,						cb[11],
		Child,						cb[12],
		Child,						cb[13],
		Child,						cb[14],
		Child,						cb[15],
		End;

    obj = (Object *) DoSuperNew(cl, obj,
                                	Child, group,
                                	TAG_MORE, ((struct opSet *)msg)->ops_AttrList);

	if (obj == NULL)
		return 0;

	data = (struct MyData *)INST_DATA(cl, obj);

	for (i = 0; i < 16; i++)
		data->cb[i] = cb[i];

	DoMethod(data->cb[0], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB0, MUIV_TriggerValue);
	DoMethod(data->cb[1], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB1, MUIV_TriggerValue);
	DoMethod(data->cb[2], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB2, MUIV_TriggerValue);
	DoMethod(data->cb[3], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB3, MUIV_TriggerValue);
	DoMethod(data->cb[4], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB4, MUIV_TriggerValue);
	DoMethod(data->cb[5], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB5, MUIV_TriggerValue);
	DoMethod(data->cb[6], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB6, MUIV_TriggerValue);
	DoMethod(data->cb[7], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB7, MUIV_TriggerValue);
	DoMethod(data->cb[8], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB8, MUIV_TriggerValue);
	DoMethod(data->cb[9], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB9, MUIV_TriggerValue);
	DoMethod(data->cb[10], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB10, MUIV_TriggerValue);
	DoMethod(data->cb[11], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB11, MUIV_TriggerValue);
	DoMethod(data->cb[12], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB12, MUIV_TriggerValue);
	DoMethod(data->cb[13], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB13, MUIV_TriggerValue);
	DoMethod(data->cb[14], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB14, MUIV_TriggerValue);
	DoMethod(data->cb[15], MUIM_Notify, MUIA_Selected, MUIV_EveryTime, MUIV_Notify_Self, 4, MUIM_CallHook, &hook_button, ID_CB15, MUIV_TriggerValue);

	return((ULONG)obj);
}

/*-----------------------------------------------------------------------------
- Dispatcher
------------------------------------------------------------------------------*/
DISPATCHER(SampleDispatcher)
{
	switch (msg->MethodID)
	{
		case OM_NEW:
			return mNew(cl, obj, (APTR)msg);
	}

	return DoSuperMethodA(cl, obj, msg);
}

/******************************************************************************
* Main-Program
*******************************************************************************/

/*-----------------------------------------------------------------------------
- main()
------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	BOOL running = TRUE;
	ULONG signal;

	init();

	if (trigSeq = (struct MUI_CustomClass *)MUI_CreateCustomClass(NULL, MUIC_Group, NULL, sizeof(struct MyData), SampleDispatcher))
	{
		if (!(App = CreateApp()))
		{
			printf("Can't Create App\n");
			end();
		}

		while (running)
		{
			switch (DoMethod(App->App, MUIM_Application_NewInput, &signal))
			{
				// Window close
				case MUIV_Application_ReturnID_Quit:
					if ((MUI_RequestA(App->App, 0, 0, "Quit?", "_Yes|_No", "\33cAre you sure?", 0)) == 1)
						running = FALSE;
				break;

				default:
					break;
			}

			if (running && signal)
				Wait(signal);
		}
		DisposeApp(App);
	}


	MUI_DeleteCustomClass(trigSeq);
	end();
}

/*-----------------------------------------------------------------------------
- init()
------------------------------------------------------------------------------*/
void init(void)
{
	if (!(IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 37)))
	{
		printf("Can't Open Intuition Library\n");
		exit(20);
	}

	if (!(MUIMasterBase = OpenLibrary(MUIMASTER_NAME, MUIMASTER_VMIN)))
	{
		printf("Can't Open MUIMaster Library\n");
		CloseLibrary((struct Library *)IntuitionBase);
		exit(20);
	}
}

/*-----------------------------------------------------------------------------
- end()
------------------------------------------------------------------------------*/
void end(void)
{
	CloseLibrary((struct Library *)MUIMasterBase);
	CloseLibrary((struct Library *)IntuitionBase);
	exit(0);
}

/*-----------------------------------------------------------------------------
- CreateApp()
------------------------------------------------------------------------------*/
struct ObjApp * CreateApp(void)
{
	struct ObjApp * ObjectApp;

	APTR	GROUP_ROOT_0;

	if (!(ObjectApp = AllocVec(sizeof(struct ObjApp),MEMF_CLEAR)))
		return(NULL);

	trigSeq = NewObject(trigSeq->mcc_Class, NULL, TAG_DONE);

	ObjectApp->BT_label_0 = SimpleButton("Quit");

	GROUP_ROOT_0 = GroupObject,
		MUIA_Group_Columns, 1,
		MUIA_Group_SameSize, TRUE,
		Child, trigSeq,
		Child, ObjectApp->BT_label_0,
	End;

	ObjectApp->WI_label_0 = WindowObject,
		MUIA_Window_Title, "MUI_TrigSeq",
		MUIA_Window_ID, MAKE_ID('0', 'W', 'I', 'N'),
		WindowContents, GROUP_ROOT_0,
	End;

	ObjectApp->App = ApplicationObject,
		MUIA_Application_Author, "M.Volkel",
		MUIA_Application_Base, "MUITRIGSEQ",
		MUIA_Application_Title, "MUI_TrigSeq",
		MUIA_Application_Version, "$VER: MUI_TrigSeq V0.1",
		MUIA_Application_Copyright, "(C)2022 M.Volkel",
		MUIA_Application_Description, "TrigSeq-Class-Test",
		SubWindow, ObjectApp->WI_label_0,
	End;


	if (!ObjectApp->App)
	{
		FreeVec(ObjectApp);
		return(NULL);
	}

	// Window-Close-Method
	DoMethod(ObjectApp->WI_label_0, MUIM_Notify, MUIA_Window_CloseRequest, TRUE, ObjectApp->App, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

	// Exit-Button
	DoMethod(ObjectApp->BT_label_0, MUIM_Notify, MUIA_Pressed, MUIV_EveryTime, ObjectApp->App, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
	
	// Open Window
	set(ObjectApp->WI_label_0, MUIA_Window_Open, TRUE);

	return(ObjectApp);
}

/*-----------------------------------------------------------------------------
- DisposeApp()
------------------------------------------------------------------------------*/
void DisposeApp(struct ObjApp * ObjectApp)
{
	MUI_DisposeObject(ObjectApp->App);
	FreeVec(ObjectApp);
}

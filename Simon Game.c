
#include "bass.h"
#include "toolbox.h" 
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Simon Game.h"

void InitMP3s ();
void grill();
void clear();

static int panelHandle, panel2, panel3;

int steps_arr[1000]={0},user_arr[1000] = {0};
int left1 = 250, right1 = 370, top1=150, bottom1 = 250;
int left2 = 380, right2 = 500, top2=150, bottom2 = 250;
int left3 = 250, right3 = 370, top3=260, bottom3 = 360;
int left4 = 380, right4 = 500, top4=260, bottom4 = 360;
int hight = 100, width=120, color, step, frame_bitmap;
int main_pic, comp_fin, i=0, j = 0 ,computer_index, flag, colorTemp, p=0, click, user_index=0;
double t1, t2,t3,t4, dt=0.5;
int board_drawed = 0 ,mute =1 ;
char turn;

int newScore, score;
char newName[300];
char line[3000];


HSTREAM START_SND;  // sound variables
HSTREAM DO_SND;
HSTREAM RE_SND;
HSTREAM MI_SND;
HSTREAM FA_SND;

typedef struct            
{                         
	int score;            
	char name[300];       
}player;

player players_arr[15], Temp, Temp2; 

void ReadTable()
{
	  FILE *fp;
	  
	
	 fp = fopen ("c:\\Users\\yoavs\\Desktop\\Simon Game\\score.csv", "r");
	 	  
	
	 for(int a=0;a<15;a++)
	 {
		 
		 if (fgets(line,100,fp)==0)
			 break;
 
		 
		 sscanf(line,"%[^,],%d", players_arr[a].name , &players_arr[a].score);
	  
		SetTableCellVal(panel2, PANEL_2_TABLE, MakePoint(2,a+2), players_arr[a].name); 
		SetTableCellVal(panel2, PANEL_2_TABLE, MakePoint(3,a+2), players_arr[a].score);
	
	 
}
 
 fclose(fp);
}

void WriteTable()
{
	FILE *fp;
	
	fp = fopen ("c:\\Users\\yoavs\\Desktop\\Simon Game\\score.csv", "w");
	for(int b=0;b<10;b++)
		fprintf(fp,"%s,%d\n",players_arr[b].name,players_arr[b].score);
	
	fclose(fp);			 
}   


void SetInTable(){
           GetCtrlVal (panel2, PANEL_2_STRING2, newName);
			Temp.score = newScore;
			strcpy(Temp.name , newName);
			for(int c=0;c<10;c++)
			{
				if(Temp.score>players_arr[c].score)
				{
					Temp2.score = players_arr[c].score;
					strcpy(Temp2.name , players_arr[c].name);
			      
					players_arr[c].score = Temp.score;
					strcpy(players_arr[c].name , Temp.name);
					
					for(int d=c+1 ; d<10 ; d++)
					{
						Temp.score = players_arr[d].score;
						strcpy(Temp.name , players_arr[d].name);
							
						players_arr[d].score = Temp2.score;
						strcpy(players_arr[d].name , Temp2.name);
				     
						Temp2.score = Temp.score ;
						strcpy(Temp2.name , Temp.name);
					}
					break;
				}
			}
}





void InitMP3s()
{
	BASS_Init( -1,44100, 0,0,NULL); 
	START_SND = BASS_StreamCreateFile(FALSE,"START_SND.mp3",0,0,0);
	DO_SND = BASS_StreamCreateFile(FALSE,"DO_SND.mp3",0,0,0);
	RE_SND = BASS_StreamCreateFile(FALSE,"RE_SND.mp3",0,0,0);
	MI_SND = BASS_StreamCreateFile(FALSE,"MI_SND.mp3",0,0,0);
	FA_SND = BASS_StreamCreateFile(FALSE,"FA_SND.mp3",0,0,0);
}

void ReleaseMP3s(void)
{
	 BASS_StreamFree(START_SND);
	  BASS_StreamFree(DO_SND);
	   BASS_StreamFree(RE_SND);
	    BASS_StreamFree(MI_SND);
		 BASS_StreamFree(FA_SND);
}


void init()
{
  srand(time(0));
  turn = 'C';
  computer_index = 1; 
  color = 0;
  
  
steps_arr[0] = 1 + rand()%4 ;

GetBitmapFromFile ("c:\\Users\\yoavs\\Desktop\\μιξεγιν\\Simon Game\\Simon Game\\frame.png", &frame_bitmap);
   
clear();


}

void draw()
{
	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	
	
	switch (steps_arr[i])
		 {
				 
			 case 1:
		  SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_DK_RED);
		 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_DK_RED);
	    CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top1,left1,hight,width), VAL_DRAW_FRAME_AND_INTERIOR);
				 BASS_ChannelPlay(DO_SND,TRUE);
	 		 break;
			
			 case 2:
		 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_GREEN);
		 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_GREEN);
		 CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top2,left2,hight,width), VAL_DRAW_FRAME_AND_INTERIOR);
				  BASS_ChannelPlay(RE_SND,TRUE);
			break;
			 
			 case 3:
					SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLUE);
							 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLUE);
					CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top3, left3, hight, width), VAL_DRAW_FRAME_AND_INTERIOR);
				 BASS_ChannelPlay(MI_SND,TRUE);
			break;
			 
			 case 4:
				 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_YELLOW);
					   SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_YELLOW);
					      CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top4, left4, hight, width), VAL_DRAW_FRAME_AND_INTERIOR);
				 BASS_ChannelPlay(FA_SND,TRUE);
						  

			break;
			
	
		 }
		 
			
		CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);

}
		  
void clear(){
	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	
  
			   	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
				
				CanvasDrawBitmap (panelHandle, PANEL_CANVAS, frame_bitmap , VAL_ENTIRE_OBJECT, MakeRect(20,20,500,700));
	            
				SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	            CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top1,left1,hight,width), VAL_DRAW_FRAME);
              	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top2,left2,hight,width), VAL_DRAW_FRAME);
               	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top3, left3, hight, width), VAL_DRAW_FRAME);
             	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top4, left4, hight, width), VAL_DRAW_FRAME);
	        	CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);
		

}
void draw2(){
	   

	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	
	
  	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	
    CanvasDrawBitmap (panelHandle, PANEL_CANVAS, frame_bitmap , VAL_ENTIRE_OBJECT, MakeRect(20,20,500,700));
	
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top1,left1,hight,width), VAL_DRAW_FRAME);
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top2,left2,hight,width), VAL_DRAW_FRAME);
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top3, left3, hight, width), VAL_DRAW_FRAME);
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top4, left4, hight, width), VAL_DRAW_FRAME);


	
	switch (color)
		 {
			 case 1:
		  SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_DK_RED);
	 	 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_DK_RED);
	     CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top1,left1,hight,width), VAL_DRAW_FRAME_AND_INTERIOR);
		 BASS_ChannelPlay(DO_SND,TRUE); 
	   	GetCtrlVal (panelHandle, PANEL_TIMER, &t1);
	 		 break;
			
			 case 2:
		 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_GREEN);
		 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_GREEN);
		 CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(top2,left2,hight,width), VAL_DRAW_FRAME_AND_INTERIOR);
		  BASS_ChannelPlay(RE_SND,TRUE);
		  GetCtrlVal (panelHandle, PANEL_TIMER, &t1);
			break;
			 
			 case 3:
					SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLUE);
					SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLUE);
					CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top3, left3, hight, width), VAL_DRAW_FRAME_AND_INTERIOR);
					BASS_ChannelPlay(MI_SND,TRUE); 
					GetCtrlVal (panelHandle, PANEL_TIMER, &t1);
			break;
			 
			 case 4:
				 SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_YELLOW);
			    SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_YELLOW);
				CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (top4, left4, hight, width), VAL_DRAW_FRAME_AND_INTERIOR);
				 BASS_ChannelPlay(FA_SND,TRUE);
				GetCtrlVal (panelHandle, PANEL_TIMER, &t1);

			break;
			
		 }
		 CanvasEndBatchDraw (panelHandle, PANEL_CANVAS); 
		 
		 	GetCtrlVal (panelHandle, PANEL_TIMER, &t2);
            if(t2 -t1>= dt)
			{
				clear();
				color =0;
				
		    }
			
		 
	
}


void game_over()
{
MessagePopup ("Game Over", "Game Over");
init();
SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);

for(int j=0;j<1000;j++){
steps_arr[j]= 0 ;
  user_arr[j] = 0 ;
  }

   SetCtrlAttribute (panel2, PANEL_2_STRING2, ATTR_VISIBLE, 1);
   SetCtrlAttribute (panel2, PANEL_2_PICTUREBTN, ATTR_VISIBLE, 1);
  DisplayPanel (panel2);

   ReadTable();
   WriteTable();
}

void check()
{

for(int q=0; q<computer_index; q++)
{
if(user_arr[q] != steps_arr[q])
	game_over();
	
}

}

void grill()
{
	
	
steps_arr[computer_index ] = 1+ rand()%4;
 computer_index++;
	
}


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Simon Game.uir", PANEL)) < 0)
		return -1;
	
	if ((panel2 = LoadPanel (0, "Simon Game.uir", PANEL_2)) < 0)
		return -1;
	
	if ((panel3 = LoadPanel (0, "Simon Game.uir", PANEL_3)) < 0)
		return -1;
	
	InitMP3s(); //connecting to sound files 
	init();
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	DiscardPanel (panel2);	
	DiscardPanel (panel3);
	ReleaseMP3s(); //Releaseing MP3 streams
	return 0;
}

int CVICALLBACK exitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK timerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{ 

	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			if(turn == 'C')
			{
			SetCtrlAttribute (panelHandle, PANEL_STRING, ATTR_CTRL_VAL, "Computer Turn");

			GetCtrlVal (panelHandle, PANEL_TIMER, &t3);
			if(t3 - t4 >= dt && board_drawed == 0){
				draw();
				board_drawed = 1;
				i++;

			
			}    
					  				 
			else if (t3 - t4 >= 3* dt && board_drawed == 1){
				clear() ;
				board_drawed = 0 ;
				t4 = t3;
			}
	

			
				 
			if( i == computer_index +1  )
			{  
			turn = 'Y';
			color = 0;
			i=0;
		
			}

			}
			
			
			if(turn == 'Y')
			{
		    	SetCtrlAttribute (panelHandle, PANEL_STRING, ATTR_CTRL_VAL, "Your Turn");

				  
				 draw2();
				 
			
			      if(click == 1)
			     {
			      click = 0;
				 
				  	  user_arr[user_index] = color;
					  color=0;
					  if(user_arr[user_index] != steps_arr[user_index])
						  game_over();
					  
					  user_index++;
					  
					  if(user_index == computer_index)
					  {
						user_index = 0;

					    turn = 'C';
						
						
						grill();
					  }
					  
				}
				
				
				
				
			 }
	}
			
	
	
	return 0;
}

int CVICALLBACK playFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			 BASS_ChannelPlay(START_SND,TRUE);
			 SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			
			break;
	}
	return 0;
}

int CVICALLBACK musicFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK canvasFunc (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
		switch(event)
		{
case EVENT_LEFT_CLICK:
case EVENT_LEFT_DOUBLE_CLICK:
		

	//player = Y    computer = C
	if(user_index == 0)
		SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
	
				if(turn == 'Y' )
				{
				if(eventData2>left1 &&   eventData2 < right1)
					if(eventData1 > top1 && eventData1  < bottom1)
					{
						color=1;
			
					}
				  if(eventData2>left2 &&   eventData2 < right2)
					if(eventData1 > top2 && eventData1  < bottom2)
					{
						color=2;
					
					}
				
				 if(eventData2>left3 &&   eventData2 < right3)
					if(eventData1 > top3 && eventData1  < bottom3)
					{
						color=3;
					
					}						
						
				
				 if(eventData2>left4 &&  eventData2 < right4)
					if(eventData1 > top4 && eventData1  < bottom4)
					{
						color=4;
					
					} 
				 click = 1;
					}
					
					
			
		 break;
		}
	return 0;
}

int CVICALLBACK RECORD (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			   ReadTable();
			   WriteTable();
				
				DisplayPanel (panel2);
			break;
	}
	return 0;
}

int CVICALLBACK mute_func (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				 GetCtrlVal (panelHandle, PANEL_MUTE, &mute);
				 
				 
				 BASS_ChannelSetAttribute(START_SND, BASS_ATTRIB_VOL, mute);
				 BASS_ChannelSetAttribute(DO_SND, BASS_ATTRIB_VOL, mute);
				 BASS_ChannelSetAttribute(RE_SND, BASS_ATTRIB_VOL, mute);
				 BASS_ChannelSetAttribute(MI_SND, BASS_ATTRIB_VOL, mute);
				 BASS_ChannelSetAttribute(FA_SND, BASS_ATTRIB_VOL, mute);
				
				  
				 
			break;
	}
	return 0;
}

int CVICALLBACK exitFunc2 (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
				 HidePanel (panel2);
			break;
	}
	return 0;
}

int CVICALLBACK btn_score (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

		newScore = computer_index;
			
		       ReadTable();
				SetInTable();
			     WriteTable();
				  ReadTable();
			break;
	}
	return 0;
}

int CVICALLBACK aboutFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 	DisplayPanel (panel3);
				break;
	}
	return 0;
}

int CVICALLBACK exitfunc3 (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panel3);
			break;
	}
	return 0;
}

int CVICALLBACK howTofunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   OpenDocumentInDefaultViewer ("c:\\Users\\yoavs\\Desktop\\Simon Game\\instruction.pdf", VAL_NO_ZOOM);
			break;
	}
	return 0;
}

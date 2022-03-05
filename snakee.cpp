#include<stdio.h>
#include<windows.h>
#include<commctrl.h>
#include<time.h>
#define NUM 200
#define Size 80 //圖標占用的位置 寬高80 
struct{int x , y;} Vector;
POINT position[NUM],foodposition;
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE prehinstance,LPSTR lpCmdLine, int mShowCmd){
	srand(time(0));
	HWND hProgmanager = FindWindowA("Progman","Program Manager");
	HWND hShellDll = FindWindowExA(hProgmanager,0,"SHELLDLL_DefView",NULL);
	HWND DesktopHwnd =  FindWindowExA(hShellDll,0,"SysListView32","FolderView");
	ShowWindow(DesktopHwnd,SW_HIDE);//隱藏所有桌面 圖標 
	//ShowWindow(DesktopHwnd,SW_NORMAL);//顯示 
	int icount = SendMessageA(DesktopHwnd,LVM_GETITEMCOUNT,0,0);//多少桌面圖標 
	int screenx = GetSystemMetrics(SM_CXSCREEN);//1920
	int screeny = GetSystemMetrics(SM_CYSCREEN);//1080
	int eatCount = 0;//吃到幾個 
	//圖標挪走
	for(int i = 0;i<icount;i++){
	SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,i,(screeny<<16)+screenx);}
	//長寬參數:一個32位數據 16x 16y
	//1 0000 0000 0000 0000 0000 0000 0000 0001
	//2 0000 0000 0000 0000 0000 0000 0000 0010 
	//合成0000 0000 0000 0001 0000 0000 0000 0010
		ShowWindow(DesktopHwnd,SW_NORMAL);
		position[0].x = rand()%(screenx / Size)*Size ;//0 80 160 320 400 ... //蛇頭
		position[0].y = rand()%(screeny / Size)*Size ;
		
	
		foodposition.x = rand()%(screenx / Size)*Size ;
		foodposition.y = rand()%(screeny / Size)*Size ;
		SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,0,(position[0].y<<16)+position[0].x);
		SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,1,(foodposition.y<<16)+foodposition.x);
		Vector.x=1,Vector.y=0;
		while(1){
			if(GetAsyncKeyState(VK_UP)!=0){
				Vector.x= 0,Vector.y = -1;
			}//按上向上 
			if(GetAsyncKeyState(VK_DOWN)!=0){
				Vector.x= 0,Vector.y = +1;
			}
			if(GetAsyncKeyState(VK_LEFT)!=0){
				Vector.x= -1,Vector.y = 0;
			}
			if(GetAsyncKeyState(VK_RIGHT)!=0){
				Vector.x= +1,Vector.y= 0;
			}
			for(int i=0 ; i<eatCount+1;i++){
				
				if(i == icount){
					return -1;
				}
				else if(eatCount-i==0){
					position[0].x += Vector.x*Size;
					position[0].y += Vector.y*Size;
					SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,0,(position[0].y<<16)+position[0].x);
				}
				else {
					position[eatCount-i].x = position[eatCount-i-1].x ;
					position[eatCount-i].y = position[eatCount-i-1].y ;
					SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,eatCount-i,(position[eatCount-i].y<<16)+position[eatCount-i].x);
				}
			
				if(position[0].x==foodposition.x&&position[0].y==foodposition.y){
						eatCount++;
						position[eatCount].x = foodposition.x ;
						position[eatCount].y = foodposition.y ;
						foodposition.x = rand()%(screenx / Size)*Size ;
						foodposition.y = rand()%(screeny / Size)*Size ;
						if(foodposition.x<100||foodposition.y<100||foodposition.x>screenx-100||foodposition.y>screeny-100){
							foodposition.x =0 ;//rand()%((screenx)/ Size)*Size;
							foodposition.y =0;//rand()%((screeny-100) / Size)*Size;
						}
						SendMessageA(DesktopHwnd,LVM_SETITEMPOSITION,eatCount+1,(foodposition.y<<16)+foodposition.x);
						
				}
				if(position[0].x<0){
					position[0].x=0;
				}
				if(position[0].y<0){ 
					position[0].y=0;
				}
				if (position[0].x>screenx){
					position[0].x=screenx;
				}
				if(position[0].y>screeny){
					position[0].y=screeny;
				}
				if(eatCount >= icount){
					break;
				}
			
				
				
			}
			Sleep(200);
		} 
}

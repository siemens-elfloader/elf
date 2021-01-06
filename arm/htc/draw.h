char co1ba[]={0,0,0,20};
char co1ba2[]={40,0,40,10};
char colba23[]={210,215,219,255};
char colba24[]={160,165,169,255};
void RedrawIconbar(void){
char cl2[]={0xFF,0xFF,0xFF,0x37};
char cl3[]={0xFF,0xFF,0xFF,0x57};
char cl4[]={0xFF,0xFF,0xFF,0xFF};
net_sdvig_w = 4;
net_sdvig_h = 3;
bat_sdvig_w = -25;
bat_sdvig_h = 1;
bt_sdvig_w = 0;
bt_sdvig_h = 0;
snd_sdvig_w = 0;
snd_sdvig_h = 0;


    DrwPngImg(FImage7, 0, -1); //Подложка под иконбар
//==================================================================================== ПЕРЕРИСОВКА СЕТИ ========================
if (network > 0) {DrawRoundedFrame(216+net_sdvig_w,15+net_sdvig_h,217+net_sdvig_w,17+net_sdvig_h,0,0,0,cl4,cl4);}
else DrawRoundedFrame(216+net_sdvig_w,15+net_sdvig_h,217+net_sdvig_w,17+net_sdvig_h,0,0,0,cl2,cl2);
if (network > 6) {DrawRoundedFrame(219+net_sdvig_w,12+net_sdvig_h,220+net_sdvig_w,17+net_sdvig_h,0,0,0,cl4,cl4);}
else DrawRoundedFrame(219+net_sdvig_w,12+net_sdvig_h,220+net_sdvig_w,17+net_sdvig_h,0,0,0,cl2,cl2);
if (network > 12) {DrawRoundedFrame(222+net_sdvig_w,9+net_sdvig_h,223+net_sdvig_w,17+net_sdvig_h,0,0,0,cl4,cl4);}
else DrawRoundedFrame(222+net_sdvig_w,9+net_sdvig_h,223+net_sdvig_w,17+net_sdvig_h,0,0,0,cl2,cl2);
if (network > 18) {DrawRoundedFrame(225+net_sdvig_w,6+net_sdvig_h,226+net_sdvig_w,17+net_sdvig_h,0,0,0,cl4,cl4);}
else DrawRoundedFrame(225+net_sdvig_w,6+net_sdvig_h,226+net_sdvig_w,17+net_sdvig_h,0,0,0,cl2,cl2);
if (network > 24) {DrawRoundedFrame(228+net_sdvig_w,3+net_sdvig_h,229+net_sdvig_w,17+net_sdvig_h,0,0,0,cl4,cl4);}
else DrawRoundedFrame(228+net_sdvig_w,3+net_sdvig_h,229+net_sdvig_w,17+net_sdvig_h,0,0,0,cl2,cl2);

DrawRoundedFrame(215+net_sdvig_w,12+net_sdvig_h,216+net_sdvig_w,9+net_sdvig_h,0,0,0,cl4,cl4);
DrawLine(211+net_sdvig_w,5+net_sdvig_h,214+net_sdvig_w,8+net_sdvig_h,0,cl4);
DrawLine(211+net_sdvig_w,4+net_sdvig_h,215+net_sdvig_w,8+net_sdvig_h,0,cl4);
DrawLine(220+net_sdvig_w,4+net_sdvig_h,216+net_sdvig_w,8+net_sdvig_h,0,cl4);
DrawLine(220+net_sdvig_w,5+net_sdvig_h,217+net_sdvig_w,8+net_sdvig_h,0,cl4);

DrawLine(211+net_sdvig_w,3+net_sdvig_h,216+net_sdvig_w,8+net_sdvig_h,0,cl3);
DrawLine(220+net_sdvig_w,3+net_sdvig_h,215+net_sdvig_w,8+net_sdvig_h,0,cl3);


DrawRoundedFrame(211+net_sdvig_w,2+net_sdvig_h,220+net_sdvig_w,3+net_sdvig_h,0,0,0,cl4,cl4);
//=================================================================================== /ПЕРЕРИСОВКА СЕТИ ========================
//==================================================================================== ПЕРЕРИСОВКА БАТАРЕИ =====================



if (battery > 80) DrawRoundedFrame(231+bat_sdvig_w,9+bat_sdvig_h,232+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl4,cl4 ); else DrawRoundedFrame(231+bat_sdvig_w,9+bat_sdvig_h,232+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl2,cl2 );
if (battery > 55) DrawRoundedFrame(228+bat_sdvig_w,9+bat_sdvig_h,229+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl4,cl4 ); else DrawRoundedFrame(228+bat_sdvig_w,9+bat_sdvig_h,229+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl2,cl2 );
if (battery > 30) DrawRoundedFrame(225+bat_sdvig_w,9+bat_sdvig_h,226+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl4,cl4 ); else DrawRoundedFrame(225+bat_sdvig_w,9+bat_sdvig_h,226+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl2,cl2 );
if (battery > 5 ) DrawRoundedFrame(222+bat_sdvig_w,9+bat_sdvig_h,223+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl4,cl4 ); else DrawRoundedFrame(222+bat_sdvig_w,9+bat_sdvig_h,223+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl2,cl2 );


DrawRoundedFrame(218+bat_sdvig_w,6+bat_sdvig_h,232+bat_sdvig_w,7+bat_sdvig_h,0,0,0, cl4,cl4 );  //верхняя полоска
DrawRoundedFrame(218+bat_sdvig_w,9+bat_sdvig_h,219+bat_sdvig_w,7+bat_sdvig_h,0,0,0, cl4,cl4 );  //левая сторона батареи (Верх)
DrawRoundedFrame(216+bat_sdvig_w,9+bat_sdvig_h,217+bat_sdvig_w,15+bat_sdvig_h,0,0,0, cl4,cl4 ); //левая сторона батареи (серцевина)
DrawRoundedFrame(218+bat_sdvig_w,15+bat_sdvig_h,219+bat_sdvig_w,17+bat_sdvig_h,0,0,0, cl4,cl4 ); //левая сторона батареи (Низ)
DrawRoundedFrame(218+bat_sdvig_w,18+bat_sdvig_h,232+bat_sdvig_w,17+bat_sdvig_h,0,0,0, cl4,cl4 );  //нижняя полоска




//=================================================================================== /ПЕРЕРИСОВКА БАТАРЕИ =====================


int *Ring=(int*)RamRingtoneStatus();


   if (*Ring==1) DrwPngImg(SetIco[44], 169+snd_sdvig_w, 6+snd_sdvig_h);
   else DrwPngImg(SetIco[42], 169+snd_sdvig_w, 6+snd_sdvig_h);



        if(GetPeripheryState(0,1)||GetPeripheryState(0,2))
        {
            DrwPngImg(SetIco[41], 149+bt_sdvig_w, 5+bt_sdvig_h);
        }
        else if(GetPeripheryState(0,4))
        {
            DrwPngImg(SetIco[37], 145+bt_sdvig_w, 5+bt_sdvig_h);

        }

}






 void MenuOnRedraw(MAIN_GUI *data)
{if (menulanch){
	if (IsUnlocked()){

int wswidth = 0;
int wsheight = 0;

if (xxl==-1 || xxl==25 || xxl==52 || xxl==79 || xxl==105 || xxl==131 || xxl==158 || xxl==183 || xxl==210 || xxl==235 ) {dovodka=0; }
if ((xxl==-1 && aLeft == 1)|| (xxl==235 && aRight == 1)) pres = 0;

    void *canvasdata=BuildCanvas();
    WSHDR * ws = AllocWS( 256 );

if (draw_net==1) {RedrawIconbar();if (draw_body==0) {if (supermod == StartMenu || supermod == StartSubMenu) {DrwPngImg(FImage10, 0, 0);}}}//Рисуем белый 'Пуск'
if (draw_body==1) {

//========================>>>>> supermod == 0 ======================================================================================
if (supermod == 0 || draw_all==1 || supermod == NumberMenu) {
    int ol = 257;

 if (pres == 0 && dovodka == 0) { //рисуется один раз при отображении новой вкладки
	if (SetCursor == 0 || SetExitMenu == 1) {
		DrwPngImg(Wall_0, 0, 0);
	}
	if (SetCursor == 0  || SetExitMenu == 1) {
		DrwPngImg(FImage6, 0, 25); //Подложка под название раздела
	}
    DrwPngImg(Wall_1, 0, 56);
    if (supermod != NumberMenu) drawmod(currentIco);
	if (SetCursor == 0  || SetExitMenu == 1) {
		RedrawIconbar();
	}
    //wsprintf (ws, "mod: %i", currentIco); DrawString( ws, 10,  3,  230, 24, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
 }
 if (pres == 0 && dovodka == 0){
	if ((SetCursor == 0 && currentIco != 4) || SetExitMenu == 1 ) {            // рисуем попап..
	//================= Popup ===============================================================================================================
		if (show_popup == 1) {DrawRectangle( 70, 32, 238,95, 0, co24mod, co25); DrawString( ussdws, 70, 32, 238,95, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );}
		wswidth = Get_WS_width(ussdws, 8);
		wsheight = (((wswidth/160)+1)*16+16)/2;
		if (show_ussd == 1) {DrawRectangle( 20, 155-wsheight, 220, 165+wsheight, 0, co24mod, co25sd);
		DrawString( ussdws, 30, 165-wsheight, 210, 155+wsheight, 8, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
	}
	//=======================================================================================================================================
 }
}

    if ((SetCursor == 0 || SetExitMenu == 1) && (!(Adr_Cur!=0 && currentIco ==1) || SetExitMenu == 1)){
	DrwPngImg(Wall_2, 0, 240);
    dovodka = 0;
    DrwPngImg(FImage1, -4-xxl, ol);			 //нижняя панель иконок с прокруткой
    DrwPngImg(FImage2, 0+xxl/1.32, ol-8);
    DrwPngImg(Ico[currentIco], 14+xxl/1.32, ol-4);    }
    omenu = 0;

if(int_settings[24]==1){
DrawRectangle( 0, 193, 194,294, 0,  co22, co25mod);
DrawRectangle( 1, 198, 193,219, 0, GetPaletteAdrByColorIndex( 23 ),co22);
ascii2ws(ws, "Приветcтвие!");     DrawString( ws, 7,  200,  150, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
if((275-(xxl*3))<250) DrwPngImg(SetIco[14], 7, 279-(xxl*3));
else DrwPngImg(SetIco[14], 7, 229+(xxl*3));
ascii2ws(ws, "Начни работу с длинного нажатия левого софта. В этом  меню  ты  сможешь найти  раздел  помощи.");
DrawString( ws, 35,  223,  194, 320, 10, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
}

}
//========================>>>>> supermod == startmenu  ======================================================================================


if (supermod == StartMenu || supermod == StartSubMenu) {

DrawRectangle( 0, 26, 160,58, 0, co25mod, co25mod);
for (int i=1; i<itemcount+1; i++){DrawRectangle( 0, 30+28*(i), 160,30+28*(i+1), 0, co25mod, co25mod);}
if (((zxmain_Y == 0) && (zxmain_X == 0)) || draw_all==1) DrwPngImg(FImage10, 0, 0); //Рисуем белый 'Пуск'
if (zxmain_Y) DrwPngImg(SetIco[10], -22, 30+28*zxmain_Y); //Курсор
for (int i=1; i<itemcount+1; i++){
	   if (menu_ico_true[i]==1){DrwPngImg(menu_ico[i], 4, 61+28*(i-1));}
    if (menu_name_true[i] == 1) {
		ascii2ws(ws, menu_name[i]);
		DrawString( ws, 36,  63+28*(i-1),  140, 320, 9, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
		if (menu_type[i]==2){
			ascii2ws(ws, ">");
			DrawString( ws, 145,  63+28*(i-1),  160, 320, 9, 1, co22, GetPaletteAdrByColorIndex( 23 ) );
		}}
	DrawLine(1,85+28*(i-2),160,85+28*(i-2),1,co22x);
}
DrawRectangle( 0, 296, 240,320, 1, co27, co27);
if (zxmain_Y) {ascii2ws(ws, "Опции"); DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );}
ascii2ws(ws, "Закрыть"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
 if(menu_state == 0) {  DrwPngImg(SetIco[23], 8, 30);
	DrwPngImg(SetIco[19], 8+30*1, 30);
	DrwPngImg(SetIco[20], 8+30*2, 30);
	DrwPngImg(SetIco[21], 8+30*4, 30);
	DrwPngImg(SetIco[22], 8+30*3, 30);}
else {
	ascii2ws(js, menu_name[0]);
	DrawString( js, 15,  30,  160, 80, 7, 1, co22, GetPaletteAdrByColorIndex( 23 ) );
	}
}

//========================>>>>> supermod == StartSubMenu ======================================================================================
if (supermod == StartSubMenu) {

DrawRectangle( 145, 193, 239,294, 0,  co22, co25mod);
DrawRectangle( 145, 198+(SubMenuCursor*25), 239,219+(SubMenuCursor*25), 0, GetPaletteAdrByColorIndex( 23 ),co22);
ascii2ws(ws, "Изменить");     DrawString( ws, 152,  200,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "Создать");      DrawString( ws, 152,  225,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "Удалить");      DrawString( ws, 152,  250,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "Обновить TF");  DrawString( ws, 152,  275,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
	}


//========================>>>>> supermod == NumberMenu  ======================================================================================
if (supermod == NumberMenu) {


DrawRectangle( 0, 296, 240,320, 1, co27, co27);
ascii2ws(ws, "Набор номера"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "Закрыть"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "<С");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
wsprintf (ws, "%s", CNumber); DrawString( ws, 20,  90,  220, 270, 1, 1, co21, GetPaletteAdrByColorIndex( 23 ) );

/*char CNumber[256];
int CCursor=0;
int CCursorCount=0;
int CCursorVisible=1;*/

	}




//======================== End Body  ======================================================================================
}
DisableIconBar(1);
draw_all=0;
SetExitMenu = 0;
draw_net=0;draw_body=0;
//wsprintf (ws, "Ыыыыы.."); DrawString( ws, 50,  50,  230, 240, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
FreeWS(ws);
}

else DrawRectangle( 0, 0, 239,319, 0,  co25black, co25black);
}

}

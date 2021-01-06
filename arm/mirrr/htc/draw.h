//char colors[2][]={0xFF,0xFF,0xFF,0x37}; //ПЕРЕРИСОВКА СЕТИ
//char colors[0][]={0xFF,0xFF,0xFF,0x57}; //ПЕРЕРИСОВКА СЕТИ
//char colors[2][]={0xFF,0xFF,0xFF,0xFF}; //ПЕРЕРИСОВКА СЕТИ И БАТАРЕИ
extern WSHDR * name_call[5];

//=========================================================================================================================================
//=========================================================================================================================================
void RedrawIconbar(void){
         if(MD6){
         battery = *RamCap();
         net_data=RamNet();
    network = ((110-net_data->power)/2);
    net_sdvig_w = 4;
    net_sdvig_h = 3;
    bat_sdvig_w = -25;
    bat_sdvig_h = 1;
    bt_sdvig_w = 0;
    bt_sdvig_h = 0;
    snd_sdvig_w = 0;
    snd_sdvig_h = 0;
    DrawRoundedFrame(0,0,240,26,0,0,0,colors[1],colors[1]);
    DrwPngImg(FImage7, 0, -1);                                                            //Подложка под иконбар
    if (supermod == StartMenu || supermod == StartSubMenu ) {DrwPngImg(FImage10, 0, 0);}   //Рисуем белый 'Пуск'

    //==================================================================================== ПЕРЕРИСОВКА СЕТИ ========================
    if (network > 0) {DrawRoundedFrame(216+net_sdvig_w,15+net_sdvig_h,217+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[2],colors[2]);}
    else DrawRoundedFrame(216+net_sdvig_w,15+net_sdvig_h,217+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[0],colors[0]);
    if (network > 6) {DrawRoundedFrame(219+net_sdvig_w,12+net_sdvig_h,220+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[2],colors[2]);}
    else DrawRoundedFrame(219+net_sdvig_w,12+net_sdvig_h,220+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[0],colors[0]);
    if (network > 12) {DrawRoundedFrame(222+net_sdvig_w,9+net_sdvig_h,223+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[2],colors[2]);}
    else DrawRoundedFrame(222+net_sdvig_w,9+net_sdvig_h,223+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[0],colors[0]);
    if (network > 18) {DrawRoundedFrame(225+net_sdvig_w,6+net_sdvig_h,226+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[2],colors[2]);}
    else DrawRoundedFrame(225+net_sdvig_w,6+net_sdvig_h,226+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[0],colors[0]);
    if (network > 24) {DrawRoundedFrame(228+net_sdvig_w,3+net_sdvig_h,229+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[2],colors[2]);}
    else DrawRoundedFrame(228+net_sdvig_w,3+net_sdvig_h,229+net_sdvig_w,17+net_sdvig_h,0,0,0,colors[0],colors[0]);

    DrawRoundedFrame(215+net_sdvig_w,12+net_sdvig_h,216+net_sdvig_w,9+net_sdvig_h,0,0,0,colors[2],colors[2]);
    DrawLine(211+net_sdvig_w,5+net_sdvig_h,214+net_sdvig_w,8+net_sdvig_h,0,colors[2]);
    DrawLine(211+net_sdvig_w,4+net_sdvig_h,215+net_sdvig_w,8+net_sdvig_h,0,colors[2]);
    DrawLine(220+net_sdvig_w,4+net_sdvig_h,216+net_sdvig_w,8+net_sdvig_h,0,colors[2]);
    DrawLine(220+net_sdvig_w,5+net_sdvig_h,217+net_sdvig_w,8+net_sdvig_h,0,colors[2]);

    DrawLine(211+net_sdvig_w,3+net_sdvig_h,216+net_sdvig_w,8+net_sdvig_h,0,colors[2]);
    DrawLine(220+net_sdvig_w,3+net_sdvig_h,215+net_sdvig_w,8+net_sdvig_h,0,colors[2]);
    DrawRoundedFrame(211+net_sdvig_w,2+net_sdvig_h,220+net_sdvig_w,3+net_sdvig_h,0,0,0,colors[2],colors[2]);
    //=================================================================================== /ПЕРЕРИСОВКА СЕТИ ========================
    //==================================================================================== ПЕРЕРИСОВКА БАТАРЕИ =====================
    if (battery > 80) DrawRoundedFrame(231+bat_sdvig_w,9+bat_sdvig_h,232+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[2],colors[2] );
    else DrawRoundedFrame(231+bat_sdvig_w,9+bat_sdvig_h,232+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[0],colors[0] );
    if (battery > 55) DrawRoundedFrame(228+bat_sdvig_w,9+bat_sdvig_h,229+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[2],colors[2] );
    else DrawRoundedFrame(228+bat_sdvig_w,9+bat_sdvig_h,229+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[0],colors[0] );
    if (battery > 30) DrawRoundedFrame(225+bat_sdvig_w,9+bat_sdvig_h,226+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[2],colors[2] );
    else DrawRoundedFrame(225+bat_sdvig_w,9+bat_sdvig_h,226+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[0],colors[0] );
    if (battery > 5 ) DrawRoundedFrame(222+bat_sdvig_w,9+bat_sdvig_h,223+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[2],colors[2] );
    else DrawRoundedFrame(222+bat_sdvig_w,9+bat_sdvig_h,223+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[0],colors[0] );
    DrawRoundedFrame(218+bat_sdvig_w,6+bat_sdvig_h,232+bat_sdvig_w,7+bat_sdvig_h,0,0,0, colors[2],colors[2] );  //верхняя полоска
    DrawRoundedFrame(218+bat_sdvig_w,9+bat_sdvig_h,219+bat_sdvig_w,7+bat_sdvig_h,0,0,0, colors[2],colors[2] );  //левая сторона батареи (Верх)
    DrawRoundedFrame(216+bat_sdvig_w,9+bat_sdvig_h,217+bat_sdvig_w,15+bat_sdvig_h,0,0,0, colors[2],colors[2] ); //левая сторона батареи (серцевина)
    DrawRoundedFrame(218+bat_sdvig_w,15+bat_sdvig_h,219+bat_sdvig_w,17+bat_sdvig_h,0,0,0, colors[2],colors[2] ); //левая сторона батареи (Низ)
    DrawRoundedFrame(218+bat_sdvig_w,18+bat_sdvig_h,232+bat_sdvig_w,17+bat_sdvig_h,0,0,0, colors[2],colors[2] );  //нижняя полоска
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
       DrwPngImg(SetIco[37], 145+bt_sdvig_w, 5+bt_sdvig_h);  //27.png
    }
 }
}


void correctDraw(){if (!(supermod == StartMenu || supermod == StartSubMenu) || playdrawmod==1){
          if (SetCursor == 0 || SetExitMenu == 1){DrawRectangle( 0, 26, 240,55, 1, colors[5], colors[5]); DrwPngImg(Wall_0, 0, 26); }       //Часть обоины (верхняя)
	if ((SetCursor == 0 || SetExitMenu == 1)&& currentIco!=4){if (FImage6->bpnum == 10){DrwPngImg(FImage6,0,25);} else DrawRectangle( -1, 26, 241,55, 1, colors[24], colors[6]);}    //Подложка под название раздела
	DrawRectangle( 0, 56, 240,242, 1, colors[5], colors[5]); DrwPngImg(Wall_1, 0, 56);                                                 //Перерисовываем кусок обоины под содержимым
          if (supermod != NumberMenu && supermod != ExitMenu && supermod != CallMenu) {
			  drawmod(currentIco); //функция перерисовки содержимого вкладки
			  chips.name_to="XTask4";
			  chips.name_from="Shell";
              chips.data=0;
              GBS_SendMessage(MMI_CEPID,MSG_IPC,currentIco,&chips);
			  
		  }
		  if (SetCursor == 0  || SetExitMenu == 1) RedrawIconbar();}
}



//=========================================================================================================================================
//======================================================   MenuOnRedraw   =================================================================

char fi5[4]={240,80,140,40};
char fi6[4]={56,156,241,40};

 void MenuOnRedraw(MAIN_GUI *data){
   
   
   if (menulanch && lui_bob>0 && lui_bob<10){
     DisableIconBar(1);
     DrawRectangle( 18, 142, 220,169, 0,  cfg222_ID, co25black);
     for(int i=1;i<=lui_bob;i++) {
               //drawArc(i*22, -4+150, i*22+18, -4+150+18,  0, 360, 0, fi6, fi6);
       DrawRectangle( i*22, 144, i*22+18,167, 0, fi6, fi6);
     }

     

   }
   
   
   
   
   if (menulanch && lui_bob==10){   //Если мы еще живы
        MString str11;
    if (IsUnlocked()){ //Если разблокированы
    int wswidth = 0;     //Размер строки сообщения в ширину (Popup)
    int wsheight = 0;    //Размер строки сообщения в высоту (очень примерный) (Popup)
    MString str11;
    if (xxl==stop9[0] || xxl==stop9[1] || xxl==stop9[2] || xxl==stop9[3] || xxl==stop9[4] || xxl==stop9[5] || xxl==stop9[6] || xxl==stop9[7] || xxl==stop9[8] || xxl==stop9[9] ) {dovodka=0; }
    if ((xxl==-1 && aLeft == 1)|| (xxl==stop8 && aRight == 1)) pres = 0; // Таблица с точками останова нижних салазок и сброс переменной -
                                                                       // датчика нажатий

    void *canvasdata=BuildCanvas();
    WSHDR * ws = AllocWS( 512 );      // Буфер для вывода текста
    if (draw_net==1) RedrawIconbar(); // Иконбар и все остальное - перерисовываются отдельно, есть две переменных, по которым определяем,
    if (draw_body==1) {               // что перерисовывать

//========================>>>>> supermod == 0 ======================================================================================
if (supermod == 0 || draw_all==1 || supermod == NumberMenu ||  ExitMenu) if (!(supermod == StartMenu || supermod == StartSubMenu) || playdrawmod==1){
    int ol = 257;

 if (!pres  && !dovodka    && !aLeft && !aRight ) {                                                 //рисуется один раз при отображении новой вкладки

        if (SetCursor == 0 || SetExitMenu == 1){



DrawRectangle( 0, 26, 240,55, 1, colors[5], colors[5]);
DrwPngImg(Wall_0, 0, 26); }       //Часть обоины (верхняя)

//---------------------------------------------------------------------------------------------------------
if ((SetCursor == 0 || SetExitMenu == 1)&& currentIco!=4){
if (FImage6->bpnum == 10)DrwPngImg(FImage6,0,25); else DrawRectangle( -1, 25, 241,55, 1, colors[24], colors[6]);


	}    //Подложка под название раздела




DrawRectangle( 0, 56, 240,242, 1, colors[5], colors[5]); DrwPngImg(Wall_1, 0, 56);                                                 //Перерисовываем кусок обоины под содержимым
        if (supermod != NumberMenu && supermod != ExitMenu && supermod != CallMenu ) {
			  drawmod(currentIco); //функция перерисовки содержимого вкладки
			  chips.name_to="XTask4";
			  chips.name_from="Shell";
              chips.data=0;
              GBS_SendMessage(MMI_CEPID,MSG_IPC,currentIco,&chips);
			  
		  }
	if (SetCursor == 0  || SetExitMenu == 1) RedrawIconbar();
 }








 if (pres == 0 && dovodka == 0){
	if ((SetCursor == 0 && currentIco != 4) || SetExitMenu == 1 ) {            // рисуем попап..
	//================= Popup ===============================================================================================================
		if (show_popup == 1) {DrawRectangle( 70, 32, 238,95, 0, co24mod, co25); DrawString( ussdws, 70, 32, 238,95, 6, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );}
		wswidth = Get_WS_width(ussdws, 8);
		wsheight = (((wswidth/160)+1)*16+16)/2;
		if (show_ussd == 1) {DrawRectangle( 20, 155-wsheight, 220, 165+wsheight, 0, co24mod, co25sd);
		DrawString( ussdws, 30, 165-wsheight, 210, 155+wsheight, 8, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
	}
	//=======================================================================================================================================
 }
}

    if ((SetCursor == 0 || SetExitMenu == 1) && (!(Adr_Cur!=0 && currentIco ==1) || SetExitMenu == 1)){
 DrawRectangle( 0, 243, 240,295, 1, colors[5], colors[5]);
DrwPngImg(Wall_2, 0, 243);                       //Часть обоины (нижняя)
    dovodka = 0;
    //DrwPngImg(FImage1, -4-xxl, ol);			 //нижняя панель иконок с прокруткой
    //========================================================================================
    int sm9=0;//смещение для следующей иконки
    for (int i=0; i<10; i++){if(ust9[i]) {  DrwPngImg(PIco[i], -4-xxl+sm9, ol);
     sm9+=PIco[i]->w;}}
    for (int i=0; i<(240/PIco[10]->w); i++){DrwPngImg(PIco[10], -4-xxl+sm9, ol); sm9+=PIco[10]->w;}



//========================================================================================




sm9=0;//смещение для следующей иконки
    for (int i=0; i<10; i++){if(ust9[i]) {    //рисуем количество новых смс в кружке
    if(i==2 && allsms) {drawArc(-4-xxl+sm9+26, ol+14, -4-xxl+sm9+43, ol+21+10, 0, 360, 0, colors[31], colors[31]);
				     str11 = allsms;
				     str11.draw( -4-xxl+sm9+26,  ol+13,  -4-xxl+sm9+43, ol+21+10, 11, 3, colors[13], GetPaletteAdrByColorIndex( 23 ));
    }
    sm9+=PIco[i]->w;}}







    DrwPngImg(FImage2, int_skin[21]+xxl/1.32, ol-8+int_skin[22]);
    DrwPngImg(Ico[currentIco], int_skin[21]+int_skin[23]+14+xxl/1.32, ol-4+int_skin[22]+int_skin[24]);

     }
    omenu = 0;
//------------------------------------------------------------------------------

//======================================================================
if(int_settings[24]==1){  //всплывающее слева сообщение
DrawRectangle( 0, 193, 194,294, 0,  co22, colors[10]);
DrawRectangle( 1, 198, 193,219, 0, GetPaletteAdrByColorIndex( 23 ),co22);
str11 = "Приветcтвие!";
str11.draw( 7,  200,  150, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ));

if((275-(xxl*3))<250) DrwPngImg(SetIco[14], 7, 279-(xxl*3));
else DrwPngImg(SetIco[14], 7, 229+(xxl*3));

str11 = "Начни работу с длинного нажатия левого софта. В этом  меню  ты  сможешь найти  раздел  помощи.";
str11.draw(35,  223,  194, 320, 10, 1, co126, GetPaletteAdrByColorIndex( 23 ) );

}

if(sey==1){  //всплывающее слева сообщение
DrawRectangle( 0, 193, 194,294, 0,  co22, colors[10]);
DrawRectangle( 1, 198, 193,219, 0, GetPaletteAdrByColorIndex( 23 ),co22);
str11 = "Сообщение:";
str11.draw( 7,  200,  150, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ));





DrwPngImg(SetIco[14], 7, 245);
utf8_2ws(ws, seytext,250);
DrawString( ws, 35,  223,  194, 320, 10, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
}

if(sey==2){  //всплывающее слева сообщение
DrawRectangle( 0, 193, 194,294, 0,  co22, colors[10]);
DrawRectangle( 1, 198, 193,219, 0, GetPaletteAdrByColorIndex( 23 ),co22);

ascii2ws(ws, seytitle);     DrawString( ws, 7,  200,  150, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
DrwPngImg(SetIco[14], 7, 245);
ascii2ws(ws, seytext);
DrawString( ws, 35,  223,  194, 320, 10, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
}

}
//========================>>>>> supermod == startmenu  ======================================================================================


if (supermod == StartMenu || supermod == StartSubMenu) {

DrawRectangle( 0, 26, 160,58, 0, colors[10], colors[10]);
for (int i=1; i<itemcount+1; i++){DrawRectangle( 0, 30+28*(i), 160,30+28*(i+1), 0, colors[10], colors[10]);}
if (zxmain_Y) DrwPngImg(SetIco[10], -22, 30+28*zxmain_Y); //Курсор
for (int i=1; i<itemcount+1; i++){
	   if (menu_ico_true[i]==1){DrwPngImg(menu_ico[i], 4, 61+28*(i-1));}
    if (menu_name_true[i] == 1) {
		ascii2ws(ws, menu_name[i]);
		DrawString( ws, 36,  63+28*(i-1),  140, 320, 9, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
		if (menu_type[i]==2){
			 str11 = ">"; str11.draw( 145,  63+28*(i-1),  160, 320, 9, 1, colors[30], GetPaletteAdrByColorIndex( 23 ) );

		}}
	DrawLine(1,85+28*(i-2),160,85+28*(i-2),1,colors[12]);
}
DrawRectangle( 0, 296, 240,320, 1, co27, co27);


if (zxmain_Y) { str11 = "Опции"; str11.draw( 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );}
			  str11 = "Закрыть"; str11.draw(  10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
 if(menu_state == 0) {  DrwPngImg(SetIco[23], 8, 30);
	DrwPngImg(SetIco[19], 8+30*1, 30);
	DrwPngImg(SetIco[20], 8+30*2, 30);
	DrwPngImg(SetIco[21], 8+30*4, 30);
	DrwPngImg(SetIco[22], 8+30*3, 30);}
else {
          str11 = menu_name[0]; str11.draw( 15,  30,  160, 80, 7, 1, colors[30], GetPaletteAdrByColorIndex( 23 ) );
	}
playdrawmod=0;
}

//========================>>>>> supermod == StartSubMenu ======================================================================================
if (supermod == StartSubMenu) {

DrawRectangle( 145, 193, 239,294, 0,  colors[11], colors[10]);
DrawRectangle( 145, 198+(SubMenuCursor*25), 239,219+(SubMenuCursor*25), 0, GetPaletteAdrByColorIndex( 23 ),colors[11]);
str11 = "Изменить";  	str11.draw( 152,  200,  230, 320, 9, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Создать";   	str11.draw( 152,  225,  230, 320, 9, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Удалить";    	str11.draw( 152,  250,  230, 320, 9, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Обновить TF";	str11.draw( 152,  275,  230, 320, 9, 1, colors[29], GetPaletteAdrByColorIndex( 23 ) );
playdrawmod=0;
	}


//========================>>>>> supermod == NumberMenu  ======================================================================================
if (supermod == NumberMenu) {


DrawRectangle( 0, 296, 240,320, 1, co27, co27);
str11 = "Набор номера";	str11.draw( 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Закрыть";  		str11.draw(10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
str11 = "<С";  				str11.draw( 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
 str11 = CNumber;  		str11.draw( 20,  90,  220, 270, 1, 1, colors[26], GetPaletteAdrByColorIndex( 23 ) );

/*char CNumber[256];
int CCursor=0;
int CCursorCount=0;
int CCursorVisible=1;*/

	}

//========================>>>>> supermod == ExitMenu  ======================================================================================

if (supermod == ExitMenu) {


DrwPngImg(SetIco[5], 0, 22+37*GTY);
DrawRectangle( 0, 296, 240,320, 1, co27, co27);

         str11 = "Завершение работы";  	str11.draw(11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Ок";  					str11.draw( 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Отмена";  				str11.draw( 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Завершить сеанс";  			
         if(GTY!=2){
         str11.draw( 42,  99,  249, 320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Завершение работы оболочки";  	str11.draw( 40,  113,  249, 320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
         } else {
         str11.draw( 42,  99,  249, 320, 9, 1, colors[13], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Завершение работы оболочки";  	str11.draw( 40,  113,  249, 320, 8, 1, colors[14], GetPaletteAdrByColorIndex( 23 ) );
         }
         DrwPngImg(SetIco[2], 8, 102);
         DrawLine(0,132,239,132,1,colors[16]);
         str11 = "Перезагрузить";  				
         if(GTY!=3){
         str11.draw(42,  136,  249, 320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Перезагрузка телефона";  		str11.draw( 40,  150,  249, 320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
         } else {
         str11.draw(42,  136,  249, 320, 9, 1, colors[13], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Перезагрузка телефона";  		str11.draw( 40,  150,  249, 320, 8, 1, colors[14], GetPaletteAdrByColorIndex( 23 ) );
         }
         
         DrwPngImg(SetIco[0], 8, 139);
         DrawLine(0,169,239,169,1,colors[16]);

         str11 = "Выключить"; 
         if(GTY!=4){
         str11.draw( 42,  173,  249, 320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Выключение телефона";  		str11.draw( 40,  187,  249, 320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
         } else {
         str11.draw( 42,  173,  249, 320, 9, 1, colors[13], GetPaletteAdrByColorIndex( 23 ) );
         str11 = "Выключение телефона";  		str11.draw( 40,  187,  249, 320, 8, 1, colors[14], GetPaletteAdrByColorIndex( 23 ) );
         }

         DrwPngImg(SetIco[4], 8, 176);

}
//========================>>>>> supermod == CallMenu  ======================================================================================

if (supermod == CallMenu) {
//int countcall=0; 				- количество телефонов
//WSHDR * ucall[4]; 			- список номеров
//int scall[4]; 					- список типов номеров
//WSHDR * name_call[Adr_Cur]; 	- имя звонящего

str11 = "Выбор номера:";  		str11.draw(15,  62,  230, 87, 5, 1, colors[25], GetPaletteAdrByColorIndex( 23 ) );
DrwPngImg(SetIco[5], 0, 22+37*GTY);
DrawRectangle( 0, 296, 240,320, 1, co27, co27);
DrawString( name_call[Adr_Cur], 11,  27,  229, 320, 5, 3, colors[29], GetPaletteAdrByColorIndex( 23 ) );

str11 = "Позвонить";  					str11.draw(10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Отмена";  					str11.draw( 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
str11 = "Телефон личный";
if(scall[0]==1)str11 =  "Телефон рабочий";
if(scall[0]==2)str11 = "Мобильный личный";
if(scall[0]==3)str11 = "Мобильный рабочий";

     str11.draw( 42,  99,  229, 119, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
     DrawString( ucall[0], 42,  113,  229, 133, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[18], 6, 97);
     DrawLine(0,132,239,132,1,colors[16]);

         if(countcall>1){
	        str11 =  "Телефон рабочий";
	        if(scall[1]==2)str11 = "Мобильный личный";
	        if(scall[1]==3)str11 = "Мобильный рабочий";
	        str11.draw( 42,  136,  229, 156, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
	        DrawString( ucall[1], 42,  150,  229, 170, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
	        DrwPngImg(SetIco[18], 6, 134);

         }
         if(countcall>2){
                DrawLine(0,169,239,169,1,colors[16]);
	        str11 = "Мобильный личный";
	        if(scall[2]==3)str11 = "Мобильный рабочий";
	        str11.draw( 42,  173,  229, 193, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
	        DrawString( ucall[2], 42,  187,  229, 207, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
	        DrwPngImg(SetIco[18], 6, 171);

         }
         if(countcall>3){
            DrawLine(0,206,239,206,1,colors[16]);
	    str11 = "Мобильный рабочий";
	    str11.draw( 42,  210,  229, 230, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
	    DrawString( ucall[3], 42,  224,  229, 244, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
	    DrwPngImg(SetIco[18], 6, 208);
	    //DrawLine(0,206,239,206,1,colors[16]);
         }


	}
//======================== End Body  ======================================================================================
}
DIconbar(1);
draw_all=0;
SetExitMenu = 0;
draw_net=0;draw_body=0;
//wsprintf (ws, "%i/%i", xxl,stop8); DrawString( ws, 10,  270,  230, 320, 9, 3, colors[7], GetPaletteAdrByColorIndex( 23 ) );
if(xxl>stop8) xxl = stop8;
FreeWS(ws);
if(extblock==1) {GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);}
} else{
if(extblock==0) {
         supermod = 0;
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);

          if (GetCPUClock()>100)  SetCpuClockLow(2);
}
 tiper=0;
DrawRectangle( 0, 0, 239,319, 0,  co25black, co25black);
}

if (IsUnlocked())  extblock=0;
else extblock=1;
//===========================================
//str11 = GetCPUClock();
//str11.draw( 150,  260,  236, 320, 9, 3, colors[7], GetPaletteAdrByColorIndex( 23 ));
//if (GetCPUClock()<200)  SetCpuClockTempHi(2);
 //GetCPUClock()
//SetCpuClockLow(int);
//SetCpuClockTempHi(int);

}

}

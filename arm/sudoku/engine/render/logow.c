


int counter = -1;
int loadbar_x;
int error_logo = 0;

void LOGOW_RENDER()
{
int pngnum;
if (SCRH>SCRHM) pngnum = 30; else pngnum = 29;//-1
  
if (errs->png_file == 0 && error_logo == 0)
{  
 GBSTIMER_KOEFFICENT = 20;
  
 DrawRectangle(0,0,SCRW - 1,SCRH - 1, 0, logo_color, logo_color);
 if (SCRH>SCRHM) DrwImg((IMGHDR*)&logo_img, SCRW/2 - logo_img.w/2, SCRH/2 - logo_img.h/2, 0, 0);
            else DrwImg((IMGHDR*)&logo_img, SCRW/2 - logo_img.w/2, SCRH/2 - 2*logo_img.h/5, 0, 0);
 
 DrawStringV2(LG_LOGO_LOADTEXT, 2, 2, SCRW, SCRH, FONT_SMALL,0, black, 0); //MSG-
 
 if (SCRH>SCRHM)
  {
    if (errs->ext_file == 0x00) {DrawStringV2(LG_LOGO_EXTFILE_E0, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - logo_img.h/2, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x01) {DrawStringV2(LG_LOGO_EXTFILE_E1, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - logo_img.h/2, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x02) {DrawStringV2(LG_LOGO_EXTFILE_E2, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - logo_img.h/2, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x03) {DrawStringV2(LG_LOGO_EXTFILE_E3, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - logo_img.h/2, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x04) {DrawStringV2(LG_LOGO_EXTFILE_E4, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - logo_img.h/2, FONT_SMALL,0, red, alpha);}  //MSG-
  }
   else
  {
    if (errs->ext_file == 0x00)  {DrawStringV2(LG_LOGO_EXTFILE_E0, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - 2*logo_img.h/5, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x01)  {DrawStringV2(LG_LOGO_EXTFILE_E1, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - 2*logo_img.h/5, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x02)  {DrawStringV2(LG_LOGO_EXTFILE_E2, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - 2*logo_img.h/5, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x03)  {DrawStringV2(LG_LOGO_EXTFILE_E3, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - 2*logo_img.h/5, FONT_SMALL,0, red, alpha);}  //MSG-
    if (errs->ext_file == 0x04)  {DrawStringV2(LG_LOGO_EXTFILE_E4, 2, 2 +  GetFontYSIZE(FONT_SMALL), SCRW, SCRH/2 - 2*logo_img.h/5, FONT_SMALL,0, red, alpha);}  //MSG-
  }
 
  if (counter == -1) {counter++; goto END_LOGOW_RENDER;}
  if (counter >= 0 && counter < 28) 
   {
     dig_img[counter] = CreateIMGHDRFromPngFile(dig[counter], 3);
     
     if (dig_img[0]->w != dig_img[counter]->w || dig_img[0]->w < 3) {error_logo = 1; goto ERROR_LOGOW;}
     if (dig_img[0]->h != dig_img[counter]->h || dig_img[0]->h < 3) {error_logo = 1; goto ERROR_LOGOW;}
     if (error_logo == 0) counter++;
     
     goto END_LOGOW_RENDER;
   }
 
  if (counter ==  28) 
   {
    bgm_img = CreateIMGHDRFromPngFile(bgm, 2);
    if (bgm_img->w != SCRW || bgm_img->h != SCRH) {error_logo = 2; goto ERROR_LOGOW;}
    if (error_logo == 0) counter++;
    
    goto END_LOGOW_RENDER;
   }
    
  if (counter ==  29)
   {
     if (SCRH>SCRHM)  bgg_img = CreateIMGHDRFromPngFile(bgg, 2);
               else   bgg_img = CreateIMGHDRFromPngFile(bgg, 2);
                      if (bgg_img->w != SCRW || bgg_img->h != SCRH) {error_logo = 2; goto ERROR_LOGOW;}
                      if (error_logo == 0) counter++;
                      
                      goto END_LOGOW_RENDER; 
   }
 
  if (SCRH>SCRHM) if (counter == 30) {sudoku_img = CreateIMGHDRFromPngFile(sudoku, 3);counter++;goto END_LOGOW_RENDER;}
 
  RENDERWINDOW = 1;
  GBSTIMER_KOEFFICENT = 1;
 
END_LOGOW_RENDER:
  
  if (counter < pngnum) loadbar_x = 4 + (((counter)*(SCRW - 8))/pngnum); else loadbar_x = SCRW - 5;
  DrawRectangle(2, SCRH - 9,SCRW - 3,SCRH - 3, 0, logo_loadbar, 0);
  DrawRectangle(4, SCRH - 7, loadbar_x,SCRH - 5, 0, logo_loadbar, logo_loadbar);
  GBS_StartTimerProc(&timer,TIMER_SECOND/GBSTIMER_KOEFFICENT,REDRAW_CONTROL);
  
}
else
{
 RENDERWINDOW = -1;
 char msg[128];
 sprintf(msg,LG_LOGO_PNGERROR,errs->png_file);
 ShowMessage(msg, FONT_SMALL, MSGERROR);
}

if (error_logo > 0)
{
ERROR_LOGOW:
  
  counter++;
  RENDERWINDOW = -1;
  GBSTIMER_KOEFFICENT = 1;
  
  char msg[128];
  sprintf(msg,LG_LOGO_BGERROR,SCRW,SCRH);
  
  if (error_logo == 1) ShowMessage(LG_LOGO_CLERROR, FONT_SMALL, MSGERROR);
  if (error_logo == 2) ShowMessage(msg, FONT_SMALL, MSGERROR);
  
}


}

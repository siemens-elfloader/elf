
char load_canvas1 = 0;
char mmenu_cur = 0;
char mmenu_str[7][16]={LG_MMENU_NEWGAME,LG_MMENU_LOADGAME,LG_MMENU_CONFIG,LG_MMENU_EDITOR,LG_MMENU_HELP,LG_MMENU_ABOUT,LG_MMENU_EXIT};

#define MMENU_XA 0
#define MMENU_YA 0
#define MMENU_CT 7 //sizeof(mmenu_str)


IMGHDR *bgm_canvas_mmenu = 0;
IMGHDR *bgm_canvas_mrsoft = 0;

void MMENU_RENDER()
{
int w, h, cmy, csx;
  
  w = 8*SCRW/10 + MMENU_XA;
  h = GetFontYSIZE(bcfg_mmenu_font) + MMENU_YA;
  
  cmy = SCRH/2 - (h*MMENU_CT)/2;
  if (SCRH>SCRHM) csx = SCRW/2 - (sudoku_img->w)/2;
  
  if (load_canvas1 == 0) 
   {
     bgm_canvas_mmenu = CreateIMGHDRbyfragmentIMGHDR(bgm_img, 0, cmy, 9*SCRW/10, h*(MMENU_CT)+1);
     bgm_canvas_mrsoft = CreateIMGHDRbyfragmentIMGHDR(bgm_img, (4*SCRW)/10, SCRH - GetFontYSIZE(bcfg_sh_softfont) - 2, 6*SCRW/10, GetFontYSIZE(bcfg_sh_softfont)+1);
     load_canvas1 = 1;
   }
  
    if (TYPEREDRAW == 0)
     {
       DrwImg(bgm_img, 0, 0, 0, 0);
       if (SCRH>SCRHM) DrwImg(sudoku_img, csx, 2, 0, 0);
     }
    else
    {
      if (pravda == 1) DrawRectangle(0,0,SCRW - 1,SCRH - 1, 0, white, white);
      DrwImg(bgm_canvas_mmenu, 0, cmy, 0, 0);
      DrwImg(bgm_canvas_mrsoft, (4*SCRW)/10, SCRH - GetFontYSIZE(bcfg_sh_softfont) - 2, 0, 0);
    }
  
   for (int k = 0; k < MMENU_CT; k++) for (int i=0; i<(9*SCRW/10); i++)                           
     {   
       int a = 100 - (i*100)/(9*SCRW/10);
       
       char color[2][4]={{bcfg_mmenu_bgcol_u[0],bcfg_mmenu_bgcol_u[1],bcfg_mmenu_bgcol_u[2],a},
                         {bcfg_mmenu_bgcol_m[0],bcfg_mmenu_bgcol_m[1],bcfg_mmenu_bgcol_m[2],a}};
             
       if (k==mmenu_cur)  DrawRoundedFrame(i, cmy + k*h, i,cmy+k*h + h,0,0,0,color[1],color[1]);
                    else  DrawRoundedFrame(i, cmy + k*h, i,cmy+k*h + h,0,0,0,color[0],color[0]);
    
     }
    
    for (int k = 0; k < MMENU_CT; k++)
    {
           char t[3]="%t";
           WSHDR *ws = AllocWS(16);
           wsprintf(ws,t,mmenu_str[k]);
           DrawString(ws,2,cmy + k*h, w,cmy+ k*h+h, bcfg_mmenu_font,0,bcfg_mmenu_col,0);
           FreeWS(ws);
    }
   

    if (errs->ext_file == 0) DrawRightSoft(LG_MMENU_RSTEXT1, bcfg_sh_softfont, bcfg_sh_softcolt, bcfg_sh_softcolg);
                        else DrawRightSoft(LG_MMENU_RSTEXT2, bcfg_sh_softfont, bcfg_sh_softcolt, bcfg_sh_softcolg);
  
    GBS_StopTimer(&timer);
}


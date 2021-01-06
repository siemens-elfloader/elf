/*
* Ping-Pong 2009 - 2010
* Redraw
* (c) Danil_e71
*/

void png(int w);
void T_Load_IMG();
void DrwImg(IMGHDR *img, int x, int y);
void Game();
void RedrawScreen();
void load_lang();
void loading(int flag);
void DRE(int x, int color);
void outtextxy(char* str);
void Init();
void GetSize();
void malloclang();
void mfreelang();
void mfreeImages();
void delimghdr();
void deleteIMGHDR(IMGHDR *img);

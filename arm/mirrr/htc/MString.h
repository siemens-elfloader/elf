
class MString{
 public:
    int leni;      //������� ����� �������� ��� ������?
    char *stri; //����� ������ ���� ������!
         int pep;

    MString();
    ~MString() ;
    MString(int len);
    MString(char *str0);
    MString( const MString&  MCopy);
    MString operator+(const MString& v);
    MString operator+(char *str0);
    void operator=(char *str0);
    void operator=(const char *str0);
    void operator=(int int0);
    void operator=(float float0);
    void operator=(double double0);
    void operator=(char char0);
    void operator=(const MString&  MCopy) ;
    void print();
    void draw(int x1,int y1,int x2,int y2,int font,int text_attribute, char *Pen, char *Brush);
    void show(int x1,int y1,int x2,int y2,int font,int text_attribute, char *Pen);
};
//==========================================================================



const char proc_i[] = "%i";
const char proc_f[] = "%f";
const char proc_d[] = "%d";
const char proc_c[] = "%c";
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString::MString(){
stri = (char*)malloc(1);
leni=0;
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString::MString(int len){
stri = (char*)malloc(len+1);
leni=len;
for (int i=0; i<len;i++) stri[i]=' ';
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString::MString(char *str0){
 if (str0 && strlen(str0))  {
          leni=strlen(str0);
          stri = (char*)malloc(leni+1);
          strcpy(stri, str0);
}else {
         leni=0;
         stri = (char*)malloc(1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString::MString( const MString&  MCopy) {
    stri= (char*)realloc(stri, MCopy.leni+1);
    leni=MCopy.leni;
    strcpy(stri, MCopy.stri);
    stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString::~MString() {
if(leni!=-1) {leni=-1;mfree(stri);}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(char *str0){
 if (str0 && strlen(str0))  {
          leni=strlen(str0);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, str0);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(const char *str0){
 if (str0 && strlen(str0))  {
          leni=strlen(str0);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, str0);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(int int0){
 char pstr[40];
 sprintf( pstr, proc_i,int0);

 if (strlen(pstr))  {
          leni=strlen(pstr);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, pstr);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(float float0){
 char pstr[40];
 sprintf( pstr, proc_f,float0);

 if (strlen(pstr))  {
          leni=strlen(pstr);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, pstr);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(double double0){
 char pstr[40];
 sprintf( pstr, proc_d,double0);

 if (strlen(pstr))  {
          leni=strlen(pstr);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, pstr);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(char char0){
 char pstr[40];
 sprintf( pstr, proc_c,char0);

 if (strlen(pstr))  {
          leni=strlen(pstr);
          stri = (char*)realloc(stri , leni+1);
          strcpy(stri, pstr);
}else {
         leni=0;
         stri = (char*)realloc(stri , 1);
}
stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::operator=(const MString&  MCopy) {
    stri= (char*)realloc(stri, MCopy.leni+1);
    leni=MCopy.leni;
    strcpy(stri, MCopy.stri);
    stri[leni]=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString MString::operator+(const MString& v){
    MString t;
    t.stri= (char*)realloc(t.stri, leni+v.leni+1);
    strcpy(t.stri, stri);
    strcat(t.stri, v.stri);
    t.leni=leni+v.leni;
    t.stri[t.leni]=0;
    return t;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MString MString::operator+(char *str0){
    MString t;
    t.leni=leni+strlen(str0);
    t.stri= (char*)realloc(t.stri, t.leni+1);
    strcpy(t.stri, stri);
    strcat(t.stri, str0);
    t.stri[t.leni]=0;
    return t;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::print(){
  char zx[250]; sprintf(zx, "~ %s ",stri);
  int logfile=fopen("0:\\zbin\\Archives\\i.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  char *data=(char*)malloc(4096);
  sprintf(data,"%s\n",zx);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::draw(int x1,int y1,int x2,int y2,int font,int text_attribute, char *Pen, char *Brush){
 if (stri && leni){
    WSHDR *zabuza = AllocWS(leni);
    ascii2ws(zabuza, stri);
    if (zabuza){
           DrawString(zabuza,x1,y1,x2,y2,font,text_attribute,Pen,Brush);
           mfree(zabuza);
    }
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MString::show(int x1,int y1,int x2,int y2,int font,int text_attribute, char *Pen){
if (stri && leni){
 WSHDR *zabuza = AllocWS(leni);
 ascii2ws(zabuza, stri);
 if (zabuza){
         DrawString(zabuza,x1,y1,x2,y2,font,text_attribute,Pen,GetPaletteAdrByColorIndex( 23 ));
         mfree(zabuza);
}

}}






#define AMR_NOT_CREATED 0
#define AMR_CREATED 1
#define AMR_WRITE 2
#define AMR_STOP 3

class amr
{
    public:
    amr(char *fname,int mode,int bitrate);
    ~amr();
    int action;
    void start();
 private:
 HObj object;
};

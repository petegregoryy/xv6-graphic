struct syscall {
    int command;
    int hdc;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
};

void moveto(int hdc, int x, int y);
void setpixel(int hdc,int x, int y);
void lineto(int hdc, int x, int y);
// ABS function

#define ABS(N) ((N<0)?(-1*(N)):(N))

int abs(int N){
    if(N<0){
        return -N;
    }else{
        return N;
    }
}
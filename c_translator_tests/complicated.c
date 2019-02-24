int a;
int b;

void addToGlobal(int x, int y)
{
    int count=3;
    while(count>0){
    a = a + x;
    b = b + y;
    count = count -1;
    }
}

void setGlobal(){
    if(1<2){
        a = 1;
        if(1<2) b = 1;
    }
    else{
        a = 0;
        b = 0;
    }
}

int oprOnGlobal(){
    b = 2*b+15-14;
    a = a*b-a;
    return a+b;
}

int main()
{
	int count = 5;
	int res;
	
    setGlobal();
    
    while(count > 2){
        addToGlobal(1,1);
        if(count == 4 || count==5){
          addToGlobal(1,1);  
        }
        else{
            if(count+3 == 6) addToGlobal(3,3); 
            else addToGlobal(0,0);
        }
		count = count -1;
    }

    res = oprOnGlobal();
    if(res >0 && res< 256){
        return 0;
    }else return res;
    
}


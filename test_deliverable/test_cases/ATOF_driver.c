#include <stdlib.h>

int _ATOF();

int main(){
	return !( (_ATOF("42")==42) && (_ATOF("-5")==-5));
}

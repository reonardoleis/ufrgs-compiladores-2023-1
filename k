int a = 0;
int b = 0;
int x = 0;
int fun(int in){
	a = 5;
	b = 777;
	x = 99 + b + fun(x) + 1111;
	if (a + 0) 
	a = 555;
	if (a + 5) {
	a = 5;
} else {
	b = -666;
}
	return 0;
}


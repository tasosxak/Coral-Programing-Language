int is_prime(int x){
	
    int i=2;

	while (i<=x/2)
    {
        // condition for nonprime number
        if(x%i==0)
        {
            return 0;
        } else {}
		i = i+1;
    }
	
    return 1;
	
}

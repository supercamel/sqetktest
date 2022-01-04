function isprime(n) {
    local i, q;
    if(n <= 1){
        return false;
    }

    if(n <= 3) {
        return true;
    }

    i = 2;
    while((i*i) <= n) {
        q = n%i;
        if(q == 0) {
           return false;
        }
        i = i + 1;
    }
    return true;
}

j <- 0;
s <- "";
for(j = 0; j < 2000000; j++) {
    if(isprime(j)) {
        s = j + " is prime\n";
    }
}


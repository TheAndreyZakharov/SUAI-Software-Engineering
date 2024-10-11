function out = f1(x)
    if x < -3 || x > 0
        error("х должен лежать на интервале от -3 до 0")
    else 
        dx = 0.001;
        ep = 0.00005;
        if x < -2
            out = 0;
        elseif x < -1
            out = 0;
            for z = -2 : dx : x
                out = out + cos(z) + 1/z;
            end
            out = real (out * dx);
        else
            out = 0;
            x_n = 2 * ep;
            n = 0;
            fac = 1;
            xPow =(x+1);
            while abs(x_n) >= ep
                x_n = x / fac;
                out = out + x_n;
                n = n + 1;
                fac = fac *(2*n)*(2*n-1);
                xPow = xPow * (x+1)^(2*n);
            end
        end
    end
end

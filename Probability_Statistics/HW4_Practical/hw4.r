##4-1

x <- runif(10000)*2 - 1
y <- (runif(10000)*2*sqrt(1-(x*x))) - sqrt(1-(x*x))

plot(x,y,asp=1)

##4-2

r <- runif(10000)
theta <- runif(10000)
theta = theta * 2*pi
plot(r*cos(theta),r*sin(theta),asp=1)


##4-3


r <- runif(10000)
theta <- runif(10000)
theta = theta * 2*pi
plot(sqrt(r)*cos(theta),sqrt(r)*sin(theta),asp=1)

##8-5

y <- runif(100000)
for (i in 1:100000)
{
  sum <- 0
  x <- runif(50)
  for (j in 1:50)
  {
    sum = sum + x[j]
  }
  sum = sum / sqrt(50)
  y[i] = sum 
  
}

hist(y,breaks = 100)

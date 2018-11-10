library(ggplot2)

n = 1000
landa = 0.1

inform <- rexp(n,landa)

plot <- ggplot(data.frame(inform),aes(x=inform, y = ..count..)) + geom_histogram(alpha = 0.5, binwidth = 1, color = "gray", fill = "gray", breaks = seq(0,100,1))

plot

plot <- ggplot(data.frame(inform),aes(x=inform, y = ..count..)) + geom_density()

plot

subset(inform,inform > 10)

plot <- ggplot(data = subset(data.frame(inform), inform > 10),aes(x=inform, y = ..count..)) + geom_histogram(alpha = 0.5, binwidth = 1, color = "gray", fill = "gray", breaks = seq(0,100,1))

plot

plot <- ggplot(data = subset(data.frame(inform), inform > 10),aes(x=inform, y = ..count..)) + geom_density()

plot

n = 1000
p = 0.01

inform <- rgeom(n,p)

plot <- ggplot(data.frame(inform),aes(x=inform/10, y = ..count..)) + geom_histogram(alpha = 0.5, binwidth = 1, color = "gray", fill = "gray", breaks = seq(0,100,1))

plot

timer = 0
counter = 0
while (timer <= 480)
{
  input = rexp(1,0.1)
  timer = timer + input
  counter = counter + 1
}

inform = c(counter)
for (i in 1:999)
{
  timer = 0
  counter = 0
  while (timer <= 480)
  {
    input = rexp(1,0.1)
    timer = timer + input
    counter = counter + 1
  }
  
  s = c(counter)
  inform = c(inform,s)
}

plot <- ggplot(data.frame(inform),aes(x=inform, y = ..count..)) + geom_histogram(alpha = 0.5, binwidth = 1, color = "gray", fill = "gray", breaks = seq(0,100,1))

plot
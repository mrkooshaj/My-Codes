inform <- rnorm(10000)
inform = -pnorm(inform)
inform = inform + 1
inform = log(inform)
inform = -inform
library(ggplot2)
plot <- ggplot(data.frame(inform),aes(x=inform, y = ..count../10000)) + geom_histogram(alpha = 0.5, binwidth = 0.1, color = "gray", fill = "gray",breaks = seq(0 , 5 , 0.1))

plot

inform <- rexp(10000)
plot <- ggplot(data.frame(inform),aes(x=inform, y = ..count../10000)) + geom_histogram(alpha = 0.5, binwidth = 0.1, color = "gray", fill = "gray",breaks = seq(0 , 5 , 0.1))

plot
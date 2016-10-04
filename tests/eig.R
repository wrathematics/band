library(band)

set.seed(1234)

n <- 10
mat <- matrix(rnorm(n*n), n, n)
sym <- as.symmetric(mat)

tester <- function(test, truth)
{
  tsv <- test$vectors
  trv <- truth$vectors
  
  if (is.null(trv))
    stopifnot(is.null(tsv))
  else
  {
    # signs can differ...
    for (i in 1:ncol(tsv))
    {
      if (!isTRUE(all.equal(tsv[, i], trv[, i])))
        stopifnot(all.equal(-tsv[, i], trv[, i]))
    }
  }
}

truth <- eigen(as.matrix(sym), only.values=TRUE)
test <- eig(sym, only.values=TRUE)
tester(test, truth)

truth <- eigen(as.matrix(sym))
test <- eig(sym)
tester(test, truth)


x <- as.matrix(sym)
truth <- eigen(x)
test <- eig(x)
tester(test, truth)







n <- 11
mat <- matrix(rnorm(n*n), n, n)
x <- as.matrix(as.symmetric(mat))
truth <- eigen(x)
test <- eig(x)
tester(test, truth)

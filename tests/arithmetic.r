library(band)

x <- as.banded(matrix(1:100, 10, 10), 2, 2)

test <- zeromat(getdim(x))
stopifnot(identical(test, x*0))
stopifnot(identical(test, 0*x))

stopifnot(identical(x, x*1.0))
stopifnot(identical(x, x*1L))
stopifnot(identical(x, 1*x))

test <- 2*x
truth <- 2*getData(x)
stopifnot(identical(test, truth))

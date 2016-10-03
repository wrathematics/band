library(band)

### New methods
symtests <- function(x)
{
  test <- as.banded(as.matrix(as.symmetric(x)), 2)
  stopifnot(isSym(test))

  test <- as.banded(x, 2, 2)
  stopifnot(!isSym(test))
}


x <- matrix(1:100, 10)
symtests(x)

storage.mode(x) <- "double"
symtests(x)



### Comparison to isSymmetric
tester <- function(x) stopifnot(identical(isSym(x), isSymmetric(x)))
tester(x)
tester(as.matrix(as.symmetric(x)))

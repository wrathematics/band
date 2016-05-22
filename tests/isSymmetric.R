library(band)

symtests <- function(x)
{
  test <- as.banded(as.matrix(as.symmetric(x)), 2)
  stopifnot(isSymmetric(test))

  test <- as.banded(x, 2, 2)
  stopifnot(!isSymmetric(test))
}


x <- matrix(1:100, 10)
symtests(x)

storage.mode(x) <- "double"
symtests(x)

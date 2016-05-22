library(band)

x <- matrix(1:100, 10)
test <- as.banded(as.matrix(as.symmetric(x)), 2)
stopifnot(isSymmetric(test))

test <- as.banded(x, 2, 2)
stopifnot(!isSymmetric(test))

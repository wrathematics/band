library(band)

x <- matrix(1:100, 10)

test <- as.matrix(as.symmetric(x, "u"))
stopifnot(isSymmetric(test))

test <- as.matrix(as.symmetric(x, "l"))
stopifnot(isSymmetric(test))

library(band)

x <- matrix(1:100, 10)

### Degenerate cases
test <- tryCatch(t(as.banded(x, 0, 0)), error=identity)
stopifnot(inherits(test, "simpleError"))

test <- tryCatch(t(as.symmetric(x)), error=identity)
stopifnot(inherits(test, "simpleError"))



### real work
band <- as.banded(x, 2, 1)
test <- as.matrix(t(band))
truth <- t(as.matrix(band))
stopifnot(all.equal(test, truth))

band <- as.banded(x, 1, 2)
test <- as.matrix(t(band))
truth <- t(as.matrix(band))
stopifnot(all.equal(test, truth))

band <- as.banded(x, 2, 2)
test <- as.matrix(t(band))
truth <- t(as.matrix(band))
stopifnot(all.equal(test, truth))

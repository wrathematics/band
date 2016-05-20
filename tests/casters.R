library(band)

### Diagonal band

diagtest <- function(x)
{
  truth <- diag(x)
  band <- as.banded(x, 0, 0)
  test <- band@Data
  stopifnot(all.equal(truth, test))

  truth <- diag(diag(x))
  # R makes literally the worst decisions about type, it's simply astounding
  if (is.logical(x)) 
    storage.mode(truth) <- "logical"
  test <- as.matrix(band)
  stopifnot(all.equal(truth, test))
}

# int
x <- matrix(1:100, 10, 10)
diagtest(x)

# double
storage.mode(x) <- "double"
diagtest(x)

# logical
storage.mode(x) <- "logical"



### General band
# Example from here: http://www.netlib.org/lapack/lug/node124.html
x <- matrix(1:25, 5, 5)
test <- as.banded(x, 2, 1)@Data
truth <- c(NA, 1, 2, 3, 6, 7, 8, 9, 12, 13, 14, 15, 18, 19, 20, NA, 24, 25, NA, NA)
stopifnot(all.equal(test, truth))

storage.mode(x) <- "integer"
test <- as.banded(x, 2, 1)@Data
truth <- c(NA, 1, 2, 3, 6, 7, 8, 9, 12, 13, 14, 15, 18, 19, 20, NA, 24, 25, NA, NA)
stopifnot(all.equal(test, truth))


# TODO as.matrix() for general band

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
# TODO

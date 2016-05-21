library(band)


dumb_symmetrizer <- function(x, triangle)
{
  ret <- x
  if (triangle == "u")
    ret[lower.tri(x)] <- t(x)[lower.tri(x)]
  else if (triangle == "l")
    ret[upper.tri(x)] <- t(x)[upper.tri(x)]
  
  ret
}

symtest <- function(x, triangle)
{
  # as.symmetric
  sym <- as.symmetric(x, triangle)
  test <- sym@Data
  trifun <- ifelse(triangle=="u", upper.tri, lower.tri)
  truth <- x[trifun(x, diag=TRUE)]
  stopifnot(all.equal(test, truth))
  
  # as.matrix
  test <- as.matrix(sym)
  truth <- dumb_symmetrizer(x, triangle)
  stopifnot(all.equal(test, truth))
}


# give ints
suite <- function(x)
{
  symtest(x, "u")
  symtest(x, "l")

  storage.mode(x) <- "double"
  symtest(x, "u")
  symtest(x, "l")
}


x <- matrix(1:100, 10)
suite(x)

x <- matrix(1:25, 5)
suite(x)

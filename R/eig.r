#' eig
#' 
#' Eigenvalue decomposition.
#' 
#' @details
#' Runtime performance for a SymMat (symmetric packed matrix) will be
#' MUCH slower than when using full (non-packed) storage.
#' 
#' @param x
#' The input matrix.
#' @param only.values
#' Should only the eigenvalues be returned, or should the eigenvectors
#' also be returned?
#' @param descending
#' Should the values/vectors be returned in descending order,
#' or ascending order?  By default, LAPACK returns them in ascending
#' order, so putting them in descending order (R's default in \code{eigen()})
#' has a performance cost.
#' 
#' @return
#' A matrix-like object of the same type as the input.
#' 
#' @export
eig <- function(x, only.values=FALSE, descending=TRUE)
{
  UseMethod("eig")
}

#' @export
eig.default <- function(x, only.values=FALSE, descending=TRUE)
{
  stop("Unsupported class 'x'")
}

#' @export
eig.SymMat <- function(x, only.values=FALSE, descending=TRUE)
{
  n <- getdim(x)[1L]
  triangle <- x@triangle
  
  data <- getData(x)
  storage.mode(data) <- "double"
  
  .Call(R_eig_sympacked, data, n, triangle, only.values, descending)
}


#' @export
eig.matrix <- function(x, only.values=FALSE, descending=TRUE)
{
  if (!is.double(x))
    storage.mode(x) <- "double"
  
  .Call(R_eig_full, x, only.values, descending)
}

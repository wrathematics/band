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
  
  .Call("R_eig_sympacked", data, n, triangle, only.values, descending)
}
